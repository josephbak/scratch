#include <iostream>
#include <cstddef> 
#include <cassert>
#include <utility>

class Matrix {
    std::size_t rows_;
    std::size_t cols_;
    double* data_;

public:

    Matrix(std::size_t r, std::size_t c): rows_(r), cols_(c), data_(new double[r * c]{}) {}
    ~Matrix(){
        delete[] data_;
    }

    // copy constructor
    Matrix(const Matrix& other) 
        : rows_(other.rows_), cols_(other.cols_), data_(new double[other.rows_ * other.cols_]{}) {
        std::cout << "COPY CTOR" << '\n';
        // this->rows_ = other.rows_;
        // this->cols_ = other.cols_;
        // this->data_ = new double[rows_ * cols_]{};
        for (std::size_t i = 0; i < rows_; ++i){
            for (std::size_t j = 0; j < cols_; ++j) {
                data_[i * cols_ + j] = other.data_[i * cols_ + j];
            }
        }
    }
    // copy assignment
    Matrix& operator=(const Matrix& other) {
        if (this == &other) {return *this;} // self-assignment guard
        std::cout << "COPY ASSIGN" << '\n';

        delete[] data_;                              // free old buffer (its size no longer valid)
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = new double[rows_ * cols_];

        for (std::size_t i = 0; i < rows_; ++i){
            for (std::size_t j = 0; j < cols_; ++j) {
                data_[i * cols_ + j] = other.data_[i * cols_ + j];
            }
        }
        return *this;
    }
    
    // move constructor
    Matrix(Matrix&& other) noexcept
        : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {   // STEAL the pointer
        std::cout << "MOVE CTOR" << '\n';
        other.data_ = nullptr;     // null the source so ITS destructor won't free our buffer
        other.rows_ = 0;
        other.cols_ = 0;
    }

    // move assignment
    Matrix& operator=(Matrix&& other) noexcept {
        if (this == &other) return *this;   // self move guard

        std::cout << "MOVE ASSIGN" << '\n';
        delete[] data_;                     // free this's current buffer
        rows_ = other.rows_;                  // steal
        cols_ = other.cols_;
        data_ = other.data_;
        other.data_ = nullptr;                // null source
        other.rows_ = 0;
        other.cols_ = 0;
        return *this;
    }

    double& operator()(std::size_t i, std::size_t j) {
        assert(i < rows_ && j < cols_ && "index out of bounds");
        return data_[i * cols_ + j]; 
    }

    double  operator()(std::size_t i, std::size_t j) const {   // returns by value (read-only)
        assert(i < rows_ && j < cols_);
        return data_[i * cols_ + j];
    }

    std::size_t get_cols() const{
        return cols_;        
    }
    std::size_t get_rows() const{
        return cols_;        
    }
};

Matrix make() {
    Matrix m(100, 100);
    return m;   // moved out (or elided entirely) — no copy of the big buffer
}

int main() {
    // Matrix m(2, 3);          // 2 rows, 3 cols — calls your constructor, allocates 6 doubles
    // m(0, 0) = 1.0;           // operator() returns a reference, so you can assign
    // m(0, 1) = 2.0;
    // m(1, 2) = 9.0;

    // std::cout << "m(0,0) = " << m(0,0) << '\n';   // read back
    // std::cout << "m(1,2) = " << m(1,2) << '\n';

    // Matrix a(2, 2);
    // a(0,0) = 1; a(1,1) = 9;
    // Matrix b(2, 2);
    // b = a;            // copy assignment
    // b(0,0) = 100;     // modify the copy
    // // confirm a(0,0) is still 1 — proves deep copy (independent buffers)
    // std::cout << a(0,0) << " " << b(0,0) << '\n';   // expect: 1 100
    // Matrix a(2, 2);
    // a(0,0) = 1;

    // Matrix b = std::move(a);    // MOVE CTOR — should print "MOVE CTOR", a is now gutted
    // std::cout << "b(0,0) = " << b(0,0) << '\n';   // 1 — b stole a's buffer

    // Matrix c(2, 2);
    // c = std::move(b);           // MOVE ASSIGN — should print "MOVE ASSIGN"
    // std::cout << "c(0,0) = " << c(0,0) << '\n';   // 1

    // Matrix a(2, 2);
    // a(0,0) = 1;
    // Matrix b = std::move(a);    // expect: MOVE CTOR
    // std::cout << "b(0,0) = " << b(0,0) << '\n';   // expect: 1
    // Matrix c(2, 2);
    // c = std::move(b);           // expect: MOVE ASSIGN
    // std::cout << "c(0,0) = " << c(0,0) << '\n';   // expect: 1
    // Matrix x = make();

    return 0;
}