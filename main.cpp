#include <iostream>
#include "interpreter.hpp"
#include "debug.hpp"

int main(int argc, char *argv[]) {
    if (argc == 1) std::cout << "Please provide a file containing code to interpret." << std::endl;
    Interpreter p(argv[1]);
    p.parse_file();
    
    return 0;
}
