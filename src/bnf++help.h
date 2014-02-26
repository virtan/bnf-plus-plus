"Usage:\n\
    bnf++ [--user-value[=type]] [--with-template] [--output=filename_wo_ext] [--templates-dir=dir] [--debug] source\n\
Options:\n\
    --user-value[=type] add definition of additional argument for user\n\
                     value to all methods of parser (for non-template\n\
                     parsers also specify it's type)\n\
    --with-template  generate template for parser class\n\
                     template parameters are string and user value if exists\n\
    --output=filename_wo_ext specify name for output files (without\n\
                     extension) if omitted bnf++ will use parser's classname\n\
    --templates-dir=dir override default directory with templates\n\
    --debug          make parser with debug output: during execution parser\n\
                     prints the name of each called method to std::cerr\n\
"
