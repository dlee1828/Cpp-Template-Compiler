#include <iostream>

/*
Assignment  
a = 1
*/
// template <int a>
// struct scope_1 {
//     static constexpr int a_1 = 1;
// };

/*
Conditional
a = 1
if (a == 0) {
    a = a + 1
}
*/
template <int a>
struct if_statement_1_condition {
    static constexpr bool value = (a == 0);
};

template <int a, bool condition_value>
struct if_statement_1_block;

template <int a>
struct if_statement_1_block<a, true> {
    static constexpr int a_2 = a + 1;
};

template <int a>
struct if_statement_1_block<a, false> {
    static constexpr int a_2 = a;
};

struct scope_1 {
    static constexpr int a_1 = 1;
    static constexpr int a_2 = if_statement_1_block<a_1, if_statement_1_condition<a_1>::value>::a_2;
    static void run() {
        std::cout << a_2 << std::endl;
    }
};

/*
Just pass all variables into new scopes, regardless of if they're actually used ?
So that all we need to keep track of is... the latest variable number (?)
Use some recursive function to keep track of variable values
So we can do something like

result = generate_next_struct(variable_values = {'x': {version: 2, value: 4}, 'y': {version: 3, value: 9}, etc});
new_variables = result.new_variables
struct_name = result.struct_name
for (each variable) write("static constexpr int {var}{version} = {result.struct_name}::{var}{version}")
*/

int main() {
    scope_1::run();
    return 0;
}