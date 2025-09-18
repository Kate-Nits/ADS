// Copyright 2025 Ekaterina Ushnitskaya

#ifndef TRIANGLE_MATRIX_TRIANGLE_MATRIX_X
#define TRIANGLE_MATRIX_TRIANGLE_MATRIX_X

#include <iostream>
#include <stdexcept>

#include "../lib_matrix/matrix.h"

/*
template <class T>
class TriangleMatrix : public TMatrix<T> {
    size_t _n;
public:
    TriangleMatrix() noexcept = default;
    TriangleMatrix(std::size_t n) {
        in_development();
        _n = n;
    }

    TriangleMatrix(const TriangleMatrix<T>& other) = default;
    TriangleMatrix(TriangleMatrix<T>&& other) noexcept = default;
    ~TriangleMatrix() = default;

    TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other) noexcept {
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

    friend std::ostream& operator<< <>(std::ostream& out, const TriangleMatrix<T>& matrix);
};

template <class T>
std::ostream& operator<<(std::ostream& out, const TriangleMatrix<T>& matrix) {
    in_development();
    out << " ";
    return out;
}
*/


#endif // TRIANGLE_MATRIX_TRIANGLE_MATRIX_X