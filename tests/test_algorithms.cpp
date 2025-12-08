// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"
#include "../lib_mathvector/MathVector.h"
#include "../lib_matrix/matrix.h"
#include "../lib_algorithms/algorithms.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestAlgorithmsLib, test_gradient_descent_from_example1) {
    // Arrange
    Matrix<int> matrix{ {3, 1, 2}, {5, 8, 4}, {7, 6, 9} };

    // Act 
    int res = gradient_descent(matrix);

    // Assert
    EXPECT_TRUE(res == 6 || res == 1);
}

TEST(TestAlgorithmsLib, test_gradient_descent_from_example2) {
    // Arrange
    Matrix<int> matrix{ {11, 15, 10, 9}, {6, 16, 3, 8}, {7, 4, 2, 13}, {14, 12, 1, 5} };

    // Act 
    int res = gradient_descent(matrix);

    // Assert
    EXPECT_TRUE(res == 6 || res == 1);
}

TEST(TestAlgorithmsLib, test_1_on_check_brackets_empty_list) {
    // Arrange
    std::string string = "";

    // Act & Assert
    EXPECT_TRUE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_2_on_check_brackets_easy) {
    // Arrange
    std::string string = "()";

    // Act & Assert
    EXPECT_TRUE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_3_on_check_brackets_easy) {
    // Arrange
    std::string string = "()()";

    // Act & Assert
    EXPECT_TRUE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_4_on_check_brackets) {
    // Arrange
    std::string string = "[(()())(())]";

    // Act & Assert
    EXPECT_TRUE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_5_on_check_brackets) {
    // Arrange
    std::string string = "(()()";

    // Act & Assert
    EXPECT_FALSE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_6_on_check_brackets) {
    // Arrange
    std::string string = "())(())";

    // Act & Assert
    EXPECT_FALSE(check_brackets(string));
}

TEST(TestAlgorithmsLib, test_7_on_check_brackets) {
    // Arrange
    std::string string = "((()()(()))";

    // Act & Assert
    EXPECT_FALSE(check_brackets(string));
}

TEST(TestAlgorithmsLib, different_types_of_brackets_correct) {
    // Arrange
    std::string str = "({[]})";

    // Act & Assert
    EXPECT_TRUE(check_brackets(str));
}

TEST(TestAlgorithmsLib, mixed_brackets_incorrect) {
    // Arrange
    std::string str = "({[}])";

    // Act & Assert
    EXPECT_FALSE(check_brackets(str));
}

TEST(TestAlgorithmsLib, real_example_with_text) {
    // Arrange
    std::string str = "[5*(x+8)-9]/[(7/(y*1))*(y*1)]";

    // Act & Assert
    EXPECT_TRUE(check_brackets(str));
}