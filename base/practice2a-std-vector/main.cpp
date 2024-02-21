#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int>& v) {
  bool first_item = true;
  for (int item : v) {
    if (first_item) {
      first_item = false;
    }
    else {
      cout << ' ';
    }
    cout << item;
  }
  cout << endl;
}

void print(const vector<float>& v) {
  bool first_item = true;
  for (float item : v) {
    if (first_item) {
      first_item = false;
    }
    else {
      cout << ' ';
    }
    cout << item;
  }
  cout << endl;
}

int main() {
  const int n = 5;

  // int_vector
  {
    vector<int> v;
    for (size_t i = 0; i < n; ++i) {
      v.push_back(static_cast<int>(i));
    }

    print(v);

    vector<int>::iterator it = v.begin() + 2;
    v.erase(it);

    print(v);
  }

  // float_vector
  {
    vector<float> v;
    for (size_t i = 0; i < n; ++i) {
      v.push_back(static_cast<float>(i) + 0.5f);
    }

    print(v);

    vector<float>::iterator it = v.begin() + 2;
    v.erase(it);

    print(v);
  }

  return 0;
}
