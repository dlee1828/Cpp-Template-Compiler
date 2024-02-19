#include <iostream>
#include "interpreter.hpp"
#include "debug.hpp"
#include "transpiler.hpp"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cout << "Please provide a file containing code to transpile." << std::endl;
        return 0;
    }
    Transpiler x(argv[1]);
    x.run();
    std::cout << "Transpiled code written to output.cpp" << std::endl;
    return 0;
}
