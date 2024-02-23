#include <iostream>
#include <sstream>
#include "interpreter.hpp"
#include "debug.hpp"
#include "transpiler.hpp"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./main input_file output_file" << std::endl;
        return 0;
    }

    std::string input_file_path = argv[1];
    std::string output_file_path = argv[2];

    std::ifstream input_file_stream(input_file_path);
    std::stringstream input_string_stream;
    input_string_stream << input_file_stream.rdbuf();
    std::string input_string = input_string_stream.str();
    input_file_stream.close();

    Transpiler x(input_string);

    std::string output_string = x.run();
    std::ofstream output_file_stream(output_file_path);
    output_file_stream << output_string;
    output_file_stream.close();

    std::cout << "Success" << std::endl;
    return 0;
}
