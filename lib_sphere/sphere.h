// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_SPHERE_SPHERE_H
#define LIB_SPHERE_SPHERE_H
#include <iostream>

#include "../lib_point/point.h"
#include "../lib_point3d/point3d.h"
#include "../lib_circle/circle.h"

class Sphere {
	Point3D _center3D;
	int _radius;
public:
	Sphere();
	Sphere(Point3D, int);
	Sphere(const Sphere&);

	Point3D get_center() const;
	void set_center(Point3D);

	int get_radius() const;
	void set_radius(int);
};

#endif // LIB_SPHERE_SPHERE_H
