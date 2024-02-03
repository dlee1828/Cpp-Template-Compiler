#include "template-struct.hpp"
#include <iostream>

std::string TS::Literal::to_string() {
    return std::to_string(value);
}

std::string TS::InternalVariable::to_string() {
    return variable_name;
}

std::string TS::ExternalVariable::to_string() {
    return "not implemented yet";
}

std::string TS::TemplateStruct::get_versioned_variable_name(const std::string& variable_name) {
    if (variable_versions.find(variable_name) == variable_versions.end()) {
        std::cerr << "Variable " << variable_name << " does not exist\n";
        throw std::exception();
    }

    return variable_name + "_" + std::to_string(variable_versions[variable_name]);
}

std::string TS::TemplateStruct::add_or_update_variable(const std::string& variable_name) {
    if (variable_versions.find(variable_name) == variable_versions.end()) variable_versions[variable_name] = 1;
    else variable_versions[variable_name]++;

    return get_versioned_variable_name(variable_name);
}

std::string TS::Statement::to_string() {
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