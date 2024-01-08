#ifndef PARSER_H
#define PARSER_H

#include "syntax-tree.hpp"
#include <string>
#include <fstream>
#include <vector>

class Parser {
private:
    std::string input_file_path;
    Variables variables;
    using Token = std::string;
    using Line = std::vector<Token>;
    std::vector<Line> lines;

    enum UnitNodeType {
        RETURN,
        ASSIGNMENT,
        IF_ELSE,
        LOOP,
        FUNCTION
    };

    void read_input_file_and_parse_into_tokens();
    bool token_is_variable_name(Token& token);
    int get_literal_value_from_token(Token& token);
    UnitNodeType get_next_unit_node_type(int line_index);
    SyntaxTreeNode* parse_binary_operation_node(int line_index);
    SyntaxTreeNode* parse_assignment_node(int line_index);
    SyntaxTreeNode* parse_single_unit_node(int line_index);
    SyntaxTreeNode* parse_block();
    void generate_syntax_tree();

public:
    Parser(std::string file_path);
};

#endif