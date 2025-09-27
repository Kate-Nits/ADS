// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_MATHVECTOR_MATHVECTOR_H
#define LIB_MATHVECTOR_MATHVECTOR_H

#include <initializer_list> // ����� ��� ������������ �� {}

#include "../lib_tvector/tvector.h"
#include "../lib_algorithms/algorithms.h"

template <class T>
class MathVector : public TVector<T> {
public:
    using TVector<T>::TVector; //�������� ��� ������������ �� TVector
    MathVector(const MathVector<T>& other) : TVector<T>(other) {}
    MathVector(const std::initializer_list<T> list) {
        this->_size = list.size();
        this->_capacity = this->_size + TVector<T>::RESERVE_MEMORY;
        this->_deleted = 0;
        this->_data = new T[this->_capacity];
        this->_states = new State[this->_capacity];
        size_t i = 0;
        for (const auto& value : list) { //auto ������������� ���������� ��� �� list
            this->_data[i] = value;
            this->_states[i] = busy;
            ++i;
        }
        for (; i < this->_capacity; ++i) {
            this->_states[i] = empty;
        }
    }

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
        in_development();
        return MathVector<T>();
    }

    MathVector<T> operator*(const T& scalar) const {
        in_development();
        return MathVector<T>();
    }

    MathVector<T>& operator+=(const MathVector<T>& other) {
        in_development();
        return *this;
    }
    MathVector<T>& operator-=(const MathVector<T>& other) {
        in_development();
        return *this;
    }
    MathVector<T>& operator*=(const T& scalar) {
        in_development();
        return *this;
    }
    T dot(const MathVector<T>& other) const { // ��������� ������������
        in_development();
        return T();
    }
};


#endif // LIB_MATHVECTOR_MATHVECTOR_H
