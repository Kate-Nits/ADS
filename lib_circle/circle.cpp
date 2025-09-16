// Copyright 2025 Ekaterina Ushnitskaya

#include <stdexcept>
#include <iostream>
////#include "../lib_point/point.h"
#include "../lib_circle/circle.h"


Circle::Circle() : _center(Point()), _radius(1) {};
Circle::Circle(Point value_dot, int value_rad) {
    if (value_rad < 0) {
        throw std::logic_error("Error!!! The radius can't be less than zero");
    }
    _center = value_dot;
    _radius = value_rad;
}

Circle::Circle(const Circle& other) {
    if (&other == NULL) {
        throw std::logic_error("Error!!!");
    }
    _center = other._center;
    _radius = other._radius;
}

Point Circle::get_center() const {
    return _center;
}
int Circle::get_radius() const {
    return _radius;
}

void Circle::set_center(Point dot) {
    _center = dot;
}
void Circle::set_radius(int rad) {
    _radius = rad;
}