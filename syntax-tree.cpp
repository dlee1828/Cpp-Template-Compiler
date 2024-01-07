#include "syntax-tree.hpp"

int SyntaxTree::StatementSequenceNode::evaluate() {
    for (SyntaxTreeNode* node : statements) {
        int value = node->evaluate();
        if (node->node_type == RETURN) return value;
    }
}

int SyntaxTree::OperandNode::evaluate() {
    switch (operand_type) {
        case IDENTIFIER:
            return variable_values.at(identifier_value);
        case LITERAL:
            return literal_value;
    }
}

int SyntaxTree::ReturnNode::evaluate() {
    return value->evaluate();    
}


int SyntaxTree::BinaryOperationNode::evaluate() {
    int left_value = left_operand->evaluate();
    int right_value = right_operand->evaluate();
    switch(operation) {
        case ADD:
            return left_value + right_value;
        case SUBTRACT:
            return left_value - right_value;
        case MULTIPLY:
            return left_value * right_value;
        case DIVIDE:
            return left_value / right_value;
        case MOD:
            return left_value % right_value;
        case LESS:
            return left_value < right_value;
        case LESS_EQUAL:
            return left_value <= right_value;
        case GREATER:
            return left_value > right_value;
        case GREATER_EQUAL:
            return left_value >= right_value;
        case EQUAL:
            return left_value == right_value;
        case NOT_EQUAL:
            return left_value != right_value;
    }
}

int SyntaxTree::IfElseNode::evaluate() {
    int condition_value = condition->evaluate();
    if (condition_value) return if_block->evaluate();
    else return else_block->evaluate();
}

int SyntaxTree::LoopNode::evaluate() {
    int iterations_value = iterations->evaluate();
    for (int i = 0; i < iterations_value; i++) {
        body->evaluate();
    }
    return 0;
}