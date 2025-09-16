// Copyright 2025 Ekaterina Ushnitskaya

#include <stdexcept>
#include <iostream>
#include <cmath>

#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"

enum Location { intersecting, do_not_intersecting, tangent, inside, coinside };
//tangent - касающиеся, intersecting - пересекающиеся, inside - один в другом, coinside - совпадают

Location check_circle_position(const Circle& circle1, const Circle& circle2) {
    Point center1 = circle1.get_center();
    Point center2 = circle2.get_center();
    int radius1 = circle1.get_radius();
    int radius2 = circle2.get_radius();

    double distance = center1.distance_to(center2);
    int sum_rad = radius1 + radius2;
    int abs_difference = std::abs(radius1 - radius2);

    if (distance == 0 && radius1 == radius2) {
        return coinside;          // Окружности совпадают
    }
    else if (distance < abs_difference) {
        return inside;            // Одна окружность внутри другой
    }
    else if (distance == abs_difference) {
        return tangent;           // Внутреннее касание
    }
    else if (distance < sum_rad && distance > abs_difference) {
        return intersecting;      // Окружности пересекаются
    }
    else if (distance == sum_rad) {
        return tangent;           // Внешнее касание
    }
    else {
        return do_not_intersecting; // Окружности не пересекаются
    }
}

Location check_sphere_position(const Sphere& sphere1, const Sphere& sphere2) {
    Point3D center1 = sphere1.get_center3D();
    Point3D center2 = sphere2.get_center3D();
    int radius1 = sphere1.get_radius();
    int radius2 = sphere2.get_radius();

    double distance = center1.distance_to(center2);
    int sum_rad = radius1 + radius2;
    int abs_difference = std::abs(radius1 - radius2);

    if (distance == 0 && radius1 == radius2) {
        return coinside;          // Сферы совпадают
    }
    else if (distance < abs_difference) {
        return inside;            // Одна сфера внутри другой
    }
    else if (distance == abs_difference) {
        return tangent;           // Внутреннее касание
    }
    else if (distance < sum_rad && distance > abs_difference) {
        return intersecting;      // Сферы пересекаются
    }
    else if (distance == sum_rad) {
        return tangent;           // Внешнее касание
    }
    else {
        return do_not_intersecting; // Сферы не пересекаются
    }
}