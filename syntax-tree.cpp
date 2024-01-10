#include "syntax-tree.hpp"

int Variables::get_variable_value(const std::string& variable_name) {
    return variable_values[variable_name];
}

void Variables::assign_variable_and_initialize_if_necessary(const std::string& variable_name, int value) {
    bool need_to_initialize = (variable_values.find(variable_name) == variable_values.end());
    variable_values[variable_name] = value;
    if (need_to_initialize) scopes.top().insert(variable_name);
}

void Variables::enter_new_scope() {
    Scope new_scope;
    scopes.push(new_scope);
}

void Variables::exit_current_scope() {
    Scope current_scope = scopes.top();
    for (std::string variable_name : current_scope) {
        variable_values.erase(variable_values.find(variable_name));
    }
    scopes.pop();
}


std::string get_node_type_string_from_enum(SyntaxTreeNodeType type) {
    switch (type) {
        case STATEMENT_SEQUENCE:
            return "STATEMENT_SEQUENCE";
        case OPERAND:
            return "OPERAND";
        case RETURN:
            return "RETURN";
        case ASSIGNMENT:
            return "ASSIGNMENT";
        case BINARY_OPERATION:
            return "BINARY_OPERATION";
        case IF_ELSE:
            return "IF_ELSE";
        case LOOP:
            return "LOOP";
        case FUNCTION:
            return "FUNCTION";
    }
}

std::ostream& operator<<(std::ostream& o, const SyntaxTreeNode* node) {
    std::string node_type_string = get_node_type_string_from_enum(node->node_type);
    o << node_type_string << " NODE";
    return o;
}


SyntaxTreeNode::EvaluationResult StatementSequenceNode::evaluate() {
    EvaluationResult result;
    for (SyntaxTreeNode* node : statements) {
        EvaluationResult node_result = node->evaluate();
        if (node_result.should_return) {
            result.return_value =  node_result.return_value;
            result.should_return = true;
            return result;
        }
    }
    return result;
}

SyntaxTreeNode::EvaluationResult OperandNode::evaluate() {
    EvaluationResult result;
    switch (operand_type) {
        case IDENTIFIER:
            result.expression_value = variables.get_variable_value(identifier_value);
        case LITERAL:
            result.expression_value = literal_value;
    }
    return result;
}

SyntaxTreeNode::EvaluationResult ReturnNode::evaluate() {
    EvaluationResult result;
    result.return_value = value->evaluate().expression_value;
    result.should_return = true;
    return result;
}

SyntaxTreeNode::EvaluationResult AssignmentNode::evaluate() {
    EvaluationResult result;
    int assignment_value = value->evaluate().expression_value;
    variables.assign_variable_and_initialize_if_necessary(variable_name, assignment_value);
    result.expression_value = 1;
    return result;
}

SyntaxTreeNode::EvaluationResult BinaryOperationNode::evaluate() {
    EvaluationResult result;
    int left_value = left_operand->evaluate().expression_value;
    int right_value = right_operand->evaluate().expression_value;

    int expression_value = 0; 
    switch(operation) {
        case ADD:
            expression_value = left_value + right_value;
        case SUBTRACT:
            expression_value = left_value - right_value;
        case MULTIPLY:
            expression_value = left_value * right_value;
        case DIVIDE:
            expression_value = left_value / right_value;
        case MOD:
            expression_value = left_value % right_value;
        case LESS:
            expression_value = left_value < right_value;
        case LESS_EQUAL:
            expression_value = left_value <= right_value;
        case GREATER:
            expression_value = left_value > right_value;
        case GREATER_EQUAL:
            expression_value = left_value >= right_value;
        case EQUAL:
            expression_value = left_value == right_value;
        case NOT_EQUAL:
            expression_value = left_value != right_value;
    }

    result.expression_value = expression_value;
    return result;
}

SyntaxTreeNode::EvaluationResult IfElseNode::evaluate() {
    variables.enter_new_scope();
    int condition_value = condition->evaluate().expression_value;
    if (condition_value) return if_block->evaluate();
    else return else_block->evaluate();
    variables.exit_current_scope();
}

SyntaxTreeNode::EvaluationResult LoopNode::evaluate() {
    variables.enter_new_scope();
    EvaluationResult result;
    int iterations_value = iterations->evaluate().expression_value;
    for (int i = 0; i < iterations_value; i++) {
        EvaluationResult current_iteration_result = body->evaluate();
        if (current_iteration_result.should_return) {
            result.should_return = true;
            result.return_value = current_iteration_result.return_value;
        }
    }
    variables.exit_current_scope();
    return result;
}

SyntaxTreeNode::EvaluationResult FunctionNode::evaluate() {
    variables.enter_new_scope();

    for (std::pair<std::string, int> argument : arguments) {
        std::string& variable_name = argument.first;
        int value = argument.second; 
        variables.assign_variable_and_initialize_if_necessary(variable_name, value);
    }

    EvaluationResult result = body->evaluate();

    variables.exit_current_scope();
    return result;
}

SyntaxTreeNode::EvaluationResult EmptyNode::evaluate() {
    EvaluationResult result;
    return result;
}