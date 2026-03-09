#include <cstddef>  // std::byte, std::size_t

template <typename T>
class BumpAllocator {
    // allocate a block, hand out pointers, free all at once
    T* pool;   // start of the pool
    T* curr;   // current free position
    std::size_t cap;   // total capacity

    public:

    BumpAllocator(std::size_t cap)
    : pool(new T[cap]), curr(pool), cap(cap) {} // member initializer list

    ~BumpAllocator(){
        delete[] pool;
    }

    T* allocate(){
        if (curr - pool + 1 <= cap) {
            T* ptr = curr;
            curr += 1;
            return ptr;
        }
        return nullptr;
    }
    
    void reset(){
        curr = pool;
    }
};