#include <iostream>
#include "interpreter.hpp"

int main() {
    Interpreter p("./sample.txt");
    p.parse_file();
    
    return 0;
}
