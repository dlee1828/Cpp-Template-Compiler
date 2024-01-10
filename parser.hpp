#ifndef PARSER_H
#define PARSER_H

#include "syntax-tree.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

class Parser {
private:
    std::string input_file_path;
    Variables variables;
    using Token = std::string;
    using Line = std::vector<Token>;
    std::vector<Line> lines;
    int total_lines;

    enum StatementNodeType {
        ASSIGNMENT,
        RETURN,
        IF_ELSE,
        LOOP,
        FUNCTION,
        EMPTY
    };

    void preprocess_input_string(std::string& input_string);
    void read_input_file_and_parse_into_tokens();
    bool token_is_variable_name(const Token& token);
    int get_literal_value_from_token(const Token& token);
    BinaryOperation binary_operation_token_to_enum(const Token& token);
    StatementNodeType get_next_statement_node_type(int& start_line);
    SyntaxTreeNode* parse_operand_token(const Token& token);
    SyntaxTreeNode* parse_binary_operation_node(const Token& left, const Token& op, const Token& right);
    SyntaxTreeNode* parse_assignment_node(int& start_line);
    int get_closing_brace_line(int opening_brace_line);
    SyntaxTreeNode* parse_braces_block(int& start_line);
    SyntaxTreeNode* parse_if_else_node(int& start_line);
    SyntaxTreeNode* parse_single_statement_node(int& start_line);
    SyntaxTreeNode* parse_block(int& start_line, int& end_line);
    void generate_syntax_tree();

public:
    Parser(std::string input_file_path) : input_file_path(input_file_path), variables(Variables()) {}
    void parse_file();
};

#endif