#include <iostream>

using namespace std;

int fact(int n) {
    int r = 1;

    for (int i = 2; i <= n; ++i) {
        r = r * i;
    }

    return r;
}

int main() {
    while (true) {
        cout << "Enter n: ";
        int n = 0;
        cin >> n;

        if (n < 0) {
            break;
        }

        int r = fact(n);
        cout << "fact(" << n << ") = " << r << '\n';
    }

    return 0;
}
