#include <iostream>
#include <numeric>

using namespace std;

struct Ratio {
private:
  int _a;
  int _b;

public:
  Ratio(int a, int b) {
    if (b == 0) {
      _a = 0;
      _b = 1;
    }

    if (b < 0) {
      a = -a;
      b = -b;
    }

    int gcd_ab = gcd(a, b);
    _a = a / gcd_ab;
    _b = b / gcd_ab;
  }

  int a() const {
    return _a;
  }

  int b() const {
    return _b;
  }
};

Ratio sum(Ratio lhs, Ratio rhs) {
  int a = lhs.a() * rhs.b() + rhs.a() * lhs.b();
  int b = lhs.b() * rhs.b();
  return Ratio(a, b);
}

int main() {
  Ratio r1(2, 10);
  Ratio r2(3, 10);

  Ratio r = sum(r1, r2);

  cout << r.a() << '/' << r.b() << '\n';
}
