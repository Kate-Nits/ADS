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
    MathVector() : TVector<T>() {}
    MathVector(const MathVector<T>& other) : TVector<T>(other) {}
    MathVector(const std::initializer_list<T> list) {
        this->_size= list.size();
        this->_capacity = this->size()+ TVector<T>::RESERVE_MEMORY;
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
    template <typename U>
    MathVector(const MathVector<U>& other) {
        this->_size = other.size();
        this->_capacity = this->size() + TVector<T>::RESERVE_MEMORY;
        this->_deleted = 0;
        this->_data = new T[this->_capacity];
        this->_states = new State[this->_capacity];

        for (size_t i = 0; i < this->_size; ++i) {
            this->_data[i] = static_cast<T>(other.data(i)); // преобразование из U в T
            this->_states[i] = other.state(i);
        }
        for (size_t i = this->_size; i < this->_capacity; ++i) {
            this->_states[i] = State::empty;
        }
    }

    MathVector<T> operator+(const MathVector<T>& other) const;
    template <typename U>
    MathVector<std::common_type_t<T, U>> operator+(const MathVector<U>& other) const;
    
    MathVector<T> operator-(const MathVector<T>& other) const;
    template <typename U>
    MathVector<std::common_type_t<T, U>> operator-(const MathVector<U>& other) const;
    
    MathVector<T> operator*(const T& scalar) const;
    template <typename U>
    MathVector<std::common_type_t<T, U>> operator*(const U& scalar) const;
    T operator*(const MathVector& other_vec) const;
    template <typename U>
    std::common_type_t<T, U> operator*(const MathVector<U>& other) const;

    MathVector<T>& operator+=(const MathVector<T>& other);
    MathVector<T>& operator-=(const MathVector<T>& other);
    MathVector<T>& operator*=(const T& scalar);

    auto length() const;
};

template <class T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other) const {
    if (this->size() != other._size) {
        throw std::invalid_argument("Vectors should have same size for addition");
    }
    MathVector<T> result(this->_size);
    for (size_t i = 0; i < this->_size; ++i) {
        result[i] = this->_data[i] + other._data[i];
        result._states[i] = busy;
    }
    return result;
}

template <class T>
template <typename U>
MathVector<std::common_type_t<T, U>> MathVector<T>::operator+(const MathVector<U>& other) const {
    using R = std::common_type_t<T, U>; // std::common_type_t<T,U> автоматически выбирает наибольший тип
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors should have same size for addition");
    }
    MathVector<R> result(this->_size);
    for (size_t i = 0; i < this->_size; ++i) {
        result[i] = static_cast<R>(this->_data[i]) + static_cast<R>(other.data(i));
    }
    return result;
}

template <class T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& other) const {
    if (this->size() != other._size) {
        throw std::invalid_argument("Vectors should have same size for subtraction");
    }
    MathVector<T> result(this->_size);
    for (size_t i = 0; i < this->_size; ++i) {
        result[i] = this->_data[i] - other._data[i];
        result._states[i] = busy;
    }
    return result;
}

template <class T>
template <typename U>
MathVector<std::common_type_t<T, U>> MathVector<T>::operator-(const MathVector<U>& other) const {
    using R = std::common_type_t<T, U>; // std::common_type_t<T,U> автоматически выбирает наибольший тип
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors should have same size for subtraction");
    }
    MathVector<R> result(this->_size);
    for (size_t i = 0; i < this->_size; ++i) {
        result[i] = static_cast<R>(this->_data[i]) - static_cast<R>(other.data(i));
    }
    return result;
}

template <class T>
MathVector<T> MathVector<T>::operator*(const T& scalar) const {
    MathVector<T> result(this->_size);
    for (size_t i = 0; i < this->_size; ++i) {
        result._data[i] = this->_data[i] * scalar;
        result._states[i] = busy;
    }
    return result;
}

template <class T>
template <typename U>
MathVector<std::common_type_t<T, U>> MathVector<T>::operator*(const U& scalar) const {
    using R = std::common_type_t<T, U>;
    MathVector<R> result(this->_size);
    for (size_t i = 0; i < this->_size; ++i) {
        result[i] = static_cast<R>(this->_data[i]) * static_cast<R>(scalar);
    }
    return result;
}

template <class T>
T MathVector<T>::operator*(const MathVector& other_vec) const {
    if (this->size() != other_vec._size) {
        throw std::invalid_argument("Vectors should have same size for dot product");
    }
    T result = 0;
    for (size_t i = 0; i < this->_size; ++i) {
        result += this->_data[i] * other_vec._data[i];
    }
    return result;
}

template <class T>
template <typename U>
std::common_type_t<T, U> MathVector<T>::operator*(const MathVector<U>& other) const {
    using R = std::common_type_t<T, U>;
    if (this->size() != other.size()) {
        throw std::invalid_argument("Vectors should have same size for dot product");
    }
    R result = 0;
    for (size_t i = 0; i < this->_size; ++i) {
        result += static_cast<R>(this->_data[i]) * static_cast<R>(other.data(i));
    }
    return result;
}

template <class T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& other) {
    if (this->size() != other._size) {
        throw std::invalid_argument("Vectors should have same size for addition");
    }
    for (size_t i = 0; i < this->_size; ++i) {
        this->_data[i] = this->_data[i] + other._data[i];
    }
    return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& other) {
    if (this->size() != other._size) {
        throw std::invalid_argument("Vectors should have same size for subtraction");
    }
    for (size_t i = 0; i < this->_size; ++i) {
        this->_data[i] = this->_data[i] - other._data[i];
    }
    return *this;
}

template <class T>
MathVector<T>& MathVector<T>::operator*=(const T& scalar) {
    for (size_t i = 0; i < this->_size; ++i) {
        this->_data[i] = this->_data[i] * scalar;
    }
    return *this;
}

template <class T>
auto MathVector<T>::length() const { // длинна вектора
    T sum = 0;
    for (size_t i = 0; i < this->_size; i++) {
        sum += this->_data[i] * this->_data[i];
    }
    return std::sqrt(sum);
}

#endif // LIB_MATHVECTOR_MATHVECTOR_H