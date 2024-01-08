#include <iostream>
int main() {
    struct A {
        int x;
        int y;
    };

    A a {
        .x = 2,
        .y = 3
    };

    std::cout << a.x << std::endl;

    return 0;
}