// a = 2
// for 5 iterations: a += 2;

template <int n, int a>
struct loop {
    static constexpr int a = loop<n - 1, a>::a + 2;
};

template <int a> // a is initial value
struct loop<0, a> {
    static constexpr int a = a;
}

int main() {
    return 0;
}
