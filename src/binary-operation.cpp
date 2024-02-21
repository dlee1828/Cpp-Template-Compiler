#include "binary-operation.hpp"
#include "syntax-tree.hpp"
BinaryOperationDetails get_binary_operation_details(BinaryOperation operation) {
    switch (operation) {
        case BinaryOperation::ADD:
            return BinaryOperationDetails{.symbol = "+", .name = "ADD"};
        case BinaryOperation::SUBTRACT:
            return BinaryOperationDetails{.symbol = "-", .name = "SUBTRACT"};
        case BinaryOperation::MULTIPLY:
            return BinaryOperationDetails{.symbol = "*", .name = "MULTIPLY"};
        case BinaryOperation::DIVIDE:
            return BinaryOperationDetails{.symbol = "/", .name = "DIVIDE"};
        case BinaryOperation::MOD:
            return BinaryOperationDetails{.symbol = "%", .name = "MOD"};
        case BinaryOperation::LESS:
            return BinaryOperationDetails{.symbol = "<", .name = "LESS"};
        case BinaryOperation::LESS_EQUAL:
            return BinaryOperationDetails{.symbol = "<=", .name = "LESS_EQUAL"};
        case BinaryOperation::GREATER:
            return BinaryOperationDetails{.symbol = ">", .name = "GREATER"};
        case BinaryOperation::GREATER_EQUAL:
            return BinaryOperationDetails{.symbol = ">=", .name = "GREATER_EQUAL"};
        case BinaryOperation::EQUAL:
            return BinaryOperationDetails{.symbol = "==", .name = "EQUAL"};
        case BinaryOperation::NOT_EQUAL:
            return BinaryOperationDetails{.symbol = "!=", .name = "NOT_EQUAL"};
        case BinaryOperation::AND:
            return BinaryOperationDetails{.symbol = "&&", .name = "AND"};
        case BinaryOperation::OR:
            return BinaryOperationDetails{.symbol = "||", .name = "OR"};
        default: {
            std::cerr << "Binary operation not handled\n";
            throw std::exception();
        }
    }
}
