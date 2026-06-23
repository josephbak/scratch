#include <iostream>
#include <cstddef> 
#include <cassert>
#include <utility>
#include <memory>
#include <algorithm>

class Matrix {
    std::size_t rows_;
    std::size_t cols_;
    std::unique_ptr<double[]> data_;

public:

    Matrix(std::size_t r, std::size_t c): rows_(r), cols_(c), data_(std::make_unique<double[]>(r * c)) {}

    Matrix(const Matrix&)            = delete;   // no copy ctor
    Matrix& operator=(const Matrix&) = delete;   // no copy assignment
    Matrix(Matrix&&) noexcept = default;   // DEFAULT move ctor — compiler generates it
    Matrix& operator=(Matrix&&) noexcept = default;   // DEFAULT move assignment

    double& operator()(std::size_t i, std::size_t j) {
        assert(i < rows_ && j < cols_ && "index out of bounds");
        return data_[i * cols_ + j]; 
    }

    double  operator()(std::size_t i, std::size_t j) const {   // returns by value (read-only)
        assert(i < rows_ && j < cols_ && "index out of bounds");
        return data_[i * cols_ + j];
    }

    std::size_t get_cols() const{
        return cols_;        
    }
    std::size_t get_rows() const{
        return rows_;        
    }

    Matrix clone() const {
        Matrix copy(rows_, cols_);
        std::copy(data_.get(), data_.get() + rows_*cols_, copy.data_.get());
        return copy;
    }
};

Matrix make() {
    Matrix m(100, 100);
    return m;   // moved out (or elided entirely) — no copy of the big buffer
}

int main() {
    Matrix a(2, 2);
    a(0,0) = 1.0;
    Matrix b = a.clone();   // explicit deep copy
    b(0,0) = 99.0;          // modify the clone
    std::cout << a(0,0) << " " << b(0,0) << '\n';   // expect: 1 99 — independent buffers

}