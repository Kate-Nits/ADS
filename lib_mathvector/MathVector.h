// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_MATHVECTOR_MATHVECTOR_H
#define LIB_MATHVECTOR_MATHVECTOR_H

#include <initializer_list> // нужно для конструктора от {}

#include "../lib_tvector/tvector.h"
#include "../lib_algorithms/algorithms.h"

template <class T>
class MathVector : public TVector<T> {
public:
    using TVector<T>::TVector; //наследую все конструкторы от TVector
    MathVector(const MathVector<T>& other) : TVector<T>(other) {}
    MathVector(const std::initializer_list<T> list) {
        this->_size = list.size();
        this->_capacity = this->_size + TVector<T>::RESERVE_MEMORY;
        this->_deleted = 0;
        this->_data = new T[this->_capacity];
        this->_states = new State[this->_capacity];
        size_t i = 0;
        for (const auto& value : list) { //auto автоматически определяет тип из list
            this->_data[i] = value;
            this->_states[i] = busy;
            ++i;
        }
        for (; i < this->_capacity; ++i) {
            this->_states[i] = empty;
        }
    }
    // Может добавить конструктор преобразования типа из int в double?
    MathVector<T> operator+(const MathVector<T>& other) const {
        if (this->_size != other._size) {
            throw std::invalid_argument("Vectors should have same size for addition");
        }
        MathVector<T> result(this->_size);
        for (size_t i = 0; i < this->_size; ++i) {
            result._data[i] = this->_data[i] + other._data[i];
            result._states[i] = busy;
        }
        return result;
    }
    MathVector<T> operator-(const MathVector<T>& other) const {
        if (this->_size != other._size) {
            throw std::invalid_argument("Vectors should have same size for subtraction");
        }
        MathVector<T> result(this->_size);
        for (size_t i = 0; i < this->_size; ++i) {
            result._data[i] = this->_data[i] - other._data[i];
            result._states[i] = State::busy;
        }
        return result;
    }

    MathVector<T> operator*(const T& scalar) const {
        MathVector<T> result(this->_size);
        for (size_t i = 0; i < this->_size; ++i) {
            result._data[i] = this->_data[i] * scalar;
        }
        return result;
    }

    T operator*(const MathVector& other_vec) const {
        if (this->_size != other_vec._size) {
            throw std::invalid_argument("Vectors should have same size for dot product");
        }
        T result = 0;
        for (size_t i = 0; i < this->_size; ++i) {
            result += this->_data[i] * other_vec._data[i];
        }
        return result;
    }

    MathVector<T>& operator+=(const MathVector<T>& other) {
        if (this->_size != other._size) {
            throw std::invalid_argument("Vectors should have same size for addition");
        }
        for (size_t i = 0; i < this->_size; ++i) {
            this->_data[i] = this->_data[i] + other._data[i];
        }
        return *this;
    }
    MathVector<T>& operator-=(const MathVector<T>& other) {
        if (this->_size != other._size) {
            throw std::invalid_argument("Vectors should have same size for subtraction");
        }
        for (size_t i = 0; i < this->_size; ++i) {
            this->_data[i] = this->_data[i] - other._data[i];
        }
        return *this;
    }
    MathVector<T>& operator*=(const T& scalar) {
        for (size_t i = 0; i < this->_size; ++i) {
            this->_data[i] = this->_data[i] * scalar;
        }
        return *this;
    }

    double length() const { // длинна вектора
        T sum = 0;
        for (size_t i = 0; i < this->_size; i++) {
            sum += this->_data[i] * this->_data[i];
        }
        return std::sqrt((double)sum);
    }
};

#endif // LIB_MATHVECTOR_MATHVECTOR_H
