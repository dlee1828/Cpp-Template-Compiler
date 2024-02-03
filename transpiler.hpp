#ifndef TRANSPILER_H
#define TRANSPILER_H
#include <string>
#include "interpreter.hpp"
#include "syntax-tree.hpp"
#include "template-struct.hpp"

class Transpiler {
private:
    std::vector<TS::TemplateStruct*> all_template_structs;

    std::string input_file_path;
    std::ofstream output;
    struct OperationDetails {
        std::string name;
        std::string expression;
    };
    OperationDetails get_binary_operation_details(BinaryOperation operation);
    std::string binary_operation_to_struct_definition(BinaryOperation operation);

    void new_template_struct(TS::TemplateStruct* template_struct);

    TS::RValue* get_operand_rvalue(OperandNode* operand_node, TS::TemplateStruct* template_struct);

    void write_binary_operator_structs();
    void process_assignment_node(AssignmentNode* node, TS::TemplateStruct* template_struct);
    void process_statement_sequence_node(StatementSequenceNode* node, TS::TemplateStruct* template_struct); 
    void process_syntax_tree_node(SyntaxTreeNode* node, TS::TemplateStruct* template_struct);

public:
    Transpiler(std::string input_file_path) : input_file_path(input_file_path) {}
    void run();
};
#endif
