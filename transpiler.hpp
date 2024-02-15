#ifndef TRANSPILER_H
#define TRANSPILER_H
#include <string>
#include <map>
#include "interpreter.hpp"
#include "syntax-tree.hpp"
#include "template-struct.hpp"

class Transpiler {
private:
    std::vector<TS::TemplateStruct*> all_template_structs;
    std::map<BinaryOperation, TS::TemplateStruct*> binary_operation_template_structs;
    std::string input_file_path;
    std::ofstream output;
    TS::TemplateStruct* get_binary_operation_template_struct(BinaryOperation operation);

    TS::RValue* get_operand_rvalue(OperandNode* operand_node, TS::TemplateStruct* template_struct);

    TS::RValue* get_rvalue_from_binary_operation_node(BinaryOperationNode* node, TS::TemplateStruct* template_struct);

    void create_binary_operation_template_structs();
    void process_assignment_node(AssignmentNode* node, TS::TemplateStruct* template_struct);
    void process_statement_sequence_node(StatementSequenceNode* node, TS::TemplateStruct* template_struct); 
    void process_if_else_node(IfElseNode* node, TS::TemplateStruct* template_struct);
    void process_while_node(WhileNode* node, TS::TemplateStruct* template_struct);
    void process_syntax_tree_node(SyntaxTreeNode* node, TS::TemplateStruct* template_struct);
    void print_all_template_structs();

    int unique_struct_name_counter = 0;
    std::string create_unique_struct_name(std::string base_name);

public:
    Transpiler(std::string input_file_path) : input_file_path(input_file_path) {}
    void run();
};

#endif
