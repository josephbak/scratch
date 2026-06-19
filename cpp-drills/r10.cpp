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
    SmallVector<int, 4> v;
    v.push_back(1); v.push_back(2); v.push_back(3);
    std::cout << "size " << v.size() << " cap " << v.capacity() << '\n';  // size 3 cap 4 (inline)

    v.push_back(4);   // fills inline (size 4 == cap 4)
    v.push_back(5);   // SPILL → grows to heap, cap becomes 8
    std::cout << "size " << v.size() << " cap " << v.capacity() << '\n';  // size 5 cap 8 (heap)

    for (std::size_t i = 0; i < v.size(); ++i) std::cout << v[i] << " ";  // 1 2 3 4 5
    std::cout << '\n';

    v.push_back(6); v.push_back(7); v.push_back(8); v.push_back(9);  // fills to 8, then spills to 16
    std::cout << "size " << v.size() << " cap " << v.capacity() << '\n';  // size 9 cap 16
}                                                                          // dtor frees heap (data_ != inline_)
