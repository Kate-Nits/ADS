// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_POINT3D_POINT3D_H
#define LIB_POINT3D_POINT3D_H

#include "../lib_point/point.h"

class Point3D : public Point {
	int _oz;

public:
	Point3D();
	Point3D(int, int, int);
	Point3D(const Point3D&);

	int get_oz() const;
	void set_oz(int);

	float distance_to(const Point3D&) const;
};

#endif // LIB_POINT3D_POINT3D_H
