#include "syntax-tree.hpp"
#include "debug.hpp"

std::ostream& operator<<(std::ostream& o, Variables& variables) {
    for (std::pair<std::string, int> map_entry : variables.variable_values) {
        o << map_entry.first << ": " << map_entry.second << std::endl;
    }
    return o;
}

int Variables::get_variable_value(const std::string& variable_name) {
    print("GETTING VARIABLE VALUE OF", variable_name);
    print("STATE OF VARIABLES:", *this);
    int value = variable_values[variable_name];
    print("VALUE WAS", value);
    return value;
}

void Variables::assign_variable_and_initialize_if_necessary(const std::string& variable_name, int value) {
    print("ABOUT TO ACTUALLY ASSIGN VARIABLE", variable_name, "VALUE", value);
    bool need_to_initialize = (variable_values.find(variable_name) == variable_values.end());
    variable_values[variable_name] = value;
    print("JUST ASSIGNED", variable_name, "=", value);
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
        case SyntaxTreeNodeType::STATEMENT_SEQUENCE:
            return "STATEMENT_SEQUENCE";
        case SyntaxTreeNodeType::OPERAND:
            return "OPERAND";
        case SyntaxTreeNodeType::RETURN:
            return "RETURN";
        case SyntaxTreeNodeType::ASSIGNMENT:
            return "ASSIGNMENT";
        case SyntaxTreeNodeType::BINARY_OPERATION:
            return "BINARY_OPERATION";
        case SyntaxTreeNodeType::IF_ELSE:
            return "IF_ELSE";
        case SyntaxTreeNodeType::LOOP:
            return "LOOP";
        case SyntaxTreeNodeType::FUNCTION_CALL:
            return "FUNCTION";
        case SyntaxTreeNodeType::PRINT:
            return "PRINT";
        case SyntaxTreeNodeType::EMPTY:
            return "EMPTY";
        case SyntaxTreeNodeType::WHILE:
            return "WHILE";
    }
}

std::ostream& operator<<(std::ostream& o, const SyntaxTreeNode* node) {
    std::string node_type_string = get_node_type_string_from_enum(node->node_type);
    o << node_type_string << " NODE";
    return o;
}


SyntaxTreeNode::EvaluationResult StatementSequenceNode::evaluate() {
    print("EVALUATING STATEMENT SEQUENCE NODE");
    EvaluationResult result;
    for (SyntaxTreeNode* node : statements) {
        print("WITHIN STATEMENT SEQUENCE NODE, ABOUT TO EVALUATE NODE OF TYPE", get_node_type_string_from_enum(node->node_type));
        print("STATE OF VARIABLES:");
        print(variables);
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
    print("EVALUATING OPERAND NODE OF TYPE", operand_type == IDENTIFIER ? "IDENTIFIER" : "LITERAL");
    EvaluationResult result;
    switch (operand_type) {
        case IDENTIFIER:
            print("IDENTIFIER =", identifier_value);
            result.expression_value = variables.get_variable_value(identifier_value);
            break;
        case LITERAL:
            print("LITERAL =", literal_value);
            result.expression_value = literal_value;
            break;
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
    print("EVALUATING ASSIGNMENT NODE WITH VARIABLE", variable_name);
    EvaluationResult result;
    print("ASSIGNMENT VALUE NODE IS NULL?", value == nullptr ? "YES" : "NO");
    EvaluationResult assignment_value_result = value->evaluate();
    int assignment_value = assignment_value_result.expression_value;
    if (value->node_type == SyntaxTreeNodeType::FUNCTION_CALL) assignment_value = assignment_value_result.return_value;
    print("DERIVED ASSIGNMENT VALUE, ASSIGNMENT VALUE =", assignment_value);
    variables.assign_variable_and_initialize_if_necessary(variable_name, assignment_value);
    result.expression_value = 1;
    return result;
}

SyntaxTreeNode::EvaluationResult BinaryOperationNode::evaluate() {
    print("ABOUT TO EVALUATE BINARY OPERATION NODE");
    EvaluationResult result;
    int left_value = left_operand->evaluate().expression_value;
    int right_value = right_operand->evaluate().expression_value;
    print("EVALUATING BINARY OPERATION NODE FOR", left_value, operation, right_value);

    int expression_value = 0; 
    switch(operation) {
        case BinaryOperation::ADD:
            expression_value = left_value + right_value;
            break;
        case BinaryOperation::SUBTRACT:
            expression_value = left_value - right_value;
            break;
        case BinaryOperation::MULTIPLY:
            expression_value = left_value * right_value;
            break;
        case BinaryOperation::DIVIDE:
            expression_value = left_value / right_value;
            break;
        case BinaryOperation::MOD:
            expression_value = left_value % right_value;
            break;
        case BinaryOperation::LESS:
            expression_value = left_value < right_value;
            break;
        case BinaryOperation::LESS_EQUAL:
            expression_value = left_value <= right_value;
            break;
        case BinaryOperation::GREATER:
            expression_value = left_value > right_value;
            break;
        case BinaryOperation::GREATER_EQUAL:
            expression_value = left_value >= right_value;
            break;
        case BinaryOperation::EQUAL:
            expression_value = left_value == right_value;
            break;
        case BinaryOperation::NOT_EQUAL:
            expression_value = left_value != right_value;
            break;
        case BinaryOperation::AND:
            expression_value = (left_value != 0) && (right_value != 0);
            break;
        case BinaryOperation::OR:
            expression_value = (left_value != 0) || (right_value != 0);
            break;
    }

    print("RESULT OF BINARY OPERATION WAS", expression_value);

    result.expression_value = expression_value;
    print("ABOUT TO RETURN RESULT WITH EXPRESSION VALUE OF", result.expression_value);
    return result;
}

SyntaxTreeNode::EvaluationResult IfElseNode::evaluate() {
    print("EVALUATING IF ELSE NODE");
    variables.enter_new_scope();
    int condition_value = condition->evaluate().expression_value;
    print("CONDITION'S ACTUAL VALUE =", condition_value);
    condition_value ? print("CONDITION WAS TRUE") : print("CONDITION WAS FALSE");
    if (condition_value) return if_block->evaluate();
    else return else_block->evaluate();
    variables.exit_current_scope();
}

SyntaxTreeNode::EvaluationResult LoopNode::evaluate() {
    EvaluationResult result;
    int iterations_value = iterations->evaluate().expression_value;
    for (int i = 0; i < iterations_value; i++) {
        variables.enter_new_scope();
        EvaluationResult current_iteration_result = body->evaluate();
        if (current_iteration_result.should_return) {
            result.should_return = true;
            result.return_value = current_iteration_result.return_value;
            break;
        }
        variables.exit_current_scope();
    }
    return result;
}

SyntaxTreeNode::EvaluationResult FunctionNode::evaluate() {
    print("EVALUATING FUNCTION NODE");
    variables.enter_new_scope();

    for (std::pair<std::string, SyntaxTreeNode*> argument : arguments) {
        std::string& variable_name = argument.first;
        SyntaxTreeNode* node = argument.second; 

        int value = node->evaluate().expression_value;

        variables.assign_variable_and_initialize_if_necessary(variable_name, value);
    }

    EvaluationResult result = body->evaluate();
    result.should_return = false;

    variables.exit_current_scope();
    return result;
}

SyntaxTreeNode::EvaluationResult EmptyNode::evaluate() {
    EvaluationResult result;
    return result;
}

SyntaxTreeNode::EvaluationResult PrintNode::evaluate() {
    EvaluationResult value_result = value->evaluate();
    print("EVALUATING PRINT NODE, VALUE_RESULT =", value_result.expression_value, value_result.return_value);
    int to_print = 0;
    if (value->node_type == FUNCTION_CALL) to_print = value_result.return_value;
    else to_print = value_result.expression_value;
    std::cout << to_print << std::endl;
    return EvaluationResult();
}

SyntaxTreeNode::EvaluationResult WhileNode::evaluate() {
    EvaluationResult result;
    while (condition->evaluate().expression_value == 1) {
        variables.enter_new_scope();
        EvaluationResult current_iteration_result = body->evaluate();
        if (current_iteration_result.should_return) {
            result.should_return = true;
            result.return_value = current_iteration_result.return_value;
            break;
        }
        variables.exit_current_scope();
    }
    return result;
}