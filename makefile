target: main.cpp interpreter.cpp syntax-tree.cpp transpiler.cpp
	@clang++ -std=c++20 -o main main.cpp interpreter.cpp syntax-tree.cpp transpiler.cpp
	@./main