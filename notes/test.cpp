#include <iostream>

void func() {
    int a = 1;
    int x = 1;
    while (a != 16) {
        a = a * 2;
        x++;
    }
}

template <int a>
struct cond {
    static constexpr value = (a != 16);
};

template <int a, int x> 
struct updates {
    static constexpr a = (a * 2);
    static constexpr x = x + 1;
};

template <int a, bool going, int x>
struct s {
    static constexpr a = s<updates<a, x>::value, cond<a>::value, updates<a, x>>::a;
    static constexpr x = x;
};

template <int a, int x>
struct s<a, false, x> {
    static constexpr a = a;
    static constexpr x = x;
};


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