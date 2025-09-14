// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_POINT_POINT_H
#define LIB_POINT_POINT_H

class Point {
protected:
	int _ox;
	int _oy;
public:
	Point();
	Point(int, int);
	Point(const Point&);

	int get_ox() const;
	int get_oy() const;
	void set_ox(int ox);
	void set_oy(int oy);

	float distance_to(const Point&) const; //расстояние между текущей точкой и другой точкой
};

#endif // LIB_POINT_POINT_H