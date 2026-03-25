#include <iostream>

// general template
template <typename T>
class Box {
public:
    T value;
    Box(T v) : value(v) {}
    void print() { std::cout << "general: " << value << std::endl; }
};

// partial specialization — any pointer type
template <typename T>
class Box<T*> {
public:
    T* value;
    Box(T* v) : value(v) {}
    void print() { std::cout << "pointer: " << *value << std::endl; }
};

// full specialization — only bool
template <>
class Box<bool> {
public:
    bool value;
    Box(bool v) : value(v) {}
    void print() { std::cout << "bool: " << (value ? "true" : "false") << std::endl; }
};

int main() {
    Box<int>  b1(42);        // general
    Box<bool> b2(true);      // full specialization
    int x = 99;
    Box<int*> b3(&x);        // partial specialization

    b1.print();
    b2.print();
    b3.print();
}