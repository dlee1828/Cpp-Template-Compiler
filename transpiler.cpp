#include <iostream>
#include <format>
#include "transpiler.hpp"
#include "debug.hpp"
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

void Transpiler::run() {
    Interpreter interpreter(input_file_path);
    SyntaxTreeNode* root_node = interpreter.generate_syntax_tree();
    output.open("output.cpp");
    write_binary_operator_structs();
    output.close();
}