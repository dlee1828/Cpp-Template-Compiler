#ifndef TEMPLATE_STRUCT_H
#define TEMPLATE_STRUCT_H

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include "syntax-tree.hpp"

namespace TS {
    class TemplateStruct;

    enum RValueType {
        LITERAL, INTERNAL_VARIABLE, EXTERNAL_VARIABLE, BINARY_OPERATION, UNDEFINED
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
        std::string versioned_variable_name;
        InternalVariable(std::string versioned_variable_name) : RValue(RValueType::INTERNAL_VARIABLE), versioned_variable_name(versioned_variable_name) {}
        std::string to_string() override;
    };

    struct BinaryOperationRValue : RValue {
        RValue* left_operand;
        RValue* right_operand;
        BinaryOperation operation;
        BinaryOperationRValue(BinaryOperation operation, RValue* left_operand, RValue* right_operand) : 
        left_operand(left_operand), right_operand(right_operand), operation(operation), RValue(RValueType::BINARY_OPERATION) {}
        std::string to_string() override;
    };

    struct ExternalVariable : RValue {
        std::string unversioned_variable_name;
        TemplateStruct* external_template_struct;
        std::vector<RValue*> template_arguments;
        ExternalVariable(std::string unversioned_variable_name, TemplateStruct* external_template_struct, std::vector<RValue*> template_arguments) : 
        RValue(RValueType::INTERNAL_VARIABLE), 
        unversioned_variable_name(unversioned_variable_name), 
        external_template_struct(external_template_struct), 
        template_arguments(template_arguments)
        {}

        std::string to_string() override;
    };


    class TemplateStruct {
    private:
        class Statement {
        private:
            std::string variable_name;
            RValue* rvalue;
        public:
            Statement(std::string variable_name, RValue* rvalue) : variable_name(variable_name), rvalue(rvalue) {}
            std::string to_string();
        };
        std::string name;
        std::vector<std::string> template_parameters;
        std::vector<std::string> template_arguments;
        std::vector<Statement> statements;
        std::map<std::string, int> variable_versions;
        bool variables_are_finalized = false;
        std::string add_or_update_variable(const std::string& variable_name); 
    public:
        TemplateStruct(std::string name, std::vector<std::string> template_parameters = {}, std::vector<std::string> template_arguments = {}, TS::TemplateStruct* base_template_struct = nullptr);
        void add_statement(std::string unversioned_variable_name, RValue* rvalue);
        std::string get_versioned_variable_name(const std::string& variable_name);
        void write_to_file(std::ofstream& file);
        std::string get_variable_reference(std::string unversioned_variable_name, std::vector<RValue*> template_arguments, TS::TemplateStruct* base_template_struct = nullptr);
        std::vector<std::string> get_all_unversioned_variable_names();
        std::vector<std::string> get_all_versioned_variable_names();
        void retrieve_local_variables_from_child(TS::TemplateStruct* child_template_struct, std::vector<TS::RValue*> template_arguments);
        std::vector<std::string> get_template_parameters() { return this->template_parameters; }
        std::string get_name() { return this->name; }
        void add_final_value_assignments();
    };
}


#endif