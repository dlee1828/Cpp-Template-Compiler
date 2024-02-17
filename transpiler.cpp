#include "binary-operation.hpp"
#include <iostream>
#include <format>
#include "transpiler.hpp"
#include "debug.hpp"
#include "template-struct.hpp"
#include <fstream>

std::string Transpiler::create_unique_struct_name(std::string base_name) {
    std::string unique_name = base_name + "_" + std::to_string(this->unique_struct_name_counter);
    this->unique_struct_name_counter++;
    return unique_name;
}

TS::TemplateStruct* Transpiler::get_binary_operation_template_struct(BinaryOperation operation) {
    TS::TemplateStruct* template_struct = new TS::TemplateStruct(get_binary_operation_details(operation).name, {"x", "y"});
    TS::RValue* binary_operation_rvalue = new TS::BinaryOperationRValue(operation, new TS::InternalVariable("x"), new TS::InternalVariable("y"));
    template_struct->add_assignment_statement("value", binary_operation_rvalue);
    return template_struct;
}

void Transpiler::create_binary_operation_template_structs() {
    print("creating binary operation template structs");
    for (int i = 0; i < BinaryOperation::_END; i++) {
        BinaryOperation operation = static_cast<BinaryOperation>(i);
        TS::TemplateStruct* template_struct = get_binary_operation_template_struct(operation);
        binary_operation_template_structs[operation] = template_struct;
        all_template_structs.push_back(template_struct);
    }
}

TS::RValue* Transpiler::get_rvalue_from_operand(OperandNode* operand_node, TS::TemplateStruct* template_struct) {
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
    TS::RValue* left_rvalue = get_rvalue_from_operand(dynamic_cast<OperandNode*>(node->left_operand), template_struct);
    TS::RValue* right_rvalue = get_rvalue_from_operand(dynamic_cast<OperandNode*>(node->right_operand), template_struct);
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
            rvalue = get_rvalue_from_operand(operand_node, template_struct);
            break;
        }
        case SyntaxTreeNodeType::BINARY_OPERATION: {
            print("Assignment value node type is binary operation");
            BinaryOperationNode* binary_operation_node = dynamic_cast<BinaryOperationNode*>(value_node);
            rvalue = get_rvalue_from_binary_operation_node(binary_operation_node, template_struct);
            break;
        }
        case SyntaxTreeNodeType::FUNCTION_CALL: {
            print("Assignment value node type is function call");
            FunctionCallNode* function_call_node = dynamic_cast<FunctionCallNode*>(value_node);
            rvalue = get_rvalue_from_function_call_node(function_call_node, template_struct);
            break;
        }
        default: {
            std::cerr << "Unhandled assignment value node type";
            std::cout << value_node->node_type << std::endl;
            throw std::exception();
            break;
        }
    }
    print("Finished processing assignment node, about to add statement");
    template_struct->add_assignment_statement(variable_name, rvalue);
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

    std::string if_else_struct_name = this->create_unique_struct_name("if_else");

    TS::TemplateStruct* base_body_template_struct = new TS::TemplateStruct(if_else_struct_name, {"condition_value"}, {}, template_struct);
    base_body_template_struct->add_final_value_assignments();

    TS::TemplateStruct* if_body_template_struct = new TS::TemplateStruct(if_else_struct_name, {}, {"1"}, template_struct);
    process_syntax_tree_node(node->if_block, if_body_template_struct);
    if_body_template_struct->add_final_value_assignments();

    all_template_structs.push_back(base_body_template_struct);
    all_template_structs.push_back(if_body_template_struct);

    TS::TemplateStruct* else_body_template_struct = nullptr;
    if (node->else_block->node_type != SyntaxTreeNodeType::EMPTY) {
        else_body_template_struct = new TS::TemplateStruct(if_else_struct_name, {}, {"0"}, template_struct);
        process_syntax_tree_node(node->else_block, else_body_template_struct);
        else_body_template_struct->add_final_value_assignments();
        all_template_structs.push_back(else_body_template_struct);
    }

    std::vector<TS::RValue*> local_variable_rvalues = template_struct->get_all_local_variable_rvalues();
    template_struct->retrieve_local_variables_from_child(base_body_template_struct, {condition_rvalue});

    std::vector<TS::RValue*> extended_template_arguments = {condition_rvalue};
    extended_template_arguments.insert(extended_template_arguments.end(), local_variable_rvalues.begin(), local_variable_rvalues.end());
    template_struct->add_external_print_all_statement(base_body_template_struct, extended_template_arguments);

    print("Successfully processed if else node");
}

void Transpiler::process_while_node(WhileNode* node, TS::TemplateStruct* template_struct) {
    BinaryOperationNode* condition = dynamic_cast<BinaryOperationNode*>(node->condition);

    std::string while_parent_struct_name = this->create_unique_struct_name("while_parent");
    TS::TemplateStruct* while_parent_struct = new TS::TemplateStruct(while_parent_struct_name, {"condition"}, {}, template_struct);

    TS::TemplateStruct* while_parent_false_struct = new TS::TemplateStruct(while_parent_struct_name, {}, {"0"}, template_struct);
    while_parent_false_struct->add_final_value_assignments();

    std::string while_body_struct_name = this->create_unique_struct_name("while_body");
    std::set<std::string> condition_set;
    TS::TemplateStruct* while_body_struct = new TS::TemplateStruct(while_body_struct_name, {}, {}, while_parent_struct, {"condition"});
    this->process_syntax_tree_node(node->body, while_body_struct);
    while_body_struct->add_final_value_assignments();

    // manually write the recursive statements for while_parent_struct
    std::vector<std::string> unversioned_variables = while_parent_struct->get_all_unversioned_variable_names();
    std::vector<std::string> unversioned_variables_excluding_condition = {};
    for (std::string variable : unversioned_variables) {
        if (variable != "condition") unversioned_variables_excluding_condition.push_back(variable);
    }

    std::vector<TS::RValue*> while_body_template_arguments;
    for (std::string variable : unversioned_variables_excluding_condition) {
        while_body_template_arguments.push_back(new TS::InternalVariable(while_parent_struct->get_versioned_variable_name(variable)));
    }

    BinaryOperationNode* condition_node = dynamic_cast<BinaryOperationNode*>(node->condition);
    TS::RValue* left_rvalue = get_rvalue_from_operand(dynamic_cast<OperandNode*>(condition_node->left_operand), while_parent_struct);
    TS::RValue* right_rvalue = get_rvalue_from_operand(dynamic_cast<OperandNode*>(condition_node->right_operand), while_parent_struct);
    if (left_rvalue->type == TS::RValueType::INTERNAL_VARIABLE) {
        std::string unversioned_variable_name = dynamic_cast<OperandNode*>(condition_node->left_operand)->identifier_value;
        left_rvalue = new TS::ExternalVariable(unversioned_variable_name, while_body_struct, while_body_template_arguments);
    }
    if (right_rvalue->type == TS::RValueType::INTERNAL_VARIABLE) {
        std::string unversioned_variable_name = dynamic_cast<OperandNode*>(condition_node->right_operand)->identifier_value;
        right_rvalue = new TS::ExternalVariable(unversioned_variable_name, while_body_struct, while_body_template_arguments);
    }
    TS::RValue* condition_rvalue_in_parent_struct = new TS::ExternalVariable("value", binary_operation_template_structs[condition->operation], {left_rvalue, right_rvalue});

    std::vector<TS::RValue*> while_parent_template_arguments = {condition_rvalue_in_parent_struct};
    for (std::string variable : unversioned_variables_excluding_condition) {
        while_parent_template_arguments.push_back(
            new TS::ExternalVariable(variable, while_body_struct, while_body_template_arguments)
        );
    }

    while_parent_struct->set_values_as_final();
    while_parent_struct->add_external_print_all_statement(while_body_struct, {while_body_template_arguments});
    for (std::string variable : unversioned_variables_excluding_condition) {
        TS::RValue* rvalue = new TS::ExternalVariable(variable, while_parent_struct, while_parent_template_arguments);
        while_parent_struct->add_assignment_statement(variable, rvalue);
    }

    all_template_structs.push_back(while_body_struct);
    all_template_structs.push_back(while_parent_struct);
    all_template_structs.push_back(while_parent_false_struct);

    TS::RValue* condition_rvalue_in_outer_struct = this->get_rvalue_from_binary_operation_node(condition, template_struct);
    template_struct->retrieve_local_variables_from_child(while_parent_struct, {condition_rvalue_in_outer_struct});
    // template_struct->add_external_print_all_statement(while_parent_struct, {condition_rvalue_in_outer_struct}, template_struct);
}

void Transpiler::process_lone_function_call_node(FunctionCallNode* node, TS::TemplateStruct* template_struct) {
    // todo later
    return;
}

TS::RValue* Transpiler::get_rvalue_from_function_call_node(FunctionCallNode* node, TS::TemplateStruct* template_struct) {
    TS::TemplateStruct* function_template_struct = function_template_struct_map[node->function_name];
    // Get return value if it exists
    bool has_return_value = false;
    for (std::string unversioned_variable_name : function_template_struct->get_all_unversioned_variable_names()) {
        if (unversioned_variable_name == "_return_value") {
            has_return_value = true;
            break;
        }
    }
    if (!has_return_value) function_template_struct->add_assignment_statement("_return_value", new TS::Literal(0));

    std::vector<TS::RValue*> function_argument_rvalues;
    for (auto [_, argument_node] : node->arguments) {
        // will be in alphabetical order, so can safely pass to template arguments 
        function_argument_rvalues.push_back(get_rvalue_from_operand(dynamic_cast<OperandNode*>(argument_node), template_struct));
    }

    TS::RValue* return_value_rvalue = new TS::ExternalVariable("_return_value", function_template_struct, function_argument_rvalues);

    return return_value_rvalue;
}

TS::RValue* Transpiler::get_rvalue_from_syntax_tree_node(SyntaxTreeNode* node, TS::TemplateStruct* template_struct) {
    TS::RValue* rvalue;
    switch(node->node_type) {
        case SyntaxTreeNodeType::OPERAND: {
            rvalue = get_rvalue_from_operand(dynamic_cast<OperandNode*>(node), template_struct);
            break;
        }
        case SyntaxTreeNodeType::BINARY_OPERATION: {
            rvalue = get_rvalue_from_binary_operation_node(dynamic_cast<BinaryOperationNode*>(node), template_struct);
            break;
        }
        case SyntaxTreeNodeType::FUNCTION_CALL: {
            rvalue = get_rvalue_from_function_call_node(dynamic_cast<FunctionCallNode*>(node), template_struct);
            break;
        }
        default : {
            print("error: node type not handled in get_rvalue_from_syntax_tree_node");
            throw std::exception();
        }
    }
    return rvalue;
}

void Transpiler::process_return_node(ReturnNode* node, TS::TemplateStruct* template_struct) {
    TS::RValue* rvalue = get_rvalue_from_syntax_tree_node(node->value, template_struct);
    template_struct->add_assignment_statement("_return_value", rvalue);
    template_struct->add_final_value_assignments();
}

void Transpiler::process_print_node(PrintNode* node, TS::TemplateStruct* template_struct) {
    TS::RValue* rvalue = get_rvalue_from_syntax_tree_node(node->value, template_struct);
    template_struct->add_print_statement(rvalue);
}

void Transpiler::process_syntax_tree_node(SyntaxTreeNode* node, TS::TemplateStruct* template_struct) {
    switch (node->node_type) {
        case SyntaxTreeNodeType::ASSIGNMENT:
            return process_assignment_node(dynamic_cast<AssignmentNode*>(node), template_struct);
        case SyntaxTreeNodeType::STATEMENT_SEQUENCE:
            return process_statement_sequence_node(dynamic_cast<StatementSequenceNode*>(node), template_struct);
        case SyntaxTreeNodeType::IF_ELSE:
            return process_if_else_node(dynamic_cast<IfElseNode*>(node), template_struct);
        case SyntaxTreeNodeType::WHILE:
            return process_while_node(dynamic_cast<WhileNode*>(node), template_struct);
        case SyntaxTreeNodeType::FUNCTION_CALL:
            return process_lone_function_call_node(dynamic_cast<FunctionCallNode*>(node), template_struct); 
        case SyntaxTreeNodeType::RETURN:
            return process_return_node(dynamic_cast<ReturnNode*>(node), template_struct);
        case SyntaxTreeNodeType::PRINT:
            return process_print_node(dynamic_cast<PrintNode*>(node), template_struct);
        case SyntaxTreeNodeType::EMPTY:
            return;
        default: {
            std::cerr << "Syntax tree node type not handled\n";
            throw std::exception();
        }
    }
}

void Transpiler::create_function_definition_template_structs() {
    for (auto [function_name, function_data] : this->function_data_map) {
        SyntaxTreeNode* function_body = function_data.body;
        std::vector<std::string> function_parameters = function_data.parameters;
        TS::TemplateStruct* function_definition_template_struct = new TS::TemplateStruct(
            "FUNCTION_" + function_name,
            function_parameters
        );
        process_syntax_tree_node(function_body, function_definition_template_struct);
        function_template_struct_map[function_name] = function_definition_template_struct;
        this->all_template_structs.push_back(function_definition_template_struct);
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
    this->function_data_map = interpreter.get_function_map();
    this->create_function_definition_template_structs();

    TS::TemplateStruct* root_template_struct = new TS::TemplateStruct("root");

    process_syntax_tree_node(root_node, root_template_struct);

    all_template_structs.push_back(root_template_struct);

    output.open("output.cpp");

    output << "#include <iostream>\n\n";

    print("printing all template structs");
    print_all_template_structs();
    print("finished printing all template structs");

    output.close();
}