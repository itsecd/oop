#include <iostream>

using namespace std;

int main() {
    int a = 0;
    cout << "Enter a: ";
    cin >> a;

    int d1 = a / 10;
    int d2 = a % 10;
    int digit_sum = d1 + d2;
    int digit_product = d1 * d2;

    cout << "Digit sum: " << digit_sum << '\n';
    cout << "Digit product: " << digit_product << '\n';

    return 0;
}
