#include <iostream>
#include "bump_allocator.hpp"

int main(int argc, char* argv[]){
    // auto ball = new BumpAllocator(1024);
    // auto ptr = ball->allocate(sizeof(int));

    BumpAllocator<int> allocator(1024);

    // for (int i = 0; i < 300; ++i) {
    //     allocator.allocate(); 
    // }

    auto iptr = allocator.allocate(); // dot, not arrow
    // int* iptr = reinterpret_cast<int*>(ptr);

    if (iptr) {
    *iptr = 42;
    std::cout << *iptr << std::endl;
    } else {
        std::cout << "allocation failed" << std::endl;
    }

}