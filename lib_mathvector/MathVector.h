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

    MathVector<T>& operator=(const MathVector<T>& other) noexcept {
        this->assign(other);
        return *this;
    }

    MathVector<T>& operator=(MathVector<T>&& other) noexcept {
        in_development();
        return *this;
    }

    T dot(const MathVector<T>& other) const { // Скалярное произведение
        in_development();
        return T();
    }


    MathVector<T> operator+(const MathVector<T>& other) const {
        in_development();
        return MathVector<T>();
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

};


#endif // LIB_MATHVECTOR_MATHVECTOR_H
