#include <cstdarg>
#include <cstdio>
#include <iostream>

using namespace std;

//int sum(int n, ...) {
//    va_list args;
//
//    va_start(args, n);
//
//    int sum = 0;
//    for (int i = 0; i < n; ++i) {
//        sum += va_arg(args, int);
//    }
//
//    va_end(args);
//
//    return sum;
//}

void print_str(const char* str) {
    for (int i = 0; str[i] != 0; ++i) {
        putchar(str[i]);
    }
}

void print_int(int value) {
    // Сделать с использованием только putchar
    cout << value;
}

void my_printf(const char* str, ...) {
    va_list args;
    va_start(args, str);

    for (int i = 0; str[i] != 0; ++i) {
        if (str[i] == '%') {

            char spec = str[i + 1];
            i += 1;

            switch (spec) {
            case 's': {
                const char* arg = va_arg(args, const char*);
                print_str(arg);
                break;
            }
            case 'd': {
                int arg = va_arg(args, int);
                print_int(arg);
                break;
            }
            }
        }
        else {
            putchar(str[i]);
        }
    }

    va_end(args);
}

int main() {
    my_printf("Hello, %s! %d<%d", "Ivan", 3, 4);
    return 0;
}
