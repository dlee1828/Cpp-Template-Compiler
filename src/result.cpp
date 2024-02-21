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

template <int _has_returned, int _return_value, int e, int i, int x>
struct while_body_3 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int e_1 = e;
	static constexpr int i_1 = i;
	static constexpr int x_1 = x;
	static constexpr int x_2 = MULTIPLY<x_1, 10>::value_1;
	static constexpr int i_2 = ADD<i_1, 1>::value_1;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int e_final = e_1;
	static constexpr int i_final = i_2;
	static constexpr int x_final = x_2;
	static void print_all() {
	}
};

template <int condition, int _has_returned, int _return_value, int e, int i, int x>
struct while_parent_2 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int e_1 = e;
	static constexpr int i_1 = i;
	static constexpr int x_1 = x;
	static void print_1() { while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::print_all(); }
	static void print_2() { while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final>::value_1, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::x_final>::print_all(); }
	static constexpr int _has_returned_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final>::value_1, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::x_final>::_has_returned_final;
	static constexpr int _return_value_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final>::value_1, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::x_final>::_return_value_final;
	static constexpr int e_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final>::value_1, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::x_final>::e_final;
	static constexpr int i_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final>::value_1, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::x_final>::i_final;
	static constexpr int x_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final>::value_1, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::e_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::i_final, while_body_3<_has_returned_1, _return_value_1, e_1, i_1, x_1>::x_final>::x_final;
	static void print_all() {
		print_1();
		print_2();
	}
};

template <int _has_returned, int _return_value, int e, int i, int x>
struct while_parent_2<0, _has_returned, _return_value, e, i, x> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int e_1 = e;
	static constexpr int i_1 = i;
	static constexpr int x_1 = x;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int e_final = e_1;
	static constexpr int i_final = i_1;
	static constexpr int x_final = x_1;
	static void print_all() {
	}
};

template <int e>
struct FUNCTION_get_pow_ten {
	static constexpr int _return_value_1 = 0;
	static constexpr int _has_returned_1 = 0;
	static constexpr int x_1 = 1;
	static constexpr int i_1 = 1;
	static void print_1() { while_parent_2<LESS_EQUAL<i_1, e>::value_1, _has_returned_1, _return_value_1, e, i_1, x_1>::print_all(); }
	static constexpr int _has_returned_2 = while_parent_2<LESS_EQUAL<i_1, e>::value_1, _has_returned_1, _return_value_1, e, i_1, x_1>::_has_returned_final;
	static constexpr int _return_value_2 = while_parent_2<LESS_EQUAL<i_1, e>::value_1, _has_returned_1, _return_value_1, e, i_1, x_1>::_return_value_final;
	static constexpr int e_1 = while_parent_2<LESS_EQUAL<i_1, e>::value_1, _has_returned_1, _return_value_1, e, i_1, x_1>::e_final;
	static constexpr int i_2 = while_parent_2<LESS_EQUAL<i_1, e>::value_1, _has_returned_1, _return_value_1, e, i_1, x_1>::i_final;
	static constexpr int x_2 = while_parent_2<LESS_EQUAL<i_1, e>::value_1, _has_returned_1, _return_value_1, e, i_1, x_1>::x_final;
	static constexpr int _return_value_3 = RETURN<_return_value_2, x_2, _has_returned_2>::_return_value_final;
	static constexpr int _has_returned_3 = 1;
	static constexpr int _has_returned_final = _has_returned_3;
	static constexpr int _return_value_final = _return_value_3;
	static constexpr int e_final = e_1;
	static constexpr int i_final = i_2;
	static constexpr int x_final = x_2;
	static void print_all() {
		print_1();
	}
};

template <int _has_returned, int _return_value, int i, int m, int multiple, int next_multiple, int x>
struct while_body_5 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int i_1 = i;
	static constexpr int m_1 = m;
	static constexpr int multiple_1 = multiple;
	static constexpr int next_multiple_1 = next_multiple;
	static constexpr int x_1 = x;
	static constexpr int multiple_2 = next_multiple_1;
	static constexpr int next_multiple_2 = ADD<next_multiple_1, m_1>::value_1;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int i_final = i_1;
	static constexpr int m_final = m_1;
	static constexpr int multiple_final = multiple_2;
	static constexpr int next_multiple_final = next_multiple_2;
	static constexpr int x_final = x_1;
	static void print_all() {
	}
};

template <int condition, int _has_returned, int _return_value, int i, int m, int multiple, int next_multiple, int x>
struct while_parent_4 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int i_1 = i;
	static constexpr int m_1 = m;
	static constexpr int multiple_1 = multiple;
	static constexpr int next_multiple_1 = next_multiple;
	static constexpr int x_1 = x;
	static void print_1() { while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::print_all(); }
	static void print_2() { while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::value_1, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::i_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::m_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::print_all(); }
	static constexpr int _has_returned_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::value_1, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::i_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::m_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::_has_returned_final;
	static constexpr int _return_value_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::value_1, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::i_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::m_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::_return_value_final;
	static constexpr int i_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::value_1, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::i_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::m_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::i_final;
	static constexpr int m_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::value_1, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::i_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::m_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::m_final;
	static constexpr int multiple_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::value_1, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::i_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::m_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::multiple_final;
	static constexpr int next_multiple_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::value_1, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::i_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::m_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::next_multiple_final;
	static constexpr int x_final = while_parent_4<LESS_EQUAL<while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::value_1, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_has_returned_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::_return_value_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::i_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::m_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::next_multiple_final, while_body_5<_has_returned_1, _return_value_1, i_1, m_1, multiple_1, next_multiple_1, x_1>::x_final>::x_final;
	static void print_all() {
		print_1();
		print_2();
	}
};

template <int _has_returned, int _return_value, int i, int m, int multiple, int next_multiple, int x>
struct while_parent_4<0, _has_returned, _return_value, i, m, multiple, next_multiple, x> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int i_1 = i;
	static constexpr int m_1 = m;
	static constexpr int multiple_1 = multiple;
	static constexpr int next_multiple_1 = next_multiple;
	static constexpr int x_1 = x;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int i_final = i_1;
	static constexpr int m_final = m_1;
	static constexpr int multiple_final = multiple_1;
	static constexpr int next_multiple_final = next_multiple_1;
	static constexpr int x_final = x_1;
	static void print_all() {
	}
};

template <int m, int x>
struct FUNCTION_get_greatest_multiple_leq {
	static constexpr int _return_value_1 = 0;
	static constexpr int _has_returned_1 = 0;
	static constexpr int i_1 = 0;
	static constexpr int multiple_1 = MULTIPLY<i_1, m>::value_1;
	static constexpr int next_multiple_1 = ADD<multiple_1, m>::value_1;
	static void print_1() { while_parent_4<LESS_EQUAL<next_multiple_1, x>::value_1, _has_returned_1, _return_value_1, i_1, m, multiple_1, next_multiple_1, x>::print_all(); }
	static constexpr int _has_returned_2 = while_parent_4<LESS_EQUAL<next_multiple_1, x>::value_1, _has_returned_1, _return_value_1, i_1, m, multiple_1, next_multiple_1, x>::_has_returned_final;
	static constexpr int _return_value_2 = while_parent_4<LESS_EQUAL<next_multiple_1, x>::value_1, _has_returned_1, _return_value_1, i_1, m, multiple_1, next_multiple_1, x>::_return_value_final;
	static constexpr int i_2 = while_parent_4<LESS_EQUAL<next_multiple_1, x>::value_1, _has_returned_1, _return_value_1, i_1, m, multiple_1, next_multiple_1, x>::i_final;
	static constexpr int m_1 = while_parent_4<LESS_EQUAL<next_multiple_1, x>::value_1, _has_returned_1, _return_value_1, i_1, m, multiple_1, next_multiple_1, x>::m_final;
	static constexpr int multiple_2 = while_parent_4<LESS_EQUAL<next_multiple_1, x>::value_1, _has_returned_1, _return_value_1, i_1, m, multiple_1, next_multiple_1, x>::multiple_final;
	static constexpr int next_multiple_2 = while_parent_4<LESS_EQUAL<next_multiple_1, x>::value_1, _has_returned_1, _return_value_1, i_1, m, multiple_1, next_multiple_1, x>::next_multiple_final;
	static constexpr int x_1 = while_parent_4<LESS_EQUAL<next_multiple_1, x>::value_1, _has_returned_1, _return_value_1, i_1, m, multiple_1, next_multiple_1, x>::x_final;
	static constexpr int _return_value_3 = RETURN<_return_value_2, multiple_2, _has_returned_2>::_return_value_final;
	static constexpr int _has_returned_3 = 1;
	static constexpr int _has_returned_final = _has_returned_3;
	static constexpr int _return_value_final = _return_value_3;
	static constexpr int i_final = i_2;
	static constexpr int m_final = m_1;
	static constexpr int multiple_final = multiple_2;
	static constexpr int next_multiple_final = next_multiple_2;
	static constexpr int x_final = x_1;
	static void print_all() {
		print_1();
	}
};

template <int condition_value, int _has_returned, int _return_value, int diff_above, int diff_below, int digits, int greatest_multiple_leq, int pow_ten, int value>
struct if_else_6 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int diff_above_1 = diff_above;
	static constexpr int diff_below_1 = diff_below;
	static constexpr int digits_1 = digits;
	static constexpr int greatest_multiple_leq_1 = greatest_multiple_leq;
	static constexpr int pow_ten_1 = pow_ten;
	static constexpr int value_1 = value;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int condition_value_final = condition_value;
	static constexpr int diff_above_final = diff_above_1;
	static constexpr int diff_below_final = diff_below_1;
	static constexpr int digits_final = digits_1;
	static constexpr int greatest_multiple_leq_final = greatest_multiple_leq_1;
	static constexpr int pow_ten_final = pow_ten_1;
	static constexpr int value_final = value_1;
	static void print_all() {
	}
};

template <int _has_returned, int _return_value, int diff_above, int diff_below, int digits, int greatest_multiple_leq, int pow_ten, int value>
struct if_else_6<1, _has_returned, _return_value, diff_above, diff_below, digits, greatest_multiple_leq, pow_ten, value> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int diff_above_1 = diff_above;
	static constexpr int diff_below_1 = diff_below;
	static constexpr int digits_1 = digits;
	static constexpr int greatest_multiple_leq_1 = greatest_multiple_leq;
	static constexpr int pow_ten_1 = pow_ten;
	static constexpr int value_1 = value;
	static constexpr int _return_value_2 = RETURN<_return_value_1, greatest_multiple_leq_1, _has_returned_1>::_return_value_final;
	static constexpr int _has_returned_2 = 1;
	static constexpr int _has_returned_final = _has_returned_2;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int diff_above_final = diff_above_1;
	static constexpr int diff_below_final = diff_below_1;
	static constexpr int digits_final = digits_1;
	static constexpr int greatest_multiple_leq_final = greatest_multiple_leq_1;
	static constexpr int pow_ten_final = pow_ten_1;
	static constexpr int value_final = value_1;
	static void print_all() {
	}
};

template <int digits, int value>
struct FUNCTION_round_value {
	static constexpr int _return_value_1 = 0;
	static constexpr int _has_returned_1 = 0;
	static void print_1() { FUNCTION_get_pow_ten<digits>::print_all(); }
	static constexpr int pow_ten_1 = FUNCTION_get_pow_ten<digits>::_return_value_final;
	static void print_2() { FUNCTION_get_greatest_multiple_leq<pow_ten_1, value>::print_all(); }
	static constexpr int greatest_multiple_leq_1 = FUNCTION_get_greatest_multiple_leq<pow_ten_1, value>::_return_value_final;
	static constexpr int diff_below_1 = SUBTRACT<value, greatest_multiple_leq_1>::value_1;
	static constexpr int diff_above_1 = SUBTRACT<pow_ten_1, diff_below_1>::value_1;
	static constexpr int _has_returned_2 = if_else_6<LESS<diff_below_1, diff_above_1>::value_1, _has_returned_1, _return_value_1, diff_above_1, diff_below_1, digits, greatest_multiple_leq_1, pow_ten_1, value>::_has_returned_final;
	static constexpr int _return_value_2 = if_else_6<LESS<diff_below_1, diff_above_1>::value_1, _has_returned_1, _return_value_1, diff_above_1, diff_below_1, digits, greatest_multiple_leq_1, pow_ten_1, value>::_return_value_final;
	static constexpr int diff_above_2 = if_else_6<LESS<diff_below_1, diff_above_1>::value_1, _has_returned_1, _return_value_1, diff_above_1, diff_below_1, digits, greatest_multiple_leq_1, pow_ten_1, value>::diff_above_final;
	static constexpr int diff_below_2 = if_else_6<LESS<diff_below_1, diff_above_1>::value_1, _has_returned_1, _return_value_1, diff_above_1, diff_below_1, digits, greatest_multiple_leq_1, pow_ten_1, value>::diff_below_final;
	static constexpr int digits_1 = if_else_6<LESS<diff_below_1, diff_above_1>::value_1, _has_returned_1, _return_value_1, diff_above_1, diff_below_1, digits, greatest_multiple_leq_1, pow_ten_1, value>::digits_final;
	static constexpr int greatest_multiple_leq_2 = if_else_6<LESS<diff_below_1, diff_above_1>::value_1, _has_returned_1, _return_value_1, diff_above_1, diff_below_1, digits, greatest_multiple_leq_1, pow_ten_1, value>::greatest_multiple_leq_final;
	static constexpr int pow_ten_2 = if_else_6<LESS<diff_below_1, diff_above_1>::value_1, _has_returned_1, _return_value_1, diff_above_1, diff_below_1, digits, greatest_multiple_leq_1, pow_ten_1, value>::pow_ten_final;
	static constexpr int value_1 = if_else_6<LESS<diff_below_1, diff_above_1>::value_1, _has_returned_1, _return_value_1, diff_above_1, diff_below_1, digits, greatest_multiple_leq_1, pow_ten_1, value>::value_final;
	static void print_3() { if_else_6<LESS<diff_below_1, diff_above_1>::value_1, _has_returned_1, _return_value_1, diff_above_1, diff_below_1, digits, greatest_multiple_leq_1, pow_ten_1, value>::print_all(); }
	static constexpr int _return_value_3 = RETURN<_return_value_2, ADD<greatest_multiple_leq_2, pow_ten_2>::value_1, _has_returned_2>::_return_value_final;
	static constexpr int _has_returned_3 = 1;
	static constexpr int _has_returned_final = _has_returned_3;
	static constexpr int _return_value_final = _return_value_3;
	static constexpr int diff_above_final = diff_above_2;
	static constexpr int diff_below_final = diff_below_2;
	static constexpr int digits_final = digits_1;
	static constexpr int greatest_multiple_leq_final = greatest_multiple_leq_2;
	static constexpr int pow_ten_final = pow_ten_2;
	static constexpr int value_final = value_1;
	static void print_all() {
		print_1();
		print_2();
		print_3();
	}
};

struct root {
	static constexpr int _return_value_1 = 0;
	static constexpr int _has_returned_1 = 0;
	static void print_1() { FUNCTION_round_value<1, 44>::print_all(); }
	static void print_2() { PRINT<FUNCTION_round_value<1, 44>::_return_value_final, _has_returned_1>::print_all(); }
	static void print_3() { FUNCTION_round_value<2, 777>::print_all(); }
	static void print_4() { PRINT<FUNCTION_round_value<2, 777>::_return_value_final, _has_returned_1>::print_all(); }
	static void print_5() { FUNCTION_round_value<5, 123456>::print_all(); }
	static void print_6() { PRINT<FUNCTION_round_value<5, 123456>::_return_value_final, _has_returned_1>::print_all(); }
	static void print_all() {
		print_1();
		print_2();
		print_3();
		print_4();
		print_5();
		print_6();
	}
};

int main() {
	root::print_all();
	return 0;
}