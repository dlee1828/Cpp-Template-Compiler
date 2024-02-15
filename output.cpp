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
template <int a, int sum>
struct while_body_1 {
	static constexpr int a_1 = a;
	static constexpr int sum_1 = sum;
	static constexpr int sum_2 = ADD<sum_1, a_1>::value_1;
	static constexpr int a_2 = ADD<a_1, 1>::value_1;
	static constexpr int a_final = a_2;
	static constexpr int sum_final = sum_2;
};
template <int condition, int a, int sum>
struct while_parent_0 {
	static constexpr int a_1 = a;
	static constexpr int sum_1 = sum;
	static constexpr int a_final = while_parent_0<LESS_EQUAL<while_body_1<a_1, sum_1>::a_final, 100>::value_1, while_body_1<a_1, sum_1>::a_final, while_body_1<a_1, sum_1>::sum_final>::a_final;
	static constexpr int sum_final = while_parent_0<LESS_EQUAL<while_body_1<a_1, sum_1>::a_final, 100>::value_1, while_body_1<a_1, sum_1>::a_final, while_body_1<a_1, sum_1>::sum_final>::sum_final;
};
template <int a, int sum>
struct while_parent_0<0, a, sum> {
	static constexpr int a_1 = a;
	static constexpr int sum_1 = sum;
	static constexpr int a_final = a_1;
	static constexpr int sum_final = sum_1;
};
struct root {
	static constexpr int a_1 = 1;
	static constexpr int sum_1 = 0;
	static constexpr int a_2 = while_parent_0<LESS_EQUAL<a_1, 100>::value_1, a_1, sum_1>::a_final;
	static constexpr int sum_2 = while_parent_0<LESS_EQUAL<a_1, 100>::value_1, a_1, sum_1>::sum_final;
};

#include <iostream>

int main () {
	std::cout << root::sum_2 << std::endl;
	return 0;
}
