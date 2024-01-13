#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "syntax-tree.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

class Interpreter {
private:
    using Token = std::string;
    using Line = std::vector<Token>;
    std::string input_file_path;
    Variables variables;
    std::vector<Line> lines;
    int total_lines;
    using FunctionMap = std::map<Token, SyntaxTreeNode*>;
    FunctionMap functions;

    enum StatementNodeType {
        ASSIGNMENT,
        RETURN,
        IF_ELSE,
        LOOP,
        LONE_FUNCTION_CALL,
        FUNCTION_DEFINITION,
        EMPTY,
        PRINT
    };

    enum AssignmentStatementType {
        BASIC,
        BINARY_OPERATION,
        FUNCTION_CALL
    };

    friend std::ostream& operator<<(std::ostream& o, Line& line);

    OperandType get_operand_type_from_token(Token& token);
    bool token_is_function_name(Token& token);
    SyntaxTreeNode* parse_function_call_node(int& line_number);
    AssignmentStatementType get_assignment_statement_type(Line& line);
    void preprocess_input_string(std::string& input_string);
    void read_input_file_and_parse_into_tokens();
    bool token_is_variable_name(const Token& token);
    int get_literal_value_from_token(const Token& token);
    BinaryOperation binary_operation_token_to_enum(const Token& token);
    bool line_is_lone_function_call(Line& line);
    StatementNodeType get_next_statement_node_type(int& start_line);
    SyntaxTreeNode* parse_operand_token(const Token& token);
    SyntaxTreeNode* parse_binary_operation_node(const Token& left, const Token& op, const Token& right);
    SyntaxTreeNode* parse_assignment_node(int& start_line);
    int get_closing_brace_line(int opening_brace_line);
    SyntaxTreeNode* parse_braces_block(int& start_line);
    SyntaxTreeNode* parse_if_else_node(int& start_line);
    SyntaxTreeNode* parse_print_node(int& start_line);
    SyntaxTreeNode* parse_loop_node(int& start_line);
    SyntaxTreeNode* parse_single_statement_node(int& start_line);
    SyntaxTreeNode* parse_function_definition(int& start_line);
    SyntaxTreeNode* parse_block(int& start_line, int& end_line);
    void generate_syntax_tree();
public:
    Interpreter(std::string input_file_path) : input_file_path(input_file_path), variables(Variables()) {}
    void parse_file();
};

std::ostream& operator<<(std::ostream& o, Interpreter::Line& line);

#endif