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
	static constexpr int b_1 = 2;
	static constexpr int c_1 = ADD<a_1, b_1>::value_1;
	static constexpr int d_1 = SUBTRACT<5, 3>::value_1;
	static constexpr int e_1 = ADD<d_1, 77>::value_1;
	static constexpr int e_2 = ADD<e_1, 1>::value_1;
	static constexpr int e_3 = ADD<e_2, 1>::value_1;
	static constexpr int e_4 = ADD<e_3, 1>::value_1;
	static constexpr int e_5 = ADD<e_4, 1>::value_1;
};
