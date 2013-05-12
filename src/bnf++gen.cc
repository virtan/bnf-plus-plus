#include <bnf++gen.h>
#include <sstream>
#include <functional>
#include <algorithm>
#include <ctype.h>

const unsigned int bnf_plusplus_gen::opt_not_specified(0x80000000);
const unsigned int bnf_plusplus_gen::opt_user_value(0x00000001);
const unsigned int bnf_plusplus_gen::opt_debug(0x00000002);
const string bnf_plusplus_gen::delim_str("-----header-body-delimiter-----\n");

bnf_plusplus_gen::bnf_plusplus_gen(const string &source, int beg, int end, const string &templ_, string &class_name_, string &header_, string &source_)
    : bnf_plusplus_parser<string,string*>(source,beg,end), opts(0), before_bnf_plusplus(true), first_name(true),
      templ(templ_), class_name(class_name_), result_header(header_), result_source(source_)
{ }

string::size_type bnf_plusplus_gen::generate()
{
    return grammar(0,NULL);
}

unsigned int bnf_plusplus_gen::options(unsigned int _opts)
{
    if(!(_opts&opt_not_specified))
        opts=_opts;
    return opts=_opts;
}

const string &bnf_plusplus_gen::options(const string &option, const string &value)
{
    string &opt=options_map[option];
    if(value!="<undefined>")
        opt=value;
    return opt;
}

void bnf_plusplus_gen::add_string(const string &toadd)
{
    if(before_bnf_plusplus) {
        if(!before_string.empty())
            before_string+="\n";
        before_string+=toadd;
    } else {
        if(!after_string.empty())
            after_string+="\n";
        after_string+=toadd;
    }
}

string bnf_plusplus_gen::as_string(int number)
{
    ostringstream os;
    os<<number;
    return os.str();
}

string bnf_plusplus_gen::indent(string str, int tabs)
{
    if(str.empty())
        return str;
    string indent_str;
    for(int i=tabs;i>0;i--)
        indent_str+="    ";
    string::size_type pos=npos;
    do {
        if((++pos)<str.size())
            str.insert(pos,indent_str);
    } while((pos=str.find('\n',pos))!=npos);
    return str;
}

string bnf_plusplus_gen::to_upper(const string &str)
{
    if(str.empty())
        return "";
    string new_str(str.size(),' ');
    transform(str.begin(),str.end(),new_str.begin(),ptr_fun<int,int>(toupper));
    return new_str;
}

string bnf_plusplus_gen::make_aux_name(int addon)
{
    string new_name;
    new_name=pos_bnf_name+"_aux_"+as_string(pos_bnf_methods_aux.size()+addon);
    return new_name;
}

string::size_type bnf_plusplus_gen::grammar(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::grammar(base,ptr);

    if(res!=npos) {

        string::size_type delim=templ.find(delim_str);
        result_header=templ.substr(0,delim!=npos?delim:templ.size());
        result_source=templ.substr(delim!=npos?delim+delim_str.size():0,templ.size());
        
        if(class_name.empty())
            class_name="unnamed_parser";

        subst_map_t subst_map;
        for(methods_t::iterator i=methods.begin();i!=methods.end();i++) {
            subst_map.clear();
            subst_map["%f"]=i->first;
            subst_cycle(result_header,"%{\n","%}\n",subst_map);
            subst_map["%F"]=indent(i->second,1);
            subst_cycle(result_source,"%{\n","%}\n",subst_map);
        }
        subst(result_header,"%{\n","%}\n","");
        subst(result_source,"%{\n","%}\n","");
        for(methods_t::iterator i=methods_aux.begin();i!=methods_aux.end();i++) {
            subst_map.clear();
            subst_map["%f"]=i->first;
            subst_cycle(result_header,"%(\n","%)\n",subst_map);
            subst_map["%F"]=indent(i->second,1);
            subst_cycle(result_source,"%(\n","%)\n",subst_map);
        }
        subst(result_header,"%(\n","%)\n","");
        subst(result_source,"%(\n","%)\n","");

        bnf_entries.erase("eoi");
        for(entries_t::iterator i=bnf_entries.begin();i!=bnf_entries.end();i++)
            if(i->second.first && i->second.second)
                bnf_entries.erase(i);
            else if(i->second.first) {
                cerr << "Warning: method " << i->first << " defined, but not used" << endl;
                bnf_entries.erase(i);
            }

        if(!bnf_entries.empty())
            for(entries_t::iterator i=bnf_entries.begin();i!=bnf_entries.end();i++) {
                subst_map.clear();
                subst_map["%f"]=i->first;
                subst_cycle(result_header,"%[\n","%]\n",subst_map);
            }
        else
            subst(result_header,"%/\n","%\\\n","");
        subst(result_header,"%[\n","%]\n","");

        subst(result_header,"%c",class_name);
        subst(result_source,"%c",class_name);
        subst(result_header,"%C",to_upper(class_name));
        subst(result_header,"%b",before_string);
        subst(result_header,"%a",after_string);
        subst(result_header,"%u",options_map["user_value_type"]);
        subst(result_source,"%u",options_map["user_value_type"]);

        if(opts&opt_debug)
            subst(result_source,"%d","");
        else
            subst(result_source,"%d","\n","");

    }

    return res;
}

void bnf_plusplus_gen::submit_bnf_string()
{
    if(!pos_class_name.empty()) {
        if(class_name.empty())
            class_name=pos_class_name;
    } else {
        if(!pos_bnf_name.empty() && !pos_bnf_body.empty())
            methods.push_back(method_t(pos_bnf_name,pos_bnf_body));
        if(!pos_bnf_methods_aux.empty()) {
            for(methods_t::iterator i=pos_bnf_methods_aux.begin();i!=pos_bnf_methods_aux.end();i++)
                methods_aux.push_back(*i);
        }
        before_bnf_plusplus=false;
        if(!pos_bnf_entries.empty()) {
            for(entries_t::iterator i=pos_bnf_entries.begin();i!=pos_bnf_entries.end();i++) {
                ent_cond_t &cond=bnf_entries[i->first];
                cond.first|=i->second.first;
                cond.second|=i->second.second;
                if(first_name && i->second.first) {
                    cond.second=true;
                    first_name=false;
                }
            }
        }
    }
    // cleanup
    pos_class_name.clear();
    pos_bnf_name.clear();
    pos_bnf_body.clear();
    pos_bnf_methods_aux.clear();
    after_string.clear();
    pos_bnf_entries.clear();
}

void bnf_plusplus_gen::subst(string &target, const string &pat, const string &subs)
{
    string::size_type o=0;
    while((o=target.find(pat,o))!=npos) {
        target.replace(o,pat.size(),subs);
        o+=subs.size();
    }
}

void bnf_plusplus_gen::subst(string &target, const string &pat_from, const string &pat_to, const string &subs)
{
    string::size_type o=0;
    while((o=target.find(pat_from,o))!=npos) {
        string::size_type o2=target.find(pat_to,o+pat_from.size());
        if(o2==npos) {
            o++;
            continue;
        }
        target.replace(o,o2+pat_to.size()-o,subs);
        o+=subs.size();
    }
}

void bnf_plusplus_gen::subst_cycle(string &target, const string &pat_from, const string &pat_to, subst_map_t &subst_map)
{
    string::size_type o=0;
    while((o=target.find(pat_from,o))!=npos) {
        string::size_type o2=target.find(pat_to,o+pat_from.size());
        if(o2==npos) {
            o++;
            continue;
        }
        string itr=target.substr(o+pat_from.size(),o2-o-pat_from.size());
        for(subst_map_t::iterator i=subst_map.begin();i!=subst_map.end();i++)
            subst(itr,i->first,i->second);
        target.insert(o,itr);
        o+=itr.size()+o2+pat_to.size()-o;
    }
}

string::size_type bnf_plusplus_gen::not_bnf_string(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::not_bnf_string(base,ptr);
    if(res!=npos)
        add_string(source.substr(base,res));
    // cleanup
    pos_class_name.clear();
    pos_bnf_name.clear();
    pos_bnf_body.clear();
    pos_bnf_methods_aux.clear();
    pos_bnf_entries.clear();
    return res;
}

string::size_type bnf_plusplus_gen::bnf_string(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_string(base,ptr);
    if(res!=npos)
        submit_bnf_string();
    return res;
}

string::size_type bnf_plusplus_gen::bnf_class_name(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_class_name(base,ptr);
    if(res!=npos)
        pos_class_name=source.substr(base,res);
    return res;
}

string::size_type bnf_plusplus_gen::bnf_name(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_name(base,ptr);
    if(res!=npos) {
        pos_bnf_name=source.substr(base,res);
        pos_bnf_entries[pos_bnf_name].first=true;
    }
    return res;
}

string::size_type bnf_plusplus_gen::bnf_body(string::size_type base, string *ptr)
{
    return bnf_plusplus_parser<string,string*>::bnf_body(base,&pos_bnf_body);
}

string::size_type bnf_plusplus_gen::bnf_description(string::size_type base, string *ptr)
{
    string temp;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_description(base,&temp);
    if(res!=npos)
        if(ptr)
            (*ptr)+=temp;
    return res;
}

string::size_type bnf_plusplus_gen::bnf_sequence(string::size_type base, string *ptr)
{
    string temp;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_sequence(base,&temp);
    if(res!=npos)
        if(ptr) {
            if(ptr->empty())
                (*ptr)=temp;
            else
                (*ptr)+="if(!match) {\n"
                        "    offset=base;\n"
                        "    match=true;\n"
                        +indent(temp,1)+
                        "}\n";
        }
    return res;
}

string::size_type bnf_plusplus_gen::bnf_item(string::size_type base, string *ptr)
{
    string temp;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_item(base,&temp);
    if(res!=npos)
        if(ptr)
            (*ptr)+=temp;
    return res;
}

string::size_type bnf_plusplus_gen::bnf_grouping_body(string::size_type base, string *ptr)
{
    string aux_body;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_grouping_body(base,&aux_body);
    if(res!=npos) {
        string aux_name=make_aux_name();
        if(ptr)
            (*ptr)+="if(match) {\n"
                    "    test="+aux_name+"(offset"+(opts&opt_user_value?",uv":"")+");\n"
                    "    if(test!=npos)\n"
                    "        offset+=test;\n"
                    "    else\n"
                    "        match=false;\n"
                    "}\n";
        pos_bnf_methods_aux.push_back(method_t(aux_name,aux_body));
    }
    return res;
}

string::size_type bnf_plusplus_gen::bnf_optim_option_repetition_body(string::size_type base, string *ptr)
{
    string temp;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_optim_option_repetition_body(base,&temp);
    if(res!=npos) {
        string aux_name=make_aux_name();
        if(ptr)
            (*ptr)+="if(match) {\n"
                    "    test="+aux_name+"(offset"+(opts&opt_user_value?",uv":"")+");\n"
                    "    if(test!=npos)\n"
                    "        offset+=test;\n"
                    "    else\n"
                    "        match=false;\n"
                    "}\n";
        string aux_body;
        string aux_name_2=make_aux_name(1);
        aux_body="for(;;) {\n"
                 "    test="+aux_name_2+"(offset"+(opts&opt_user_value?",uv":"")+");\n"
                 "    if(test!=npos) {\n"
                 "        offset+=test;\n"
                 "        continue;\n"
                 "    }\n"
                 "    break;\n"
                 "}\n";
        pos_bnf_methods_aux.push_back(method_t(aux_name,aux_body));
        pos_bnf_methods_aux.push_back(method_t(aux_name_2,temp));
    }
    return res;
}

string::size_type bnf_plusplus_gen::bnf_option_body(string::size_type base, string *ptr)
{
    string temp;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_option_body(base,&temp);
    if(res!=npos) {
        string aux_name=make_aux_name();
        if(ptr)
            (*ptr)+="if(match) {\n"
                    "    test="+aux_name+"(offset"+(opts&opt_user_value?",uv":"")+");\n"
                    "    if(test!=npos)\n"
                    "        offset+=test;\n"
                    "    else\n"
                    "        match=false;\n"
                    "}\n";
        string aux_body;
        aux_body=temp+
                 "if(!match) {\n"
                 "    offset=base;\n"
                 "    match=true;\n"
                 "}\n";
        pos_bnf_methods_aux.push_back(method_t(aux_name,aux_body));
    }
    return res;
}

string::size_type bnf_plusplus_gen::bnf_repetition_body(string::size_type base, string *ptr)
{
    string temp;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_repetition_body(base,&temp);
    if(res!=npos) {
        string aux_name=make_aux_name();
        if(ptr)
            (*ptr)+="if(match) {\n"
                    "    test="+aux_name+"(offset"+(opts&opt_user_value?",uv":"")+");\n"
                    "    if(test!=npos)\n"
                    "        offset+=test;\n"
                    "    else\n"
                    "        match=false;\n"
                    "}\n";
        string aux_body;
        string aux_name_2=make_aux_name(1);
        aux_body="int cycle=0;\n"
                 "while(++cycle) {\n"
                 "    test="+aux_name_2+"(offset"+(opts&opt_user_value?",uv":"")+");\n"
                 "    if(test!=npos) {\n"
                 "        offset+=test;\n"
                 "        continue;\n"
                 "    }\n"
                 "    break;\n"
                 "}\n"
                 "if(cycle==1)\n"
                 "    match=false;\n";
        pos_bnf_methods_aux.push_back(method_t(aux_name,aux_body));
        pos_bnf_methods_aux.push_back(method_t(aux_name_2,temp));
    }
    return res;
}

string::size_type bnf_plusplus_gen::bnf_not_eoi(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_not_eoi(base,ptr);
    if(res!=npos)
        if(ptr)
            (*ptr)=(*ptr)+"if(match) {\n"
                    "    test=eoi(offset"+(opts&opt_user_value?",uv":"")+");\n"
                    "    if(test!=npos)\n"
                    "        match=false;\n"
                    "}\n";
    return res;
}

string::size_type bnf_plusplus_gen::bnf_not_istring_string(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_not_istring_string(base,NULL);
    if(res!=npos)
        if(ptr)
            (*ptr)+="if(match) {\n"
                    "    test=find_string(offset,"+source.substr(base,res)+(opts&opt_user_value?",uv":"")+");\n"
                    "    if(test!=npos)\n"
                    "        offset+=test;\n"
                    "    else\n"
                    "        offset=end;\n"
                    "}\n";
    return res;
}

string::size_type bnf_plusplus_gen::bnf_negation(string::size_type base, string *ptr)
{
    string temp;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_negation(base,&temp);
    if(res!=npos)
        if(ptr)
            (*ptr)+=temp;
    return res;
}

string::size_type bnf_plusplus_gen::bnf_negation_item(string::size_type base, string *ptr)
{
    string temp;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_negation_item(base,&temp);
    if(res!=npos) {
        string aux_name=make_aux_name();
        if(ptr)
            (*ptr)+="if(match) {\n"
                    "    test="+aux_name+"(offset"+(opts&opt_user_value?",uv":"")+");\n"
                    "    if(test!=npos)\n"
                    "        match=false;\n"
                    "    else if(eoi(offset"+(opts&opt_user_value?",uv":"")+")==npos)\n"
                    "        offset+=1;\n"
                    "    else\n"
                    "        match=false;\n"
                    "}\n";
        pos_bnf_methods_aux.push_back(method_t(aux_name,temp));
    }
    return res;
}

string::size_type bnf_plusplus_gen::bnf_entry(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_entry(base,ptr);
    if(res!=npos) {
        string entry_name=source.substr(base,res);
        pos_bnf_entries[entry_name].second=true;
        if(ptr) {
            (*ptr)+="if(match) {\n"
                    "    test="+entry_name+"(offset"+(opts&opt_user_value?",uv":"")+");\n"
                    "    if(test!=npos)\n"
                    "        offset+=test;\n"
                    "    else\n"
                    "        match=false;\n"
                    "}\n";
        }
    }
    return res;
}

string::size_type bnf_plusplus_gen::bnf_symbol(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_symbol(base,NULL);
    if(res!=npos)
        if(ptr)
            (*ptr)+="if(match) {\n"
                    "    test=compare_symbol(offset,"+source.substr(base,res)+(opts&opt_user_value?",uv":"")+");\n"
                    "    if(test!=npos)\n"
                    "        offset+=test;\n"
                    "    else\n"
                    "        match=false;\n"
                    "}\n";
    return res;
}

string::size_type bnf_plusplus_gen::bnf_istring(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_istring(base,NULL);
    if(res!=npos)
        if(ptr)
            (*ptr)+="if(match) {\n"
                    "    test=compare_string(offset,"+source.substr(base,res)+(opts&opt_user_value?",uv":"")+");\n"
                    "    if(test!=npos)\n"
                    "        offset+=test;\n"
                    "    else\n"
                    "        match=false;\n"
                    "}\n";
    return res;
}

string::size_type bnf_plusplus_gen::bnf_range(string::size_type base, string *ptr)
{
    string temp;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_range(base,&temp);
    if(res!=npos)
        if(ptr)
            (*ptr)+="if(match) {\n"
                    "    test=npos;\n"
                    +indent(temp,1)+
                    "    if(test!=npos)\n"
                    "        offset+=test;\n"
                    "    else\n"
                    "        match=false;\n"
                    "}\n";
    return res;
}

string::size_type bnf_plusplus_gen::bnf_range_item(string::size_type base, string *ptr)
{
    string temp;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_range_item(base,&temp);
    if(res!=npos)
        if(ptr)
            (*ptr)+="if(test==npos)\n"
                    "    test="+temp+";\n";
    return res;
}

string::size_type bnf_plusplus_gen::bnf_range_symbol_range(string::size_type base, string *ptr)
{
    string temp;
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_range_symbol_range(base,&temp);
    if(res!=npos)
        if(ptr)
            (*ptr)+="compare_range(offset,"+temp+(opts&opt_user_value?",uv":"")+")";
    return res;
}

string::size_type bnf_plusplus_gen::bnf_range_symbol_range_since(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_range_symbol_range_since(base,NULL);
    if(res!=npos)
        if(ptr)
            (*ptr)+='\''+source.substr(base,res)+"',";
    return res;
}

string::size_type bnf_plusplus_gen::bnf_range_symbol_range_till(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_range_symbol_range_till(base,NULL);
    if(res!=npos)
        if(ptr)
            (*ptr)+='\''+source.substr(base,res)+'\'';
    return res;
}

string::size_type bnf_plusplus_gen::bnf_range_symbol(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_range_symbol(base,NULL);
    if(res!=npos)
        if(ptr)
            (*ptr)+="compare_symbol(offset,'"+source.substr(base,res)+"'"+(opts&opt_user_value?",uv":"")+")";
    return res;
}

string::size_type bnf_plusplus_gen::bnf_dot(string::size_type base, string *ptr)
{
    string::size_type res=bnf_plusplus_parser<string,string*>::bnf_dot(base,ptr);
    if(res!=npos)
        if(ptr)
            (*ptr)=(*ptr)+"if(match) {\n"
                    "    test=compare_symbol(offset,0"+(opts&opt_user_value?",uv":"")+");\n"
                    "    if(test!=npos)\n"
                    "        offset+=test;\n"
                    "    else\n"
                    "        match=false;\n"
                    "}\n";
    return res;
}

