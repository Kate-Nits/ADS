// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_SPHERE_SPHERE_H
#define LIB_SPHERE_SPHERE_H
#include <iostream>

#include "../lib_point/point.h"
#include "../lib_point3d/point3d.h"
#include "../lib_circle/circle.h"

class Sphere : public Circle {
	Point3D _center3D;
public:
	Sphere();
	Sphere(Point3D, int);
	Sphere(const Sphere&);

	Point3D get_center3D() const;
	void set_center3D(Point3D);
};

#endif // LIB_SPHERE_SPHERE_H
