// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_CIRCLE_CIRCLE_H
#define LIB_CIRCLE_CIRCLE_H

#include "../lib_point/point.h"


class Circle {
protected:
	Point _center;
	int _radius;
public:
	Circle();
	Circle(Point, int);
	Circle(const Circle&);

	Point get_center() const;
	int get_radius() const;

	void set_center(Point);
	void set_radius(int);
};

#endif // LIB_CIRCLE_CIRCLE_H
