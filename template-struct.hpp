#ifndef TEMPLATE_STRUCT_H
#define TEMPLATE_STRUCT_H

#include <vector>
#include <string>

namespace TS {
    enum RValueType {
        LITERAL, INTERNAL_VARIABLE, EXTERNAL_VARIABLE, UNDEFINED
    };

    struct RValue {
        RValueType type;
        RValue(RValueType type) : type(type) {}
    };

    struct Literal : RValue {
        int value;
        Literal(int value) : RValue(RValueType::LITERAL), value(value) {}
    };

    struct InternalVariable : RValue {
        std::string variable_name;
        InternalVariable(std::string variable_name) : RValue(RValueType::INTERNAL_VARIABLE), variable_name(variable_name) {}
    };

    struct ExternalVariable : RValue {
        std::string variable_name;
        TemplateStruct* external_template_struct;
        std::vector<RValue*> template_arguments;
        ExternalVariable(std::string variable_name, TemplateStruct* external_template_struct, std::vector<RValue*> template_arguments) : 
        RValue(RValueType::INTERNAL_VARIABLE), 
        variable_name(variable_name), 
        external_template_struct(external_template_struct), 
        template_arguments(template_arguments)
        {}
    };

    class Statement {
    private:
        std::string variable_name;
        RValue* rvalue;
    public:
        Statement(std::string variable_name, RValue* rvalue) : variable_name(variable_name), rvalue(rvalue) {}
    };

    class TemplateStruct {
    private:
        std::vector<std::string> template_parameters;
        std::vector<Statement> statements;
    public:
        TemplateStruct(std::vector<std::string> template_parameters) : template_parameters(template_parameters) {}
        void add_statement(Statement statement) { statements.push_back(statement); }
    };
}
#endif