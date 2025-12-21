// Copyright 2025 Ekaterina Ushnitskaya

#include <stdexcept>
#include <iostream>
#include <windows.h>
#include <cmath>
#include <cstring>

#include "../lib_algorithms/algorithms.h"
//#include "../lib_circle/circle.h"
//#include "../lib_sphere/sphere.h"
//#include "../lib_stack/stack.h"
//#include "../lib_matrix/matrix.h"
//#include "../lib_triangle_matrix/triangle_matrix.h"
//#include "../lib_node/node.h"
//#include "../lib_list/list.h"

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

#define STANDART 1
#define TRIANGLE 2

#define SIZE_OF_STACK_FOR_CHECK_BRACKETS 150

void set_color(int text_color, int bg_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

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
    std::cout << "======================================================" << std::endl;
    std::cout << "              WORKING WITH MATRICES               " << std::endl;
    std::cout << "======================================================" << std::endl;
    std::cout << "  1. Matrix calculator " << std::endl;
    std::cout << "  2. Viewing saved matrices " << std::endl;
    std::cout << "  3. Exit " << std::endl;
    std::cout << "======================================================" << std::endl;
    //std::cout << "======================================================" << std::endl;
    //std::cout << "" << std::endl;
}
void print_menu_matrix_calculator() {
    system("cls");
    std::cout << "======================================================" << std::endl;
    std::cout << "  What would you like to do with matrices:" << std::endl;
    std::cout << "      1. Add " << std::endl;
    std::cout << "      2. Subtract" << std::endl;
    std::cout << "      3. multiply" << std::endl;
    std::cout << "      4. Exit" << std::endl;
    std::cout << "======================================================" << std::endl;
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
    std::cout << "======================================================" << std::endl;
    std::cout << "  What will the first matrix be like?" << std::endl;
    std::cout << "      1. Standart" << std::endl;
    std::cout << "      2. Triangle" << std::endl;
    std::cout << "      3. Exit" << std::endl;
    while (!input_user_choice(link_user_choice, WHAT_MATRIX_MENU));
    if (user_choice == 3) {
        isExit = YES;
    }
    else {
        if (user_choice == STANDART) { what_the_first_matrix = STANDART;}
        else { what_the_first_matrix = TRIANGLE; }
        std::cout << "======================================================" << std::endl;
        std::cout << "  What will the second matrix be like?" << std::endl;
        std::cout << "      1. Standart" << std::endl;
        std::cout << "      2. Triangle" << std::endl;
        while (!input_user_choice(link_user_choice, 2));
        if (user_choice == STANDART) { what_the_second_matrix = STANDART; }
        else { what_the_second_matrix = TRIANGLE; }
    }
}
void what_matrix_sizes(const int& type_matrix, size_t& size_rows, size_t& size_cols) {
    if (type_matrix == STANDART) {
        std::cout << "======================================================" << std::endl;
        std::cout << "Enter the number of rows (parametr M): ";
        std::cin >> size_rows;
        std::cout << "Enter the number of columns (parametr N): ";
        std::cin >> size_cols;
    }
    else if (type_matrix == TRIANGLE) {
        std::cout << "======================================================" << std::endl;
        std::cout << "Enter the size of the triangle matrix (parametr N): ";
        std::cin >> size_rows;
        size_cols = size_rows;
    }
    else {
        throw std::logic_error("The matrix has an invalid type!");
    }
    
}
void do_user_want_to_save(int& want_to_save) {
    std::cout << "======================================================" << std::endl;
    std::cout << "Would you like to save result?" << std::endl;
    std::cout << "======================================================" << std::endl;
    std::cout << "If answer - yes - input 1. If no, then input 0: ";
    std::cin >> want_to_save;
    while (want_to_save != YES && want_to_save != NO) {
        std::cout << "======================================================" << std::endl;
        set_color(12, 0);
        std::cout << "ERROR: ";
        set_color(7, 0);
        std::cout << "your choice is more than points" << std::endl;
        std::cout << "======================================================" << std::endl;
        std::cout << "Tru again" << std::endl;
        std::cout << "If answer - yes - input 1. If no, then input 0: ";
        std::cin >> want_to_save;
    }
}
void input_standart_matrix(Matrix<int>& matrix, size_t rows, size_t cols) {
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
void start_matrix_calculator(int& link_user_choice, int& link_want_to_save, Matrix<int> res, 
    int& count_of_saved_matrices, Matrix<int>& matrix1, Matrix<int>& matrix2, Matrix<int>& matrix3, 
    int& isThereMatrix1, int& isThereMatrix2, int& isThereMatrix3) {
    
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
        size_t size_rows1 = 0, size_cols1 = 0, size_rows2 = 0, size_cols2 = 0;
        size_t size_res_rows = 0, size_res_cols = 0;
        if (what_the_first_matrix == TRIANGLE || what_the_second_matrix == TRIANGLE || link_user_choice == ADD || link_user_choice == SUBTRACT) {
            if (what_the_first_matrix == TRIANGLE || what_the_second_matrix == TRIANGLE) {
                what_matrix_sizes(TRIANGLE, size_rows1, size_cols1);
                size_rows2 = size_rows1;
                size_cols2 = size_cols1;
                size_res_rows = size_rows1;
                size_res_cols = size_cols1;
            }
            else {
                what_matrix_sizes(what_the_first_matrix, size_rows1, size_cols1);
                size_rows2 = size_rows1;
                size_cols2 = size_cols1;
                size_res_rows = size_rows1;
                size_res_cols = size_cols1;
            }
        }
        else {
            std::cout << "======================================================" << std::endl;
            std::cout << "  For the first matrix" << std::endl;
            what_matrix_sizes(what_the_first_matrix, size_cols1, size_rows1);
            std::cout << "======================================================" << std::endl;
            std::cout << "  For the second matrix" << std::endl;
            what_matrix_sizes(what_the_second_matrix, size_cols2, size_rows2);
            while (size_cols1 != size_rows2) {
                set_color(12, 0);
                std::cout << "ERROR: ";
                set_color(7, 0);
                std::cout << "The parameter N for 1 of the matrix and the parametr M for 2 must be equal" << std::endl;
                std::cout << "======================================================" << std::endl;
                std::cout << "  For the first matrix" << std::endl;
                what_matrix_sizes(what_the_first_matrix, size_cols1, size_rows1);
                std::cout << "======================================================" << std::endl;
                std::cout << "  For the second matrix" << std::endl;
                what_matrix_sizes(what_the_second_matrix, size_cols2, size_rows2);
            }
            size_res_rows = size_cols1;
            size_res_rows = size_rows2;
        }

        if (what_the_first_matrix == STANDART && what_the_second_matrix == STANDART) {
            Matrix<int> matrix1(size_rows1, size_cols1);
            Matrix<int> matrix2(size_rows2, size_cols2);
            Matrix<int> intermediate_res;
            std::cout << "======================================================" << std::endl;
            std::cout << "  For the first matrix:" << std::endl;
            input_standart_matrix(matrix1, size_rows1, size_cols1);
            std::cout << "======================================================" << std::endl;
            std::cout << "  For the second matrix:" << std::endl;
            input_standart_matrix(matrix2, size_rows2, size_cols2);
            switch (link_user_choice) {
            case ADD: intermediate_res = matrix1 + matrix2; break;
            case SUBTRACT: intermediate_res = matrix1 - matrix2; break;
            case MULTIPLY: intermediate_res = matrix1 * matrix2; break;
            }
            res = intermediate_res;
            std::cout << "======================================================" << std::endl;
            std::cout << "  RESULT:" << std::endl;
            std::cout << res << std::endl;
            do_user_want_to_save(link_want_to_save);
        }
        else if (what_the_first_matrix == TRIANGLE && what_the_second_matrix == TRIANGLE) {
            TriangleMatrix<int> matrix1(size_rows1);
            TriangleMatrix<int> matrix2(size_rows2);
            TriangleMatrix<int> intermediate_res;
            std::cout << "======================================================" << std::endl;
            std::cout << "  For the first triangle matrix:" << std::endl;
            input_triangle_matrix(matrix1, size_rows1);
            std::cout << "======================================================" << std::endl;
            std::cout << "  For the second triangle matrix:" << std::endl;
            input_triangle_matrix(matrix2, size_rows2);
            switch (link_user_choice) {
            case ADD: intermediate_res = matrix1 + matrix2; break;
            case SUBTRACT: intermediate_res = matrix1 - matrix2; break;
            case MULTIPLY: intermediate_res = matrix1 * matrix2; break;
            }
            res = triangle_to_full(intermediate_res);
            std::cout << "======================================================" << std::endl;
            std::cout << "  RESULT:" << std::endl;
            std::cout << res << std::endl;
            do_user_want_to_save(link_want_to_save); 
        }
        else if (what_the_first_matrix == STANDART && what_the_second_matrix == TRIANGLE) {
            Matrix<int> matrix1(size_rows1, size_cols1), intermediate_res;
            TriangleMatrix<int> matrix2(size_rows2);
            std::cout << "======================================================" << std::endl;
            std::cout << "  For the first standart matrix:" << std::endl;
            input_standart_matrix(matrix1, size_rows1, size_cols1);
            std::cout << "======================================================" << std::endl;
            std::cout << "  For the second triangle matrix:" << std::endl;
            input_triangle_matrix(matrix2, size_rows2);
            switch (link_user_choice) {
            case ADD: intermediate_res = matrix1 + matrix2; break;
            case SUBTRACT: intermediate_res = matrix1 - matrix2; break;
            case MULTIPLY: intermediate_res = matrix1 * matrix2; break;
            }
            res = intermediate_res;
            std::cout << "======================================================" << std::endl;
            std::cout << "  RESULT:" << std::endl;
            std::cout << res << std::endl;
            do_user_want_to_save(link_want_to_save);
        }
        else if (what_the_first_matrix == TRIANGLE && what_the_second_matrix == STANDART) {
            TriangleMatrix<int> matrix1(size_rows1);
            Matrix<int> matrix2(size_rows2, size_cols2), intermediate_res;
            std::cout << "======================================================" << std::endl;
            std::cout << "  For the first triangle matrix:" << std::endl;
            input_triangle_matrix(matrix1, size_rows1);
            std::cout << "======================================================" << std::endl;
            std::cout << "  For the second standart matrix:" << std::endl;
            input_standart_matrix(matrix2, size_rows2, size_cols2);
            switch (link_user_choice) {
            case ADD: intermediate_res = matrix1 + matrix2; break;
            case SUBTRACT: intermediate_res = matrix1 - matrix2; break;
            case MULTIPLY: intermediate_res = matrix1 * matrix2; break;
            }
            res = intermediate_res;
            std::cout << "======================================================" << std::endl;
            std::cout << "  RESULT:" << std::endl;
            std::cout << res << std::endl;
            do_user_want_to_save(link_want_to_save);
        }

        if (link_want_to_save == YES) {
            int user_choice_for_deleted;
            while ((count_of_saved_matrices + 1) > MAX_COUNT_OF_SAVED_MATRICES) {
                deleted_saved_matrix(user_choice_for_deleted, isThereMatrix1, isThereMatrix2, isThereMatrix3);
                if (user_choice_for_deleted == EXIT_DELETED_SAVED_MATRICES_MENU) { break; }
                else { count_of_saved_matrices--; }
            }
            if (isThereMatrix1 == NO) {
                std::cout << "======================================================" << std::endl;
                std::cout << "  The result will be written to the matrix1" << std::endl;
                isThereMatrix1 = YES;
                count_of_saved_matrices++;
                matrix1 = res;
            }
            else if (isThereMatrix2 == NO) {
                std::cout << "======================================================" << std::endl;
                std::cout << "  The result will be written to the matrix2" << std::endl;
                isThereMatrix2 = YES;
                count_of_saved_matrices++;
                matrix2 = res;
            }
            else if (isThereMatrix3 == NO) {
                std::cout << "======================================================" << std::endl;
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
    }
}
void deleted_saved_matrix(int& link_user_choice_for_deleted, int& isThereMatrix1, int& isThereMatrix2, int& isThereMatrix3) {
    std::cout << "======================================================" << std::endl;
    std::cout << "  You can store a limited number of matrices" << std::endl;
    std::cout << "  Which one would you like to delete?" << std::endl;
    std::cout << "      1. matrix1" << std::endl;
    std::cout << "      2. matrix2" << std::endl;
    std::cout << "      3. matrix3" << std::endl;;
    std::cout << "      4. exit" << std::endl;

    while (!input_user_choice(link_user_choice_for_deleted, EXIT_DELETED_SAVED_MATRICES_MENU));
    switch (link_user_choice_for_deleted) {
    case MATRIX1: isThereMatrix1 = NO; break;
    case MATRIX2: isThereMatrix2 = NO; break;
    case MATRIX3: isThereMatrix3 = NO; break;
    case EXIT_DELETED_SAVED_MATRICES_MENU: break;
    }
}
void viewing_saved_matrices(int count_of_saved_matrices, Matrix<int> matrix1, Matrix<int> matrix2, Matrix<int> matrix3) {
    std::cout << "======================================================" << std::endl;
    if (count_of_saved_matrices > 0) {
        std::cout << "  Which matrix would you like to look at?" << std::endl;
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
            std::cout << "======================================================" << std::endl << std::endl;
            std::cout << matrix1 << std::endl;
        }
        else if (user_choice == MATRIX2) {
            std::cout << "======================================================" << std::endl;
            std::cout << matrix2 << std::endl;
        }
        else if (user_choice == MATRIX3) {
            std::cout << "======================================================" << std::endl;
            std::cout << matrix3 << std::endl;
        }
    }
    else if (count_of_saved_matrices == 0) {
        std::cout << "  You don't have any saved matrices" << std::endl;
    }
    std::cout << "======================================================" << std::endl;
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
            start_matrix_calculator(user_choice, want_to_save, res, count_of_saved_matrices, matrix1, matrix2, matrix3, isThereMatrix1, isThereMatrix2, isThereMatrix3);
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


inline bool is_open_bracket(char symbol) {
    return symbol == '(' || symbol == '[' || symbol == '{';
}
inline bool is_close_bracket(char symbol) {
    return symbol == ')' || symbol == ']' || symbol == '}';
}
inline bool matches_pair(char open, char close) {
    return (open == '(' && close == ')') ||
        (open == '[' && close == ']') ||
        (open == '{' && close == '}');
}
bool check_brackets(const std::string& str) {
    Stack<char> stack(SIZE_OF_STACK_FOR_CHECK_BRACKETS);
    for (size_t i = 0; i < str.length(); ++i) {
        char symbol = str[i];
        if (is_open_bracket(symbol)) {
            try {
                stack.push(symbol);
            }
            catch (const std::overflow_error&) {
                std::cout << "Stack is full" << std::endl;
                return false;
            }
        }
        else if (is_close_bracket(symbol)) {
            if (stack.is_empty()) {
                return false;
            }
            char top = stack.top();
            if (!matches_pair(top, symbol)) {
                return false;
            }
            stack.pop();
        }
    }
    return stack.is_empty();
}

