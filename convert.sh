emcc -sNO_DISABLE_EXCEPTION_CATCHING -sALLOW_MEMORY_GROWTH -std=c++20 -o web/index.html src/main.cpp src/interpreter.cpp src/syntax-tree.cpp src/transpiler.cpp src/template-struct.cpp src/binary-operation.cpp --shell-file web/html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS='["_transpile"]' -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']"