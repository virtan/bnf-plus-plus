#ifndef BNF_PLUSPLUS_PARSER_H
#define BNF_PLUSPLUS_PARSER_H

// bnf++ syntax

// short description of syntax:
// | - or
// ( ) - grouping
// [ ] - option
// { } - repetition (1 or more)
// . - any symbol
// ' ' - symbol
// " " - string
// ! - not
// < > - ranges (like [] in regexp)
// eoi - end of input checking rule (not moving the offset)

// note 1: spaces are not neccessary, when not ambiguous
// note 2: escaping in symbol and string as in C






template<class STRING, class UV>
class bnf_plusplus_parser
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
        bnf_plusplus_parser(const STRING &_source, const size_type &_beg, const size_type &_end);
        virtual ~bnf_plusplus_parser();

    // service functions
    public:
        virtual size_type eoi(size_type base, UV uv);
        virtual size_type compare_symbol(size_type base, unsigned char symbol, UV uv);
        virtual size_type compare_range(size_type base, unsigned char since, unsigned char till, UV uv);
        virtual size_type compare_string(size_type base, const char *str, UV uv);
        virtual size_type find_string(size_type base, const char *str, UV uv);

    // parser functions
    public:
        virtual size_type grammar(size_type base, UV uv);
        virtual size_type any_string(size_type base, UV uv);
        virtual size_type eos(size_type base, UV uv);
        virtual size_type ws(size_type base, UV uv);
        virtual size_type wsnl(size_type base, UV uv);
        virtual size_type comment(size_type base, UV uv);
        virtual size_type bnf_string(size_type base, UV uv);
        virtual size_type not_bnf_string(size_type base, UV uv);
        virtual size_type bnf_expression(size_type base, UV uv);
        virtual size_type bnf_assignment(size_type base, UV uv);
        virtual size_type bnf_class_definition(size_type base, UV uv);
        virtual size_type bnf_class_name(size_type base, UV uv);
        virtual size_type bnf_name(size_type base, UV uv);
        virtual size_type bnf_body(size_type base, UV uv);
        virtual size_type bnf_description(size_type base, UV uv);
        virtual size_type bnf_sequence(size_type base, UV uv);
        virtual size_type bnf_item(size_type base, UV uv);
        virtual size_type bnf_grouping(size_type base, UV uv);
        virtual size_type bnf_grouping_body(size_type base, UV uv);
        virtual size_type bnf_optim_option_repetition(size_type base, UV uv);
        virtual size_type bnf_optim_option_repetition_body(size_type base, UV uv);
        virtual size_type bnf_option(size_type base, UV uv);
        virtual size_type bnf_option_body(size_type base, UV uv);
        virtual size_type bnf_repetition(size_type base, UV uv);
        virtual size_type bnf_repetition_body(size_type base, UV uv);
        virtual size_type bnf_not_eoi(size_type base, UV uv);
        virtual size_type bnf_not_istring(size_type base, UV uv);
        virtual size_type bnf_not_istring_string(size_type base, UV uv);
        virtual size_type bnf_negation(size_type base, UV uv);
        virtual size_type bnf_negation_item(size_type base, UV uv);
        virtual size_type bnf_entry(size_type base, UV uv);
        virtual size_type bnf_symbol(size_type base, UV uv);
        virtual size_type bnf_symbol_symbol(size_type base, UV uv);
        virtual size_type bnf_istring(size_type base, UV uv);
        virtual size_type bnf_istring_symbol(size_type base, UV uv);
        virtual size_type bnf_range(size_type base, UV uv);
        virtual size_type bnf_range_item(size_type base, UV uv);
        virtual size_type bnf_range_symbol_range(size_type base, UV uv);
        virtual size_type bnf_range_symbol_range_since(size_type base, UV uv);
        virtual size_type bnf_range_symbol_range_till(size_type base, UV uv);
        virtual size_type bnf_range_symbol(size_type base, UV uv);
        virtual size_type bnf_dot(size_type base, UV uv);
        virtual size_type bnf_escaped_symbol(size_type base, UV uv);
        virtual size_type bnf_escaped_code(size_type base, UV uv);
        virtual size_type bnf_escaped_code_oct(size_type base, UV uv);
        virtual size_type bnf_escaped_code_oct_char(size_type base, UV uv);
        virtual size_type bnf_escaped_code_hex(size_type base, UV uv);
        virtual size_type bnf_escaped_code_hex_char(size_type base, UV uv);
        virtual size_type bnf_escaped_char(size_type base, UV uv);

    // parser auxiliary functions
    private:
        inline size_type grammar_aux_0(size_type base, UV uv);
        inline size_type any_string_aux_0(size_type base, UV uv);
        inline size_type ws_aux_0(size_type base, UV uv);
        inline size_type wsnl_aux_0(size_type base, UV uv);
        inline size_type comment_aux_0(size_type base, UV uv);
        inline size_type comment_aux_1(size_type base, UV uv);
        inline size_type bnf_string_aux_0(size_type base, UV uv);
        inline size_type bnf_string_aux_1(size_type base, UV uv);
        inline size_type bnf_string_aux_2(size_type base, UV uv);
        inline size_type bnf_string_aux_3(size_type base, UV uv);
        inline size_type not_bnf_string_aux_0(size_type base, UV uv);
        inline size_type not_bnf_string_aux_1(size_type base, UV uv);
        inline size_type bnf_assignment_aux_0(size_type base, UV uv);
        inline size_type bnf_assignment_aux_1(size_type base, UV uv);
        inline size_type bnf_class_name_aux_0(size_type base, UV uv);
        inline size_type bnf_name_aux_0(size_type base, UV uv);
        inline size_type bnf_description_aux_0(size_type base, UV uv);
        inline size_type bnf_description_aux_1(size_type base, UV uv);
        inline size_type bnf_description_aux_2(size_type base, UV uv);
        inline size_type bnf_sequence_aux_0(size_type base, UV uv);
        inline size_type bnf_grouping_aux_0(size_type base, UV uv);
        inline size_type bnf_grouping_aux_1(size_type base, UV uv);
        inline size_type bnf_optim_option_repetition_aux_0(size_type base, UV uv);
        inline size_type bnf_optim_option_repetition_aux_1(size_type base, UV uv);
        inline size_type bnf_optim_option_repetition_aux_2(size_type base, UV uv);
        inline size_type bnf_optim_option_repetition_aux_3(size_type base, UV uv);
        inline size_type bnf_option_aux_0(size_type base, UV uv);
        inline size_type bnf_option_aux_1(size_type base, UV uv);
        inline size_type bnf_repetition_aux_0(size_type base, UV uv);
        inline size_type bnf_repetition_aux_1(size_type base, UV uv);
        inline size_type bnf_not_eoi_aux_0(size_type base, UV uv);
        inline size_type bnf_not_istring_aux_0(size_type base, UV uv);
        inline size_type bnf_not_istring_string_aux_0(size_type base, UV uv);
        inline size_type bnf_negation_aux_0(size_type base, UV uv);
        inline size_type bnf_entry_aux_0(size_type base, UV uv);
        inline size_type bnf_symbol_symbol_aux_0(size_type base, UV uv);
        inline size_type bnf_istring_aux_0(size_type base, UV uv);
        inline size_type bnf_istring_symbol_aux_0(size_type base, UV uv);
        inline size_type bnf_range_aux_0(size_type base, UV uv);
        inline size_type bnf_range_symbol_range_since_aux_0(size_type base, UV uv);
        inline size_type bnf_range_symbol_range_till_aux_0(size_type base, UV uv);
        inline size_type bnf_range_symbol_aux_0(size_type base, UV uv);
        inline size_type bnf_escaped_code_aux_0(size_type base, UV uv);
        inline size_type bnf_escaped_code_oct_aux_0(size_type base, UV uv);
        inline size_type bnf_escaped_code_oct_aux_1(size_type base, UV uv);
        inline size_type bnf_escaped_code_hex_aux_0(size_type base, UV uv);

};



#endif
