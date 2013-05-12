#ifndef BNF_PLUSPLUS_GEN_H
#define BNF_PLUSPLUS_GEN_H

#include <config.h>

#include <iostream>
#include <string>
#include <utility>
#include <list>
#include <map>

#include <bnf++parser.cc>

using namespace std;

class bnf_plusplus_gen : private bnf_plusplus_parser<string,string*>
{
    public:
        static const unsigned int opt_not_specified;
        static const unsigned int opt_user_value;
        static const unsigned int opt_debug;
        static const string delim_str;

    public:
        bnf_plusplus_gen(const string &source, int beg, int end, const string &templ_, string &class_name_, string &header_, string &source_);
        string::size_type generate();
        unsigned int options(unsigned int _opts=opt_not_specified);
        const string &options(const string &option, const string &value="<undefined>");


    private:
        typedef pair<string,string> method_t;
        typedef list<method_t> methods_t;
        typedef list<string> strings_t;
        typedef pair<bool,bool> ent_cond_t;
        typedef map<string,ent_cond_t> entries_t;
        typedef map<string,string> subst_map_t;
        typedef map<string,string> options_t;

        string pos_bnf_name;
        string pos_bnf_body;
        string pos_class_name;
        methods_t pos_bnf_methods_aux;
        entries_t pos_bnf_entries;

        string &class_name;
        methods_t methods;
        methods_t methods_aux;
        string before_string;
        string after_string;
        entries_t bnf_entries;

        string &result_header;
        string &result_source;

        const string &templ;

        options_t options_map;
        unsigned int opts;
        bool before_bnf_plusplus;
        bool first_name;

    private:
        void add_string(const string &toadd);
        void submit_bnf_string();
        string as_string(int number);
        string indent(string str, int tabs);
        string to_upper(const string &str);
        string make_aux_name(int addon=0);

        void subst(string &target, const string &pat, const string &subs);
        void subst(string &target, const string &pat_from, const string &pat_to, const string &subs);
        void subst_cycle(string &target, const string &pat_from, const string &pat_to, subst_map_t &subst_map);

    private:
        string::size_type grammar(string::size_type base, string *ptr);
        string::size_type not_bnf_string(string::size_type base, string *ptr);
        string::size_type bnf_string(string::size_type base, string *ptr);
        string::size_type bnf_class_name(string::size_type base, string *ptr);
        string::size_type bnf_name(string::size_type base, string *ptr);
        string::size_type bnf_body(string::size_type base, string *ptr);
        string::size_type bnf_description(string::size_type base, string *ptr);
        string::size_type bnf_sequence(string::size_type base, string *ptr);
        string::size_type bnf_item(string::size_type base, string *ptr);
        string::size_type bnf_grouping_body(string::size_type base, string *ptr);
        string::size_type bnf_optim_option_repetition_body(string::size_type base, string *ptr);
        string::size_type bnf_option_body(string::size_type base, string *ptr);
        string::size_type bnf_repetition_body(string::size_type base, string *ptr);
        string::size_type bnf_not_eoi(string::size_type base, string *ptr);
        string::size_type bnf_not_istring_string(string::size_type base, string *ptr);
        string::size_type bnf_negation(string::size_type base, string *ptr);
        string::size_type bnf_negation_item(string::size_type base, string *ptr);
        string::size_type bnf_entry(string::size_type base, string *ptr);
        string::size_type bnf_symbol(string::size_type base, string *ptr);
        string::size_type bnf_istring(string::size_type base, string *ptr);
        string::size_type bnf_range(string::size_type base, string *ptr);
        string::size_type bnf_range_item(string::size_type base, string *ptr);
        string::size_type bnf_range_symbol_range(string::size_type base, string *ptr);
        string::size_type bnf_range_symbol_range_since(string::size_type base, string *ptr);
        string::size_type bnf_range_symbol_range_till(string::size_type base, string *ptr);
        string::size_type bnf_range_symbol(string::size_type base, string *ptr);
        string::size_type bnf_dot(string::size_type base, string *ptr);
};

#endif
