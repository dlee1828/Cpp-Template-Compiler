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
}


Parser::Parser(std::string input_file_path) : input_file_path(input_file_path), variables(Variables()) {
    read_input_file_and_parse_into_tokens();
}

void Parser::generate_syntax_tree() {

}

Parser::UnitNodeType Parser::get_next_unit_node_type(int line_index) {
    Line& line = lines[line_index];
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

bool Parser::token_is_variable_name(Token& token) {
    char first_letter = token[0];
    if ('0' <= first_letter && first_letter <= '9') return false;
    else return true;
}

int Parser::get_literal_value_from_token(Token& token) {
    return std::stoi(token);
}

SyntaxTreeNode* Parser::parse_binary_operation_node(int line_index) {

}

SyntaxTreeNode* Parser::parse_assignment_node(int line_index) {
    Line& line = lines[line_index];
    Token variable_name = line[0];
    bool contains_binary_operation = line.size() > 3;
    if (contains_binary_operation) {

    } else {
        Token value_token = line[2];
        OperandType operand_type = token_is_variable_name(line[2]) ? IDENTIFIER : LITERAL;
        SyntaxTreeNode* value_node = nullptr;
        if (operand_type == LITERAL) value_node = new OperandNode(operand_type, get_literal_value_from_token(value_token), variables);
        else value_node = new OperandNode(operand_type, value_token, variables);
        SyntaxTreeNode* node = new AssignmentNode(variable_name, value_node, variables);
    }
}

SyntaxTreeNode* Parser::parse_single_unit_node(int line_index) {
    Parser::UnitNodeType unit_node_type = get_next_unit_node_type(line_index);
}

SyntaxTreeNode* Parser::parse_block() {
    std::vector<SyntaxTreeNode*> nodes;
    // while (true) { // todo: need to only do it within current scope
    //     SyntaxTreeNode* node = parse_single_unit_node();
    //     nodes.push_back(node);
    // }
    if (nodes.size() == 1) return nodes[0];
    else return new StatementSequenceNode(nodes, variables);
}