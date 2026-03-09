#include <cstddef>  // std::byte, std::size_t

// // template <typename T>
// // class BumpAllocator {
// //     // allocate a block, hand out pointers, free all at once

// };

class BumpAllocator {
    // what data members do you need?
    std::byte* pool;   // start of the pool
    std::byte* curr;   // current free position
    std::size_t cap;   // total capacity


    BumpAllocator(std::size_t cap)
    : pool(new std::byte[cap]), curr(pool), cap(cap) {} // member initializer list

    ~BumpAllocator(){
        delete[] pool;
    }

    public:

    std::byte* allocate(std::size_t size){
        if (curr - pool + size <= cap) {
            curr += size;
            return curr - size;
        }
        return nullptr;
    }

    void reset(){
        curr = pool;
    }
};