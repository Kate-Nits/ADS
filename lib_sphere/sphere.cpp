// Copyright 2025 Ekaterina Ushnitskaya

#include <stdexcept>
#include "../lib_sphere/sphere.h"

Sphere::Sphere() : Circle(), _center3D(Point3D()) {}
Sphere::Sphere(Point3D center, int value_radius) {
	if (value_radius < 0) {
		throw std::logic_error("Error!!! The radius can't be less than zero");
	}
	_center3D = center;
	_radius = value_radius;
}
Sphere::Sphere(const Sphere& other) {
	if (&other == NULL) {
		throw std::logic_error("Error!!!");
	}
	_center3D = other._center3D;
	_radius = other._radius;
}

Point3D Sphere::get_center3D() const {
	return _center3D;
}
void Sphere::set_center3D(Point3D center) {
	_center3D = center;
}