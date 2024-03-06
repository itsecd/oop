#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void* operator new(size_t size) {
  void* ptr = malloc(size);
  cout << "allocated " << size << " bytes at " << ptr << '\n';
  return ptr;
}

void operator delete(void* ptr) {
  cout << "deallocated at " << ptr << '\n';
  free(ptr);
}

class MyString {
  char* _buf;
  size_t _size;

public:
  MyString() : _size(0), _buf(new char[1]()) { }

  MyString(const char* str) : _size(strlen(str)) {
    _buf = new char[_size + 1];
    strcpy(_buf, str);
  }

  MyString(const MyString& str) : _size(str._size) {
    _buf = new char[_size + 1];
    strcpy(_buf, str._buf);
  }

  ~MyString() {
    delete[] _buf;
  }

  void swap(MyString& str) noexcept {
    std::swap(_buf, str._buf);
    std::swap(_size, str._size);
  }

  MyString& operator=(MyString str) {
    swap(str);
    return *this;
  }

  size_t size() const {
    return _size;
  }

  char operator[](size_t idx) const {
    if (idx >= _size) {
      throw std::logic_error("invalid index");
    }
    return _buf[idx];
  }

  char& operator[](size_t idx) {
    if (idx >= _size) {
      throw std::logic_error("invalid index");
    }
    return _buf[idx];
  }

  const char* c_str() const {
    return _buf;
  }

  MyString& operator+=(const MyString& str) {
    size_t new_size = _size + str._size;
    char* new_buf = new char[new_size + 1];
    strcpy(new_buf, _buf);
    strcat(new_buf, str._buf);

    delete[] _buf;

    _buf = new_buf;
    _size = new_size;

    return *this;
  }
};

// MyString можно заменить на std::string
using String = MyString;

int main() {
  String s;
  s += String("abc");
  s += String("def");
  s[0] = '!';

  cout << s.c_str() << '\n';
  cout << s.size() << '\n';
}
