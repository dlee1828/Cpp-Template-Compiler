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
template <int a, int b>
struct add {
	static constexpr int return_value_1 = ADD<a, b>::value_1;
	static constexpr int a_final = a;
	static constexpr int b_final = b;
	static constexpr int return_value_final = return_value_1;
};
struct root {
};
