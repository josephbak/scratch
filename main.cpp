#include <iostream>
#include "bump_allocator.hpp"

int main(int argc, char* argv[]){

    // BumpAllocator<int> allocator(1024);

    // for (int i = 0; i < 300; ++i) {
    //     allocator.allocate(); 
    // }

    // auto iptr = allocator.allocate(); // dot, not arrow
    // int* iptr = reinterpret_cast<int*>(ptr);

    // if (iptr) {
    // *iptr = 42;
    // std::cout << *iptr << std::endl;
    // } else {
    //     std::cout << "allocation failed" << std::endl;
    // }

    BumpAllocator<int> a(1024);
    int* p1 = a.allocate();
    *p1 = 42;

    // BumpAllocator<int> b = a;  // invokes copy constructor
    BumpAllocator<int> b(1024);
    int* p2 = b.allocate();
    *p2 = 99;

    b = a;  // copy assignment — b's old pool should be freed, b gets a's data

    int* p3 = b.allocate();  // allocate from b's new state
    *p3 = 77;

    std::cout << *p1 << std::endl;  // 42 — a unchanged
    std::cout << *p3 << std::endl;  // 77 — b working correctly

    // test self-assignment
    a = a;
    std::cout << *p1 << std::endl;  // 42 — should still work, not crash
}