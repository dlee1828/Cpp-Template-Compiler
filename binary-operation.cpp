#include "binary-operation.hpp"
#include <iostream>

BinaryOperationDetails get_binary_operation_details(BinaryOperation operation) {
    switch (operation) {
        case BinaryOperation::ADD:
            return BinaryOperationDetails{.symbol = "+"};
        case BinaryOperation::SUBTRACT:
            return BinaryOperationDetails{.symbol = "-"};
        case BinaryOperation::MULTIPLY:
            return BinaryOperationDetails{.symbol = "*"};
        case BinaryOperation::DIVIDE:
            return BinaryOperationDetails{.symbol = "/"};
        case BinaryOperation::MOD:
            return BinaryOperationDetails{.symbol = "%"};
        case BinaryOperation::LESS:
            return BinaryOperationDetails{.symbol = "<"};
        case BinaryOperation::LESS_EQUAL:
            return BinaryOperationDetails{.symbol = "<="};
        case BinaryOperation::GREATER:
            return BinaryOperationDetails{.symbol = ">"};
        case BinaryOperation::GREATER_EQUAL:
            return BinaryOperationDetails{.symbol = ">="};
        case BinaryOperation::EQUAL:
            return BinaryOperationDetails{.symbol = "=="};
        case BinaryOperation::NOT_EQUAL:
            return BinaryOperationDetails{.symbol = "!="};
        case BinaryOperation::AND:
            return BinaryOperationDetails{.symbol = "&&"};
        case BinaryOperation::OR:
            return BinaryOperationDetails{.symbol = "||"};
        default: {
            std::cerr << "Binary operation not handled\n";
            throw std::exception();
        }
    }
}
