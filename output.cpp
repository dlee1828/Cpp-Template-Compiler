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
struct root {
	static constexpr int a_1 = 1;
	static constexpr int b_1 = 0;
	static constexpr int a_2 = if_else<EQUAL<a_1, 1>::value_1, a_1, b_1>::a_1;
	static constexpr int b_2 = if_else<EQUAL<a_1, 1>::value_1, a_1, b_1>::b_1;
};
template <int condition_value, int a, int b>
struct if_else {
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
};
template <int condition_value, int a, int b>
struct if_else {
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
	static constexpr int b_2 = 1;
};
