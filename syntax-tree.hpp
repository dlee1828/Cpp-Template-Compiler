#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <vector>
#include <string>
#include <map>

class SyntaxTree {
private:
    enum SyntaxTreeNodeType {
        STATEMENT_SEQUENCE,
        OPERAND,
        RETURN,
        BINARY_OPERATION,
        IF_ELSE,
        LOOP
    };

    struct SyntaxTreeNode {
        virtual int evaluate () const = 0;
        SyntaxTreeNodeType node_type;
        SyntaxTreeNode(SyntaxTreeNodeType type) : node_type(type) {};
        virtual ~SyntaxTreeNode();
    };

    struct StatementSequenceNode : SyntaxTreeNode {
        const std::vector<SyntaxTreeNode*> statements;
        StatementSequenceNode(const std::vector<SyntaxTreeNode*>& statements) : statements(statements), SyntaxTreeNode(STATEMENT_SEQUENCE) {};
        int evaluate();
    };

    enum OperandType {
        IDENTIFIER, LITERAL
    };


    struct OperandNode : SyntaxTreeNode {
        OperandType operand_type;
        std::string identifier_value;
        int literal_value;
        const std::map<std::string, int>& variable_values;
        OperandNode(OperandType operand_type, std::string identifier_value, const std::map<std::string, int>& variable_values) : operand_type(operand_type), identifier_value(identifier_value), variable_values(variable_values), SyntaxTreeNode(OPERAND) {};
        OperandNode(OperandType operand_type, int literal_value, const std::map<std::string, int>& variable_values) : operand_type(operand_type), literal_value(literal_value), variable_values(variable_values), SyntaxTreeNode(OPERAND) {};
        int evaluate();
    };

    struct ReturnNode : SyntaxTreeNode {
        const SyntaxTreeNode* value;
        ReturnNode(const SyntaxTreeNode* value) : value(value), SyntaxTreeNode(RETURN) {};
        int evaluate();
    };

    enum BinaryOperation {
        ADD, SUBTRACT, MULTIPLY, DIVIDE, MOD, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL, EQUAL, NOT_EQUAL
    };

    struct BinaryOperationNode : SyntaxTreeNode {
        BinaryOperation operation;
        SyntaxTreeNode* left_operand;
        SyntaxTreeNode* right_operand;
        BinaryOperationNode(BinaryOperation operation, SyntaxTreeNode* left_operand, SyntaxTreeNode* right_operand) : operation(operation), left_operand(left_operand), right_operand(right_operand), SyntaxTreeNode(BINARY_OPERATION) {};
        int evaluate();
    };

    struct IfElseNode : SyntaxTreeNode {
        SyntaxTreeNode* condition;
        SyntaxTreeNode* if_block;
        SyntaxTreeNode* else_block;
        IfElseNode(SyntaxTreeNode* condition, SyntaxTreeNode* if_block, SyntaxTreeNode* else_block) : condition(condition), if_block(if_block), else_block(else_block), SyntaxTreeNode(IF_ELSE) {};
        int evaluate();
    };

    struct LoopNode : SyntaxTreeNode {
        SyntaxTreeNode* iterations; 
        SyntaxTreeNode* body;
        LoopNode(SyntaxTreeNode* iterations, SyntaxTreeNode* body) : iterations(iterations), body(body), SyntaxTreeNode(LOOP) {};
        int evaluate();
    };
};

#endif