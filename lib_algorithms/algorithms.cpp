// Copyright 2025 Ekaterina Ushnitskaya

#include <stdexcept>
#include <iostream>
#include <windows.h>
#include <cmath>

#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"

#include "../lib_matrix/matrix.h"
#include "../lib_triangle_matrix/triangle_matrix.h"

#define START_MENU_FOR_MATRIX_SIZE 3
#define START_MENU_MATRIX_CALCULATE_SIZE 4
#define WHAT_MATRIX_MENU 3
#define YES 1
#define NO 0
#define MAX_COUNT_OF_SAVED_MATRICES 3
#define EXIT_DELETED_SAVED_MATRICES_MENU 4
#define MATRIX1 1
#define MATRIX2 2
#define MATRIX3 3

#define MATRIX_CALCULATOR 1
#define VIEWING_SAVED_MATRICES 2
#define EXIT_MAIN_MENU 3

#define ADD 1
#define SUBTRACT 2
#define MULTIPLY 3
#define EXIT_CALCULATE_MATRIX_MENU 4

#define REALISED_ADD
#define REALISED_SUBTRACT
#define REALISED_MULTIPLY
#define REALISED_OPERATOR
#define REALISED_CLASSES

#define STANDART 1
#define TRIANGLE 2

void set_color(int text_color, int bg_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

//enum Location { intersecting, do_not_intersecting, tangent, inside, coinside };
//tangent - касающиеся, intersecting - пересекающиеся, inside - один в другом, coinside - совпадают
void print_result_position(const std::string& description, Location result) {
    std::cout << description << ": ";
    switch (result) {
    case coinside: std::cout << "COINCIDE"; break;
    case inside: std::cout << "INSIDE"; break;
    case tangent: std::cout << "TANGENT"; break;
    case intersecting: std::cout << "INTERSECTING"; break;
    case do_not_intersecting: std::cout << "DO_NOT_INTERSECT"; break;
    }
    std::cout << std::endl;
}

void in_development() {
    std::cout << "  Sorry, the function is in development " << std::endl;
    std::cout << "  Press Enter to exit " << std::endl;
    getchar();
    getchar();
    system("cls");
}
void start_menu_for_matrix() {
    std::cout << "==================================================" << std::endl;
    std::cout << "              WORKING WITH MATRICES               " << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "  1. Matrix calculator " << std::endl;
    std::cout << "  2. Viewing saved matrices " << std::endl;
    std::cout << "  3. Exit " << std::endl;
    std::cout << "==================================================" << std::endl;
    //std::cout << "==================================================" << std::endl;
    //std::cout << "" << std::endl;
}
void print_menu_matrix_calculator() {
    std::cout << "==================================================" << std::endl;
    std::cout << "  What would you like to do with matrices:" << std::endl;
    std::cout << "      1. Add " << std::endl;
    std::cout << "      2. Subtract" << std::endl;
    std::cout << "      3. multiply" << std::endl;
    std::cout << "      4. Exit" << std::endl;
    std::cout << "==================================================" << std::endl;
}

void check_user_input(int user_choice, int true_number) {
    if (user_choice > true_number) {
        set_color(12, 0);
        std::cout << "ERROR: ";
        set_color(7, 0);
        throw std::logic_error("your choice is more than points\n");
    }
    else if (user_choice <= 0) {
        set_color(12, 0);
        std::cout << "ERROR: ";
        set_color(7, 0);
        throw std::logic_error("your choice is less than points\n");
    }
}
bool input_user_choice(int& user_choice, int true_number) {
    std::cout << "  Enter the menu you need: " << std::endl;
    std::cout << "  (if you are sure, press enter)" << std::endl;
    std::cout << "  ";
    std::cin >> user_choice;
    try {
        check_user_input(user_choice, true_number);
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what();
        std::cout << "  Try again:" << std::endl;
        return false;
    }
    return true;
}
void what_matrices(int& what_the_first_matrix, int& what_the_second_matrix, int& isExit) {
    int user_choice;
    int& link_user_choice = user_choice;
    std::cout << "==================================================" << std::endl;
    std::cout << "  What will the matrices be like?" << std::endl;
    std::cout << "      1. Standart" << std::endl;
    std::cout << "      2. Triangle" << std::endl;
    std::cout << "      3. Exit" << std::endl;
    while (!input_user_choice(link_user_choice, WHAT_MATRIX_MENU));
    if (user_choice == 3) {
        isExit = YES;
    }
    else if (user_choice == STANDART) {
        what_the_first_matrix = STANDART;
        what_the_second_matrix = STANDART;
    }
    else {
        what_the_first_matrix = TRIANGLE;
        what_the_second_matrix = TRIANGLE;
    }
}
void what_matrix_sizes(size_t& size_n, size_t& size_m) {
    std::cout << "==================================================" << std::endl;
    std::cout << "Enter the number of lines (parametr M): ";
    std::cin >> size_m;
    std::cout << "Enter the number of columns (parametr N): ";
    std::cin >> size_n;
}
void print_res(const Matrix<int>& matrix, size_t size_m, size_t size_N) {
    for (size_t i = 0; i < size_m; i++) {
        for (size_t j = 0; j < size_N; j++) {
            std::cout << matrix.at(i, j) << "   ";
        }
        std::cout << std::endl;
    }
}
void do_user_want_to_save(int& want_to_save) {
    std::cout << "==================================================" << std::endl;
    std::cout << "Would you like to save result?" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "If answer - yes - input 1. If no, then input 0: ";
    std::cin >> want_to_save;
    while (want_to_save != YES || want_to_save != NO) {
        std::cout << "==================================================" << std::endl;
        set_color(12, 0);
        std::cout << "ERROR: ";
        set_color(7, 0);
        std::cout << "your choice is more than points" << std::endl;
        std::cout << "==================================================" << std::endl;
        std::cout << "Tru again" << std::endl;
        std::cout << "If answer - yes - input 1. If no, then input 0: ";
        std::cin >> want_to_save;
    }
}
void input_standard_matrix(Matrix<int>& matrix, size_t rows, size_t cols) {
    std::cout << "Enter matrix elements:" << std::endl;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << "[" << i << "][" << j << "] = ";
            std::cin >> matrix[i][j];
        }
    }
}
void input_triangle_matrix(TriangleMatrix<int>& matrix, size_t n) {
    std::cout << "Enter upper-triangle elements (including diagonal):" << std::endl;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i; j < n; ++j) {
            std::cout << "[" << i << "][" << j << "] = ";
            std::cin >> matrix.at(i, j);
        }
    }
}
Matrix<int> triangle_to_full(const TriangleMatrix<int>& matrix) {
    Matrix<int> result(matrix.n(), matrix.n());
    for (size_t i = 0; i < matrix.n(); ++i)
        for (size_t j = 0; j < matrix.n(); ++j)
            result.at(i, j) = matrix.at(i, j);
    return result;
}
void start_matrix_calculator(int& link_user_choice, int& link_want_to_save, Matrix<int> res) {
    int isExit = NO;
    while (!isExit) {
        print_menu_matrix_calculator();
        while (!input_user_choice(link_user_choice, START_MENU_MATRIX_CALCULATE_SIZE));
        system("cls");
        if (link_user_choice == EXIT_CALCULATE_MATRIX_MENU) { break; }
        int what_the_first_matrix = 0;
        int what_the_second_matrix = 0;
        int inner_exit = NO;
        what_matrices(what_the_first_matrix, what_the_second_matrix, inner_exit);
        system("cls");
        if (inner_exit == YES) { break; }

        size_t size_m1 = 0, size_n1 = 0, size_m2 = 0, size_n2 = 0;
        size_t size_res_m = 0, size_res_n = 0;
        if (link_user_choice == ADD || link_user_choice == SUBTRACT) {
            what_matrix_sizes(size_n1, size_m1);
            size_m2 = size_m1;
            size_n2 = size_n1;
            size_res_m = size_m1;
            size_res_n = size_n1;
        }
        else if (link_user_choice == MULTIPLY) {
            std::cout << "==================================================" << std::endl;
            std::cout << "  For the first matrix" << std::endl;
            what_matrix_sizes(size_n1, size_m1);
            std::cout << "==================================================" << std::endl;
            std::cout << "  For the second matrix" << std::endl;
            what_matrix_sizes(size_n2, size_m2);
            while (size_n1 != size_m2) {
                set_color(12, 0);
                std::cout << "ERROR: ";
                set_color(7, 0);
                std::cout << "The parameter N for 1 of the matrix and the parametr M for 2 must be equal" << std::endl;
                std::cout << "==================================================" << std::endl;
                std::cout << "  For the first matrix" << std::endl;
                what_matrix_sizes(size_n1, size_m1);
                std::cout << "==================================================" << std::endl;
                std::cout << "  For the second matrix" << std::endl;
                what_matrix_sizes(size_n2, size_m2);
            }
            size_res_m = size_n1;
            size_res_m = size_m2;
        }
        if (what_the_first_matrix == STANDART && what_the_second_matrix == STANDART) {
            Matrix<int> matrix1(size_m1, size_n1);
            Matrix<int> matrix2(size_m2, size_n2);
            Matrix<int> intermediate_res;
            input_standard_matrix(matrix1, size_m1, size_n1);
            input_standard_matrix(matrix2, size_m2, size_n2);
            switch (link_user_choice) {
            case ADD: intermediate_res = matrix1 + matrix2; break;
            case SUBTRACT: intermediate_res = matrix1 - matrix2; break;
            case MULTIPLY: intermediate_res = matrix1 * matrix2; break;
            }
            res = intermediate_res;
            print_res(res, size_res_m, size_res_n);
            do_user_want_to_save(link_want_to_save);
        }
        else if (what_the_first_matrix == TRIANGLE && what_the_second_matrix == TRIANGLE) {
            TriangleMatrix<int> matrix1(size_m1);
            TriangleMatrix<int> matrix2(size_m2);
            TriangleMatrix<int> intermediate_res;
            input_triangle_matrix(matrix1, size_m1);
            input_triangle_matrix(matrix2, size_m2);

            switch (link_user_choice) {
            case ADD: intermediate_res = matrix1 + matrix2; break;
            case SUBTRACT: intermediate_res = matrix1 - matrix2; break;
            case MULTIPLY: intermediate_res = matrix1 * matrix2; break;
            }
            res = triangle_to_full(intermediate_res);
            print_res(res, size_res_m, size_res_n);
            do_user_want_to_save(link_want_to_save);
        }
        else {
            if (what_the_first_matrix == STANDART && what_the_second_matrix == TRIANGLE) {
                Matrix<int> matrix1(size_m1, size_n1), intermediate_res;
                TriangleMatrix<int> matrix2(size_m2);
                input_standard_matrix(matrix1, size_m1, size_n1);
                input_triangle_matrix(matrix2, size_m2);

                switch (link_user_choice) {
                case ADD: intermediate_res = matrix1 + matrix2; break;
                case SUBTRACT: intermediate_res = matrix1 - matrix2; break;
                case MULTIPLY: intermediate_res = matrix1 * matrix2; break;
                }
                res = intermediate_res;
                print_res(res, size_res_m, size_res_n);
                do_user_want_to_save(link_want_to_save);
            }
            else if (what_the_first_matrix == TRIANGLE && what_the_second_matrix == STANDART) {
                TriangleMatrix<int> matrix1(size_m1);
                Matrix<int> matrix2(size_m2, size_n2), intermediate_res;
                input_triangle_matrix(matrix1, size_m1);
                input_standard_matrix(matrix2, size_m2, size_n2);

                switch (link_user_choice) {
                case ADD: intermediate_res = matrix1 + matrix2; break;
                case SUBTRACT: intermediate_res = matrix1 - matrix2; break;
                case MULTIPLY: intermediate_res = matrix1 * matrix2; break;
                }
                res = intermediate_res;
                print_res(res, size_res_m, size_res_n);
                do_user_want_to_save(link_want_to_save);
            }
        }
        std::cout << "Press Enter to continue..." << std::endl;
        getchar();
        getchar();
        system("cls");
    }
}
void deleted_saved_matrix(int& link_user_choice_for_deleted, int& isThereMatrix1, int& isThereMatrix2, int& isThereMatrix3) {
    std::cout << "==================================================" << std::endl;
    std::cout << "  You can store a limited number of matrices" << std::endl;
    std::cout << "  Which one would you like to delete?" << std::endl;
    std::cout << "      1. matrix1" << std::endl;
    std::cout << "      2. matrix2" << std::endl;
    std::cout << "      3. matrix3" << std::endl;;
    std::cout << "      4. exit" << std::endl;

    while (!input_user_choice(link_user_choice_for_deleted, EXIT_DELETED_SAVED_MATRICES_MENU));
    switch (link_user_choice_for_deleted) {
    case MATRIX1:
        isThereMatrix1 = NO;
        break;

    case MATRIX2:
        isThereMatrix2 = NO;
        break;

    case MATRIX3:
        isThereMatrix3 = NO;
        break;
    case EXIT_DELETED_SAVED_MATRICES_MENU:
        break;
    }
}
void viewing_saved_matrices(int count_of_saved_matrices, Matrix<int> matrix1, Matrix<int> matrix2, Matrix<int> matrix3) {
    std::cout << "==================================================" << std::endl;
    std::cout << "  Which matrix would you like to look at?" << std::endl;
    if (count_of_saved_matrices > 0) {
        if (count_of_saved_matrices == MAX_COUNT_OF_SAVED_MATRICES) {
            std::cout << "  1. matrix1" << std::endl;
            std::cout << "  2. matrix2" << std::endl;
            std::cout << "  3. matrix3" << std::endl;
        }
        else if (count_of_saved_matrices == MAX_COUNT_OF_SAVED_MATRICES - 1) {
            std::cout << "  1. matrix1" << std::endl;
            std::cout << "  2. matrix2" << std::endl;
        }
        else if (count_of_saved_matrices == MAX_COUNT_OF_SAVED_MATRICES - 2) {
            std::cout << "  1. matrix1" << std::endl;
        }
        int user_choice;
        int& link_user_choice = user_choice;
        while (!input_user_choice(link_user_choice, START_MENU_FOR_MATRIX_SIZE));
        if (user_choice == MATRIX1) {
            matrix1.print();
        }
        else if (user_choice == MATRIX2) {
            matrix2.print();
        }
        else if (user_choice == MATRIX3) {
            matrix3.print();
        }
    }
    else if (count_of_saved_matrices == 0) {
        std::cout << "  You don't have any saved matrices" << std::endl;
    }
    std::cout << "==================================================" << std::endl;
    std::cout << "  Press Enter to exit " << std::endl;
    getchar();
    getchar();
    system("cls");
}
void matrix_application() {
    int user_choice = 0;
    int isExit = NO;
    int want_to_save = NO;
    int count_of_saved_matrices = 0;
    Matrix<int> res, matrix1, matrix2, matrix3;
    int isThereMatrix1 = NO;
    int isThereMatrix2 = NO;
    int isThereMatrix3 = NO;
    while (!isExit) {
        start_menu_for_matrix();
        while (!input_user_choice(user_choice, START_MENU_FOR_MATRIX_SIZE));
        system("cls");
        switch (user_choice) {
        case MATRIX_CALCULATOR:
            start_matrix_calculator(user_choice, want_to_save, res);
            if (want_to_save == YES) {
                int user_choice_for_deleted;
                while ((count_of_saved_matrices + 1) > MAX_COUNT_OF_SAVED_MATRICES) {
                    deleted_saved_matrix(user_choice_for_deleted, isThereMatrix1, isThereMatrix2, isThereMatrix3);
                    if (user_choice_for_deleted == EXIT_DELETED_SAVED_MATRICES_MENU) {
                        break;
                    }
                    else {
                        count_of_saved_matrices--;
                    }
                }
                if (isThereMatrix1 == NO) {
                    std::cout << "==================================================" << std::endl;
                    std::cout << "  The result will be written to the matrix1" << std::endl;
                    isThereMatrix1 = YES;
                    count_of_saved_matrices++;
                    matrix1 = res;
                } 
                else if (isThereMatrix2 == NO) {
                    std::cout << "==================================================" << std::endl;
                    std::cout << "  The result will be written to the matrix2" << std::endl;
                    isThereMatrix2 = YES;
                    count_of_saved_matrices++;
                    matrix2 = res;
                }
                else if (isThereMatrix3 == NO) {
                    std::cout << "==================================================" << std::endl;
                    std::cout << "  The result will be written to the matrix3" << std::endl;
                    isThereMatrix3 = YES;
                    count_of_saved_matrices++;
                    matrix3 = res;
                }
                std::cout << "  Press Enter to exit " << std::endl;
                getchar();
                getchar();
                system("cls");
            }
            break;
        case VIEWING_SAVED_MATRICES:
            viewing_saved_matrices(count_of_saved_matrices, matrix1, matrix2, matrix3);
            break;
        case EXIT_MAIN_MENU:
            isExit = YES;
            break;
        }
    }
}