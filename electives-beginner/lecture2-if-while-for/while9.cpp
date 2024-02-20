#include <iostream>

using namespace std;

int main() {
    cout << "Enter n: ";
    int n = 0;
    cin >> n;

    int k = 1;
    int pow3k = 3;

    while (pow3k <= n) {
        ++k;
        pow3k *= 3;
    }

    cout << "min k: 3^k>n: k=" << k;

    return 0;
}
