#include <iostream>

struct Base {
    Base(int x) {
        std::cout << x << '\n';
    }

    Base(const char* s) {
        std::cout << s << '\n';
    }
    
    Base (const Base& other) {
        std::cout << "copy constructor\n";
    }
};

struct D1 : Base {
};

struct D2 : Base {
    using Base::Base;
};

struct D3 : Base {
    using Base::Base;
    int extra;
};

struct D4 : Base {
    using Base::Base;
    D4(int x) : Base(x) {
        std::cout << 2 * x << '\n';
    }
};

struct D6 : Base {
    using Base::Base;
    int extra = 7;
};

int main() {
    // D1 d1(42);
    D2 d2(42);
    D3 d3(42);
    std::cout << d3.extra << '\n';

    D4 d4(42);
    
    // D2 d5 = d2;
    
    std::cout << "============\n";
    D6 a(42);
    a.extra = 99;
    D6 b = a;
    std::cout << b.extra << '\n';   // 99


    return 0;
}