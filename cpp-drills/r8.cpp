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
        return rows_;        
    }
};

Matrix multiply(const Matrix& a, const Matrix& b) {
    std::size_t a_cols = a.get_cols();
    std::size_t a_rows = a.get_rows();
    std::size_t b_cols = b.get_cols();
    std::size_t b_rows = b.get_rows();

    assert(a_cols == b_rows && "inner dimensions must match");

    Matrix C(a_rows, b_cols);

    for (std::size_t i = 0; i < a_rows; ++i) {
        for (std::size_t j = 0; j < b_cols; ++j) {
            double sum = 0.0;
            for (std::size_t k = 0; k < a_cols; ++k) {
                sum += a(i, k) * b(k, j);
            }
            C(i, j) = sum;
        }

    }

    return C;
}

// RVO
Matrix make() {
    Matrix m(100, 100);
    return m;   // moved out (or elided entirely) — no copy of the big buffer
}

int main() {
    // Matrix a(2, 3);
    // a(0,0)=1; a(0,1)=2; a(0,2)=3;
    // a(1,0)=4; a(1,1)=5; a(1,2)=6;

    // Matrix b(3, 2);
    // b(0,0)=7;  b(0,1)=8;
    // b(1,0)=9;  b(1,1)=10;
    // b(2,0)=11; b(2,1)=12;

    // Matrix c = multiply(a, b);
    // // expected:
    // // c(0,0)=1*7+2*9+3*11=58   c(0,1)=1*8+2*10+3*12=64
    // // c(1,0)=4*7+5*9+6*11=139  c(1,1)=4*8+5*10+6*12=154
    // for (std::size_t i=0;i<2;++i){ for(std::size_t j=0;j<2;++j) std::cout<<c(i,j)<<" "; std::cout<<'\n'; }
    // // 58 64
    // // 139 154


    Matrix I(3,3);
    I(0,0)=1; I(1,1)=1; I(2,2)=1;   // identity (rest are 0 from your zero-init ctor)
    Matrix m(3,3);
    for (std::size_t i=0;i<3;++i) for (std::size_t j=0;j<3;++j) m(i,j)=i*3+j;  // 0..8
    Matrix r = multiply(I, m);   // r should equal m exactly

    for (std::size_t i=0;i<3;++i){ for(std::size_t j=0;j<3;++j) std::cout<<r(i,j)<<" "; std::cout<<'\n'; }

    return 0;
}