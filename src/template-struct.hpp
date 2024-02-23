#ifndef TEMPLATE_STRUCT_H
#define TEMPLATE_STRUCT_H

#include <vector>
#include <string>
#include <map>
#include <fstream>
#include "syntax-tree.hpp"
#include "debug.hpp"

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
        ExternalVariable(std::string unversioned_variable_name, TemplateStruct* external_template_struct, std::vector<RValue*> template_arguments = {}) : 
        RValue(RValueType::INTERNAL_VARIABLE), 
        unversioned_variable_name(unversioned_variable_name), 
        external_template_struct(external_template_struct), 
        template_arguments(template_arguments)
        {}

        std::string to_string() override;
    };


    class TemplateStruct {
    private:
        enum StatementType {
            ASSIGNMENT,
            PRINT,
            EXTERNAL_PRINT_ALL
        };
        class Statement {
        protected:
            StatementType type;
        public:
            virtual std::string to_string() = 0;
            Statement(StatementType type) : type(type) {};
        };
        class AssignmentStatement : public Statement {
        private:
            std::string variable_name;
            RValue* rvalue;
        public:
            AssignmentStatement(std::string variable_name, RValue* rvalue) : rvalue(rvalue), variable_name(variable_name), Statement(StatementType::ASSIGNMENT) {}
            std::string to_string();
        };
        class PrintStatement : public Statement {
        private:
            TS::RValue* rvalue;
            int print_statement_index;
        public:
            PrintStatement(RValue* rvalue, int print_statement_index) : rvalue(rvalue), print_statement_index(print_statement_index), Statement(StatementType::PRINT) {}
            std::string to_string();
        };
        class ExternalPrintAllStatement : public Statement {
        private:
            TS::TemplateStruct* external_template_struct;
            std::vector<RValue*> template_arguments;
            TS::TemplateStruct* base_template_struct;
            int print_statement_index;
        public: 
            ExternalPrintAllStatement(TS::TemplateStruct* external_template_struct, std::vector<RValue*> template_arguments, int print_statement_index, TS::TemplateStruct* base_template_struct = nullptr) 
            :
            external_template_struct(external_template_struct),
            template_arguments(template_arguments),
            base_template_struct(base_template_struct),
            print_statement_index(print_statement_index),
            Statement(StatementType::EXTERNAL_PRINT_ALL) {}
            std::string to_string();
        };
        std::string name;
        std::vector<std::string> template_parameters;
        std::vector<std::string> template_arguments;
        std::vector<Statement*> statements;
        std::map<std::string, int> variable_versions;
        bool variables_are_final = false;
        std::string add_or_update_variable(const std::string& variable_name); 

        int number_of_print_statements = 0;
    public:
        TemplateStruct(
            std::string name, 
            std::vector<std::string> template_parameters = {}, 
            std::vector<std::string> template_arguments = {}, 
            TS::TemplateStruct* base_template_struct = nullptr,
            std::set<std::string> variables_to_ignore_in_base_template_struct = {}
        );
        void add_assignment_statement(std::string unversioned_variable_name, RValue* rvalue);
        void add_print_statement(RValue* rvalue);
        void add_external_print_all_statement(TS::TemplateStruct* external_template_struct, std::vector<RValue*> template_arguments);
        std::string get_versioned_variable_name(const std::string& variable_name);
        void write_to_stream(std::stringstream& stream);
        std::string get_template_reference_prefix(std::vector<RValue*> template_arguments, TS::TemplateStruct* base_template_struct);
        std::string get_variable_reference(std::string unversioned_variable_name, std::vector<RValue*> template_arguments, TS::TemplateStruct* base_template_struct = nullptr);
        std::vector<std::string> get_all_unversioned_variable_names();
        std::vector<std::string> get_all_versioned_variable_names();
        std::vector<TS::RValue*> get_all_local_variable_rvalues();
        void retrieve_local_variables_from_child(TS::TemplateStruct* child_template_struct, std::vector<TS::RValue*> template_arguments);
        std::vector<std::string> get_template_parameters() { return this->template_parameters; }
        std::string get_name() { return this->name; }
        void add_final_value_assignments();
        void set_values_as_final();
        int get_new_print_statement_index() { return ++number_of_print_statements; }
    };
}


#endif