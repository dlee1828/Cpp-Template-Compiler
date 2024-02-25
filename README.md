# C++ Template Transpiler
The C++ template transpiler takes code written in [a simple programming language I made up](https://github.com/dlee1828/Cpp-Template-Compiler/blob/master/notes/base-language-specification.md) and 
converts it to [C++ template code](https://en.wikipedia.org/wiki/Template_metaprogramming). 

You can use it here: https://cpp-template-compiler.vercel.app

## How it works
The transpiler itself is written in C++ and is located in `/src`. 
It parses input code, constructs an abstract syntax tree, and then uses this abstract syntax tree to 
construct a set of data structures representing C++ template structs. 
These template structs are then written to a string which gets returned. 

`/web` contains the code for the web app. To make the transpiler accessible in the browser, I compile the transpiler code into WebAssembly using [emscripten](https://emscripten.org/).