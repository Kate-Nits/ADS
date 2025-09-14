// Copyright 2025 Ekaterina Ushnitskaya

#include <stdexcept>
#include <iostream>
#include <cmath>
#include "../lib_point/point.h"

Point::Point() : _ox(0), _oy(0) {};

Point::Point(int value_ox, int value_oy) : _ox(value_ox), _oy(value_oy) {};

Point::Point(const Point& other) {
    if (&other == NULL) {
        throw std::logic_error("Error!!!");
    }
    _ox = other._ox;
    _oy = other._oy;
}

int Point::get_ox() const {
    return _ox;
}
int Point::get_oy() const {
    return _oy;
}
void Point::set_ox(int ox) {
    _ox = ox;
}
void Point::set_oy(int oy) {
    _oy = oy;
}

bool Point:: operator == (const Point& other) const noexcept {
    return this->_ox == other._ox && this->_oy == other._oy;
}

float Point::distance_to(const Point& other) const {
    float res = std::sqrt(std::pow(_ox - other._ox, 2) + std::pow(_oy - other._oy, 2)); //std::pow - возведение в степень
    return res;
}