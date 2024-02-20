#include <iostream>

using namespace std;

int main() {
    cout << "Enter c (N, S, W or E): ";
    char c = 0;
    cin >> c;

    cout << "Enter n (0, 1 or -1): ";
    int n = 0;
    cin >> n;

    //     N
    //     |
    //  W - - E
    //     |
    //     S
    switch (n) {
    case 1: // left
        switch (c) {
        case 'N':
            c = 'W';
            break;
        case 'E':
            c = 'N';
            break;
        case 'S':
            c = 'E';
            break;
        case 'W':
            c = 'S';
            break;
        }
        break;

    case -1: // right
        switch (c) {
        case 'N':
            c = 'E';
            break;
        case 'E':
            c = 'S';
            break;
        case 'S':
            c = 'W';
            break;
        case 'W':
            c = 'N';
            break;
        }
        break;
    }

    cout << c;

    return 0;
}
