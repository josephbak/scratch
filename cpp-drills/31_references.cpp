#include <iostream>


int main() {
    int n = 5;

    // predict compile? Y/N + why
    int&        a = n;              // (1) lvalue ref ← lvalue
    // int&        b = 5;              // (2) lvalue ref ← rvalue
    const int&  c = n;              // (3) const lvalue ref ← lvalue
    const int&  d = 5;              // (4) const lvalue ref ← rvalue
    int&&       e = 5;              // (5) rvalue ref ← rvalue
    // int&&       f = n;              // (6) rvalue ref ← lvalue
    int&&       g = std::move(n);   // (7) rvalue ref ← moved lvalue

    int x = 1;
    int& r = x;
    r = 99;
    // predict: what does x print? why?
    std::cout << x << '\n';

    return 0;
}