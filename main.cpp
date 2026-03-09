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

    BumpAllocator<int> b = a;  // invokes copy constructor
    int* p2 = b.allocate();
    *p2 = 99;

    std::cout << *p1 << std::endl;  // should print 42
    std::cout << *p2 << std::endl;  // should print 99

}