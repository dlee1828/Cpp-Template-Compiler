target: main.cpp interpreter.cpp syntax-tree.cpp 
	@clang++ -std=c++20 main.cpp interpreter.cpp syntax-tree.cpp
	@./a.out
	@rm ./a.out