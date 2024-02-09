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
template <int condition_value, int a, int b, int c>
struct if_else_1 {
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
	static constexpr int c_1 = c;
	static constexpr int a_final = a_1;
	static constexpr int b_final = b_1;
	static constexpr int c_final = c_1;
	static constexpr int condition_value_final = condition_value;
};
template <int a, int b, int c>
struct if_else_1<1, a, b, c> {
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
	static constexpr int c_1 = c;
	static constexpr int c_2 = 1;
	static constexpr int a_final = a_1;
	static constexpr int b_final = b_1;
	static constexpr int c_final = c_2;
};
template <int condition_value, int a, int b, int c>
struct if_else_0 {
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
	static constexpr int c_1 = c;
	static constexpr int a_final = a_1;
	static constexpr int b_final = b_1;
	static constexpr int c_final = c_1;
	static constexpr int condition_value_final = condition_value;
};
template <int a, int b, int c>
struct if_else_0<1, a, b, c> {
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
	static constexpr int c_1 = c;
	static constexpr int a_2 = if_else_1<NOT_EQUAL<b_1, 2>::value_1, a_1, b_1, c_1>::a_final;
	static constexpr int b_2 = if_else_1<NOT_EQUAL<b_1, 2>::value_1, a_1, b_1, c_1>::b_final;
	static constexpr int c_2 = if_else_1<NOT_EQUAL<b_1, 2>::value_1, a_1, b_1, c_1>::c_final;
	static constexpr int a_final = a_2;
	static constexpr int b_final = b_2;
	static constexpr int c_final = c_2;
};
struct root {
	static constexpr int a_1 = 1;
	static constexpr int b_1 = 2;
	static constexpr int c_1 = 0;
	static constexpr int a_2 = if_else_0<EQUAL<a_1, 1>::value_1, a_1, b_1, c_1>::a_final;
	static constexpr int b_2 = if_else_0<EQUAL<a_1, 1>::value_1, a_1, b_1, c_1>::b_final;
	static constexpr int c_2 = if_else_0<EQUAL<a_1, 1>::value_1, a_1, b_1, c_1>::c_final;
};
