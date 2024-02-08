#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>
#include <vector>

#define DEBUG_ON true

template<typename T>
concept Printable = requires (T x) {
    std::cout << x;
};

template<Printable T>
void print_impl(T x) {
    std::cout << x << std::endl;
}

template <Printable T>
void print_impl(std::vector<T> v) {
    for (auto elem : v) {
        print_impl(elem);
    }
}

template <Printable T, Printable... Rest>
void print_impl(T x, Rest... rest) {
    std::cout << x << " ";
    print_impl(rest...);
}


template <typename... T>
void print(T... args) {
    if (DEBUG_ON) print_impl(args...);
}

#endif