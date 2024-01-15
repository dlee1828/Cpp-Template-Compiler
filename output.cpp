template <int x, int y>
struct BINARY_OPERATION_ADD {
	static constexpr int value = x + y;
};

template <int x, int y>
struct BINARY_OPERATION_SUBTRACT {
	static constexpr int value = x - y;
};

template <int x, int y>
struct BINARY_OPERATION_MULTIPLY {
	static constexpr int value = x * y;
};

template <int x, int y>
struct BINARY_OPERATION_DIVIDE {
	static constexpr int value = x / y;
};

template <int x, int y>
struct BINARY_OPERATION_MOD {
	static constexpr int value = x % y;
};

template <int x, int y>
struct BINARY_OPERATION_LESS {
	static constexpr int value = x < y;
};

template <int x, int y>
struct BINARY_OPERATION_LESS_EQUAL {
	static constexpr int value = x <= y;
};

template <int x, int y>
struct BINARY_OPERATION_GREATER {
	static constexpr int value = x > y;
};

template <int x, int y>
struct BINARY_OPERATION_GREATER_EQUAL {
	static constexpr int value = x >= y;
};

template <int x, int y>
struct BINARY_OPERATION_EQUAL {
	static constexpr int value = x == y;
};

template <int x, int y>
struct BINARY_OPERATION_NOT_EQUAL {
	static constexpr int value = x != y;
};

template <int x, int y>
struct BINARY_OPERATION_AND {
	static constexpr int value = (x != 0) && (y != 0);
};

