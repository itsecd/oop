#include <iostream>

using namespace std;

int main() {
    int sum = 0;

    while (true) {
        int n = 0;
        cin >> n;

        if (n > 0 && n % 2 == 0) {
            sum += n;
        }

        if (n == 0) {
            break;
        }
    }

    cout << sum;

    return 0;
}
