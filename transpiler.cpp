#include <iostream>
#include <format>
#include "transpiler.hpp"
#include "debug.hpp"
#include "template-struct.hpp"
#include <fstream>

Transpiler::OperationDetails Transpiler::get_binary_operation_details(BinaryOperation operation) {
    switch(operation) {
        case BinaryOperation::ADD:
            return {
                .name = "ADD",
                .expression = "x + y"
            };
        case BinaryOperation::SUBTRACT:
            return {
                .name = "SUBTRACT",
                .expression = "x - y"
            };
        case BinaryOperation::MULTIPLY:
            return {
                .name = "MULTIPLY",
                .expression = "x * y"
            };
        case BinaryOperation::DIVIDE:
            return {
                .name = "DIVIDE",
                .expression = "x / y"
            };
        case BinaryOperation::MOD:
            return {
                .name = "MOD",
                .expression = "x % y"
            };
        case BinaryOperation::LESS:
            return {
                .name = "LESS",
                .expression = "x < y"
            };
        case BinaryOperation::LESS_EQUAL:
            return {
                .name = "LESS_EQUAL",
                .expression = "x <= y"
            };
        case BinaryOperation::GREATER:
            return {
                .name = "GREATER",
                .expression = "x > y"
            };
        case BinaryOperation::GREATER_EQUAL:
            return {
                .name = "GREATER_EQUAL",
                .expression = "x >= y"
            };
        case BinaryOperation::EQUAL:
            return {
                .name = "EQUAL",
                .expression = "x == y"
            };
        case BinaryOperation::NOT_EQUAL:
            return {
                .name = "NOT_EQUAL",
                .expression = "x != y"
            };
        case BinaryOperation::AND:
            return {
                .name = "AND",
                .expression = "(x != 0) && (y != 0)"
            };
        case BinaryOperation::OR:
            return {
                .name = "OR",
                .expression = "(x != 0) || (y != 0)"
            };
    }
}

std::string Transpiler::binary_operation_to_struct_definition(BinaryOperation operation) {
    OperationDetails operation_details = get_binary_operation_details(operation);
    std::string definition = 
        "template <int x, int y>\n" + 
        ("struct BINARY_OPERATION_" + operation_details.name + " {\n") + 
        ("\tstatic constexpr int value = " + operation_details.expression + ";\n") +
        "};\n";
    return definition;
};

/*
a = 1 ->
struct scope_1 {
    constexpr int a =  1;
}

a = 1
if (a == 1) {
    b = 2
} else {
    b = 1
}

* struct for a = 1 (main scope)
* struct for condition (_ == 1)
* struct for true-body 
* struct for false-body
* copy all the body-struct-variables into the main scope 

Okay. So when we write the function for processing an if-else node, we need to pass:
* the if-else-node
* a reference to the outer-scope struct
* All the necessary outer-scope variables that need to be passed in
* that's all (?)

So in general, we will maintain a vector of these struct-objects, and there will be 
parent/child relationships between certain ones

The main data-transfer between these struct-objects is the passing of variables

E.g.
struct scope_1 {
    int a_1 = 2
    int a_2 = scope_2::a_2
}

So how will we handle this variable naming stuff?
Within each struct-object have a list of variable names which are the ones inherited from the outer scope?
Also keep track of current latest variable version?
*/
void Transpiler::write_binary_operator_structs() {
    for (int i = 0; i < 12; i++) {
        BinaryOperation operation = static_cast<BinaryOperation>(i);
        std::string definition = binary_operation_to_struct_definition(operation);
        output << definition << std::endl;
    }
}

void Transpiler::new_template_struct(TS::TemplateStruct* template_struct) {
    all_template_structs.push_back(template_struct);
}

TS::RValue* Transpiler::get_operand_rvalue(OperandNode* operand_node, TS::TemplateStruct* template_struct) {
    if (operand_node->operand_type == OperandType::IDENTIFIER) {
        std::string& identifer_value = operand_node->identifier_value;
        std::string versioned = template_struct->get_versioned_variable_name(identifer_value);
        return new TS::InternalVariable(versioned);
    } else if (operand_node->operand_type == OperandType::LITERAL) {
        return new TS::Literal(operand_node->literal_value);
    } else {
        std::cerr << "Operand node type not handled\n"; 
        throw std::exception();
    }
}

void Transpiler::process_assignment_node(AssignmentNode* node, TS::TemplateStruct* template_struct) {
    std::string& variable_name = node->variable_name;
    SyntaxTreeNode* value_node = node->value;
    TS::RValue* rvalue = nullptr;
    switch (value_node->node_type) {
        case SyntaxTreeNodeType::OPERAND: {
            OperandNode* operand_node = dynamic_cast<OperandNode*>(value_node);
            rvalue = get_operand_rvalue(operand_node, template_struct);
            break;
        }
        case SyntaxTreeNodeType::BINARY_OPERATION: {
            BinaryOperationNode* binary_operation_node = dynamic_cast<BinaryOperationNode*>(value_node);
            TS::RValue* left_rvalue = get_operand_rvalue(dynamic_cast<OperandNode*>(binary_operation_node->left_operand), template_struct);
            TS::RValue* right_rvalue = get_operand_rvalue(dynamic_cast<OperandNode*>(binary_operation_node->right_operand), template_struct);
            break;
        }
    }

    std::string versioned_variable_name = template_struct->add_or_update_variable(variable_name);

    template_struct->add_statement(TS::Statement(versioned_variable_name, rvalue));
}

void Transpiler::process_statement_sequence_node(StatementSequenceNode* node, TS::TemplateStruct* template_struct) {
    for (SyntaxTreeNode* node : node->statements) 
        process_syntax_tree_node(node, template_struct);
}

void Transpiler::process_syntax_tree_node(SyntaxTreeNode* node, TS::TemplateStruct* template_struct) {
    switch (node->node_type) {
        case SyntaxTreeNodeType::ASSIGNMENT:
            return process_assignment_node(dynamic_cast<AssignmentNode*>(node), template_struct);
        case SyntaxTreeNodeType::STATEMENT_SEQUENCE:
            return process_statement_sequence_node(dynamic_cast<StatementSequenceNode*>(node), template_struct);
        default: {
            std::cerr << "Syntax tree node type not handled\n";
            throw std::exception();
        }
    }
}

void Transpiler::run() {
    Interpreter interpreter(input_file_path);
    SyntaxTreeNode* root_node = interpreter.generate_syntax_tree();

    TS::TemplateStruct* root_template_struct = new TS::TemplateStruct();
    new_template_struct(root_template_struct);

    process_syntax_tree_node(root_node, root_template_struct);

    output.open("output.cpp");
    write_binary_operator_structs();

    root_template_struct->write_to_file(output, "root_scope");

    output.close();
}