#ifndef PARSER_H
#define PARSER_H

#include "syntax-tree.hpp"
#include <string>

class parser {
private:
    std::string file_path;
    syntax_tree code_syntax_tree;

    void generate_synatx_tree();
public:
    parser(std::string file_path);
    syntax_tree get_syntax_tree();
};

#endif