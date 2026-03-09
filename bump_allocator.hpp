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

    // copy constructor
    BumpAllocator(const BumpAllocator<T>& other)
    : pool(new T[other.cap]), curr(pool), cap(other.cap){
        // need to copy each element from the beginning to curr

        T* ptr = other.pool; // pointer copy
        while (ptr < other.curr){
            *curr = *ptr;
            curr += 1; // move by the size of T
            ptr += 1;
        }
    }

    // copy assignment
    BumpAllocator& operator=(const BumpAllocator<T>& other){
        if (this == &other) return *this; // in the self-assignment case

        delete[] pool;
        pool = new T[other.cap];
        curr = pool;
        cap = other.cap;

        T* ptr = other.pool; // pointer copy
        while (ptr < other.curr){
            *curr = *ptr;
            curr += 1; // move by the size of T
            ptr += 1;
        }
        return *this;
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