// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_MATRIX_MATRIX_H
#define LIB_MATRIX_MATRIX_H

#include "../lib_algorithms/algorithms.h"
#include "../lib_mathvector/MathVector.h"

template <class T>
class TMatrix : public MathVector<MathVector<T>> {
public:
    TMatrix<T>& add_matrices(const TMatrix<T>& other) {
        in_development();
        return *this;
    }

    TMatrix<T>& operator=(const TMatrix<T>& other) noexcept {
        in_development();
        return *this;
    }

    TMatrix<T>& subtract_matrices(const TMatrix<T>& other) {
        in_development();
        return *this;
    }

    TMatrix<T>& multiply_matrices(const TMatrix<T>& other) {
        in_development();
        return *this;
    }
};

#endif // LIB_MATRIX_MATRIX_H
