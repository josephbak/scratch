// loop.cpp — toggle the line below
#include <iostream>
int main() {
    for (int i = 0; i < 100000; i++) {
        // std::cout << i << '\n';        // version A
        std::cout << i << std::endl; // version B
    }
}