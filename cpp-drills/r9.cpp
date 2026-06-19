#include <iostream>
#include <utility>

template <typename T>
class Span {
    T* ptr_;
    std::size_t len_;

public:
    Span(T* p, std::size_t n) : ptr_(p), len_(n) {}
    Span(std::vector<T>& v) : ptr_(v.data()), len_(v.size()) {}

    std::size_t size() const { return len_; }

    T& operator[](std::size_t i) {
        assert(i < len_ && "Span index out of bounds");
        return ptr_[i];
    }

    T* begin() const { return ptr_; }
    T* end() const { return ptr_ + len_; } // ptr_ advanced by len_ ELEMENTS = one-past-last
};


int mian() {

}