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

template <int condition_value, int disable, int value>
struct if_else_0 {
	static constexpr int disable_1 = disable;
	static constexpr int value_1 = value;
	static constexpr int condition_value_final = condition_value;
	static constexpr int disable_final = disable_1;
	static constexpr int value_final = value_1;
	static void print_all() {
	}
};

template <int disable, int value>
struct if_else_0<1, disable, value> {
	static constexpr int disable_1 = disable;
	static constexpr int value_1 = value;
	static void print_1() { std::cout << value_1 << std::endl; }
	static constexpr int disable_final = disable_1;
	static constexpr int value_final = value_1;
	static void print_all() {
		print_1();
	}
};

template <int value, int disable>
struct PRINT {
	static constexpr int disable_1 = if_else_0<NOT_EQUAL<disable, 1>::value_1, disable, value>::disable_final;
	static constexpr int value_1 = if_else_0<NOT_EQUAL<disable, 1>::value_1, disable, value>::value_final;
	static void print_1() { if_else_0<NOT_EQUAL<disable, 1>::value_1, disable, value>::print_all(); }
	static void print_all() {
		print_1();
	}
};

template <int condition_value, int _return_value, int disable, int new_return_value, int old_return_value>
struct if_else_1 {
	static constexpr int _return_value_1 = _return_value;
	static constexpr int disable_1 = disable;
	static constexpr int new_return_value_1 = new_return_value;
	static constexpr int old_return_value_1 = old_return_value;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int condition_value_final = condition_value;
	static constexpr int disable_final = disable_1;
	static constexpr int new_return_value_final = new_return_value_1;
	static constexpr int old_return_value_final = old_return_value_1;
	static void print_all() {
	}
};

template <int _return_value, int disable, int new_return_value, int old_return_value>
struct if_else_1<1, _return_value, disable, new_return_value, old_return_value> {
	static constexpr int _return_value_1 = _return_value;
	static constexpr int disable_1 = disable;
	static constexpr int new_return_value_1 = new_return_value;
	static constexpr int old_return_value_1 = old_return_value;
	static constexpr int _return_value_2 = new_return_value_1;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int disable_final = disable_1;
	static constexpr int new_return_value_final = new_return_value_1;
	static constexpr int old_return_value_final = old_return_value_1;
	static void print_all() {
	}
};

template <int old_return_value, int new_return_value, int disable>
struct RETURN {
	static constexpr int _return_value_1 = old_return_value;
	static constexpr int _return_value_2 = if_else_1<NOT_EQUAL<disable, 1>::value_1, _return_value_1, disable, new_return_value, old_return_value>::_return_value_final;
	static constexpr int disable_1 = if_else_1<NOT_EQUAL<disable, 1>::value_1, _return_value_1, disable, new_return_value, old_return_value>::disable_final;
	static constexpr int new_return_value_1 = if_else_1<NOT_EQUAL<disable, 1>::value_1, _return_value_1, disable, new_return_value, old_return_value>::new_return_value_final;
	static constexpr int old_return_value_1 = if_else_1<NOT_EQUAL<disable, 1>::value_1, _return_value_1, disable, new_return_value, old_return_value>::old_return_value_final;
	static void print_1() { if_else_1<NOT_EQUAL<disable, 1>::value_1, _return_value_1, disable, new_return_value, old_return_value>::print_all(); }
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int disable_final = disable_1;
	static constexpr int new_return_value_final = new_return_value_1;
	static constexpr int old_return_value_final = old_return_value_1;
	static void print_all() {
		print_1();
	}
};

template <int condition_value, int _has_returned, int _return_value, int a, int a_squared, int b, int b_squared, int c, int c_squared, int n, int sum>
struct if_else_8 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int a_squared_1 = a_squared;
	static constexpr int b_1 = b;
	static constexpr int b_squared_1 = b_squared;
	static constexpr int c_1 = c;
	static constexpr int c_squared_1 = c_squared;
	static constexpr int n_1 = n;
	static constexpr int sum_1 = sum;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int a_final = a_1;
	static constexpr int a_squared_final = a_squared_1;
	static constexpr int b_final = b_1;
	static constexpr int b_squared_final = b_squared_1;
	static constexpr int c_final = c_1;
	static constexpr int c_squared_final = c_squared_1;
	static constexpr int condition_value_final = condition_value;
	static constexpr int n_final = n_1;
	static constexpr int sum_final = sum_1;
	static void print_all() {
	}
};

template <int _has_returned, int _return_value, int a, int a_squared, int b, int b_squared, int c, int c_squared, int n, int sum>
struct if_else_8<1, _has_returned, _return_value, a, a_squared, b, b_squared, c, c_squared, n, sum> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int a_squared_1 = a_squared;
	static constexpr int b_1 = b;
	static constexpr int b_squared_1 = b_squared;
	static constexpr int c_1 = c;
	static constexpr int c_squared_1 = c_squared;
	static constexpr int n_1 = n;
	static constexpr int sum_1 = sum;
	static void print_1() { PRINT<a_1, _has_returned_1>::print_all(); }
	static void print_2() { PRINT<b_1, _has_returned_1>::print_all(); }
	static void print_3() { PRINT<c_1, _has_returned_1>::print_all(); }
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int a_final = a_1;
	static constexpr int a_squared_final = a_squared_1;
	static constexpr int b_final = b_1;
	static constexpr int b_squared_final = b_squared_1;
	static constexpr int c_final = c_1;
	static constexpr int c_squared_final = c_squared_1;
	static constexpr int n_final = n_1;
	static constexpr int sum_final = sum_1;
	static void print_all() {
		print_1();
		print_2();
		print_3();
	}
};

template <int _has_returned, int _return_value, int a, int b, int c, int n>
struct while_body_7 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
	static constexpr int c_1 = c;
	static constexpr int n_1 = n;
	static constexpr int a_squared_1 = MULTIPLY<a_1, a_1>::value_1;
	static constexpr int b_squared_1 = MULTIPLY<b_1, b_1>::value_1;
	static constexpr int sum_1 = ADD<a_squared_1, b_squared_1>::value_1;
	static constexpr int c_squared_1 = MULTIPLY<c_1, c_1>::value_1;
	static constexpr int _has_returned_2 = if_else_8<EQUAL<sum_1, c_squared_1>::value_1, _has_returned_1, _return_value_1, a_1, a_squared_1, b_1, b_squared_1, c_1, c_squared_1, n_1, sum_1>::_has_returned_final;
	static constexpr int _return_value_2 = if_else_8<EQUAL<sum_1, c_squared_1>::value_1, _has_returned_1, _return_value_1, a_1, a_squared_1, b_1, b_squared_1, c_1, c_squared_1, n_1, sum_1>::_return_value_final;
	static constexpr int a_2 = if_else_8<EQUAL<sum_1, c_squared_1>::value_1, _has_returned_1, _return_value_1, a_1, a_squared_1, b_1, b_squared_1, c_1, c_squared_1, n_1, sum_1>::a_final;
	static constexpr int a_squared_2 = if_else_8<EQUAL<sum_1, c_squared_1>::value_1, _has_returned_1, _return_value_1, a_1, a_squared_1, b_1, b_squared_1, c_1, c_squared_1, n_1, sum_1>::a_squared_final;
	static constexpr int b_2 = if_else_8<EQUAL<sum_1, c_squared_1>::value_1, _has_returned_1, _return_value_1, a_1, a_squared_1, b_1, b_squared_1, c_1, c_squared_1, n_1, sum_1>::b_final;
	static constexpr int b_squared_2 = if_else_8<EQUAL<sum_1, c_squared_1>::value_1, _has_returned_1, _return_value_1, a_1, a_squared_1, b_1, b_squared_1, c_1, c_squared_1, n_1, sum_1>::b_squared_final;
	static constexpr int c_2 = if_else_8<EQUAL<sum_1, c_squared_1>::value_1, _has_returned_1, _return_value_1, a_1, a_squared_1, b_1, b_squared_1, c_1, c_squared_1, n_1, sum_1>::c_final;
	static constexpr int c_squared_2 = if_else_8<EQUAL<sum_1, c_squared_1>::value_1, _has_returned_1, _return_value_1, a_1, a_squared_1, b_1, b_squared_1, c_1, c_squared_1, n_1, sum_1>::c_squared_final;
	static constexpr int n_2 = if_else_8<EQUAL<sum_1, c_squared_1>::value_1, _has_returned_1, _return_value_1, a_1, a_squared_1, b_1, b_squared_1, c_1, c_squared_1, n_1, sum_1>::n_final;
	static constexpr int sum_2 = if_else_8<EQUAL<sum_1, c_squared_1>::value_1, _has_returned_1, _return_value_1, a_1, a_squared_1, b_1, b_squared_1, c_1, c_squared_1, n_1, sum_1>::sum_final;
	static void print_1() { if_else_8<EQUAL<sum_1, c_squared_1>::value_1, _has_returned_1, _return_value_1, a_1, a_squared_1, b_1, b_squared_1, c_1, c_squared_1, n_1, sum_1>::print_all(); }
	static constexpr int c_3 = ADD<c_2, 1>::value_1;
	static constexpr int _has_returned_final = _has_returned_2;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int a_final = a_2;
	static constexpr int a_squared_final = a_squared_2;
	static constexpr int b_final = b_2;
	static constexpr int b_squared_final = b_squared_2;
	static constexpr int c_final = c_3;
	static constexpr int c_squared_final = c_squared_2;
	static constexpr int n_final = n_2;
	static constexpr int sum_final = sum_2;
	static void print_all() {
		print_1();
	}
};

template <int condition, int _has_returned, int _return_value, int a, int b, int c, int n>
struct while_parent_6 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
	static constexpr int c_1 = c;
	static constexpr int n_1 = n;
	static void print_1() { while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::print_all(); }
	static void print_2() { while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::a_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::b_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::print_all(); }
	static constexpr int _has_returned_final = while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::a_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::b_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::_has_returned_final;
	static constexpr int _return_value_final = while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::a_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::b_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::_return_value_final;
	static constexpr int a_final = while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::a_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::b_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::a_final;
	static constexpr int b_final = while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::a_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::b_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::b_final;
	static constexpr int c_final = while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::a_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::b_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::c_final;
	static constexpr int n_final = while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::a_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::b_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final, while_body_7<_has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final>::n_final;
	static void print_all() {
		print_1();
		print_2();
	}
};

template <int _has_returned, int _return_value, int a, int b, int c, int n>
struct while_parent_6<0, _has_returned, _return_value, a, b, c, n> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
	static constexpr int c_1 = c;
	static constexpr int n_1 = n;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int a_final = a_1;
	static constexpr int b_final = b_1;
	static constexpr int c_final = c_1;
	static constexpr int n_final = n_1;
	static void print_all() {
	}
};

template <int _has_returned, int _return_value, int a, int b, int n>
struct while_body_5 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
	static constexpr int n_1 = n;
	static constexpr int c_1 = b_1;
	static void print_1() { while_parent_6<LESS_EQUAL<c_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::print_all(); }
	static constexpr int _has_returned_2 = while_parent_6<LESS_EQUAL<c_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_has_returned_final;
	static constexpr int _return_value_2 = while_parent_6<LESS_EQUAL<c_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::_return_value_final;
	static constexpr int a_2 = while_parent_6<LESS_EQUAL<c_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::a_final;
	static constexpr int b_2 = while_parent_6<LESS_EQUAL<c_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::b_final;
	static constexpr int c_2 = while_parent_6<LESS_EQUAL<c_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::c_final;
	static constexpr int n_2 = while_parent_6<LESS_EQUAL<c_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, c_1, n_1>::n_final;
	static constexpr int b_3 = ADD<b_2, 1>::value_1;
	static constexpr int _has_returned_final = _has_returned_2;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int a_final = a_2;
	static constexpr int b_final = b_3;
	static constexpr int c_final = c_2;
	static constexpr int n_final = n_2;
	static void print_all() {
		print_1();
	}
};

template <int condition, int _has_returned, int _return_value, int a, int b, int n>
struct while_parent_4 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
	static constexpr int n_1 = n;
	static void print_1() { while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::print_all(); }
	static void print_2() { while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::value_1, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::a_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::print_all(); }
	static constexpr int _has_returned_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::value_1, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::a_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::_has_returned_final;
	static constexpr int _return_value_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::value_1, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::a_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::_return_value_final;
	static constexpr int a_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::value_1, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::a_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::a_final;
	static constexpr int b_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::value_1, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::a_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::b_final;
	static constexpr int n_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::value_1, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::a_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final, while_body_5<_has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final>::n_final;
	static void print_all() {
		print_1();
		print_2();
	}
};

template <int _has_returned, int _return_value, int a, int b, int n>
struct while_parent_4<0, _has_returned, _return_value, a, b, n> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int b_1 = b;
	static constexpr int n_1 = n;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int a_final = a_1;
	static constexpr int b_final = b_1;
	static constexpr int n_final = n_1;
	static void print_all() {
	}
};

template <int _has_returned, int _return_value, int a, int n>
struct while_body_3 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int n_1 = n;
	static constexpr int b_1 = a_1;
	static void print_1() { while_parent_4<LESS_EQUAL<b_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, n_1>::print_all(); }
	static constexpr int _has_returned_2 = while_parent_4<LESS_EQUAL<b_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, n_1>::_has_returned_final;
	static constexpr int _return_value_2 = while_parent_4<LESS_EQUAL<b_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, n_1>::_return_value_final;
	static constexpr int a_2 = while_parent_4<LESS_EQUAL<b_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, n_1>::a_final;
	static constexpr int b_2 = while_parent_4<LESS_EQUAL<b_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, n_1>::b_final;
	static constexpr int n_2 = while_parent_4<LESS_EQUAL<b_1, n_1>::value_1, _has_returned_1, _return_value_1, a_1, b_1, n_1>::n_final;
	static constexpr int a_3 = ADD<a_2, 1>::value_1;
	static constexpr int _has_returned_final = _has_returned_2;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int a_final = a_3;
	static constexpr int b_final = b_2;
	static constexpr int n_final = n_2;
	static void print_all() {
		print_1();
	}
};

template <int condition, int _has_returned, int _return_value, int a, int n>
struct while_parent_2 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int n_1 = n;
	static void print_1() { while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::print_all(); }
	static void print_2() { while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::n_final>::value_1, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::n_final>::print_all(); }
	static constexpr int _has_returned_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::n_final>::value_1, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::n_final>::_has_returned_final;
	static constexpr int _return_value_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::n_final>::value_1, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::n_final>::_return_value_final;
	static constexpr int a_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::n_final>::value_1, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::n_final>::a_final;
	static constexpr int n_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::n_final>::value_1, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, n_1>::n_final>::n_final;
	static void print_all() {
		print_1();
		print_2();
	}
};

template <int _has_returned, int _return_value, int a, int n>
struct while_parent_2<0, _has_returned, _return_value, a, n> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int n_1 = n;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int a_final = a_1;
	static constexpr int n_final = n_1;
	static void print_all() {
	}
};

template <int n>
struct FUNCTION_print_pythagorean_triples {
	static constexpr int _return_value_1 = 0;
	static constexpr int _has_returned_1 = 0;
	static constexpr int a_1 = 1;
	static void print_1() { while_parent_2<LESS_EQUAL<a_1, n>::value_1, _has_returned_1, _return_value_1, a_1, n>::print_all(); }
	static constexpr int _has_returned_2 = while_parent_2<LESS_EQUAL<a_1, n>::value_1, _has_returned_1, _return_value_1, a_1, n>::_has_returned_final;
	static constexpr int _return_value_2 = while_parent_2<LESS_EQUAL<a_1, n>::value_1, _has_returned_1, _return_value_1, a_1, n>::_return_value_final;
	static constexpr int a_2 = while_parent_2<LESS_EQUAL<a_1, n>::value_1, _has_returned_1, _return_value_1, a_1, n>::a_final;
	static constexpr int n_1 = while_parent_2<LESS_EQUAL<a_1, n>::value_1, _has_returned_1, _return_value_1, a_1, n>::n_final;
	static constexpr int _has_returned_final = _has_returned_2;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int a_final = a_2;
	static constexpr int n_final = n_1;
	static void print_all() {
		print_1();
	}
};

struct root {
	static constexpr int _return_value_1 = 0;
	static constexpr int _has_returned_1 = 0;
	static void print_1() { FUNCTION_print_pythagorean_triples<20>::print_all(); }
	static void print_all() {
		print_1();
	}
};

int main() {
	root::print_all();
	return 0;
}