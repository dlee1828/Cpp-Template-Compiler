#include <iostream>
#include "interpreter.hpp"
#include "debug.hpp"
#include "transpiler.hpp"

int main(int argc, char *argv[]) {
    // if (argc == 1) std::cout << "Please provide a file containing code to interpret." << std::endl;
    // Interpreter p(argv[1]);
    // SyntaxTreeNode* n = p.generate_syntax_tree();
    // n->evaluate();
    Transpiler x("test.txt");
    x.run();
    return 0;
}
