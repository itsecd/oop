#include <iostream>

using namespace std;

void print(int* data, size_t n) {
    cout << "{";
    for (size_t i = 0; i < n; ++i) {
        if (i != 0) {
            cout << ", ";
        }
        cout << data[i];
    }
    cout << "}\n";
}

void fill_fib(int* data, size_t n) {
    if (n == 0) {
        return;
    }

    data[0] = 1;

    if (n == 1) {
        return;
    }

    data[1] = 1;

    for (size_t i = 2; i < n; ++i) {
        data[i] = data[i - 1] + data[i - 2];
    }
}

int main() {
    size_t n = 0;
    cout << "Enter n: ";
    cin >> n;

    int* data = new int[n]();
    fill_fib(data, n);

    print(data, n);

    delete[] data;
}
