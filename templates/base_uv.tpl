#ifndef %C_H
#define %C_H

%b
class %c
{

    // definition of size_type
    public:
        typedef string::size_type size_type;

    // variables
    public:
        const string &source;
        const size_type beg;
        const size_type end;
        static const size_type npos;

    // constructor / destructor
    public:
        %c(const string &_source, const size_type &_beg, const size_type &_end);
        virtual ~%c();

    // service functions
    public:
        virtual size_type eoi(size_type base, %u uv);
        virtual size_type compare_symbol(size_type base, unsigned char symbol, %u uv);
        virtual size_type compare_range(size_type base, unsigned char since, unsigned char till, %u uv);
        virtual size_type compare_string(size_type base, const char *str, %u uv);
        virtual size_type find_string(size_type base, const char *str, %u uv);

    // parser functions
    public:
%{
        virtual size_type %f(size_type base, %u uv);
%}

    // parser auxiliary functions
    private:
%(
        inline size_type %f(size_type base, %u uv);
%)
%/

    // not defined functions
    public:
%\
%[
        virtual size_type %f(size_type base, %u uv)=0;
%]

};
 
%a
#endif
-----header-body-delimiter-----
#include <%c.h>
%d#include <iostream>


// constants

const %c::size_type %c::npos(string::npos);


// constructor / destructor

%c::%c(const string &_source, const size_type &_beg, const size_type &_end)
    : source(_source), beg(_beg), end(_end)
{
}

%c::~%c()
{
}


// service functions

%c::size_type %c::eoi(size_type base, %u uv)
{
%d    std::cerr << "eoi(" << base << ") = " << (base<end?-1:0) << std::endl;
    return base<end?npos:0;
}

%c::size_type %c::compare_symbol(size_type base, unsigned char symbol, %u uv)
{
    size_type res;
    if(base>=end)
        res=npos;
    else if(symbol)
        res=source[base]==symbol?1:npos;
    else
        res=1;
%d    std::cerr << "compare_symbol(" << base << ",'" << symbol << "') = " << static_cast<int>(res) << std::endl;
    return res;
}

%c::size_type %c::compare_range(size_type base, unsigned char since, unsigned char till, %u uv)
{
    size_type res;
    if(base>=end)
        res=npos;
    else if(source[base]>=since && source[base]<=till)
        res=1;
    else
        res=npos;
%d    std::cerr << "compare_range(" << base << ",'" << since << "','" << till << "') = " << static_cast<int>(res) << std::endl;
    return res;
}

%c::size_type %c::compare_string(size_type base, const char *str, %u uv)
{
    int str_len=strlen(str);
    int cmp=source.compare(base,str_len,str);
%d    std::cerr << "compare_string(" << base << ",\"" << str << "\") = " << (cmp?-1:str_len) << std::endl;
    return cmp?npos:str_len;
}

%c::size_type %c::find_string(size_type base, const char *str, %u uv)
{
    size_type pos=source.find(str,base);
%d    std::cerr << "find_string(" << base << ",\"" << str << "\") = " << (pos==npos?-1:pos-base) << std::endl;
    return pos==npos?pos:pos-base;
}


// parser functions

%{
%c::size_type %c::%f(size_type base, %u uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;
%d    std::cerr << "%f(" << base << ") ..." << std::endl;

%F
%d    std::cerr << "%f(" << base << ") = " << static_cast<int>(match?offset-base:-1) << std::endl;
    return match?offset-base:npos;
}

%}


// parser auxiliary functions

%(
%c::size_type %c::%f(size_type base, %u uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

%F
    return match?offset-base:npos;
}

%)

