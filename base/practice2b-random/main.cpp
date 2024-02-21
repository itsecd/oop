#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

int main() {
  const size_t n = 10;

  default_random_engine dre;

  {
    uniform_int_distribution<int> ud(1, 3);

    for (size_t i = 0; i < n; ++i) {
      if (i != 0) {
        cout << ' ';
      }
      cout << ud(dre);
    }
    cout << '\n';
  }

  {
    uniform_real_distribution<float> fd(0, 1);

    cout << fixed << setprecision(3);

    for (size_t i = 0; i < n; ++i) {
      if (i != 0) {
        cout << ' ';
      }
      cout << fd(dre);
    }
    cout << '\n';
  }

  return 0;
}
