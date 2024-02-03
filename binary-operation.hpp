// IMPROVE: migrate all binary operation stuff into this file

enum BinaryOperation {
    ADD, SUBTRACT, MULTIPLY, DIVIDE, MOD, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL, EQUAL, NOT_EQUAL, AND, OR, _END
};

struct BinaryOperationDetails {
    std::string symbol;
};

BinaryOperationDetails get_binary_operation_details(BinaryOperation operation);
