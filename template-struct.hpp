#ifndef TEMPLATE_STRUCT_H
#define TEMPLATE_STRUCT_H

#include <vector>
#include <string>
#include <map>
#include <fstream>

namespace TS {
    class TemplateStruct;

    enum RValueType {
        LITERAL, INTERNAL_VARIABLE, EXTERNAL_VARIABLE, UNDEFINED
    };

    struct RValue {
        RValueType type;
        RValue(RValueType type) : type(type) {}
        virtual std::string to_string() = 0;
    };

    struct Literal : RValue {
        int value;
        Literal(int value) : RValue(RValueType::LITERAL), value(value) {}
        std::string to_string() override;
    };

    struct InternalVariable : RValue {
        std::string variable_name;
        InternalVariable(std::string variable_name) : RValue(RValueType::INTERNAL_VARIABLE), variable_name(variable_name) {}
        std::string to_string() override;
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

        std::string to_string() override;
    };

    class Statement {
    private:
        std::string variable_name;
        RValue* rvalue;
    public:
        Statement(std::string variable_name, RValue* rvalue) : variable_name(variable_name), rvalue(rvalue) {}
        std::string to_string();
    };

    class TemplateStruct {
    private:
        std::vector<std::string> template_parameters;
        std::vector<Statement> statements;
        std::map<std::string, int> variable_versions;
    public:
        TemplateStruct(std::vector<std::string> template_parameters) : template_parameters(template_parameters) {}
        TemplateStruct() : TemplateStruct(std::vector<std::string>()) {}
        void add_statement(Statement statement) { statements.push_back(statement); }
        std::string get_versioned_variable_name(const std::string& variable_name);
        std::string add_or_update_variable(const std::string& variable_name); 
        void write_to_file(std::ofstream& file, const std::string& template_struct_name);
    };
}


#endif