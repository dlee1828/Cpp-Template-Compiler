template <int x, int y>
struct ADD {
	static constexpr int value_1 = x + y;
};
template <int x, int y>
struct SUBTRACT {
	static constexpr int value_1 = x - y;
};
template <int x, int y>
struct MULTIPLY {
	static constexpr int value_1 = x * y;
};
template <int x, int y>
struct DIVIDE {
	static constexpr int value_1 = x / y;
};
template <int x, int y>
struct MOD {
	static constexpr int value_1 = x % y;
};
template <int x, int y>
struct LESS {
	static constexpr int value_1 = x < y;
};
template <int x, int y>
struct LESS_EQUAL {
	static constexpr int value_1 = x <= y;
};
template <int x, int y>
struct GREATER {
	static constexpr int value_1 = x > y;
};
template <int x, int y>
struct GREATER_EQUAL {
	static constexpr int value_1 = x >= y;
};
template <int x, int y>
struct EQUAL {
	static constexpr int value_1 = x == y;
};
template <int x, int y>
struct NOT_EQUAL {
	static constexpr int value_1 = x != y;
};
template <int x, int y>
struct AND {
	static constexpr int value_1 = x && y;
};
template <int x, int y>
struct OR {
	static constexpr int value_1 = x || y;
};
template <int a>
struct while_body_1 {
	static constexpr int a_1 = a;
	static constexpr int a_2 = ADD<a_1, 1>::value_1;
	static constexpr int a_final = a_2;
};
template <int condition, int a>
struct while_parent_0 {
	static constexpr int a_1 = a;
	static constexpr int a_final = while_parent_0<LESS<a_1, 10>::value_1, while_body_1<a_1>::a_final>::a_final;
};
template <int a>
struct while_parent_0<0, a> {
	static constexpr int a_1 = a;
	static constexpr int a_final = a_1;
};
struct root {
	static constexpr int a_1 = 0;
	static constexpr int a_2 = while_parent_0<LESS<a_1, 10>::value_1, a_1>::a_final;
};

#include <iostream>
int main() {
	std::cout << root::a_2 << std::endl;
	return 0;
}