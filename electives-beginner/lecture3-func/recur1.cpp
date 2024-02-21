#include <iostream>

using namespace std;

int fact(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return fact(n - 1) * n;
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
