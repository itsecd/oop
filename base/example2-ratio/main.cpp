#include <iostream>
#include <numeric>
#include <stdexcept>

using namespace std;

struct Ratio {
private:
  int _a;
  int _b;

  void simplify() noexcept {
    int gcd_ab = gcd(_a, _b);
    _a /= gcd_ab;
    _b /= gcd_ab;
  }

public:
  Ratio(int a, int b) : _a(a), _b(b) {
    if (_b == 0) {
      throw logic_error("The denominator can't be zero.");
    }

    if (_b < 0) {
      _a = -_a;
      _b = -_b;
    }

    simplify();
  }

  Ratio& operator+=(const Ratio& other) {
    int a = _a * other._b + other._a * _b;
    int b = _b * other._b;
    _a = a;
    _b = b;

    simplify();

    return *this;
  }

  int a() const {
    return _a;
  }

  int b() const {
    return _b;
  }
};

Ratio operator+(Ratio lhs, const Ratio& rhs) {
  lhs += rhs;
  return lhs;
}

ostream& operator<<(ostream& stream, const Ratio& r) {
  stream << r.a() << '/' << r.b();
  return stream;
}

int main() {
  try {
    Ratio r1(2, 10);
    Ratio r2(3, 10);
    Ratio r = r1 + r2;
    cout << r1 << " + " << r2 << " = " << r << '\n';

    cout << "Try to create fraction with zero denominator...\n";
    Ratio invalid_ratio(1, 0);
    cout << invalid_ratio << '\n'; // Dead code
  }
  catch (const logic_error& e) {
    cout << e.what() << '\n';
  }
}
