// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_tvector/tvector.h"
#include "../lib_mathvector/MathVector.h"
#include "../lib_matrix/matrix.h"
#include "../lib_algorithms/algorithms.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestAlgorithmsLib, test_position00_value11_from_example) {
    // Arrange (Настройка)
    Matrix<int> matrix{ {11, 15, 10, 9}, {6, 16, 3, 8}, {7, 4, 2, 13}, {14, 12, 1, 5} };

    // Act 
    std::cout << "Testing with start position [0][0] = value 11" << std::endl;
    int res = gradient_descent(matrix);

    // Assert
    EXPECT_EQ(6, res);
}

TEST(TestAlgorithmsLib, test_position20_value7_from_example) {
    // Arrange (Настройка)
    Matrix<int> matrix{ {11, 15, 10, 9}, {6, 16, 3, 8}, {7, 4, 2, 13}, {14, 12, 1, 5} };

    // Act 
    std::cout << "Testing with start position [2][0] = value 7" << std::endl;
    int res = gradient_descent(matrix);

    // Assert
    EXPECT_EQ(1, res);
}

TEST(TestAlgorithmsLib, test_position22_value9_from_example) {
    // Arrange (Настройка)
    Matrix<int> matrix{ {3, 1, 2}, {5, 8, 4}, {7, 6, 9} };

    // Act 
    std::cout << "Testing with start position [2][2] = value 9" << std::endl;
    int res = gradient_descent(matrix);

    // Assert
    EXPECT_EQ(1, res);
}