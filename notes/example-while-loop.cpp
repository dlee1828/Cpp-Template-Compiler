#include <iostream>

template <int n> struct collatz_update {
  static constexpr int n_value = (n % 2 == 0) ? n / 2 : 3 * n + 1;
};

template <int n> struct collatz_condition {
  static constexpr bool going = n != 1;
};

template <int n, bool going> struct collatz {
  static constexpr int n_value =
      collatz<collatz_update<n>::n_value, collatz_condition<n>::going>::n_value;	
  static void run() {
	  std::cout << n << std::endl;
      collatz<collatz_update<n>::n_value, collatz_condition<collatz_update<n>::n_value>::going>::run();	
  }
};

template <int n> struct collatz<n, false> {
  static constexpr int n_value = n;
  static void run() {
	  std::cout << n << std::endl;
  }
};

int main() { 
	collatz<100, true>::run();
}