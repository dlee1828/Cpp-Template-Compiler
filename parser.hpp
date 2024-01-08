#ifndef PARSER_H
#define PARSER_H

#include "syntax-tree.hpp"
#include <string>
#include <fstream>

class Parser {
private:
    std::string file_path;
    std::ifstream input;
    SyntaxTree syntax_tree;

    void generate_synatx_tree();
public:
    Parser(std::string file_path);
    SyntaxTree get_syntax_tree();
};

#endif