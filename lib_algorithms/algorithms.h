// Copyright 2025 Ekaterina Ushnitskaya


#ifndef LIB_ALGORITHMS_H
#define  LIB_ALGORITHMS_H

#include <cstdlib>
#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"
#include "../lib_tvector/tvector.h"
#include "../lib_mathvector/MathVector.h"
#include "../lib_matrix/matrix.h"
#include "../lib_triangle_matrix/triangle_matrix.h"
#include "../lib_stack/stack.h"
#include "../lib_node/node.h"
#include "../lib_list/list.h"

#define START_MENU_MATRIX_SIZE 3
#define REALISED_Matrix

#define NUMBER1 1
#define NUMBER2 2
#define NUMBER3 3
#define NUMBER4 4

template <class T> class Matrix;
template <class T> class TriangleMatrix;

enum Location { intersecting, do_not_intersecting, tangent, inside, coinside };
//tangent - касающиеся, intersecting - пересекающиеся, inside - один в другом, coinside - совпадают

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

template <class T>
bool has_unique_elements(const Matrix<T>& matrix) {
    TVector<T> elements;
    for (size_t i = 0; i < matrix.rows(); i++) {
        for (size_t j = 0; j < matrix.cols(); j++) {
            elements.push_back(matrix.at(i, j));
        }
    }
    quick_sort(elements);
    for (size_t i = 1; i < elements.size(); ++i) {
        if (elements[i] == elements[i - 1]) { return false; }
    }
    return true;
}
template <class T>
int what_number_less(const T& num1, const T& num2, const T& num3, const T& num4) {
    if (num1 < num2 && num1 < num3 && num1 < num4) {
        return NUMBER1;
    }
    else if (num2 < num1 && num2 < num3 && num2 < num4) {
        return NUMBER2;
    }
    else if (num3 < num1 && num3 < num2 && num3 < num4) {
        return NUMBER3;
    }
    else {
        return NUMBER4;
    }
}
template <class T>
T gradient_descent(const Matrix<T>& matrix) {
    srand(time(0));
    if (matrix.cols() != matrix.rows()) {
        throw std::invalid_argument("The Matrix should be square");
    }
    if (!has_unique_elements(matrix)) {
        throw std::invalid_argument("The Matrix should has only unique elements");
    }

    size_t start_row_pos = 0, start_col_pos = 0;
    start_row_pos = rand() % matrix.rows() + 0;
    start_col_pos = rand() % matrix.cols() + 0;
    
    if (start_row_pos >= matrix.rows() || start_col_pos >= matrix.cols()) {
        throw std::out_of_range("Start position out of matrix bounds");
    }

    T current_value = matrix.at(start_row_pos, start_col_pos);
    size_t current_row = start_row_pos;
    size_t current_col = start_col_pos;

    const size_t max_steps = matrix.rows() * matrix.cols();
    size_t steps = 0;
    bool improved = true;

    while (improved && steps < max_steps) {
        improved = false;
        T best_neighbor_value = current_value;
        size_t best_neighbor_row = current_row;
        size_t best_neighbor_col = current_col;

        if (current_row > 0) { // вверх
            T up_value = matrix.at(current_row - 1, current_col);
            if (up_value < best_neighbor_value) {
                best_neighbor_value = up_value;
                best_neighbor_row = current_row - 1;
                best_neighbor_col = current_col;
                improved = true;
            }
        }

        if (current_col < matrix.cols() - 1) { // вправо
            T right_value = matrix.at(current_row, current_col + 1);
            if (right_value < best_neighbor_value) {
                best_neighbor_value = right_value;
                best_neighbor_row = current_row;
                best_neighbor_col = current_col + 1;
                improved = true;
            }
        }

        if (current_row < matrix.rows() - 1) { // вниз
            T down_value = matrix.at(current_row + 1, current_col);
            if (down_value < best_neighbor_value) {
                best_neighbor_value = down_value;
                best_neighbor_row = current_row + 1;
                best_neighbor_col = current_col;
                improved = true;
            }
        }

        if (current_col > 0) { // влево
            T left_value = matrix.at(current_row, current_col - 1);
            if (left_value < best_neighbor_value) {
                best_neighbor_value = left_value;
                best_neighbor_row = current_row;
                best_neighbor_col = current_col - 1;
                improved = true;
            }
        }

        if (improved) {
            current_row = best_neighbor_row;
            current_col = best_neighbor_col;
            current_value = best_neighbor_value;
            steps++;
        }
    }
    std::cout << "Final value: " << current_value << std::endl;

    return current_value;
}

void start_menu_for_matrix();
void viewing_saved_matrices(int count_of_saved_matrices, Matrix<int> matrix1, Matrix<int> matrix2, Matrix<int> matrix3);
void start_matrix_calculator(int& link_user_choice, int& link_want_to_save, Matrix<int> res, int& count_of_saved_matrices, Matrix<int>& matrix1, Matrix<int>& matrix2, Matrix<int>& matrix3, int& isThereMatrix1, int& isThereMatrix2, int& isThereMatrix3);
void do_user_want_to_save(int& want_to_save);
void input_standart_matrix(Matrix<int>& matrix, size_t rows, size_t cols);
void input_triangle_matrix(TriangleMatrix<int>& matrix, size_t n);
Matrix<int> triangle_to_full(const TriangleMatrix<int>& matrix);
void check_user_input(int user_choice, int true_number);
bool input_user_choice(int& user_choice, int true_number);
void what_matrices(int& what_the_first_matrix, int& what_the_second_matrix, int& isExit);
void print_menu_matrix_calculator();
void what_matrix_sizes(const int& type_matrix, size_t& size_rows, size_t& size_cols);
void deleted_saved_matrix(int& link_user_choice_for_deleted, int& isThereMatrix1, int& isThereMatrix2, int& isThereMatrix3);
void matrix_application();

inline bool is_open_bracket(char symbol);
inline bool is_close_bracket(char symbol);
inline bool matches_pair(char open, char close);
bool check_brackets(const std::string& str);

template <class T>
bool is_looped_hare_and_turtle(const List<T>& list);
template <class T>
bool is_looped_turn_ptr(List<T>& list);
template <class T>
Node<T>* find_loop_node(List<T>& list);

#endif //  LIB_ALGORITHMS_H