// Copyright 2025 Ekaterina Ushnitskaya

#ifndef TRIANGLE_MATRIX_TRIANGLE_MATRIX_X
#define TRIANGLE_MATRIX_TRIANGLE_MATRIX_X

#include <iostream>
#include <stdexcept>
template <class T>
class Matrix;
#include "../lib_matrix/matrix.h"

template <class T>
class TriangleMatrix : public Matrix<T> {
    size_t _n;
public:
    TriangleMatrix() : Matrix<T>(), _n(0) {}
    explicit TriangleMatrix(size_t n) : Matrix<T>(n, n), _n(n) {
        this->_rows = n;
        this->_cols = n;
        this->_size = n;
        this->_capacity = n + TVector<T>::RESERVE_MEMORY;
        this->_deleted = 0;
        this->_data = new MathVector<T>[this->_capacity];
        this->_states = new State[this->_capacity];

        for (size_t i = 0; i < n; i++) {
            this->_data[i] = MathVector<T>(n - i);
            this->_states[i] = busy;
            for (size_t j = 0; j < n - i; ++j) {
                this->_data[i][j] = T{};
            }
        }
        for (size_t i = n; i < this->_capacity; i++) {
            this->_states[i] = empty;
        }

    }
    TriangleMatrix(const TriangleMatrix<T>& other) : Matrix<T>(other), _n(other._n) {}
    ~TriangleMatrix() = default;
    T& at(size_t i, size_t j) {
        if (i >= _n || j >= _n) {
            throw std::out_of_range("Index out of range");
        }
        if (i > j) {
            static T zero{};
            return zero;
        }
        return this->_data[i][j - i];
    }
    const T& at(size_t i, size_t j) const {
        if (i >= _n || j >= _n) {
            throw std::out_of_range("Index out of range");
        }
        if (i > j) {
            static const T zero{};
            return zero;
        }
        return this->_data[i][j - i];
    }
    /*TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other) noexcept {
        in_development();
        return *this;
    }

    TriangleMatrix<T>& operator=(TriangleMatrix<T>&& other) noexcept {
        in_development();
        return *this;
    }

    TriangleMatrix<T> add_matrices(const TriangleMatrix<T>& other) const {
        in_development();
        return TriangleMatrix<T>();
    }

    TriangleMatrix<T> subtract_matrices(const TriangleMatrix<T>& other) const {
        in_development();
        return TriangleMatrix<T>();
    }

    TriangleMatrix<T> multiply_matrices(const TriangleMatrix<T>& other) const {
        in_development();
        return TriangleMatrix<T>();
    }

    MathVector<T>& operator[](size_t other) {
        in_development();
    }

    const MathVector<T>& operator[](size_t row) const {
        in_development();
    }

    friend std::ostream& operator<< <>(std::ostream& out, const TriangleMatrix<T>& matrix);*/
};
/*
template <class T>
std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& matrix) {
    in_development();
    out << " ";
    return out;
}
*/

#endif // TRIANGLE_MATRIX_TRIANGLE_MATRIX_X