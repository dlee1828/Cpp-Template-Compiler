#include <iostream>
#include "parser.hpp"

int main() {
    Parser p("./sample.txt");
    p.parse_file();
    
    return 0;
}
