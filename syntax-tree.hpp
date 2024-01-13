#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <vector>
#include <string>
#include <map>
#include <stack>
#include <set>
#include <unordered_set>
#include <iostream>
class Variables {
private:
    using VariableMap = std::map<std::string, int>;
    VariableMap variable_values;
    using Scope = std::unordered_set<std::string>;
    std::stack<Scope> scopes;
    friend std::ostream& operator<<(std::ostream& o, Variables& variables);

public:
    Variables() : variable_values(VariableMap()), scopes(std::stack<Scope>()) {
        scopes.push(Scope());
    }
    int get_variable_value(const std::string& variable_name);
    void assign_variable_and_initialize_if_necessary(const std::string& variable_name, int value);
    void enter_new_scope();
    void exit_current_scope();
};

std::ostream& operator<<(std::ostream& o, Variables& variables);


enum SyntaxTreeNodeType {
    STATEMENT_SEQUENCE,
    OPERAND,
    RETURN,
    ASSIGNMENT,
    BINARY_OPERATION,
    IF_ELSE,
    LOOP,
    FUNCTION_CALL,
    PRINT,
    EMPTY
};

struct SyntaxTreeNode {
    struct EvaluationResult {
        int expression_value;
        int return_value;
        bool should_return;
        EvaluationResult() : expression_value(0), return_value(0), should_return(false) {}
    };
    virtual EvaluationResult evaluate () = 0;
    SyntaxTreeNodeType node_type;
    Variables& variables;
    SyntaxTreeNode(SyntaxTreeNodeType type, Variables& variables) : node_type(type), variables(variables) {}
};

std::ostream& operator<<(std::ostream& o, const SyntaxTreeNode* node);

struct StatementSequenceNode : SyntaxTreeNode {
    std::vector<SyntaxTreeNode*> statements;
    StatementSequenceNode(std::vector<SyntaxTreeNode*>& statements, Variables& variables) : statements(statements), SyntaxTreeNode(STATEMENT_SEQUENCE, variables) {}
    EvaluationResult evaluate();
};

enum OperandType {
    IDENTIFIER, LITERAL
};

struct OperandNode : SyntaxTreeNode {
    OperandType operand_type;
    std::string identifier_value;
    int literal_value;
    OperandNode(OperandType operand_type, std::string identifier_value, Variables& variables) : operand_type(operand_type), identifier_value(identifier_value), SyntaxTreeNode(OPERAND, variables) {}
    OperandNode(OperandType operand_type, int literal_value, Variables& variables) : operand_type(operand_type), literal_value(literal_value), SyntaxTreeNode(OPERAND, variables) {}
    EvaluationResult evaluate();
};

struct ReturnNode : SyntaxTreeNode {
    SyntaxTreeNode* value;
    ReturnNode(SyntaxTreeNode* value, Variables& variables) : value(value), SyntaxTreeNode(RETURN, variables) {}
    EvaluationResult evaluate();
};

struct AssignmentNode : SyntaxTreeNode {
    std::string variable_name;
    SyntaxTreeNode* value;
    EvaluationResult evaluate();
    AssignmentNode(std::string variable_name, SyntaxTreeNode* value, Variables& variables) : variable_name(variable_name), value(value), SyntaxTreeNode(ASSIGNMENT, variables) {}
};

enum BinaryOperation {
    ADD, SUBTRACT, MULTIPLY, DIVIDE, MOD, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL, EQUAL, NOT_EQUAL
};
struct BinaryOperationNode : SyntaxTreeNode {
    BinaryOperation operation;
    SyntaxTreeNode* left_operand;
    SyntaxTreeNode* right_operand;
    BinaryOperationNode(BinaryOperation operation, SyntaxTreeNode* left_operand, SyntaxTreeNode* right_operand, Variables& variables) : operation(operation), left_operand(left_operand), right_operand(right_operand), SyntaxTreeNode(BINARY_OPERATION, variables) {}
    EvaluationResult evaluate();
};

struct IfElseNode : SyntaxTreeNode {
    SyntaxTreeNode* condition;
    SyntaxTreeNode* if_block;
    SyntaxTreeNode* else_block;
    IfElseNode(SyntaxTreeNode* condition, SyntaxTreeNode* if_block, SyntaxTreeNode* else_block, Variables& variables) : condition(condition), if_block(if_block), else_block(else_block), SyntaxTreeNode(IF_ELSE, variables) {}
    EvaluationResult evaluate();
};

struct LoopNode : SyntaxTreeNode {
    SyntaxTreeNode* iterations; 
    SyntaxTreeNode* body;
    LoopNode(SyntaxTreeNode* iterations, SyntaxTreeNode* body, Variables& variables) : iterations(iterations), body(body), SyntaxTreeNode(LOOP, variables) {}
    EvaluationResult evaluate();
};

struct FunctionNode : SyntaxTreeNode {
    SyntaxTreeNode* body;
    std::map<std::string, SyntaxTreeNode*> arguments;
    FunctionNode(SyntaxTreeNode* body, std::map<std::string, SyntaxTreeNode*> arguments, Variables& variables) : body(body), arguments(arguments), SyntaxTreeNode(FUNCTION_CALL, variables) {}
    EvaluationResult evaluate();
};

struct PrintNode : SyntaxTreeNode {
    SyntaxTreeNode* value; 
    PrintNode(SyntaxTreeNode* value, Variables& variables) : value(value), SyntaxTreeNode(PRINT, variables) {}
    EvaluationResult evaluate();
};

struct EmptyNode : SyntaxTreeNode {
    EmptyNode(Variables& variables) : SyntaxTreeNode(EMPTY, variables) {}
    EvaluationResult evaluate();
};

std::string get_node_type_string_from_enum(SyntaxTreeNodeType type);

#endif