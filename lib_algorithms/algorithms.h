// Copyright 2025 Ekaterina Ushnitskaya


#ifndef LIB_ALGORITHMS_H
#define  LIB_ALGORITHMS_H

#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"

#define START_MENU_MATRIX_SIZE 3

enum Location { intersecting, do_not_intersecting, tangent, inside, coinside };
//tangent - касающиеся, intersecting - пересекающиеся, inside - один в другом, coinside - совпадают


// функции для консоли
void set_color(int text_color, int bg_color);
void print_result_position(const std::string& description, Location result);
void start_menu_for_matrix();

template <class T>
Location check_position(const T& circle1, const T& circle2) {
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

void matrix_application();
void check_user_input(int user_choice, int true_number);
bool input_user_choice(int& user_choice, int true_number);


#endif //  LIB_ALGORITHMS_H