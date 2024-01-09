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
    int total_lines;

    enum StatementNodeType {
        RETURN,
        ASSIGNMENT,
        IF_ELSE,
        LOOP,
        FUNCTION
    };

    void read_input_file_and_parse_into_tokens();
    bool token_is_variable_name(const Token& token);
    int get_literal_value_from_token(const Token& token);
    BinaryOperation binary_operation_token_to_enum(const Token& token);
    StatementNodeType get_next_statement_node_type(int& line_num);
    SyntaxTreeNode* parse_operand_token(const Token& token);
    SyntaxTreeNode* parse_binary_operation_node(int& line_num);
    SyntaxTreeNode* parse_assignment_node(int& line_num);
    SyntaxTreeNode* parse_single_statement_node(int& line_num);
    SyntaxTreeNode* parse_block(int& line_num);
    void generate_syntax_tree();

public:
    Parser(std::string input_file_path) : input_file_path(input_file_path), variables(Variables()) {};
    void parse_file();
};

#endif