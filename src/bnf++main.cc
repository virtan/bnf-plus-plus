#include <config.h>
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

string output_filename;
string user_value_type;
bool debug=false;
bool user_value=false;
bool with_template=false;

string version()
{
    return 
#include <bnf++version.h>
    ;
}

string help()
{
    return
#include <bnf++help.h>
    ;
}

bool args(int argc, char **argv, string &filename)
{
    for(int i=1;i<argc;i++) {
        if(argv[i][0]!='-' && filename.empty()) {
            filename=argv[i];
            continue;
        } else if(argv[i][0]!='-' || argv[i][1]!='-') {
            continue;
        }
        if(!strcmp(argv[i]+2,"version")) {
            cout << version();
            return false;
        }
        if(!strcmp(argv[i]+2,"help")) {
            cout << version() << endl;
            cout << help();
            return false;
        }
        if(!strncmp(argv[i]+2,"output=",7) && output_filename.empty()) {
            output_filename=argv[i]+9;
            continue;
        }
        if(!strncmp(argv[i]+2,"user-value",10)) {
            user_value=true;
            if(argv[i][2+10]=='=' && user_value_type.empty())
                user_value_type=argv[i]+2+10+1;
            continue;
        }
        if(!strcmp(argv[i]+2,"with-template")) {
            with_template=true;
            continue;
        }
        if(!strcmp(argv[i]+2,"debug")) {
            debug=true;
            continue;
        }
    }

    if(!with_template && user_value && user_value_type.empty())
        user_value_type="int"; // default type for user value

    return true;
}

#include <bnf++gen.h>

#include <fstream>

int main(int argc, char **argv)
{
    string filename;
    if(!args(argc,argv,filename)) {
        return 0;
    }
    if(filename.empty()) {
        cerr << "No source specified" << endl;
        return 1;
    }

    string source;
    ifstream input;
    input.exceptions(ifstream::badbit|ifstream::failbit);
    try {
        input.open(filename.c_str(),ifstream::in|ifstream::binary);
        input.seekg(0,ifstream::end);
        streampos length=input.tellg();
        input.seekg(0,ifstream::beg);
        char *buffer=new char[length];
        input.read(buffer,length);
        source=buffer;
        input.close();
    } catch(ifstream::failure e) {
        cerr << "Error opening/reading from " << filename << endl;
        return 1;
    }

    string templ_file=TEMPLATES_DIR;
    templ_file+="/";
    templ_file+=(with_template?"template":"base");
    templ_file+=(user_value?"_uv":"");
    templ_file+=".tpl";
    
    string templ;
    try {
        input.open(templ_file.c_str(),ifstream::in|ifstream::binary);
        input.seekg(0,ifstream::end);
        streampos length=input.tellg();
        input.seekg(0,ifstream::beg);
        char *buffer=new char[length];
        input.read(buffer,length);
        templ=buffer;
        input.close();
    } catch(ifstream::failure e) {
        cerr << "Error opening/reading template from " << templ_file << endl;
        return 1;
    }

    for(string::size_type o=0;(o=templ.find("\r",o))!=string::npos;)
        templ.erase(o,1);

    string cn,hdr,src;

    bnf_plusplus_gen bnfpp(source,0,source.size(),templ,cn,hdr,src);
    bnfpp.options((user_value?bnf_plusplus_gen::opt_user_value:0)|
                  (debug?bnf_plusplus_gen::opt_debug:0));
    bnfpp.options("user_value_type",user_value_type);

    string::size_type res=bnfpp.generate();
    if(res==static_cast<string::size_type>(-1)) {
        cerr << "Can't parse " << filename << ": not a bnf++ syntax" << endl;
        return 1;
    } else if(res!=source.size()) {
        cerr << "Only " << res << " bytes of " << filename << " parsed: rest have not a bnf++ syntax" << endl;
    }

    bool all_is_good=true;
    ofstream output;
    output.exceptions(ofstream::badbit|ofstream::failbit);
    try {
        filename=(output_filename.empty()?cn:output_filename)+".h";
        output.open(filename.c_str(),ofstream::out|ofstream::trunc|ofstream::binary);
        output << hdr;
        output.close();
    } catch(ofstream::failure e) {
        cerr << "Error opening/writing to " << filename << endl;
        all_is_good=false;
    }
    try {
        filename=(output_filename.empty()?cn:output_filename)+".cc";
        output.open(filename.c_str(),ofstream::out|ofstream::trunc|ofstream::binary);
        output << src;
        output.close();
    } catch(ofstream::failure e) {
        cerr << "Error opening/writing to " << filename << endl;
        all_is_good=false;
    }

    return !all_is_good;
}
