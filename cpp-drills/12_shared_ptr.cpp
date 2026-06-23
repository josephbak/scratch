#include <iostream>
#include <memory>
#include <cassert>

struct Tracked {
    int id;
    Tracked(int i) : id(i) { std::cout << "construct " << id << '\n'; }
    ~Tracked() { std::cout << "destruct " << id << '\n'; }
};

template <typename T>
class SharedPtr {
private:
    T* ptr_;
    long* count_;

    void release() {                          // ordinary helper, NOT the destructor
        if (count_ && --*count_ == 0) {
            delete ptr_;
            delete count_;
        }
    }

public:
    explicit SharedPtr(T* p) : ptr_(p), count_(new long(1)) {}

    ~SharedPtr() { 
        release();
    }

    // copy ctor
    SharedPtr(const SharedPtr& o) : ptr_(o.ptr_), count_(o.count_) { ++*count_; }

    // copy assignment
    SharedPtr& operator=(const SharedPtr& o) {
        if (this == &o) return *this;

        // release our CURRENT object (we're leaving it)
        release();

        // adopt o's object (join it)
        ptr_ = o.ptr_;
        count_ = o.count_;
        ++*count_;

        return *this;
    }

    // move ctor
    SharedPtr(SharedPtr&& o) noexcept : ptr_(o.ptr_), count_(o.count_) {
        o.ptr_ = nullptr;
        o.count_ = nullptr;
    }

    // move assignment
    SharedPtr& operator=(SharedPtr&& o) noexcept {
        if (this == &o) return *this;

        release();

        ptr_ = o.ptr_;
        count_ = o.count_;

        o.ptr_ = nullptr;
        o.count_ = nullptr;

        return *this;
    }


    long use_count() const {return *count_;}
    T* get() const { return ptr_; }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

};


int main() {
    SharedPtr<Tracked> a(new Tracked(1));
    std::cout << a.use_count() << '\n';      // 1
    SharedPtr<Tracked> b = std::move(a);     // move — count stays 1, a nulled
    std::cout << b.use_count() << '\n';      // 1 (NOT 2 — proves move ≠ copy)
    std::cout << b->id << '\n';              // operator-> : 1
    std::cout << (*b).id << '\n';            // operator* : 1
    // a is moved-from (null count_); destroying it must not crash — proves the guard

    return 0;
}