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

template <int condition_value, int _has_returned, int _return_value, int a, int count, int n, int remainder>
struct if_else_4 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int count_1 = count;
	static constexpr int n_1 = n;
	static constexpr int remainder_1 = remainder;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int a_final = a_1;
	static constexpr int condition_value_final = condition_value;
	static constexpr int count_final = count_1;
	static constexpr int n_final = n_1;
	static constexpr int remainder_final = remainder_1;
	static void print_all() {
	}
};

template <int _has_returned, int _return_value, int a, int count, int n, int remainder>
struct if_else_4<1, _has_returned, _return_value, a, count, n, remainder> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int count_1 = count;
	static constexpr int n_1 = n;
	static constexpr int remainder_1 = remainder;
	static constexpr int count_2 = ADD<count_1, 1>::value_1;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int a_final = a_1;
	static constexpr int count_final = count_2;
	static constexpr int n_final = n_1;
	static constexpr int remainder_final = remainder_1;
	static void print_all() {
	}
};

template <int _has_returned, int _return_value, int a, int count, int n>
struct while_body_3 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int count_1 = count;
	static constexpr int n_1 = n;
	static constexpr int remainder_1 = MOD<n_1, a_1>::value_1;
	static constexpr int _has_returned_2 = if_else_4<EQUAL<remainder_1, 0>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n_1, remainder_1>::_has_returned_final;
	static constexpr int _return_value_2 = if_else_4<EQUAL<remainder_1, 0>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n_1, remainder_1>::_return_value_final;
	static constexpr int a_2 = if_else_4<EQUAL<remainder_1, 0>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n_1, remainder_1>::a_final;
	static constexpr int count_2 = if_else_4<EQUAL<remainder_1, 0>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n_1, remainder_1>::count_final;
	static constexpr int n_2 = if_else_4<EQUAL<remainder_1, 0>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n_1, remainder_1>::n_final;
	static constexpr int remainder_2 = if_else_4<EQUAL<remainder_1, 0>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n_1, remainder_1>::remainder_final;
	static void print_1() { if_else_4<EQUAL<remainder_1, 0>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n_1, remainder_1>::print_all(); }
	static constexpr int a_3 = ADD<a_2, 1>::value_1;
	static constexpr int _has_returned_final = _has_returned_2;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int a_final = a_3;
	static constexpr int count_final = count_2;
	static constexpr int n_final = n_2;
	static constexpr int remainder_final = remainder_2;
	static void print_all() {
		print_1();
	}
};

template <int condition, int _has_returned, int _return_value, int a, int count, int n>
struct while_parent_2 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int count_1 = count;
	static constexpr int n_1 = n;
	static void print_1() { while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::print_all(); }
	static void print_2() { while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::value_1, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::count_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::print_all(); }
	static constexpr int _has_returned_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::value_1, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::count_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::_has_returned_final;
	static constexpr int _return_value_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::value_1, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::count_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::_return_value_final;
	static constexpr int a_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::value_1, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::count_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::a_final;
	static constexpr int count_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::value_1, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::count_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::count_final;
	static constexpr int n_final = while_parent_2<LESS_EQUAL<while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::value_1, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_has_returned_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::_return_value_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::a_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::count_final, while_body_3<_has_returned_1, _return_value_1, a_1, count_1, n_1>::n_final>::n_final;
	static void print_all() {
		print_1();
		print_2();
	}
};

template <int _has_returned, int _return_value, int a, int count, int n>
struct while_parent_2<0, _has_returned, _return_value, a, count, n> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int a_1 = a;
	static constexpr int count_1 = count;
	static constexpr int n_1 = n;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int a_final = a_1;
	static constexpr int count_final = count_1;
	static constexpr int n_final = n_1;
	static void print_all() {
	}
};

template <int n>
struct FUNCTION_count_divisors {
	static constexpr int _return_value_1 = 0;
	static constexpr int _has_returned_1 = 0;
	static constexpr int count_1 = 0;
	static constexpr int a_1 = 1;
	static void print_1() { while_parent_2<LESS_EQUAL<a_1, n>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n>::print_all(); }
	static constexpr int _has_returned_2 = while_parent_2<LESS_EQUAL<a_1, n>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n>::_has_returned_final;
	static constexpr int _return_value_2 = while_parent_2<LESS_EQUAL<a_1, n>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n>::_return_value_final;
	static constexpr int a_2 = while_parent_2<LESS_EQUAL<a_1, n>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n>::a_final;
	static constexpr int count_2 = while_parent_2<LESS_EQUAL<a_1, n>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n>::count_final;
	static constexpr int n_1 = while_parent_2<LESS_EQUAL<a_1, n>::value_1, _has_returned_1, _return_value_1, a_1, count_1, n>::n_final;
	static constexpr int _return_value_3 = RETURN<_return_value_2, count_2, _has_returned_2>::_return_value_final;
	static constexpr int _has_returned_3 = 1;
	static constexpr int _has_returned_final = _has_returned_3;
	static constexpr int _return_value_final = _return_value_3;
	static constexpr int a_final = a_2;
	static constexpr int count_final = count_2;
	static constexpr int n_final = n_1;
	static void print_all() {
		print_1();
	}
};

template <int condition_value, int _has_returned, int _return_value, int divisors, int n>
struct if_else_5 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int divisors_1 = divisors;
	static constexpr int n_1 = n;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int condition_value_final = condition_value;
	static constexpr int divisors_final = divisors_1;
	static constexpr int n_final = n_1;
	static void print_all() {
	}
};

template <int _has_returned, int _return_value, int divisors, int n>
struct if_else_5<1, _has_returned, _return_value, divisors, n> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int divisors_1 = divisors;
	static constexpr int n_1 = n;
	static constexpr int _return_value_2 = RETURN<_return_value_1, 1, _has_returned_1>::_return_value_final;
	static constexpr int _has_returned_2 = 1;
	static constexpr int _has_returned_final = _has_returned_2;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int divisors_final = divisors_1;
	static constexpr int n_final = n_1;
	static void print_all() {
	}
};

template <int _has_returned, int _return_value, int divisors, int n>
struct if_else_5<0, _has_returned, _return_value, divisors, n> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int divisors_1 = divisors;
	static constexpr int n_1 = n;
	static constexpr int _return_value_2 = RETURN<_return_value_1, 0, _has_returned_1>::_return_value_final;
	static constexpr int _has_returned_2 = 1;
	static constexpr int _has_returned_final = _has_returned_2;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int divisors_final = divisors_1;
	static constexpr int n_final = n_1;
	static void print_all() {
	}
};

template <int n>
struct FUNCTION_check_prime {
	static constexpr int _return_value_1 = 0;
	static constexpr int _has_returned_1 = 0;
	static void print_1() { FUNCTION_count_divisors<n>::print_all(); }
	static constexpr int divisors_1 = FUNCTION_count_divisors<n>::_return_value_final;
	static constexpr int _has_returned_2 = if_else_5<EQUAL<divisors_1, 2>::value_1, _has_returned_1, _return_value_1, divisors_1, n>::_has_returned_final;
	static constexpr int _return_value_2 = if_else_5<EQUAL<divisors_1, 2>::value_1, _has_returned_1, _return_value_1, divisors_1, n>::_return_value_final;
	static constexpr int divisors_2 = if_else_5<EQUAL<divisors_1, 2>::value_1, _has_returned_1, _return_value_1, divisors_1, n>::divisors_final;
	static constexpr int n_1 = if_else_5<EQUAL<divisors_1, 2>::value_1, _has_returned_1, _return_value_1, divisors_1, n>::n_final;
	static void print_2() { if_else_5<EQUAL<divisors_1, 2>::value_1, _has_returned_1, _return_value_1, divisors_1, n>::print_all(); }
	static constexpr int _has_returned_final = _has_returned_2;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int divisors_final = divisors_2;
	static constexpr int n_final = n_1;
	static void print_all() {
		print_1();
		print_2();
	}
};

template <int condition_value, int _has_returned, int _return_value, int i, int is_prime, int n>
struct if_else_8 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int i_1 = i;
	static constexpr int is_prime_1 = is_prime;
	static constexpr int n_1 = n;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int condition_value_final = condition_value;
	static constexpr int i_final = i_1;
	static constexpr int is_prime_final = is_prime_1;
	static constexpr int n_final = n_1;
	static void print_all() {
	}
};

template <int _has_returned, int _return_value, int i, int is_prime, int n>
struct if_else_8<1, _has_returned, _return_value, i, is_prime, n> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int i_1 = i;
	static constexpr int is_prime_1 = is_prime;
	static constexpr int n_1 = n;
	static void print_1() { PRINT<i_1, _has_returned_1>::print_all(); }
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int i_final = i_1;
	static constexpr int is_prime_final = is_prime_1;
	static constexpr int n_final = n_1;
	static void print_all() {
		print_1();
	}
};

template <int _has_returned, int _return_value, int i, int n>
struct while_body_7 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int i_1 = i;
	static constexpr int n_1 = n;
	static void print_1() { FUNCTION_check_prime<i_1>::print_all(); }
	static constexpr int is_prime_1 = FUNCTION_check_prime<i_1>::_return_value_final;
	static constexpr int _has_returned_2 = if_else_8<EQUAL<is_prime_1, 1>::value_1, _has_returned_1, _return_value_1, i_1, is_prime_1, n_1>::_has_returned_final;
	static constexpr int _return_value_2 = if_else_8<EQUAL<is_prime_1, 1>::value_1, _has_returned_1, _return_value_1, i_1, is_prime_1, n_1>::_return_value_final;
	static constexpr int i_2 = if_else_8<EQUAL<is_prime_1, 1>::value_1, _has_returned_1, _return_value_1, i_1, is_prime_1, n_1>::i_final;
	static constexpr int is_prime_2 = if_else_8<EQUAL<is_prime_1, 1>::value_1, _has_returned_1, _return_value_1, i_1, is_prime_1, n_1>::is_prime_final;
	static constexpr int n_2 = if_else_8<EQUAL<is_prime_1, 1>::value_1, _has_returned_1, _return_value_1, i_1, is_prime_1, n_1>::n_final;
	static void print_2() { if_else_8<EQUAL<is_prime_1, 1>::value_1, _has_returned_1, _return_value_1, i_1, is_prime_1, n_1>::print_all(); }
	static constexpr int i_3 = ADD<i_2, 1>::value_1;
	static constexpr int _has_returned_final = _has_returned_2;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int i_final = i_3;
	static constexpr int is_prime_final = is_prime_2;
	static constexpr int n_final = n_2;
	static void print_all() {
		print_1();
		print_2();
	}
};

template <int condition, int _has_returned, int _return_value, int i, int n>
struct while_parent_6 {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int i_1 = i;
	static constexpr int n_1 = n;
	static void print_1() { while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::print_all(); }
	static void print_2() { while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::i_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::i_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::n_final>::print_all(); }
	static constexpr int _has_returned_final = while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::i_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::i_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::n_final>::_has_returned_final;
	static constexpr int _return_value_final = while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::i_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::i_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::n_final>::_return_value_final;
	static constexpr int i_final = while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::i_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::i_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::n_final>::i_final;
	static constexpr int n_final = while_parent_6<LESS_EQUAL<while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::i_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::n_final>::value_1, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::_has_returned_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::_return_value_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::i_final, while_body_7<_has_returned_1, _return_value_1, i_1, n_1>::n_final>::n_final;
	static void print_all() {
		print_1();
		print_2();
	}
};

template <int _has_returned, int _return_value, int i, int n>
struct while_parent_6<0, _has_returned, _return_value, i, n> {
	static constexpr int _has_returned_1 = _has_returned;
	static constexpr int _return_value_1 = _return_value;
	static constexpr int i_1 = i;
	static constexpr int n_1 = n;
	static constexpr int _has_returned_final = _has_returned_1;
	static constexpr int _return_value_final = _return_value_1;
	static constexpr int i_final = i_1;
	static constexpr int n_final = n_1;
	static void print_all() {
	}
};

template <int n>
struct FUNCTION_print_primes {
	static constexpr int _return_value_1 = 0;
	static constexpr int _has_returned_1 = 0;
	static constexpr int i_1 = 1;
	static void print_1() { while_parent_6<LESS_EQUAL<i_1, n>::value_1, _has_returned_1, _return_value_1, i_1, n>::print_all(); }
	static constexpr int _has_returned_2 = while_parent_6<LESS_EQUAL<i_1, n>::value_1, _has_returned_1, _return_value_1, i_1, n>::_has_returned_final;
	static constexpr int _return_value_2 = while_parent_6<LESS_EQUAL<i_1, n>::value_1, _has_returned_1, _return_value_1, i_1, n>::_return_value_final;
	static constexpr int i_2 = while_parent_6<LESS_EQUAL<i_1, n>::value_1, _has_returned_1, _return_value_1, i_1, n>::i_final;
	static constexpr int n_1 = while_parent_6<LESS_EQUAL<i_1, n>::value_1, _has_returned_1, _return_value_1, i_1, n>::n_final;
	static constexpr int _has_returned_final = _has_returned_2;
	static constexpr int _return_value_final = _return_value_2;
	static constexpr int i_final = i_2;
	static constexpr int n_final = n_1;
	static void print_all() {
		print_1();
	}
};

struct root {
	static constexpr int _return_value_1 = 0;
	static constexpr int _has_returned_1 = 0;
	static void print_1() { FUNCTION_print_primes<100>::print_all(); }
	static void print_all() {
		print_1();
	}
};

int main() {
	root::print_all();
	return 0;
}