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