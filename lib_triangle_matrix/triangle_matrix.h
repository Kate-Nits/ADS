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
    size_t n() const noexcept { return _n;  }
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
    MathVector<T>& operator[](size_t i) {
        if (i >= _n) {
            throw std::out_of_range("Index out of range");
        }
        return this->_data[i];
    }
    const MathVector<T>& operator[](size_t row) const {
        if (i >= _n) {
            throw std::out_of_range("Index out of range");
        }
        return this->_data[i];
    }

    TriangleMatrix<T>& operator=(const TriangleMatrix<T>& other) noexcept {
        if (this != &other) {
            Matrix<T>::operator=(other);
            _n = other._n;
        }
        return *this;
    }

    TriangleMatrix<T> operator+(const TriangleMatrix<T>& other) const {
        if (_n != other._n) {
            throw std::invalid_argument("Triangle Matrix should have the same size for addition");
        }
        TriangleMatrix<T> result(_n);
        for (size_t i = 0; i < _n; ++i) {
            for (size_t j = i; j < _n; ++j) {
                result.at(i, j) = this->at(i, j) + other.at(i, j);
            }
        }
        return result;
    }
    TriangleMatrix<T> operator-(const TriangleMatrix<T>& other) const {
        if (_n != other._n) {
            throw std::invalid_argument("Triangle Matrix should have the same size for subtraction");
        }
        TriangleMatrix<T> result(_n);
        for (size_t i = 0; i < _n; ++i) {
            for (size_t j = i; j < _n; ++j) {
                result.at(i, j) = this->at(i, j) - other.at(i, j);
            }
        }
        return result;
    }
    TriangleMatrix<T> operator*(const T scalar) const {
        TriangleMatrix<T> result(_n);
        for (size_t i = 0; i < _n; ++i) {
            for (size_t j = i; j < _n; ++j) {
                result.at(i, j) = this->at(i, j) * scalar;
            }
        }
        return result;
    }
    MathVector<T> operator*(const MathVector<T>& vec) const {
        if (_n != vec.size()) {
            throw std::invalid_argument("Size of vector should have same size of cols for mult");
        }
        MathVector<T> result(_n);
        for (size_t i = 0; i < _n; ++i) {
            for (size_t j = i; j < _n; ++j) {
                T sum{};
                for (size_t k = i; k <= j; ++k) {
                    sum += this->at(i, k) * vec.at(k);
                }
                result[i] = sum;
            }
        }
        return result;
    }
    TriangleMatrix<T> operator*(const TriangleMatrix<T>& other) const {
        if (_n != other._n) {
            throw std::invalid_argument("Triangle Matrix should have the same size for mult");
        }
        TriangleMatrix<T> result(_n);
        for (size_t i = 0; i < _n; ++i) {
            for (size_t j = i; j < _n; ++j) {
                T sum{};
                for (size_t k = i; k <= j; ++k) {
                    sum += this->at(i, k) * other.at(k, j);
                }
                result.at(i, j) = sum;
            }
        }
        return result;
    }
    
    friend std::ostream& operator<< <>(std::ostream& out, const TriangleMatrix<T>& matrix);
};
template <class T>
std::ostream& operator<< <>(std::ostream& out, const TriangleMatrix<T>& matrix) {
    for (size_t i = 0; i < matrix.n(); ++i) {
        out << "[ ";
        for (size_t j = 0; i < matrix.n(); ++j) {
            out << matrix.at(i, j) << "  ";
        }
        out << "]\n";
    }
    return out;
}

template <class T>
Matrix<T> operator+(const Matrix<T>& matrix, const TriangleMatrix<T>& triangle_matrix) {
    if (matrix.rows() != triangle_matrix.n() || matrix.cols() != triangle_matrix.n()) {
        throw std::invalid_argument("Matrixes should have the same size for addition");
    }
    Matrix<T> result(matrix.rows(), matrix.cols());
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            result[i][j] = matrix.at(i, j) + triangle_matrix.at(i, j);
        }
    }
    return result;
}
template <class T>
Matrix<T> operator+(const TriangleMatrix<T>& triangle_matrix, const Matrix<T>& matrix) {
    if (matrix.rows() != triangle_matrix.n() || matrix.cols() != triangle_matrix.n()) {
        throw std::invalid_argument("Matrixes should have the same size for addition");
    }
    Matrix<T> result(matrix.rows(), matrix.cols());
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            result[i][j] = matrix.at(i, j) + triangle_matrix.at(i, j);
        }
    }
    return result;
}
#endif // TRIANGLE_MATRIX_TRIANGLE_MATRIX_X