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

#define MATRIX_CALCULATOR 1
#define VIEWING_SAVED_MATRICES 2
#define EXIT_MAIN_MENU 3

#define ADD 1
#define SUBTRACT 2
#define MULTIPLY 3
#define EXIT_CALCULATE_MATRIX_MENU 4

//#define REALISED_ADD
//#define REALISED_SUBTRACT
//#define REALISED_MULTIPLY
//#define REALISED_OPERATOR[]

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
    std::cout << "  2. Exit " << std::endl;
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
void what_matrix_sizes(size_t& sizeN, size_t& sizeM) {
    std::cout << "==================================================" << std::endl;
    std::cout << "Enter the number of lines (parametr M): ";
    std::cin >> sizeM;
    std::cout << "Enter the number of columns (parametr N): ";
    std::cin >> sizeN;
}
void print_res(const TMatrix<TMatrix<int>>& matrix, size_t size_M, size_t size_N) {
#ifndef REALISED_OPERATOR[]
    in_development();
#else
    for (size_t i = 0; i < size_M; i++) {
        for (size_t j = 0; j < size_N; j++) {
            std::cout << matrix[i][j] << "   ";
        }
        std::cout << std::endl;
    }
#endif // REALISED_OPERATOR[] 
}
void print_res(const TMatrix<int>& matrix, size_t size_M, size_t size_N) {
#ifndef REALISED_OPERATOR[]
    in_development();
#else
    for (size_t i = 0; i < size_M; i++) {
        for (size_t j = 0; j < size_N; j++) {
            std::cout << matrix[i][j] << "   ";
        }
        std::cout << std::endl;
    }
#endif // REALISED_OPERATOR[] 
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
void start_matrix_calculator(int& link_user_choice) {
    int isExit = NO;
    int& link_isExit = isExit;
    int want_to_save = NO;
    int& linkwant_to_save = want_to_save;
    int what_the_first_matrix = 0;
    int what_the_second_matrix = 0;
    int& link_what_the_first_matrix = what_the_first_matrix;
    int& link_what_the_second_matrix = what_the_second_matrix;
    print_menu_matrix_calculator();
    while (!input_user_choice(link_user_choice, START_MENU_MATRIX_CALCULATE_SIZE));
    system("cls");
    while (!isExit) {
        if (link_user_choice != EXIT_CALCULATE_MATRIX_MENU) {
            what_matrices(link_what_the_first_matrix, link_what_the_second_matrix, link_isExit);
            system("cls");
            if (isExit == YES) {
                break;
            }
            size_t sizeM1, sizeN1;
            size_t& link_sizeM1 = sizeM1;
            size_t& link_sizeN1 = sizeN1;
            size_t sizeM2, sizeN2;
            size_t& link_sizeM2 = sizeM2;
            size_t& link_sizeN2 = sizeN2;
            size_t size_resM, size_resN;
            size_t& link_size_resM = size_resM;
            size_t& link_size_resN = size_resN;
            if (link_user_choice == ADD || link_user_choice == SUBTRACT) {
                what_matrix_sizes(link_sizeN1, link_sizeM1);
                sizeM2 = sizeM1;
                size_resM = sizeM1;
                sizeN2 = sizeN1;
                size_resN = sizeN1;
            }
            else if (link_user_choice == MULTIPLY) {
                std::cout << "==================================================" << std::endl;
                std::cout << "  For the first matrix" << std::endl;
                what_matrix_sizes(link_sizeN1, link_sizeM1);
                std::cout << "==================================================" << std::endl;
                std::cout << "  For the second matrix" << std::endl;
                what_matrix_sizes(link_sizeN2, link_sizeM2);
                while (sizeN1 != sizeM2) {
                    set_color(12, 0);
                    std::cout << "ERROR: ";
                    set_color(7, 0);
                    std::cout << "The parameter N for 1 of the matrix and the parametr M for 2 must be equal" << std::endl;
                    std::cout << "==================================================" << std::endl;
                    std::cout << "  For the first matrix" << std::endl;
                    what_matrix_sizes(link_sizeN1, link_sizeM1);
                    std::cout << "==================================================" << std::endl;
                    std::cout << "  For the second matrix" << std::endl;
                    what_matrix_sizes(link_sizeN2, link_sizeM2);
                }
                size_resM = sizeN1;
                size_resM = sizeM2;
            }
            if (what_the_first_matrix == STANDART && what_the_second_matrix == STANDART) {
                TMatrix<TMatrix<int>> matrix1;
                TMatrix<TMatrix<int>> matrix2;
                TMatrix<TMatrix<int>> res;
                
            }
            else if (what_the_first_matrix == TRIANGLE && what_the_second_matrix == TRIANGLE) {
                TriangleMatrix<TriangleMatrix<int>> matrix1;
                TriangleMatrix<TriangleMatrix<int>> matrix2;
                TriangleMatrix<TriangleMatrix<int>> res;
            }
        }
        system("cls");
        switch (link_user_choice) {
        case ADD:
#ifndef REALISED_ADD
            in_development();
#else
            res = matrix1.add_matrices(matrix2);
            print_res(res, size_resM, size_resN);
            void do_user_want_to_save(link_want_to_save);
#endif //REALISED_ADD
            break;

        case SUBTRACT:
#ifndef REALISED_SUBTRACT
            in_development();
#else
            res = matrix1.subtract_matrices(matrix2);
            print_res(res, size_resM, size_resN);
#endif //REALISED_SUBTRACT
            break;

        case MULTIPLY:
#ifndef REALISED_MULTIPLY
            in_development();
#else
            res = matrix1.multiply_matrices(matrix2);
            print_res(res, size_resM, size_resN);
#endif //REALISED_MULTIPLY
            break;

        case EXIT_CALCULATE_MATRIX_MENU:
            isExit = YES;
            break;
        }
    }
}
void matrix_application() {
    int user_choice;
    int& link_user_choice = user_choice;
    int isExit = NO;
    while (!isExit) {
        start_menu_for_matrix();
        while (!input_user_choice(link_user_choice, START_MENU_FOR_MATRIX_SIZE));
        system("cls");
        switch (user_choice) {
        case MATRIX_CALCULATOR:
            start_matrix_calculator(link_user_choice);
            break;
        case VIEWING_SAVED_MATRICES:

            break;
        case EXIT_MAIN_MENU:
            isExit = YES;
            break;
        }
    }
}


