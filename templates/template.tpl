#ifndef %C_H
#define %C_H

%b
template<class STRING>
class %c
{

    // definition of size_type
    public:
        typedef typename STRING::size_type size_type;

    // variables
    public:
        const STRING &source;
        const size_type beg;
        const size_type end;
        static const size_type npos;

    // constructor / destructor
    public:
        %c(const STRING &_source, const size_type &_beg, const size_type &_end);
        virtual ~%c();

    // service functions
    public:
        virtual size_type eoi(size_type base);
        virtual size_type compare_symbol(size_type base, unsigned char symbol);
        virtual size_type compare_range(size_type base, unsigned char since, unsigned char till);
        virtual size_type compare_string(size_type base, const char *str);
        virtual size_type find_string(size_type base, const char *str);

    // parser functions
    public:
%{
        virtual size_type %f(size_type base);
%}

    // parser auxiliary functions
    private:
%(
        inline size_type %f(size_type base);
%)
%/

    // not defined functions
    public:
%\
%[
        virtual size_type %f(size_type base)=0;
%]

};
 
%a
#endif
-----header-body-delimiter-----
#include <string.h>
#include <%c.h>
%d#include <iostream>


// constants

template<class STRING>
const typename %c<STRING>::size_type %c<STRING>::npos(STRING::npos);


// constructor / destructor

template<class STRING>
%c<STRING>::%c(const STRING &_source, const size_type &_beg, const size_type &_end)
    : source(_source), beg(_beg), end(_end)
{
}

template<class STRING>
%c<STRING>::~%c()
{
}


// service functions

template<class STRING>
typename %c<STRING>::size_type %c<STRING>::eoi(size_type base)
{
%d    std::cerr << "eoi(" << base << ") = " << (base<end?-1:0) << std::endl;
    return base<end?npos:0;
}

template<class STRING>
typename %c<STRING>::size_type %c<STRING>::compare_symbol(size_type base, unsigned char symbol)
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

template<class STRING>
typename %c<STRING>::size_type %c<STRING>::compare_range(size_type base, unsigned char since, unsigned char till)
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

template<class STRING>
typename %c<STRING>::size_type %c<STRING>::compare_string(size_type base, const char *str)
{
    int str_len=strlen(str);
    int cmp=source.compare(base,str_len,str);
%d    std::cerr << "compare_string(" << base << ",\"" << str << "\") = " << (cmp?-1:str_len) << std::endl;
    return cmp?npos:str_len;
}

template<class STRING>
typename %c<STRING>::size_type %c<STRING>::find_string(size_type base, const char *str)
{
    size_type pos=source.find(str,base);
%d    std::cerr << "find_string(" << base << ",\"" << str << "\") = " << (pos==npos?-1:pos-base) << std::endl;
    return pos==npos?pos:pos-base;
}


// parser functions

%{
template<class STRING>
typename %c<STRING>::size_type %c<STRING>::%f(size_type base)
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
template<class STRING>
typename %c<STRING>::size_type %c<STRING>::%f(size_type base)
{
    size_type offset=base;
    size_type test;
    bool match=true;

%F
    return match?offset-base:npos;
}

%)

