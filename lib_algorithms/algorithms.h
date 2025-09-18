// Copyright 2025 Ekaterina Ushnitskaya


#ifndef LIB_ALGORITHMS_H
#define  LIB_ALGORITHMS_H

#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"
#include "../lib_matrix/matrix.h"
#include "../lib_triangle_matrix/triangle_matrix.h"

#define START_MENU_MATRIX_SIZE 3
//#define REALISED_TMATRIX

enum Location { intersecting, do_not_intersecting, tangent, inside, coinside };
//tangent - касающиеся, intersecting - пересекающиеся, inside - один в другом, coinside - совпадают


// функции для консоли
void set_color(int text_color, int bg_color);
void print_result_position(const std::string& description, Location result);

void in_development();


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

void start_menu_for_matrix();
#ifndef REALISED_TMATRIX
#else 
void viewing_saved_matrices(int count_of_saved_matrices, TMatrix<int> matrix1, TMatrix<int> matrix2, TMatrix<int> matrix3);
void start_matrix_calculator(int& link_user_choice, int& link_want_to_save, TMatrix<int> res);
void print_res(const TMatrix<int>& matrix, size_t size_M, size_t size_N);
#endif //REALISED_TMATRIX
void check_user_input(int user_choice, int true_number);
bool input_user_choice(int& user_choice, int true_number);
void what_matrices(int& what_the_first_matrix, int& what_the_second_matrix, int& isExit);
void print_menu_matrix_calculator();
void what_matrix_sizes(size_t& link_sizeN, size_t& link_sizeM);
void deleted_saved_matrix(int& link_user_choice_for_deleted, int& isThereMatrix1, int& isThereMatrix2, int& isThereMatrix3);
void do_user_want_to_save(int& want_to_save);
void matrix_application();

#endif //  LIB_ALGORITHMS_H