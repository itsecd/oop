#include <iostream>

using namespace std;

int main() {
    cout << "Enter a: ";
    int a = 0;
    cin >> a;

    cout << "Enter b: ";
    int b = 0;
    cin >> b;

    if (a < b) {
        cout << b << " " << a;
    }
    else {
        cout << a << " " << b;
    }

    return 0;
}
