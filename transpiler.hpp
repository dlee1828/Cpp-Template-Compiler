#ifndef TRANSPILER_H
#define TRANSPILER_H
#include <string>
#include "interpreter.hpp"
#include "syntax-tree.hpp"

class Transpiler {
private:
    std::vector<TS::TemplateStruct> all_template_structs;

    std::string input_file_path;
    std::ofstream output;
    struct OperationDetails {
        std::string name;
        std::string expression;
    };
    OperationDetails get_binary_operation_details(BinaryOperation operation);
    std::string binary_operation_to_struct_definition(BinaryOperation operation);
    void write_binary_operator_structs();
    TS::Statement process_assignment_node(AssignmentNode* node);
    TS::Statement process_statement_node(SyntaxTreeNode* node);
    std::vector<TS::Statement> process_statement_sequence_node(StatementSequenceNode* node); 

public:
    Transpiler(std::string input_file_path) : input_file_path(input_file_path) {}
    void run();
};
#endif
