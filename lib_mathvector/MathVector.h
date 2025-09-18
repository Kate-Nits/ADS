// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_MATHVECTOR_MATHVECTOR_H
#define LIB_MATHVECTOR_MATHVECTOR_H

#include <cmath>
#include <iostream>
#include <stdexcept>

#include "../lib_tvector/tvector.h"
#include "../lib_algorithms/algorithms.h"

template <class T>
class MathVector : public TVector<T> {
public:
    MathVector() noexcept : TVector<T>() {}
    MathVector(size_t size) : TVector<T>(size) {}
    MathVector(const MathVector<T>& other) = default;
    MathVector(MathVector<T>&& other) noexcept = default;
    ~MathVector() = default;

    MathVector<T>& operator=(const MathVector<T>& other) noexcept {
        this->assign(other);
        return *this;
    }

    MathVector<T>& operator=(MathVector<T>&& other) noexcept {
        in_development();
        return *this;
    }

    T dot(const MathVector<T>& other) const { // —кал€рное произведение
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
