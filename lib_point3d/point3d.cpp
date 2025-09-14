// Copyright 2025 Ekaterina Ushnitskaya

#include <stdexcept>
#include <iostream>
#include <cmath>
//#include "../lib_point/point.h"
#include "../lib_point3d/point3d.h"

Point3D::Point3D() : Point(), _oz(0) {}
Point3D::Point3D(int ox, int oy, int oz) {
    _ox = ox;
    _oy = oy;
    _oz = oz;
}
Point3D::Point3D(const Point3D& other) {
    if (&other == NULL) {
        throw std::logic_error("Error!!!");
    }
    _ox = other._ox;
    _oy = other._oy;
    _oz = other._oz;
}

int Point3D::get_oz() const {
    return _oz;
}
void Point3D::set_oz(int oz) {
    _oz = oz;
}

double Point3D::distance_to(const Point3D& other) const {
    double res = std::sqrt(std::pow(_ox - other._ox, 2) + std::pow(_oy - other._oy, 2) + std::pow(_oz - other._oz, 2));
    return res;
}