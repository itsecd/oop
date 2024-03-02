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

void remove_item(int** data_ptr, size_t* n_ptr, size_t idx) {
    int* data = *data_ptr;
    size_t n = *n_ptr;

    if (idx >= n) {
        return;
    }

    int* new_data = new int[n - 1];

    for (size_t i = 0; i < idx; ++i) {
        new_data[i] = data[i];
    }

    for (size_t i = idx; i < n - 1; ++i) {
        new_data[i] = data[i + 1];
    }

    delete[] data;

    *data_ptr = new_data;
    *n_ptr = n - 1;
}

void remove_adjacent_duplicates_bad(int** data_ptr, size_t* n_ptr) {
    int* data = *data_ptr;
    size_t n = *n_ptr;

    size_t i = 1;
    while (i < n) {
        if (data[i] == data[i - 1]) {
            remove_item(&data, &n, i);
        }
        else {
            ++i;
        }
    }

    *data_ptr = data;
    *n_ptr = n;
}

void remove_adjacent_duplicates_good(int** data_ptr, size_t* n_ptr) {
    // 1. Посчитать количество удаляемых дубликатов
    // 2. Выделить нужную память нового размера
    // 3. Перенести данные из старого массива в новый без дубликатов
    // 4. Освободить старый массив
    // 5. Обновить оригиналы, на которые указывают data_ptr и n_ptr
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

    remove_adjacent_duplicates_bad(&data, &n);

    print(data, n);

    delete[] data;
}
