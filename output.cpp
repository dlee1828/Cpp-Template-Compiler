#include <iostream>

template <int x, int y>
struct ADD {
	static constexpr int value_1 = x + y;
	static void print_all() {
	}
};
template <int x, int y>
struct SUBTRACT {
	static constexpr int value_1 = x - y;
	static void print_all() {
	}
};
template <int x, int y>
struct MULTIPLY {
	static constexpr int value_1 = x * y;
	static void print_all() {
	}
};
template <int x, int y>
struct DIVIDE {
	static constexpr int value_1 = x / y;
	static void print_all() {
	}
};
template <int x, int y>
struct MOD {
	static constexpr int value_1 = x % y;
	static void print_all() {
	}
};
template <int x, int y>
struct LESS {
	static constexpr int value_1 = x < y;
	static void print_all() {
	}
};
template <int x, int y>
struct LESS_EQUAL {
	static constexpr int value_1 = x <= y;
	static void print_all() {
	}
};
template <int x, int y>
struct GREATER {
	static constexpr int value_1 = x > y;
	static void print_all() {
	}
};
template <int x, int y>
struct GREATER_EQUAL {
	static constexpr int value_1 = x >= y;
	static void print_all() {
	}
};
template <int x, int y>
struct EQUAL {
	static constexpr int value_1 = x == y;
	static void print_all() {
	}
};
template <int x, int y>
struct NOT_EQUAL {
	static constexpr int value_1 = x != y;
	static void print_all() {
	}
};
template <int x, int y>
struct AND {
	static constexpr int value_1 = x && y;
	static void print_all() {
	}
};
template <int x, int y>
struct OR {
	static constexpr int value_1 = x || y;
	static void print_all() {
	}
};
template <int condition_value, int a>
struct if_else_0 {
	static constexpr int a_1 = a;
	static constexpr int a_final = a_1;
	static constexpr int condition_value_final = condition_value;
	static void print_all() {
	}
};
template <int a>
struct if_else_0<1, a> {
	static constexpr int a_1 = a;
	static constexpr int a_2 = ADD<a_1, 1>::value_1;
	static void print_1() { std::cout << a_2 << std::endl; }
	static constexpr int a_final = a_2;
	static void print_all() {
		print_1();
	}
};
template <int a>
struct if_else_0<0, a> {
	static constexpr int a_1 = a;
	static constexpr int b_1 = 100;
	static void print_1() { std::cout << b_1 << std::endl; }
	static constexpr int a_final = a_1;
	static constexpr int b_final = b_1;
	static void print_all() {
		print_1();
	}
};
struct root {
	static constexpr int a_1 = 1;
	static constexpr int a_2 = if_else_0<LESS<a_1, 2>::value_1, a_1>::a_final;
	static void print_1() { if_else_0<LESS<a_1, 2>::value_1, a_1>::print_all(); }
	static void print_all() {
		print_1();
	}
};

int main() {
	root::print_all();
	return 0;
}
