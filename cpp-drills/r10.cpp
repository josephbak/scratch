#include <iostream>
#include <cassert>
#include <cstddef>

template <typename T, std::size_t N>
class SmallVector {
    T inline_[N];
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

public:
    SmallVector() {
        data_ = inline_;
        size_ = 0;
        capacity_ = N;
    }

    ~SmallVector() {
        if (inline_ != data_) {
            delete[] data_;
        }
    }

    // copy constructor
    SmallVector(const SmallVector& o) : size_(o.size_) {
        if (o.size_ <= N) {
            data_ = inline_; capacity_ = N;
        }else{
            capacity_ = o.capacity_;
            data_ = new T[capacity_];
        }
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = o.data_[i];   // one loop, both modes
        }
    }

    // copy assignment
    SmallVector& operator=(const SmallVector& o) {
        if (this == &o) return *this;
        if (data_ != inline_) {
            // free if there is existing heap buffer
            delete[] data_;
        }
        size_ = o.size_;
        if (o.size_ <= N) {
            data_ = inline_;
            capacity_ = N;
        }else {
            data_ = new T[o.capacity_];
            capacity_ = o.capacity_;
        }
        for (std::size_t i = 0; i < o.size_; ++i) {
            data_[i] = o.data_[i];
        }
        return *this;
    }

    // move constructor
    SmallVector(SmallVector&& o) noexcept : size_(o.size_) {
        if (o.data_ == o.inline_) {
            // small mode -> can't steal -> must copy
            // can't transfer ownership of memory that's physically part of another object — it dies when o dies.
            capacity_ = N;
            data_ = inline_;
            // copy
            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = o.data_[i];
            }
        } else {
            capacity_ = o.capacity_;
            data_ = o.data_; // steal
            o.data_ = o.inline_;
            o.size_ = 0;
            o.capacity_ = N;
        }
    }

    // move assignment
    SmallVector& operator=(SmallVector&& o) noexcept {
        if (this == &o) return *this;
        if (data_ != inline_) {
            // need to free
            delete[] data_;
        }
        size_ = o.size_;
        if (o.data_ == o.inline_) {
            capacity_ = N;
            data_ = inline_;
            // copy since we can't move
            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = o.data_[i];
            }
        } else {
            capacity_ = o.capacity_;
            data_ = o.data_; // steal
            o.data_ = o.inline_;
            o.size_ = 0;
            o.capacity_ = N;
        }
        return *this;
    }


    void push_back(const T& value) {
        if (size_ == capacity_) {
            std::size_t new_cap = capacity_ * 2;
            T* tmp = new T[new_cap];
            for (std::size_t i = 0; i < size_ ; ++i) {
                tmp[i] = data_[i];
            }
            if (data_ != inline_) {     // ← free old buffer ONLY if it was heap
                std::cout << "one heap data freed" << '\n';
                delete[] data_;        //    (don't delete[] inline_!)
            }
            capacity_ = new_cap;
            data_ = tmp;
        }
        data_[size_] = value;
        size_++;
    }

    T& operator[](std::size_t i){
        assert(i < size_ && "index should be leq to the size");
        return data_[i];
    }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    
};

int main() {
    SmallVector<int,4> a;
    for (int i = 0; i < 6; ++i) a.push_back(i);   // a spills to heap (size 6, cap 8)

    SmallVector<int,4> b = a;              // copy ctor — b independent deep copy
    b[0] = 99;
    std::cout << a[0] << " " << b[0] << '\n';      // 0 99 — proves deep copy

    SmallVector<int,4> c;
    c = a;                                 // copy assign
    std::cout << c[0] << " " << c.size() << '\n';  // 0 6

    SmallVector<int,4> d = std::move(a);   // move ctor (large mode → steal)
    std::cout << d.size() << '\n';         // 6 (a now gutted but valid)

    SmallVector<int,4> e;
    e = std::move(d);                      // move assign (large mode → steal)
    std::cout << e.size() << '\n';         // 6

    return 0;
}
