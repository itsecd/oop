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

int find_first_extremum_v1(int* data, size_t n) {
    if (n == 0) {
        return -1;
    }

    int min_idx = 0;
    int max_idx = 0;
    for (size_t i = 1; i < n; ++i) {
        if (data[i] < data[min_idx]) {
            min_idx = i;
        }
        if (data[i] > data[max_idx]) {
            max_idx = i;
        }
    }

    return min_idx < max_idx ? min_idx : max_idx;
}

typedef bool (*comparer)(int a, int b); // a < b -> true

int find_first(int* data, size_t n, comparer c) {
    if (n == 0) {
        return -1;
    }

    int min_idx = 0;
    for (size_t i = 1; i < n; ++i) {
        if (c(data[i], data[min_idx])) {
            min_idx = i;
        }
    }

    return min_idx;
}

bool min_comparer(int a, int b) {
    return a < b;
}

bool max_comparer(int a, int b) {
    return a > b;
}

int find_first_extremum_v2(int* data, size_t n) {
    int min_idx = find_first(data, n, min_comparer);
    int max_idx = find_first(data, n, max_comparer);

    if (min_idx < max_idx) {
        return min_idx;
    }
    else {
        return max_idx;
    }
}

int main() {
    size_t n = 0;
    cout << "Enter element count: ";
    cin >> n;

    int* data = new int[n];
    cout << "Enter elements: \n";
    for (size_t i = 0; i < n; ++i) {
        cin >> data[i];
    }

    print(data, n);

    cout << "Result v1: " << find_first_extremum_v1(data, n) << '\n';
    cout << "Result v2: " << find_first_extremum_v2(data, n) << '\n';

    delete[] data;
}
