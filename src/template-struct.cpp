#include "template-struct.hpp"
#include "debug.hpp"
#include <iostream>
#include <sstream>

TS::TemplateStruct::TemplateStruct(
    std::string name, 
    std::vector<std::string> template_parameters, 
    std::vector<std::string> template_arguments, 
    TS::TemplateStruct* base_template_struct,
    std::set<std::string> variables_to_ignore_in_base_template_struct
) : name(name)
{
    print("Constructing template struct with name", name);
    print("Variables to ignore:");
    for (auto v : variables_to_ignore_in_base_template_struct) {
        print(v);
    }

    for (std::string& param : template_parameters) 
        variable_versions[param] = 0; // version 0 is reserved for template parameters

    if (base_template_struct != nullptr) {
        std::vector<std::string> unversioned_variable_names = base_template_struct->get_all_unversioned_variable_names();
        for (std::string var : unversioned_variable_names) {
            if (variables_to_ignore_in_base_template_struct.find(var) == variables_to_ignore_in_base_template_struct.end()) 
                template_parameters.push_back(var);
        }

        for (std::string& param : unversioned_variable_names) {
            if (variables_to_ignore_in_base_template_struct.find(param) == variables_to_ignore_in_base_template_struct.end()) {
                print("About to set", param, "to 0");
                variable_versions[param] = 0;
                add_assignment_statement(param, new InternalVariable(param));
            }
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

void TS::TemplateStruct::add_assignment_statement(std::string unversioned_variable_name, RValue* rvalue) {
    print("Adding statement for unversioned variable name", unversioned_variable_name);
    std::string versioned_variable_name = add_or_update_variable(unversioned_variable_name);
    statements.push_back(new AssignmentStatement(versioned_variable_name, rvalue));
}

void TS::TemplateStruct::add_print_statement(RValue* rvalue) {
    print("Adding print statement");
    int print_statement_index = this->get_new_print_statement_index();
    statements.push_back(new PrintStatement(rvalue, print_statement_index));
}

std::string TS::TemplateStruct::get_versioned_variable_name(const std::string& variable_name) {
    if (variable_versions.find(variable_name) == variable_versions.end()) {
        log_error("Variable", variable_name, "does not exist");
        throw std::exception();
    }

    if (this->variables_are_final) return variable_name + "_final";

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

void TS::TemplateStruct::write_to_stream(std::stringstream& stream) {
    if (this->template_parameters.size() > 0) {
        stream << "template <";
        for (int i = 0; i < template_parameters.size(); i++) {
            stream << "int " << template_parameters[i];
            if (i != template_parameters.size() - 1) stream << ", ";
        }
        stream << ">" << "\n";
    }

    stream << "struct " << name;

    if (this->template_arguments.size() > 0) {
        stream << "<";
        for (int i = 0; i < template_arguments.size(); i++) {
            stream << template_arguments[i];
            if (i != template_arguments.size() - 1) stream << ", ";
        }
        stream << ">";
    }

    stream << " {";
    stream << "\n";

    // print("there are", statements.size(), "statements");

    for (Statement* statement : statements) 
        stream << "\t" << statement->to_string() << "\n";

    // Create aggregate print function
    stream << "\tstatic void print_all() {\n";
    for (int i = 1; i <= this->number_of_print_statements; i++) {
        stream << "\t\tprint_" << std::to_string(i) << "();\n";
    }
    stream << "\t}\n";

    stream << "};\n\n";
}

std::string TS::TemplateStruct::get_template_reference_prefix(std::vector<RValue*> template_arguments, TS::TemplateStruct* base_template_struct) {
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
    return result;
}

std::string TS::TemplateStruct::get_variable_reference(std::string unversioned_variable_name, std::vector<RValue*> template_arguments, TS::TemplateStruct* base_template_struct) {
    return get_template_reference_prefix(template_arguments, base_template_struct) + get_versioned_variable_name(unversioned_variable_name);
}

std::vector<std::string> TS::TemplateStruct::get_all_unversioned_variable_names() {
    print(variable_versions.size());
    std::vector<std::string> result;
    for (auto [variable_name, version_number] : variable_versions) {
        print(variable_name, version_number);
        result.push_back(variable_name);
    }
    print("successfully got all unversioned variable names");
    return result;
}

std::vector<std::string> TS::TemplateStruct::get_all_versioned_variable_names() {
    std::vector<std::string> result;
    for (auto [variable_name, version_number] : variable_versions) {
        result.push_back(get_versioned_variable_name(variable_name));
    }
    return result;
}


std::vector<TS::RValue*> TS::TemplateStruct::get_all_local_variable_rvalues() {
    std::vector<std::string> versioned_variable_names = this->get_all_versioned_variable_names();
    std::vector<TS::RValue*> variable_name_rvalues;
    for (std::string variable_name : versioned_variable_names)
        variable_name_rvalues.push_back(new TS::InternalVariable(variable_name));
    return variable_name_rvalues;
}

void TS::TemplateStruct::retrieve_local_variables_from_child(TS::TemplateStruct* child_template_struct, std::vector<TS::RValue*> template_arguments) {
    std::vector<TS::RValue*> variable_name_rvalues = get_all_local_variable_rvalues();
    template_arguments.insert(template_arguments.end(), variable_name_rvalues.begin(), variable_name_rvalues.end());

    for (std::string unversioned_variable_name : get_all_unversioned_variable_names()) {
        print("About to try to get versioned variable name for", unversioned_variable_name);
        RValue* rvalue = new TS::ExternalVariable(
            unversioned_variable_name, 
            child_template_struct, 
            template_arguments
        );
        print("About to add statement");
        add_assignment_statement(unversioned_variable_name, rvalue);
    }
}

void TS::TemplateStruct::add_external_print_all_statement(TemplateStruct* external_template_struct, std::vector<RValue*> template_arguments) {
    int print_statement_index = this->get_new_print_statement_index();
    statements.push_back(new ExternalPrintAllStatement(external_template_struct, template_arguments, print_statement_index));
}

void TS::TemplateStruct::add_final_value_assignments() {
    std::map<std::string, std::string> assignment_values;
    for (auto [unversioned_variable_name, _] : this->variable_versions) 
        assignment_values[unversioned_variable_name] = this->get_versioned_variable_name(unversioned_variable_name);

    this->variables_are_final = true;
    for (auto [unversioned_variable_name, _] : this->variable_versions)
        this->add_assignment_statement(unversioned_variable_name, new InternalVariable(assignment_values[unversioned_variable_name]));
}

void TS::TemplateStruct::set_values_as_final() {
    this->variables_are_final = true;
}

std::string TS::TemplateStruct::AssignmentStatement::to_string() {
    return "static constexpr int " + variable_name + " = " + rvalue->to_string() + ";"; 
}

std::string TS::TemplateStruct::PrintStatement::to_string() { 
    return "static void print_" + std::to_string(print_statement_index) + "() { std::cout << " + rvalue->to_string() + " << std::endl; }";
}

std::string TS::TemplateStruct::ExternalPrintAllStatement::to_string() { 
    std::string prefix = external_template_struct->get_template_reference_prefix(template_arguments, base_template_struct);
    return "static void print_" + std::to_string(print_statement_index) + "() { " + prefix + "print_all();" + " }";
}