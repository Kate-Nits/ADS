// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_triangle_matrix/triangle_matrix.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestTriangleMatrixLib, default_constructor) {
    // Arrange & Act
    TriangleMatrix<int> m;

    // Assert
    EXPECT_EQ(0, m.rows());
    EXPECT_EQ(0, m.cols());
}

TEST(TestTriangleMatrixLib, constructor_for_int_matrix_with_size) {
    // Arrange & Act
    TriangleMatrix<int> m(4);

    // Assert
    EXPECT_EQ(4, m.rows());
    EXPECT_EQ(4, m.cols());
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.cols(); ++j) {
            EXPECT_EQ(0, m.at(i, j));
        }
    }
}

TEST(TestTriangleMatrixLib, constructor_for_double_matrix_with_size) {
    // Arrange & Act
    TriangleMatrix<int> m(5);

    // Assert
    EXPECT_EQ(5, m.rows());
    EXPECT_EQ(5, m.cols());
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.cols(); ++j) {
            EXPECT_EQ(0.0, m.at(i, j));
        }
    }
}

TEST(TestTriangleMatrixLib, constructor_copy) {
    // Arrange
    TriangleMatrix<int> matrix1(3);
    matrix1.at(0, 0) = 1;
    matrix1.at(0, 1) = 2;

    // Act
    TriangleMatrix<int> matrix2(matrix1);

    // Assert
    EXPECT_EQ(3, matrix2.rows());
    EXPECT_EQ(3, matrix2.cols());
    EXPECT_EQ(1, matrix2.at(0, 0));
    EXPECT_EQ(2, matrix2.at(0, 1));
}