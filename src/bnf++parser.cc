#include <string.h>
#include <bnf++parser.h>


// constants

template<class STRING, class UV>
const typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::npos(STRING::npos);


// constructor / destructor

template<class STRING, class UV>
bnf_plusplus_parser<STRING,UV>::bnf_plusplus_parser(const STRING &_source, const size_type &_beg, const size_type &_end)
    : source(_source), beg(_beg), end(_end)
{
}

template<class STRING, class UV>
bnf_plusplus_parser<STRING,UV>::~bnf_plusplus_parser()
{
}


// service functions

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::eoi(size_type base, UV uv)
{
    return base<end?npos:0;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::compare_symbol(size_type base, unsigned char symbol, UV uv)
{
    if(base>=end)
        return npos;
    if(symbol)
        return source[base]==symbol?1:npos;
    return 1;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::compare_range(size_type base, unsigned char since, unsigned char till, UV uv)
{
    if(base>=end)
        return npos;
    if(source[base]>=since && source[base]<=till)
        return 1;
    return npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::compare_string(size_type base, const char *str, UV uv)
{
    int str_len=strlen(str);
    int cmp=source.compare(base,str_len,str);
    return cmp?npos:str_len;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::find_string(size_type base, const char *str, UV uv)
{
    size_type pos=source.find(str,base);
    return pos==npos?pos:pos-base;
}


// parser functions

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::grammar(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=grammar_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::any_string(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=any_string_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=eos(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::eos(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'\n',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=eoi(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::ws(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=ws_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::wsnl(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::comment(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_string(offset,"//",uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=comment_aux_1(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=compare_string(offset,"/*",uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match) {
            test=find_string(offset,"*/",uv);
            if(test!=npos)
                offset+=test;
            else
                offset=end;
        }
        if(match) {
            test=compare_string(offset,"*/",uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_string(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_string_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_expression(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_string_aux_1(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,';',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_string_aux_2(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_string_aux_3(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::not_bnf_string(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=not_bnf_string_aux_1(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_expression(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_assignment(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_class_definition(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_assignment(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_name(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_assignment_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_string(offset,"::=",uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_assignment_aux_1(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_body(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_class_definition(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_string(offset,"classname",uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_class_name(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_class_name(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_class_name_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_name(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_name_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_body(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_description(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_description(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_sequence(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_description_aux_2(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_sequence(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_item(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_sequence_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_item(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_grouping(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_optim_option_repetition(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_option(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_repetition(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_not_eoi(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_not_istring(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_negation(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_entry(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_symbol(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_istring(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_range(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_dot(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_grouping(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'(',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_grouping_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_grouping_body(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_grouping_aux_1(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,')',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_grouping_body(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_description(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_optim_option_repetition(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'[',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_optim_option_repetition_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,'{',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_optim_option_repetition_aux_1(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_optim_option_repetition_body(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_optim_option_repetition_aux_2(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,'}',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_optim_option_repetition_aux_3(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,']',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_optim_option_repetition_body(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_description(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_option(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'[',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_option_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_option_body(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_option_aux_1(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,']',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_option_body(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_description(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_repetition(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'{',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_repetition_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_repetition_body(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_repetition_aux_1(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,'}',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_repetition_body(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_description(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_not_eoi(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'!',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_not_eoi_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_string(offset,"eoi",uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_not_istring(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'!',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_not_istring_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_not_istring_string(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_not_istring_string(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'"',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_not_istring_string_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,'"',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_negation(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'!',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_negation_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_negation_item(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_negation_item(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_item(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_entry(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_entry_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_symbol(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'\'',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_symbol_symbol(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,'\'',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_symbol_symbol(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_escaped_symbol(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_symbol_symbol_aux_0(offset,uv);
            if(test!=npos)
                match=false;
            else
                offset+=1;
        }
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_istring(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'"',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_istring_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,'"',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_istring_symbol(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_escaped_symbol(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_istring_symbol_aux_0(offset,uv);
            if(test!=npos)
                match=false;
            else
                offset+=1;
        }
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_range(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'<',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_range_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,'>',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_range_item(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_range_symbol_range(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_range_symbol(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_range_symbol_range(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_range_symbol_range_since(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,'-',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_range_symbol_range_till(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_range_symbol_range_since(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_range_symbol_range_since_aux_0(offset,uv);
        if(test!=npos)
            match=false;
        else
            offset+=1;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_range_symbol_range_till(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_range_symbol_range_till_aux_0(offset,uv);
        if(test!=npos)
            match=false;
        else
            offset+=1;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_range_symbol(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_escaped_symbol(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_range_symbol_aux_0(offset,uv);
            if(test!=npos)
                match=false;
            else
                offset+=1;
        }
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_dot(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'.',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_escaped_symbol(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_escaped_code(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_escaped_char(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_escaped_code(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'\\',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_escaped_code_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_escaped_code_oct(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_escaped_code_oct_char(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_escaped_code_oct_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_escaped_code_oct_aux_1(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_escaped_code_oct_char(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=npos;
        if(test==npos)
            test=compare_range(offset,'0','7',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_escaped_code_hex(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'x',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_escaped_code_hex_char(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=bnf_escaped_code_hex_aux_0(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_escaped_code_hex_char(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=npos;
        if(test==npos)
            test=compare_range(offset,'0','9',uv);
        if(test==npos)
            test=compare_range(offset,'A','F',uv);
        if(test==npos)
            test=compare_range(offset,'a','f',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_escaped_char(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'\\',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(match) {
        test=compare_symbol(offset,0,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}


// parser auxiliary functions

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::grammar_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    while(1) {
        if(match) {
            test=any_string(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match) {
            test=eoi(offset,uv);
            if(test!=npos)
                match=false;
        }
        if(match)
            continue;
        break;
    }
    match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::any_string_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_string(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=not_bnf_string(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::ws_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    int cycle=0;
    while(++cycle) {
        if(match) {
            test=npos;
            if(test==npos)
                test=compare_symbol(offset,' ',uv);
            if(test==npos)
                test=compare_symbol(offset,'\t',uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match)
            continue;
        break;
    }
    if(cycle!=1)
        match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::wsnl_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    int cycle=0;
    while(++cycle) {
        if(match) {
            test=npos;
            if(test==npos)
                test=compare_symbol(offset,' ',uv);
            if(test==npos)
                test=compare_symbol(offset,'\t',uv);
            if(test==npos)
                test=compare_symbol(offset,'\n',uv);
            if(test==npos)
                test=compare_symbol(offset,'\r',uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match)
            continue;
        break;
    }
    if(cycle!=1)
        match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::comment_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=eos(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::comment_aux_1(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    while(1) {
        if(match) {
            test=comment_aux_0(offset,uv);
            if(test!=npos)
                match=false;
            else
                offset+=1;
        }
        if(match)
            continue;
        break;
    }
    match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_string_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=ws(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_string_aux_1(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_string_aux_2(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=ws(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_string_aux_3(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=comment(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::not_bnf_string_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=eos(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::not_bnf_string_aux_1(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    while(1) {
        if(match) {
            test=not_bnf_string_aux_0(offset,uv);
            if(test!=npos)
                match=false;
            else
                offset+=1;
        }
        if(match)
            continue;
        break;
    }
    match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_assignment_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_assignment_aux_1(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_class_name_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    int cycle=0;
    while(++cycle) {
        if(match) {
            test=npos;
            if(test==npos)
                test=compare_range(offset,'A','Z',uv);
            if(test==npos)
                test=compare_range(offset,'a','z',uv);
            if(test==npos)
                test=compare_range(offset,'0','9',uv);
            if(test==npos)
                test=compare_symbol(offset,'_',uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match)
            continue;
        break;
    }
    if(cycle!=1)
        match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_name_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    int cycle=0;
    while(++cycle) {
        if(match) {
            test=npos;
            if(test==npos)
                test=compare_range(offset,'A','Z',uv);
            if(test==npos)
                test=compare_range(offset,'a','z',uv);
            if(test==npos)
                test=compare_range(offset,'0','9',uv);
            if(test==npos)
                test=compare_symbol(offset,'_',uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match)
            continue;
        break;
    }
    if(cycle!=1)
        match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_description_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_description_aux_1(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_description_aux_2(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    while(1) {
        if(match) {
            test=bnf_description_aux_0(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match) {
            test=compare_symbol(offset,'|',uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match) {
            test=bnf_description_aux_1(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match) {
            test=bnf_sequence(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match)
            continue;
        break;
    }
    match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_sequence_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    while(1) {
        if(match) {
            test=wsnl(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match) {
            test=bnf_item(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match)
            continue;
        break;
    }
    match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_grouping_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_grouping_aux_1(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_optim_option_repetition_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_optim_option_repetition_aux_1(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_optim_option_repetition_aux_2(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_optim_option_repetition_aux_3(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_option_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_option_aux_1(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_repetition_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_repetition_aux_1(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_not_eoi_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_not_istring_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_not_istring_string_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    int cycle=0;
    while(++cycle) {
        if(match) {
            test=bnf_istring_symbol(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match)
            continue;
        break;
    }
    if(cycle!=1)
        match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_negation_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=wsnl(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_entry_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    int cycle=0;
    while(++cycle) {
        if(match) {
            test=npos;
            if(test==npos)
                test=compare_range(offset,'A','Z',uv);
            if(test==npos)
                test=compare_range(offset,'a','z',uv);
            if(test==npos)
                test=compare_range(offset,'0','9',uv);
            if(test==npos)
                test=compare_symbol(offset,'_',uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match)
            continue;
        break;
    }
    if(cycle!=1)
        match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_symbol_symbol_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'\'',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_istring_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    int cycle=0;
    while(++cycle) {
        if(match) {
            test=bnf_istring_symbol(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match)
            continue;
        break;
    }
    if(cycle!=1)
        match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_istring_symbol_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'"',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_range_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    int cycle=0;
    while(++cycle) {
        if(match) {
            test=bnf_range_item(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
        if(match)
            continue;
        break;
    }
    if(cycle!=1)
        match=true;

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_range_symbol_range_since_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'>',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_range_symbol_range_till_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'>',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_range_symbol_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=compare_symbol(offset,'>',uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_escaped_code_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_escaped_code_oct(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
        if(match) {
            test=bnf_escaped_code_hex(offset,uv);
            if(test!=npos)
                offset+=test;
            else
                match=false;
        }
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_escaped_code_oct_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_escaped_code_oct_char(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_escaped_code_oct_aux_1(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_escaped_code_oct_char(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

template<class STRING, class UV>
typename bnf_plusplus_parser<STRING,UV>::size_type bnf_plusplus_parser<STRING,UV>::bnf_escaped_code_hex_aux_0(size_type base, UV uv)
{
    size_type offset=base;
    size_type test;
    bool match=true;

    if(match) {
        test=bnf_escaped_code_hex_char(offset,uv);
        if(test!=npos)
            offset+=test;
        else
            match=false;
    }
    if(!match) {
        offset=base;
        match=true;
    }

    return match?offset-base:npos;
}

