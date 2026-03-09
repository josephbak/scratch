#include <iostream>
#include "bump_allocator.hpp"

int main(int argc, char* argv[]){
    // auto ball = new BumpAllocator(1024);
    // auto ptr = ball->allocate(sizeof(int));

    BumpAllocator allocator(1024);
    allocator.allocate(sizeof(int));  // dot, not arrow
    auto ptr = allocator.allocate(sizeof(int));


    int* iptr = reinterpret_cast<int*>(ptr);
    *iptr = 42;

    std::cout << *iptr << std::endl;
}