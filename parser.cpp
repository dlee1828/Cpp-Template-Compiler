#include "parser.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

void Parser::read_input_file_and_parse_into_tokens() {
    std::ifstream input_file_stream(input_file_path);

    std::string line_string;
    Line current_line;
    while (getline(input_file_stream, line_string)) {
        current_line.clear();
        std::stringstream line_stream(line_string);
        Token token;
        while (line_stream >> token) {
            current_line.push_back(token);
        }
        lines.push_back(current_line);
    }

    total_lines = lines.size();
}


void Parser::generate_syntax_tree() {

}

Parser::StatementNodeType Parser::get_next_statement_node_type(int& line_num) {
    Line& line = lines[line_num];
    int num_tokens = line.size();
    if (num_tokens > 1 && line[1] == "=") return ASSIGNMENT;
    else if (num_tokens > 0 && line[0] == "if") return IF_ELSE;
    else if (num_tokens > 0 && line[0] == "for") return LOOP;
    else if (num_tokens > 0 && line[0] == "return") return RETURN;
    else {
        std::cerr << "Error: unidentified unit node type" << std::endl;
        return ASSIGNMENT;
    }
}

BinaryOperation Parser::binary_operation_token_to_enum(const Token& token) {
    if (token == "+") return BinaryOperation::ADD;
    else if (token == "-") return BinaryOperation::SUBTRACT;
    else if (token == "*") return BinaryOperation::MULTIPLY;
    else if (token == "/") return BinaryOperation::DIVIDE;
    else if (token == "%") return BinaryOperation::MOD;
    else if (token == "<") return BinaryOperation::LESS;
    else if (token == "<=") return BinaryOperation::LESS_EQUAL;
    else if (token == ">") return BinaryOperation::GREATER;
    else if (token == ">=") return BinaryOperation::GREATER_EQUAL;
    else if (token == "==") return BinaryOperation::EQUAL;
    else if (token == "!=") return BinaryOperation::NOT_EQUAL;

    std::cerr << "Error: unidentified operation token" << std::endl; 
    return BinaryOperation::ADD;
}

bool Parser::token_is_variable_name(const Token& token) {
    char first_letter = token[0];
    if ('0' <= first_letter && first_letter <= '9') return false;
    else return true;
}

int Parser::get_literal_value_from_token(const Token& token) {
    return std::stoi(token);
}

SyntaxTreeNode* Parser::parse_binary_operation_node(int& line_num) {

}

SyntaxTreeNode* Parser::parse_operand_token(const Token& token) {
    OperandType operand_type = token_is_variable_name(token) ? IDENTIFIER : LITERAL;
    SyntaxTreeNode* operand_node = nullptr;
    if (operand_type == LITERAL) operand_node = new OperandNode(operand_type, get_literal_value_from_token(token), variables);
    else operand_node = new OperandNode(operand_type, token, variables);
    return operand_node;
}



SyntaxTreeNode* Parser::parse_assignment_node(int& line_num) {
    Line& line = lines[line_num];
    Token variable_name = line[0];
    bool contains_binary_operation = line.size() > 3;
    SyntaxTreeNode* assignment_node = nullptr;
    if (contains_binary_operation) {
        SyntaxTreeNode* left_operand = parse_operand_token(line[2]);
        Token operator_token = line[3];
        SyntaxTreeNode* right_operand = parse_operand_token(line[4]);

        SyntaxTreeNode* binary_operation_node = new BinaryOperationNode(binary_operation_token_to_enum(operator_token), left_operand, right_operand, variables);
        assignment_node = new AssignmentNode(variable_name, binary_operation_node, variables);
    } else {
        SyntaxTreeNode* value_node = parse_operand_token(line[2]);
        assignment_node = new AssignmentNode(variable_name, value_node, variables);
    }
    line_num++;
    return assignment_node;
}

SyntaxTreeNode* Parser::parse_single_statement_node(int& line_num) {
    Parser::StatementNodeType unit_node_type = get_next_statement_node_type(line_num);
    SyntaxTreeNode* node = nullptr;
    switch (unit_node_type) {
        case StatementNodeType::ASSIGNMENT:
            node = parse_assignment_node(line_num);
    }
    return node;
}

SyntaxTreeNode* Parser::parse_block(int& line_num) {
    std::vector<SyntaxTreeNode*> nodes;
    // while (true) { // todo: need to only do it within current scope
    //     SyntaxTreeNode* node = parse_single_unit_node();
    //     nodes.push_back(node);
    // }
    if (nodes.size() == 1) return nodes[0];
    else return new StatementSequenceNode(nodes, variables);
}

void Parser::parse_file() {
    read_input_file_and_parse_into_tokens();
    int line_num = 0;
    while (line_num < total_lines) {
        SyntaxTreeNode* node = parse_single_statement_node(line_num);
        std::cout << node << std::endl;
    }
}