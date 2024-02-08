#include "binary-operation.hpp"
#include <iostream>
#include <format>
#include "transpiler.hpp"
#include "debug.hpp"
#include "template-struct.hpp"
#include <fstream>

TS::TemplateStruct* Transpiler::get_binary_operation_template_struct(BinaryOperation operation) {
    TS::TemplateStruct* template_struct = new TS::TemplateStruct(get_binary_operation_details(operation).name, {"x", "y"});
    TS::RValue* binary_operation_rvalue = new TS::BinaryOperationRValue(operation, new TS::InternalVariable("x"), new TS::InternalVariable("y"));
    template_struct->add_statement("value", binary_operation_rvalue);
    return template_struct;
}

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
void Transpiler::create_binary_operation_template_structs() {
    print("creating binary operation template structs");
    for (int i = 0; i < BinaryOperation::_END; i++) {
        BinaryOperation operation = static_cast<BinaryOperation>(i);
        TS::TemplateStruct* template_struct = get_binary_operation_template_struct(operation);
        binary_operation_template_structs[operation] = template_struct;
        all_template_structs.push_back(template_struct);
    }
}

void Transpiler::new_template_struct(TS::TemplateStruct* template_struct) {
    all_template_structs.push_back(template_struct);
}

TS::RValue* Transpiler::get_operand_rvalue(OperandNode* operand_node, TS::TemplateStruct* template_struct) {
    print("Getting operand rvalue");
    if (operand_node->operand_type == OperandType::IDENTIFIER) {
        print("Operand has type identifier");
        std::string& identifer_value = operand_node->identifier_value;
        std::string versioned = template_struct->get_versioned_variable_name(identifer_value);
        return new TS::InternalVariable(versioned);
    } else if (operand_node->operand_type == OperandType::LITERAL) {
        print("Operand has type literal");
        return new TS::Literal(operand_node->literal_value);
    } else {
        std::cerr << "Operand node type not handled\n"; 
        throw std::exception();
    }
}

TS::RValue* Transpiler::get_rvalue_from_binary_operation_node(BinaryOperationNode* node, TS::TemplateStruct* template_struct) {
    print("Getting rvalue from binary operation node");
    TS::RValue* left_rvalue = get_operand_rvalue(dynamic_cast<OperandNode*>(node->left_operand), template_struct);
    TS::RValue* right_rvalue = get_operand_rvalue(dynamic_cast<OperandNode*>(node->right_operand), template_struct);
    return new TS::ExternalVariable("value", binary_operation_template_structs[node->operation], {left_rvalue, right_rvalue});
}

void Transpiler::process_assignment_node(AssignmentNode* node, TS::TemplateStruct* template_struct) {
    print("> Processing assignment node");
    std::string& variable_name = node->variable_name;
    SyntaxTreeNode* value_node = node->value;
    TS::RValue* rvalue = nullptr;
    switch (value_node->node_type) {
        case SyntaxTreeNodeType::OPERAND: {
            print("Assignment value node type is operand");
            OperandNode* operand_node = dynamic_cast<OperandNode*>(value_node);
            rvalue = get_operand_rvalue(operand_node, template_struct);
            break;
        }
        case SyntaxTreeNodeType::BINARY_OPERATION: {
            print("Assignment value node type is binary operation");
            BinaryOperationNode* binary_operation_node = dynamic_cast<BinaryOperationNode*>(value_node);
            rvalue = get_rvalue_from_binary_operation_node(binary_operation_node, template_struct);
            break;
        }
        default: {
            std::cerr << "Unhandled assignment value node type";
            throw std::exception();
            break;
        }
    }
    print("Finished processing assignment node, about to add statement");
    template_struct->add_statement(variable_name, rvalue);
}

void Transpiler::process_statement_sequence_node(StatementSequenceNode* node, TS::TemplateStruct* template_struct) {
    print("> Processing statement sequence node");
    for (SyntaxTreeNode* node : node->statements) 
        process_syntax_tree_node(node, template_struct);
}

void Transpiler::process_if_else_node(IfElseNode* node, TS::TemplateStruct* template_struct) {
    print("> Processing if else node");
    // assume condition is a binary operation node
    BinaryOperationNode* condition = dynamic_cast<BinaryOperationNode*>(node->condition);
    TS::RValue* condition_rvalue = get_rvalue_from_binary_operation_node(condition, template_struct);
    print("Finished getting rvalue from binary operation node");

    TS::TemplateStruct* base_body_template_struct = new TS::TemplateStruct("if_else", {"condition_value"}, {}, template_struct);
    print("Printing template parameters for base body template struct");
    for (auto s : base_body_template_struct->get_template_parameters()) {
        print(s);
    }

    TS::TemplateStruct* if_body_template_struct = new TS::TemplateStruct("if_else", {"condition_value"}, {"true"}, template_struct);
    process_syntax_tree_node(node->if_block, if_body_template_struct);

    all_template_structs.push_back(base_body_template_struct);
    all_template_structs.push_back(if_body_template_struct);

    TS::TemplateStruct* else_body_template_struct = nullptr;
    if (node->else_block->node_type != SyntaxTreeNodeType::EMPTY) {
        else_body_template_struct = new TS::TemplateStruct("if_else", {"condition_value"}, {"false"}, template_struct);
        process_syntax_tree_node(node->else_block, else_body_template_struct);
        all_template_structs.push_back(else_body_template_struct);
    }

    // This is a bit of an issue.
    template_struct->retrieve_local_variables_from_child(base_body_template_struct, {condition_rvalue});

    print("Successfully processed if else node");
}

void Transpiler::process_syntax_tree_node(SyntaxTreeNode* node, TS::TemplateStruct* template_struct) {
    switch (node->node_type) {
        case SyntaxTreeNodeType::ASSIGNMENT:
            return process_assignment_node(dynamic_cast<AssignmentNode*>(node), template_struct);
        case SyntaxTreeNodeType::STATEMENT_SEQUENCE:
            return process_statement_sequence_node(dynamic_cast<StatementSequenceNode*>(node), template_struct);
        case SyntaxTreeNodeType::IF_ELSE:
            return process_if_else_node(dynamic_cast<IfElseNode*>(node), template_struct);
        default: {
            std::cerr << "Syntax tree node type not handled\n";
            throw std::exception();
        }
    }
}

void Transpiler::print_all_template_structs() {
    for (TS::TemplateStruct* template_struct : all_template_structs) {
        template_struct->write_to_file(output);
    }
}

void Transpiler::run() {
    create_binary_operation_template_structs();

    Interpreter interpreter(input_file_path);
    SyntaxTreeNode* root_node = interpreter.generate_syntax_tree();
    TS::TemplateStruct* root_template_struct = new TS::TemplateStruct("root");
    new_template_struct(root_template_struct);

    process_syntax_tree_node(root_node, root_template_struct);

    output.open("output.cpp");

    print_all_template_structs();

    output.close();
}