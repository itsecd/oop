#include <iostream>

using namespace std;

int main() {
    int a = 0;
    cout << "Enter a: ";
    cin >> a;

    int b = 0;
    cout << "Enter b: ";
    cin >> b;

    bool is_any_odd = (a % 2 == 1) || (b % 2 == 1);

    cout << "Is any odd? " << is_any_odd << '\n';

    return 0;
}
