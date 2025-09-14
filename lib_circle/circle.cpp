// Copyright 2025 Ekaterina Ushnitskaya

#include <stdexcept>
#include <iostream>
//#include "../lib_point/point.h"
#include "../lib_circle/circle.h"

Circle::Circle() {
    Point a;
    int rad = 0;
    _center = a;
    _radius = rad;
}
Circle::Circle(Point dot, int rad) {
    _center = dot;
    _radius = rad;
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