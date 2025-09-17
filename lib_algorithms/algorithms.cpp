// Copyright 2025 Ekaterina Ushnitskaya

#include <stdexcept>
#include <iostream>
#include <windows.h>
#include <cmath>

#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"

#define START_MENU_MATRIX_SIZE 3

void set_color(int text_color, int bg_color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

enum Location { intersecting, do_not_intersecting, tangent, inside, coinside };
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

void start_menu_for_matrix() {
    std::cout << "==========================================" << std::endl;
    std::cout << "          WORKING WITH MATRICES           " << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "  1. Matrix calculator " << std::endl;
    std::cout << "  2. Viewing saved matrices " << std::endl;
    std::cout << "  3. Exit " << std::endl;
    std::cout << "==========================================" << std::endl;
    
    //std::cout << "==========================================" << std::endl;
    //std::cout << "" << std::endl;
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

void matrix_application() {
    int user_choice;
    int& link_user_choice = user_choice;
    start_menu_for_matrix();
    while (!input_user_choice(link_user_choice, START_MENU_MATRIX_SIZE));
}


