#ifndef TRANSPILER_H
#define TRANSPILER_H
#include <string>
#include <map>
#include "interpreter.hpp"
#include "syntax-tree.hpp"
#include "template-struct.hpp"

class Transpiler {
private:
    Interpreter::FunctionDataMap function_data_map;
    std::map<std::string, TS::TemplateStruct*> function_template_struct_map;
    std::vector<TS::TemplateStruct*> all_template_structs;
    std::map<BinaryOperation, TS::TemplateStruct*> binary_operation_template_structs;
    std::string input_file_path;
    std::ofstream output;
    TS::TemplateStruct* print_wrapper_template_struct = nullptr;
    TS::TemplateStruct* return_wrapper_template_struct = nullptr;

    TS::TemplateStruct* get_binary_operation_template_struct(BinaryOperation operation);

    TS::RValue* get_rvalue_from_operand(OperandNode* operand_node, TS::TemplateStruct* template_struct);

    TS::RValue* get_rvalue_from_binary_operation_node(BinaryOperationNode* node, TS::TemplateStruct* template_struct);

    void create_binary_operation_template_structs();
    void create_function_definition_template_structs();
    void create_print_wrapper_template_struct();
    void create_return_wrapper_template_struct();
    void process_assignment_node(AssignmentNode* node, TS::TemplateStruct* template_struct);
    void process_statement_sequence_node(StatementSequenceNode* node, TS::TemplateStruct* template_struct); 
    void process_if_else_node(IfElseNode* node, TS::TemplateStruct* template_struct);
    void process_while_node(WhileNode* node, TS::TemplateStruct* template_struct);
    std::vector<TS::RValue*> get_function_argument_rvalues(FunctionCallNode* function_call_node, TS::TemplateStruct* template_struct);
    TS::RValue* get_rvalue_from_function_call_node(FunctionCallNode* node, TS::TemplateStruct* template_struct);
    TS::RValue* get_rvalue_from_syntax_tree_node(SyntaxTreeNode* node, TS::TemplateStruct* template_struct);
    void add_external_print_statement_for_function_call(FunctionCallNode* function_call_node, TS::TemplateStruct* template_struct);
    void process_lone_function_call_node(FunctionCallNode* node, TS::TemplateStruct* template_struct);
    void process_return_node(ReturnNode* node, TS::TemplateStruct* template_struct);
    void process_print_node(PrintNode* node, TS::TemplateStruct* template_struct);
    void process_syntax_tree_node(SyntaxTreeNode* node, TS::TemplateStruct* template_struct);
    void generate_output_file();

    int unique_struct_name_counter = 0;
    std::string create_unique_struct_name(std::string base_name);

public:
    Transpiler(std::string input_file_path) : input_file_path(input_file_path) {}
    void run();
};

#endif
