// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_ALGORITHMS_H
#define  LIB_ALGORITHMS_H

#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"

enum Location { intersecting, do_not_intersecting, tangent, inside, coinside };
//tangent - касающиеся, intersecting - пересекающиеся, inside - один в другом, coinside - совпадают

Location check_circle_position(const Circle& circle1, const Circle& circle2);
Location check_sphere_position(const Sphere& sphere1, const Sphere& sphere2);



#endif //  LIB_ALGORITHMS_H