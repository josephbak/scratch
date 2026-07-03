#include <iostream>
#include <type_traits>

template <typename T>
void probe(T&& x) {
    std::cout << "T is lvalue ref? " << std::is_lvalue_reference_v<T> << '\n';
    std::cout << "T is rvalue ref? " << std::is_rvalue_reference_v<T> << '\n';
    std::cout << "x itself is lvalue? " << /* is `x` used-by-name an lvalue? */ '\n';
} 


int main() {

    int n = 5;
    probe(n);              // (a) lvalue
    std::cout << '\n';
    probe(5);              // (b) rvalue literal
    std::cout << '\n';
    probe(std::move(n));   // (c) xvalue (rvalue via move-cast)
    std::cout << '\n';

    // predict (a): T = int& , T&& = int& && = int&      (write "int&", not "T&")
    // predict (b): T = int , T&& = int&&               (no collapse)
    // predict (c): T = int , T&& = int&&

    return 0;
}