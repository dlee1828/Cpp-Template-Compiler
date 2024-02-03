#include "template-struct.hpp"
#include <iostream>

TS::TemplateStruct::TemplateStruct(std::vector<std::string> template_parameters) : template_parameters(template_parameters) {
    for (std::string& param : template_parameters) 
        variable_versions[param] = 0; // version 0 is reserved for template parameters
}


std::string TS::Literal::to_string() {
    return std::to_string(value);
}

std::string TS::InternalVariable::to_string() {
    return variable_name;
}

std::string TS::ExternalVariable::to_string() {
    return "not implemented yet";
}

std::string TS::BinaryOperationRValue::to_string() {

}

void TS::TemplateStruct::add_statement(std::string unversioned_variable_name, RValue* rvalue) {
    std::string versioned_variable_name = add_or_update_variable(unversioned_variable_name);
    statements.push_back(Statement(versioned_variable_name, rvalue));
}

std::string TS::TemplateStruct::get_versioned_variable_name(const std::string& variable_name) {
    if (variable_versions.find(variable_name) == variable_versions.end()) {
        std::cerr << "Variable " << variable_name << " does not exist\n";
        throw std::exception();
    }

    int version_number = variable_versions[variable_name];

    if (version_number == 0) return variable_name;
    else return variable_name + "_" + std::to_string(version_number);
}

std::string TS::TemplateStruct::add_or_update_variable(const std::string& variable_name) {
    if (variable_versions.find(variable_name) == variable_versions.end()) variable_versions[variable_name] = 1;
    else variable_versions[variable_name]++;

    return get_versioned_variable_name(variable_name);
}

std::string TS::TemplateStruct::Statement::to_string() {
    return "static constexpr int " + variable_name + " = " + rvalue->to_string() + ";";
}

void TS::TemplateStruct::write_to_file(std::ofstream& file, const std::string& template_struct_name) {
    if (template_parameters.size() > 0) {
        file << "template <";
        for (int i = 0; i < template_parameters.size(); i++) {
            file << "int " << template_parameters[i];
            if (i != template_parameters.size() - 1) file << ", ";
        }
        file << ">" << "\n";
    }

    file << "struct " << template_struct_name << " {";
    file << "\n";

    for (Statement statement : statements) 
        file << "\t" << statement.to_string() << "\n";

    file << "};";
}