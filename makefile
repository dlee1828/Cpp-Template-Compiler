target: main.cpp parser.cpp syntax-tree.cpp
	@clang++ -std=c++20 main.cpp parser.cpp syntax-tree.cpp
	@./a.out
	@rm ./a.out