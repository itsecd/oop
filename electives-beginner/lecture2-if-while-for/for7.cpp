#include <iostream>

using namespace std;

int main() {
    cout << "Enter a: ";
    int a = 0;
    cin >> a;

    cout << "Enter b: ";
    int b = 0;
    cin >> b;

    int sum = 0;
    for (int i = a; i <= b; ++i) {
        sum += i;
    }

    cout << sum;

    return 0;
}
