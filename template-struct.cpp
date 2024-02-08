#include "template-struct.hpp"
#include "debug.hpp"
#include <iostream>

TS::TemplateStruct::TemplateStruct(
    std::string name, 
    std::vector<std::string> template_parameters, 
    std::vector<std::string> template_arguments, 
    TS::TemplateStruct* base_template_struct
) : name(name)
{
    for (std::string& param : template_parameters) 
        variable_versions[param] = 0; // version 0 is reserved for template parameters

    if (base_template_struct != nullptr) {
        std::vector<std::string> unversioned_variable_names = base_template_struct->get_all_unversioned_variable_names();
        template_parameters.insert(template_parameters.end(), unversioned_variable_names.begin(), unversioned_variable_names.end());

        for (std::string& param : unversioned_variable_names) {
            print("About to set", param, "to 0");
            variable_versions[param] = 0;
            add_statement(param, new InternalVariable(param));
        }

        if (template_arguments.size() > 0) {
            template_arguments.insert(template_arguments.end(), unversioned_variable_names.begin(), unversioned_variable_names.end());
        }
    }
    
    this->template_parameters = template_parameters; 
    this->template_arguments = template_arguments;
}

std::string TS::Literal::to_string() {
    return std::to_string(value);
}

std::string TS::InternalVariable::to_string() {
    return versioned_variable_name;
}

std::string TS::ExternalVariable::to_string() {
    return external_template_struct->get_variable_reference(unversioned_variable_name, template_arguments);
}

std::string TS::BinaryOperationRValue::to_string() {
    return left_operand->to_string() + " " + get_binary_operation_details(operation).symbol + " " + right_operand->to_string();
}

void TS::TemplateStruct::add_statement(std::string unversioned_variable_name, RValue* rvalue) {
    print("Adding statement for unversioned variable name", unversioned_variable_name);
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
    print("in template struct", this->name, "add or update variable", variable_name);
    if (variable_versions.find(variable_name) == variable_versions.end()) variable_versions[variable_name] = 1;
    else variable_versions[variable_name]++;
    print("new version is", variable_versions[variable_name]);

    std::string versioned_variable_name = get_versioned_variable_name(variable_name);
    print("versioned variable name is", versioned_variable_name);
    return versioned_variable_name;
}

std::string TS::TemplateStruct::Statement::to_string() {
    return "static constexpr int " + variable_name + " = " + rvalue->to_string() + ";";
}

void TS::TemplateStruct::write_to_file(std::ofstream& file) {
    if (template_parameters.size() > 0) {
        file << "template <";
        for (int i = 0; i < template_parameters.size(); i++) {
            file << "int " << template_parameters[i];
            if (i != template_parameters.size() - 1) file << ", ";
        }
        file << ">" << "\n";
    }

    file << "struct " << name << " {";
    file << "\n";

    for (Statement statement : statements) 
        file << "\t" << statement.to_string() << "\n";

    file << "};\n";
}

std::string TS::TemplateStruct::get_variable_reference(std::string unversioned_variable_name, std::vector<RValue*> template_arguments, TS::TemplateStruct* base_template_struct) {
    std::string result = name;
    if (base_template_struct != nullptr) {
        std::vector<std::string> versioned_variable_names = this->get_all_versioned_variable_names();
        for (std::string variable_name : versioned_variable_names) {
            template_arguments.push_back(new InternalVariable(variable_name));
        }
    }
    if (template_arguments.size() > 0) {
        result += "<";
        for (int i = 0; i < template_arguments.size(); i++) {
            result += template_arguments[i]->to_string();
            if (i != template_arguments.size() - 1) result += ", ";
        }
        result += ">";
    }
    result += "::";
    result += get_versioned_variable_name(unversioned_variable_name);
    return result;
}

std::vector<std::string> TS::TemplateStruct::get_all_unversioned_variable_names() {
    std::vector<std::string> result;
    for (auto [variable_name, version_number] : variable_versions) {
        result.push_back(variable_name);
    }
    return result;
}

std::vector<std::string> TS::TemplateStruct::get_all_versioned_variable_names() {
    std::vector<std::string> result;
    for (auto [variable_name, version_number] : variable_versions) {
        result.push_back(get_versioned_variable_name(variable_name));
    }
    return result;
}

void TS::TemplateStruct::retrieve_local_variables_from_child(TS::TemplateStruct* child_template_struct, std::vector<TS::RValue*> template_arguments) {
    print("Retrieving local variables from", child_template_struct->get_name(), "to", this->get_name());
    std::vector<std::string> versioned_variable_names = get_all_versioned_variable_names();
    print("Successfully got all versioned variable names");
    std::vector<TS::RValue*> variable_name_rvalues;
    for (std::string variable_name : versioned_variable_names)
        variable_name_rvalues.push_back(new TS::InternalVariable(variable_name));

    template_arguments.insert(template_arguments.end(), variable_name_rvalues.begin(), variable_name_rvalues.end());

    for (std::string unversioned_variable_name : get_all_unversioned_variable_names()) {
        print("About to try to get versioned variable name for", unversioned_variable_name);
        RValue* rvalue = new TS::ExternalVariable(
            unversioned_variable_name, 
            child_template_struct, 
            template_arguments
        );
        print("About to add statement");
        add_statement(unversioned_variable_name, rvalue);
    }
}
