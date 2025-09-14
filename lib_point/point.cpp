// Copyright 2025 Ekaterina Ushnitskaya

#include <stdexcept>
#include <iostream>
#include <cmath>
#include "../lib_point/point.h"

Point::Point() {
    int ox = 0, oy = 0;
    _ox = ox;
    _oy = oy;
}
Point::Point(int ox, int oy) {
    _ox = ox;
    _oy = oy;
}
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

double Point::distance_to(const Point& other) const {
    double res = std::sqrt(std::pow(_ox - other._ox, 2) + std::pow(_oy - other._oy, 2));
    return res;
}