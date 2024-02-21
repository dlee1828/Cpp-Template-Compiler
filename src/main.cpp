#include <iostream>
#include "interpreter.hpp"
#include "debug.hpp"
#include "transpiler.hpp"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./main input_file output_file" << std::endl;
        return 0;
    }
    Transpiler x(argv[1], argv[2]);
    x.run();
    std::cout << "Success" << std::endl;
    return 0;
}
