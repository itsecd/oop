#include <cstdio>
#include <stdexcept>

using namespace std;

class IntList {
    static const int CAPACITY = 10;
    int _data[CAPACITY] = {0};
    int _size;
    
public:
    IntList() : _size(0) { }
    
    int size() const {
        return _size;
    }
    
    int operator[](int index) const {
        if (index < 0 || _size <= index) {
            throw runtime_error("Index out of range.");
        }
        
        return _data[index];
    }
    
    int& operator[](int index) {
        if (index < 0 || _size <= index) {
            throw runtime_error("Index out of range.");
        }
        
        return _data[index];
    }
    
    void add(int item) {
        if (_size == CAPACITY) {
            throw runtime_error("Full capacity reached.");
        }
        
        _data[_size] = item;
        ++_size;
    }
    
    void clear() {
        _size = 0;
    }
};

void print(const IntList& list) {
    int size = list.size();
    printf("size=%d:", size);
    for (int i = 0; i < size; ++i) {
        printf(" %d", list[i]);
    }
    printf("\n");
}

int main() {
    IntList list;
    print(list);
    
    list.add(4);
    list.add(1);
    list[1] = 2;
    print(list);
    
    list.clear();
    print(list);
}
