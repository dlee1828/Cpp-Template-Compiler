// IMPROVE: migrate all binary operation stuff into this file
#ifndef BINARY_OPERATION_H
#define BINARY_OPERATION_H
#include <string>


enum BinaryOperation {
    ADD, SUBTRACT, MULTIPLY, DIVIDE, MOD, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL, EQUAL, NOT_EQUAL, AND, OR, _END
};

struct BinaryOperationDetails {
    std::string symbol;
    std::string name;
};

BinaryOperationDetails get_binary_operation_details(BinaryOperation operation);

#endif