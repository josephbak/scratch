#include <iostream>

struct Base {
public:
    virtual void hello() { std::cout << "Base Hello\n"; }
    ~Base() { std::cout << "~Base\n"; }

};

struct Derived : Base {
    int* arr = new int[100];

public:
    void hello() override { std::cout << "Derived Hello\n"; }
    ~Derived() { delete[] arr; std::cout << "~Derived\n"; }  // you forgot delete[] arr

};


int main() {
    Base* p = new Base();
    delete p;

    // Derived der;
    // Base* ptr = &der;

    // ptr->hello();
    // delete der;

    return 0;
}