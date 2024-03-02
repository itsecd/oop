#include <iostream>

using namespace std;

int fact(int n, int offset = 0) {
    cout << string(offset, ' ') << "fact(" << n << ") enter &n=" << &n << '\n';

    if (n == 0 || n == 1) {
        cout << string(offset, ' ') << "fact(" << n << ") exit\n";
        return 1;
    }

    int r = fact(n - 1, offset + 2) * n;

    cout << string(offset, ' ') << "fact(" << n << ") exit\n";

    return r;
}

int main() {
    int n = 42;
    int* p = &n;
    cout << "sizeof(n)=" << sizeof(n) << '\n';
    cout << "sizeof(p)=" << sizeof(p) << '\n';
    cout << "sizeof(*p)=" << sizeof(*p) << '\n';
    cout << "n=" << n << '\n';
    cout << "p=" << p << '\n';
    cout << "*p=" << *p << '\n';

    cout << '\n';

    fact(4);
}