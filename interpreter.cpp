#include "interpreter.hpp"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "debug.hpp"

std::ostream& operator<<(std::ostream& o, Interpreter::Line& line) {
    for (Interpreter::Token token : line) {
        o << token << " ";
    }
    o << std::endl;
    return o;
}

void Interpreter::preprocess_input_string(std::string& input_string) {
    std::string temp = input_string;
    input_string = "";
    for (char c : temp) {
        if (c == '{' || c == '}') {
            input_string.push_back('\n');
            input_string.push_back(c);
            input_string.push_back('\n');
        } else input_string.push_back(c);
    }

    temp = input_string;
    input_string = "";
    for (char c : temp) {
        if (c == '(' || c == ')' || c == ',') {
            input_string.push_back(' ');
            input_string.push_back(c);
            input_string.push_back(' ');
        } else input_string.push_back(c);
    }

    temp = input_string;
    input_string = "";
    bool seen_char = false;
    for (int i = 0; i < temp.size(); i++) {
        char c = temp[i];
        if (c == '\n') seen_char = false;
        else if (c == ' ' || c == '\t') {
            if (!seen_char) continue;
        }
        else seen_char = true;

        input_string.push_back(c);
    }

    temp = input_string;
    input_string = "";
    for (int i = 0; i < temp.size(); i++) {
        if (
            temp[i] == '\n' && 
            (i == temp.size() - 1 || (i > 0 && temp[i - 1] == '\n'))
        ) continue;
        else input_string.push_back(temp[i]);
    }
}

void Interpreter::read_input_file_and_parse_into_tokens() {

    std::ifstream input_file_stream(input_file_path);
    std::stringstream input_string_stream;
    input_string_stream << input_file_stream.rdbuf();
    std::string input_string = input_string_stream.str();
    preprocess_input_string(input_string);
    print(input_string);
    input_string_stream = std::stringstream(input_string);

    std::string line_string;
    Line current_line;
    while (getline(input_string_stream, line_string)) {
        print(line_string);
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


void Interpreter::generate_syntax_tree() {

}

bool Interpreter::token_is_function_name(Token& token) {
    return functions.find(token) != functions.end();
}

bool Interpreter::line_is_lone_function_call(Line& line) {
    Token first_token = line[0];
    return token_is_function_name(first_token);
}

Interpreter::StatementNodeType Interpreter::get_next_statement_node_type(int& start_line) {
    Line& line = lines[start_line];
    int num_tokens = line.size();
    if (num_tokens > 1 && line[1] == "=") return ASSIGNMENT;
    else if (line[0] == "if") return IF_ELSE;
    else if (line[0] == "for") return LOOP;
    else if (line[0] == "return") return RETURN;
    else if (line[0] == "print") return PRINT;
    else if (line[0] == "function") return FUNCTION_DEFINITION;
    else if (line_is_lone_function_call(line)) return LONE_FUNCTION_CALL;
    else {
        std::cerr << "Error: unidentified unit node type" << std::endl;
        return ASSIGNMENT;
    }
}

BinaryOperation Interpreter::binary_operation_token_to_enum(const Token& token) {
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

bool Interpreter::token_is_variable_name(const Token& token) {
    char first_letter = token[0];
    if ('0' <= first_letter && first_letter <= '9') return false;
    else return true;
}

int Interpreter::get_literal_value_from_token(const Token& token) {
    return std::stoi(token);
}

SyntaxTreeNode* Interpreter::parse_operand_token(const Token& token) {
    print("PARSING OPERAND TOKEN FOR TOKEN", token);
    OperandType operand_type = token_is_variable_name(token) ? IDENTIFIER : LITERAL;
    SyntaxTreeNode* operand_node = nullptr;
    if (operand_type == LITERAL) operand_node = new OperandNode(operand_type, get_literal_value_from_token(token), variables);
    else operand_node = new OperandNode(operand_type, token, variables);
    return operand_node;
}

SyntaxTreeNode* Interpreter::parse_binary_operation_node(const Token& left, const Token& op, const Token& right) {
    print("PARSING BINARY OPERATION NODE FOR", left, op, right);
    SyntaxTreeNode* left_operand = parse_operand_token(left);
    SyntaxTreeNode* right_operand = parse_operand_token(right);
    return new BinaryOperationNode(binary_operation_token_to_enum(op), left_operand, right_operand, variables);
}

Interpreter::AssignmentStatementType Interpreter::get_assignment_statement_type(Line& line) {
    if (line.size() == 3) return AssignmentStatementType::BASIC;
    Token possible_function_name = line[2];
    if (functions.find(possible_function_name) != functions.end()) return AssignmentStatementType::FUNCTION_CALL;
    else return AssignmentStatementType::BINARY_OPERATION;
}

OperandType Interpreter::get_operand_type_from_token(Token& token) {
    bool all_numeric = true;
    bool all_letters = true;
    for (char c : token) {
        if (!('0' <= c && c <= '9')) all_numeric = false;
        if (!(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))) all_letters = false;
    }

    if (all_numeric) return OperandType::LITERAL;
    else if (all_letters) return OperandType::IDENTIFIER;
    else {
        std::cerr << "Error: operand type is neither literal nor identifier";
        return OperandType::LITERAL;
    }
}

SyntaxTreeNode* Interpreter::parse_function_call_node(int& line_number) {
    Line& line = lines[line_number];
    line_number++;

    int function_name_index = 0;
    while (!token_is_function_name(line[function_name_index])) function_name_index++;
    Token function_name = line[function_name_index];

    int first_argument_index = function_name_index + 2;
    std::vector<SyntaxTreeNode*> argument_nodes;
    for (int i = first_argument_index; line[i] != ")"; i++) {
        if (line[i] != ",") {
            Token argument = line[i];
            OperandType operand_type = get_operand_type_from_token(argument);
            OperandNode* argument_node = nullptr;
            if (operand_type == OperandType::LITERAL) argument_node = new OperandNode(operand_type, std::stoi(argument), variables);
            else argument_node = new OperandNode(operand_type, argument, variables);
            argument_nodes.push_back(argument_node);
        }
    }

    SyntaxTreeNode* function_body = functions[function_name];

    // TODO need to store parameter names when reading function definition
    // so that argument_nodes can be a map instead of a vector
    return new FunctionNode(function_body, argument_nodes, variables);
}

SyntaxTreeNode* Interpreter::parse_assignment_node(int& start_line) {
    Line& line = lines[start_line];
    Token variable_name = line[0];

    AssignmentStatementType assignment_statement_type = get_assignment_statement_type(line);

    bool contains_binary_operation = line.size() > 3;
    SyntaxTreeNode* assignment_node = nullptr;

    switch(assignment_statement_type) {
        case AssignmentStatementType::BASIC: {
            SyntaxTreeNode* value_node = parse_operand_token(line[2]);
            assignment_node = new AssignmentNode(variable_name, value_node, variables);
            break;
        }
        case AssignmentStatementType::BINARY_OPERATION: {
            SyntaxTreeNode* binary_operation_node = parse_binary_operation_node(line[2], line[3], line[4]);
            assignment_node = new AssignmentNode(variable_name, binary_operation_node, variables);
            break;
        }
        case AssignmentStatementType::FUNCTION_CALL: {
            Token function_name = line[2];
        }
    }

    start_line++;
    return assignment_node;
}

int Interpreter::get_closing_brace_line(int opening_brace_line) {
    print("GETTING CLOSING BRACE FOR OPENING BRACE STARTING AT", opening_brace_line);
    int num_open_braces = 1;
    int i = opening_brace_line + 1;
    while (i < total_lines) {
        print(i);
        if (lines[i][0] == "{") num_open_braces++;
        else if (lines[i][0] == "}") num_open_braces--;
        if (num_open_braces == 0) return i;
        i++;
    }
    std::cerr << "Error: No closing brace found";
    return -1;
}

SyntaxTreeNode* Interpreter::parse_braces_block(int& start_line) {
    int end_line = get_closing_brace_line(start_line);
    print("PARSING BRACES BLOCK FROM LINE", start_line, "TO", end_line);
    start_line++;
    end_line--;
    SyntaxTreeNode* node = parse_block(start_line, end_line);
    print("PARSED BRACES BLOCK, RESULT:", node);
    start_line++;
    return node;
}

SyntaxTreeNode* Interpreter::parse_if_else_node(int& start_line) {
    print("PARSING IF ELSE NODE STARTING AT", start_line);
    Line& line = lines[start_line];

    SyntaxTreeNode* binary_operation_node = parse_binary_operation_node(line[2], line[3], line[4]);
    start_line++;
    SyntaxTreeNode* if_block_node = parse_braces_block(start_line);
    SyntaxTreeNode* else_block_node = nullptr;
    if (start_line < total_lines && lines[start_line][0] == "else") {
        start_line++;
        else_block_node = parse_braces_block(start_line);
    } else else_block_node = new EmptyNode(variables);

    return new IfElseNode(binary_operation_node, if_block_node, else_block_node, variables);
}

SyntaxTreeNode* Interpreter::parse_print_node(int& start_line) {
    Line& line = lines[start_line];
    print("PARSING PRINT NODE FOR LINE", line);
    Token print_value_token = line[2];
    SyntaxTreeNode* print_value_node = parse_operand_token(print_value_token);
    print("SUCCESSFULLY PARSED OPERAND TOKEN IN PRINT NODE FOR LINE", line);
    SyntaxTreeNode* node = new PrintNode(print_value_node, variables);
    print("SUCCESSFULLY INSTANTIATED NEW PRINT NODE");
    start_line++;
    return node;
}

SyntaxTreeNode* Interpreter::parse_loop_node(int& start_line) {
    Line& line = lines[start_line];
    Token iterations_token = line[2];
    SyntaxTreeNode* iterations_node = parse_operand_token(iterations_token);
    start_line++;
    SyntaxTreeNode* body_node = parse_braces_block(start_line);
    return new LoopNode(iterations_node, body_node, variables);
}

SyntaxTreeNode* Interpreter::parse_function_definition(int& start_line) {
    Token function_name = lines[start_line][1];
    start_line++;
    SyntaxTreeNode* function_body_node = parse_braces_block(start_line);
    functions[function_name] = function_body_node;
    return new EmptyNode(variables);
}

SyntaxTreeNode* Interpreter::parse_single_statement_node(int& start_line) {
    Interpreter::StatementNodeType unit_node_type = get_next_statement_node_type(start_line);
    SyntaxTreeNode* node = nullptr;
    switch (unit_node_type) {
        case StatementNodeType::ASSIGNMENT:
            return parse_assignment_node(start_line);
        case StatementNodeType::IF_ELSE:
            return parse_if_else_node(start_line);
        case StatementNodeType::PRINT:
            return parse_print_node(start_line);
        case StatementNodeType::LOOP:
            return parse_loop_node(start_line);
        case StatementNodeType::FUNCTION_DEFINITION:
            return parse_function_definition(start_line);
    }
    print("ERROR: SINGLE STATEMENT NODE = NULLPTR");
    return nullptr;
}


SyntaxTreeNode* Interpreter::parse_block(int& start_line, int& end_line) {
    std::vector<SyntaxTreeNode*> nodes;
    while (start_line <= end_line) {
        SyntaxTreeNode* node = parse_single_statement_node(start_line);
        print("DONE PARSING NODE OF TYPE", get_node_type_string_from_enum(node->node_type));
        nodes.push_back(node);
    }
    if (nodes.size() == 1) return nodes[0];
    else return new StatementSequenceNode(nodes, variables);
}

void Interpreter::parse_file() {
    read_input_file_and_parse_into_tokens();
    int start = 0;
    int end = total_lines - 1;
    SyntaxTreeNode* node = parse_block(start, end);
    node->evaluate();
}