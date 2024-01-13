#include <iostream>
#include "interpreter.hpp"
#include "debug.hpp"

int main(int argc, char *argv[]) {
    Interpreter p("sample.txt");
    p.parse_file();
    
    return 0;
}
