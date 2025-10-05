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

TEST(TestTriangleMatrixLib, test_addition_int_triangle_matrix_with_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(3), b(3);
    a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3; a.at(1, 1) = 4; a.at(1, 2) = 5; a.at(2, 2) = 6;
    b.at(0, 0) = 7; b.at(0, 1) = 8; b.at(0, 2) = 9; b.at(1, 1) = 10; b.at(1, 2) = 11; b.at(2, 2) = 12;
    
    // Act
    TriangleMatrix<int> c = a + b;

    // Assert
    EXPECT_EQ(8, c.at(0, 0));
    EXPECT_EQ(10, c.at(0, 1));
    EXPECT_EQ(12, c.at(0, 2));
    EXPECT_EQ(0, c.at(1, 0));
    EXPECT_EQ(14, c.at(1, 1));
    EXPECT_EQ(16, c.at(1, 2));
    EXPECT_EQ(0, c.at(2, 0));
    EXPECT_EQ(0, c.at(2, 1));
    EXPECT_EQ(18, c.at(2, 2));
}

TEST(TestTriangleMatrixLib, test_addition_int_triangle_matrix_without_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(3), b(4);

    // Act & Assert
    EXPECT_ANY_THROW(a + b);
}

TEST(TestTriangleMatrixLib, test_subtraction_int_triangle_matrix_with_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(3), b(3);
    int number = 1;
    a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3; a.at(1, 1) = 4; a.at(1, 2) = 5; a.at(2, 2) = 6;
    b.at(0, 0) = 7; b.at(0, 1) = 8; b.at(0, 2) = 9; b.at(1, 1) = 10; b.at(1, 2) = 11; b.at(2, 2) = 12;

    // Act
    TriangleMatrix<int> c = b - a;

    // Assert
    EXPECT_EQ(6, c.at(0, 0));
    EXPECT_EQ(6, c.at(0, 1));
    EXPECT_EQ(6, c.at(0, 2));
    EXPECT_EQ(0, c.at(1, 0));
    EXPECT_EQ(6, c.at(1, 1));
    EXPECT_EQ(6, c.at(1, 2));
    EXPECT_EQ(0, c.at(2, 0));
    EXPECT_EQ(0, c.at(2, 1));
    EXPECT_EQ(6, c.at(2, 2));
}

TEST(TestTriangleMatrixLib, test_subtraction_int_triangle_matrix_without_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(4), b(3);

    // Act & Assert
    EXPECT_ANY_THROW(a - b);
}