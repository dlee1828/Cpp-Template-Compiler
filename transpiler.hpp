#ifndef TRANSPILER_H
#define TRANSPILER_H
#include <string>
#include "interpreter.hpp"
#include "syntax-tree.hpp"

class Transpiler {
private:
    std::string input_file_path;
    std::ofstream output;
    struct OperationDetails {
        std::string name;
        std::string expression;
    };
    OperationDetails get_binary_operation_details(BinaryOperation operation);
    std::string binary_operation_to_struct_definition(BinaryOperation operation);
    void write_binary_operator_structs();

public:
    Transpiler(std::string input_file_path) : input_file_path(input_file_path) {}
    void run();
};

#endif
