// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_MATRIX_MATRIX_H
#define LIB_MATRIX_MATRIX_H

#include <iostream>
#include <stdexcept>

#include "../lib_algorithms/algorithms.h"
#include "../lib_mathvector/MathVector.h"

template <class T>
class TMatrix : public MathVector< MathVector<T> > {
    size_t _rows;
    size_t _cols;
public:
    TMatrix() noexcept = default;
    TMatrix(size_t rows, size_t cols) {
        in_development();
        _rows = rows;
        _cols = cols;
    }

    TMatrix(const TMatrix<T>& other) = default;
    TMatrix(TMatrix<T>&& other) noexcept = default;
    ~TMatrix() = default;

    TMatrix<T>& operator=(const TMatrix<T>& other) noexcept {
        in_development();
        return *this;
    }

    TMatrix<T>& operator=(TMatrix<T>&& other) noexcept {
        in_development();
        return *this;
    }

    MathVector<T>& operator[](size_t row) {
        in_development();
    }

    const MathVector<T>& operator[](size_t row) const {
        in_development();
    }

    TMatrix<T> add_matrices(const TMatrix<T>& other) const {
        in_development();
        return TMatrix<T>();
    }

    TMatrix<T> subtract_matrices(const TMatrix<T>& other) const {
        in_development();
        return TMatrix<T>();
    }

    TMatrix<T> multiply_matrices(const TMatrix<T>& other) const {
        in_development();
        return TMatrix<T>();
    }

    size_t rows() const noexcept {
        in_development();
        return _rows;
    }

    size_t cols() const noexcept {
        in_development();
        return _cols;
    }

    void resize(size_t newRows, size_t newCols) {
        in_development();
        _rows = newRows;
        _cols = newCols;
    }

    void transpose() {
        in_development();
    }

    void print() const {
        in_development();
    }

    friend std::ostream& operator<< <>(std::ostream& out, const TMatrix<T>& matrix);
};


template <class T>
std::ostream& operator<<(std::ostream& out, const TMatrix<T>& matrix) {
    in_development();
    out << "";
    return out;
}

#endif // LIB_MATRIX_MATRIX_H
