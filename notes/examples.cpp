#include <iostream>

template <int x> 
struct Test {};

/*
Ideas: In templates, we can only initialize new variables, never re-define
So whenever a var is redefined in source code, just initialize a new version
a_1, a_2, a_3, etc etc
*/

// JUST MANIPULATING VALUES
template<int a, int b>
struct addition {
    static constexpr int value = a + b;
};

constexpr int a = 5;
constexpr int b = 3;
constexpr int c = addition<a, b>::value;
constexpr int d = a + b + c; // recursive addition with ...

// LOOP STUFF


// PLAYGROUND

template<int x, int y>
struct operation_add {
    static constexpr int value = x + y;
};

template<int x, int y>
struct operation_subtract {
    static constexpr int value = x - y;
};

template<int x, int y>
struct operation_multiply {
    static constexpr int value = x * y;
};

template<int x, int y>
struct operation_divide {
    static constexpr int value = x / y;
};

template<int x, int y>
struct operation_mod {
    static constexpr int value = x % y;
};

template<int x, int y>
struct less {
    static constexpr int value = x < y;
};

template<int x, int y>
struct less_equal {
    static constexpr int value = x <= y;
};

template<int x, int y>
struct greater {
    static constexpr int value = x > y;
};

template<int x, int y>
struct greater_equal {
    static constexpr int value = x > y;
};

template<int x, int y>
struct equal {
    static constexpr int value = x == y;
};

template<int x, int y>
struct not_equal {
    static constexpr int value = x != y;
};

template <int x>
struct condition_1 {
    static constexpr bool value = x < 0;
};

template<bool b, int a>
struct condition_1_body {
};

template<int a>
struct condition_1_body<true, a> {
    static constexpr int e_2 = -1;
    static constexpr int a_3 = a;
};

template<int a>
struct condition_1_body<false, a> {
    static constexpr int e_2 = 1;
    static constexpr int a_3 = a + 2;
};

template <int i>
struct loop_condition {
    static constexpr bool value = (i < 5);
};

template <int a, int e>
struct value_update {
    static constexpr int a_4 = a - 2;
    static constexpr int e_3 = e + 1;
};

template <int i, bool going, int a, int e> 
struct loop {
    static constexpr int a_4 = loop<i + 1, loop_condition<i+1>::value, value_update<a, e>::a_4, value_update<a, e>::e_3>::a_4;
    static constexpr int e_3 = loop<i + 1, loop_condition<i+1>::value, value_update<a, e>::a_4, value_update<a, e>::e_3>::e_3;
};

template<int i, int a, int e>
struct loop<i, false, a, e> {
    static constexpr int a_4 = a;
    static constexpr int e_3 = e;
};

struct x {
    static constexpr int a = 1;
    static constexpr int b = 2;
    static constexpr int c = add<a, b>::value;
    static constexpr int a_2 = subtract<a, 5>::value;
    static constexpr int d = multiply<c, a_2>::value;
    static constexpr int e = 0;
    static constexpr int e_2 = condition_1_body<condition_1<d>::value, a_2>::e_2;
    static constexpr int a_3 = condition_1_body<condition_1<d>::value, a_2>::a_3;
    static constexpr int e_3 = loop<0, loop_condition<0>::value, a_3, e_2>::e_3;
    static constexpr int a_4 = loop<0, loop_condition<0>::value, a_3, e_2>::a_4;
    static constexpr int result = e_3 + a_4;
};

int func () {
    int a = 1;
    int b = 2;
    int c = a + b;
    a = a - 5;
    int d = c * a;

    int e = 0;
    if (d < 0) {
        e = -1;
    } else {
        e = 1;
        a = a + 2;
    }

    for (int i = 0; i < 5; i++) {
        e = e + 1;
        a = a - 2;
    }

    return e + a;
}

int main() {
    std::cout << func() << std::endl;
    static constexpr int result = x::result;
    std::cout << result << std::endl;
    return 0;
}