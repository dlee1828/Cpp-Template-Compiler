#ifndef TEMPLATE_STRUCT_H
#define TEMPLATE_STRUCT_H

#include <vector>
#include <string>

namespace TS {
    enum RValueType {
        LITERAL, INTERNAL_VARIABLE, EXTERNAL_VARIABLE
    };

    struct RValue {
        RValueType type;
        RValue(RValueType type) : type(type) {}
    };

    class Literal : RValue {
        int value;
        Literal(int value) : RValue(RValueType::LITERAL), value(value) {}
    };

    class InternalVariable : RValue {
        std::string variable_name;
        InternalVariable(std::string variable_name) : RValue(RValueType::INTERNAL_VARIABLE), variable_name(variable_name) {}
    };

    class ExternalVariable : RValue {
        std::string variable_name;
        std::string external_ts_name;
        ExternalVariable(std::string variable_name, std::string external_ts_name) : RValue(RValueType::INTERNAL_VARIABLE), variable_name(variable_name), external_ts_name(external_ts_name) {}
    };

    class Statement {
    private:
        std::string variable_name;

    };

    class TemplateStruct {
    private:
        std::vector<std::string> template_parameters;


    public:
    };
}
#endif