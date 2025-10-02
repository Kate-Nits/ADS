// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_MATRIX_MATRIX_H
#define LIB_MATRIX_MATRIX_H

#include <iostream>
#include <stdexcept>
template <class T>
class MathVector;
#include "../lib_mathvector/MathVector.h"


template <class T>
class Matrix : public MathVector<MathVector<T>> {
    size_t _rows; // строки
    size_t _cols; // столбцы
public:
    using MathVector<MathVector<T>>::MathVector; // наследую конструкторы
    Matrix() : MathVector<MathVector<T>>(), _rows(0), _cols(0) {}
    Matrix(size_t value_rows, size_t value_cols) : MathVector<MathVector<T>>(value_rows), _rows(value_rows), _cols(value_cols) {
        for (size_t i = 0; i < value_rows; ++i) {
            this->_data[i] = MathVector<T>(value_cols);
            this->_states[i] = busy;
            for (size_t j = 0; j < value_cols; ++j) {
                this->_data[i][j] = T{}; // {} нужны чтобы проинициализировался автоматом 0 и подстроился под тип
            }
        }
    }
    Matrix(const std::initializer_list<MathVector<T>> list) {
        if (list.size() == 0) { // без это поверки, если размер нулевой по умолчанию получиться list.begin() == list.end() 
            _rows = 0;
            _cols = 0;
            this->_size = 0;
            this->_capacity = TVector<T>::RESERVE_MEMORY;
            this->_deleted = 0;

            this->_data = new MathVector<T>[this->_capacity];
            this->_states = new State[this->_capacity];
            for (size_t i = 0; i < this->_capacity; ++i) {
                this->_states[i] = empty;
            }
            return;
        }
        _rows = list.size();
        _cols = list.begin()->size();

        this->_size = _rows;
        this->_capacity = _rows + TVector<T>::RESERVE_MEMORY;
        this->_deleted = 0;

        this->_data = new MathVector<T>[this->_capacity];
        this->_states = new State[this->_capacity];

        size_t i = 0;
        for (const auto& row : list) { //auto автоматически определяет тип из list
            if (row.size() != _cols) {
                throw std::invalid_argument("All rows must have the same size");
            }
            this->_data[i] = row;
            this->_states[i] = busy;
            ++i;
        }
        for (; i < this->_capacity; ++i) {
            this->_states[i] = empty;
        }
    }
    Matrix(const Matrix<T>& other) : MathVector<MathVector<T>>(other), _rows(other._rows), _cols(other._cols) {}

    size_t rows() const noexcept { return _rows; }
    size_t cols() const noexcept { return _cols; }
    T& at(size_t row, size_t col) { 
        if (row >= _rows) {
            throw std::out_of_range("Row index out of range");
        }
        if (col >= _cols) {
            throw std::out_of_range("Col index out of range");
        }
        return this->_data[row][col]; 
    }
    const T& at(size_t row, size_t col) const { 
        if (row >= _rows) {
            throw std::out_of_range("Row index out of range");
        }
        if (col >= _cols) {
            throw std::out_of_range("Col index out of range");
        }
        return this->_data[row][col]; 
    }
    MathVector<T>& operator[](size_t row) { return this->_data[row]; }
    const MathVector<T>& operator[](size_t row) const { return this->_data[row]; } // для столбцов должен вызваться [] от TVector

    Matrix<T>& operator=(const Matrix<T>& other) {
        if (this != &other) {
            MathVector<MathVector<T>>::operator=(other);
            _rows = other._rows;
            _cols = other._cols;
        }
        return *this;
    }

    Matrix<T>& transpose() { 
        Matrix<T> result(_cols, _rows);
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                result[j][i] = this->at(i, j);
            }
        }
        (*this) = result;
        return *this;
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        if (_rows != other._rows) {
            throw std::invalid_argument("Rows should have same size for addition");
        }
        if (_cols != other._cols) {
            throw std::invalid_argument("Cols should have same size for addition");
        }
        Matrix<T> result(_rows, _cols);
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                result[i][j] = this->at(i, j) + other.at(i, j);
            }
        }
        return result;
    }
    Matrix<T> operator-(const Matrix<T>& other) const {
        if (_rows != other._rows) {
            throw std::invalid_argument("Rows should have same size for subtraction");
        }
        if (_cols != other._cols) {
            throw std::invalid_argument("Cols should have same size for subtraction");
        }
        Matrix<T> result(_rows, _cols);
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                result[i][j] = this->at(i, j) - other.at(i, j);
            }
        }
        return result;
    }
    Matrix<T> operator*(const T scalar) const {
        Matrix<T> result(_rows, _cols);
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                result[i][j] = this->at(i, j) * scalar;
            }
        }
        return result;
    }
    MathVector<T> operator*(const MathVector<T>& vec) const {
        if (_cols != vec.size()) {
            throw std::invalid_argument("Size of vector should have same size of cols for mult");
        }
        MathVector<T> result(_rows);
        for (size_t i = 0; i < _rows; ++i) {
            result[i] = this->data(i) * vec;
        }
        return result;
    }
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (_cols != other.rows()) {
            throw std::invalid_argument("Cols of the first matrix should be equal rows of the second matrix for mult");
        }
        Matrix<T> result(_rows, other.cols());
        Matrix<T> transport_other = other;
        transport_other.transpose();
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < transport_other.rows(); ++j) {
                result[i][j] = (*this)[i] * transport_other[j];
            }
        }
        return result;
    }
    void print() const {
        for (size_t i = 0; i < _rows; ++i) {
            std::cout << "[ ";
            for (size_t j = 0; j < _cols; ++j) {
                std::cout << this->at(i, j) << "  ";
            }
            std::cout << "]" << std::endl;;
        }
    }
    friend std::ostream& operator<< <>(std::ostream& out, const Matrix<T>& matrix);
};
template <typename T>
std::ostream& operator<< <>(std::ostream& out, const Matrix<T>& matrix) {
    for (size_t i = 0; i < matrix.rows(); ++i) {
        out << "[ ";
        for (size_t j = 0; j < matrix.cols(); ++j) {
            out << matrix.at(i, j) << " ";
        }
        out << "]\n";
    }
    return out;
}
#endif // LIB_MATRIX_MATRIX_H