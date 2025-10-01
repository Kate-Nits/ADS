// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_matrix/matrix.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestMatrixLib, default_constructor) {
    // Arrange & Act
    Matrix<int> m;

    // Assert
    EXPECT_EQ(0, m.rows());
    EXPECT_EQ(0, m.cols());
}

TEST(TestMatrixLib, constructor_with_size) {
    // Arrange & Act
    Matrix<int> m(3, 4);

    // Assert
    EXPECT_EQ(3, m.rows());
    EXPECT_EQ(4, m.cols());
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.cols(); ++j) {
            EXPECT_EQ(0, m.at(i, j));
        }
    }
}

TEST(TestMatrixLib, constructor_with_initializer_list_of_int_vectors_with_equal_size) {
    // Arrange 
    MathVector<int> vec1{ 1, 2, 3 };
    MathVector<int> vec2{ 4, 5, 6 };
    int number = 1;

    // Act
    Matrix<int> m{ vec1, vec2 };

    // Assert
    EXPECT_EQ(2, m.rows());
    EXPECT_EQ(3, m.cols());
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.cols(); ++j) {
            EXPECT_EQ(number, m.at(i, j));
            number++;
        }
    }
}

TEST(TestMatrixLib, constructor_with_initializer_list_of_double_vectors_with_equal_size) {
    // Arrange 
    MathVector<double> vec1{ 1.1, 2.2 };
    MathVector<double> vec2{ 4.4, 5.5 };

    // Act
    Matrix<double> m{ vec1, vec2 };

    // Assert
    EXPECT_EQ(2, m.rows());
    EXPECT_EQ(2, m.cols());
    EXPECT_NEAR(1.1, m.at(0, 0), EPSILON);
    EXPECT_NEAR(2.2, m.at(0, 1), EPSILON);
    EXPECT_NEAR(4.4, m.at(1, 0), EPSILON);
    EXPECT_NEAR(5.5, m.at(1, 1), EPSILON);
}

TEST(TestMatrixLib, constructor_with_initializer_list_of_vectors_with_different_size) {
    // Arrange 
    MathVector<int> vec1{ 1, 2 };
    MathVector<int> vec2{ 4, 5, 6 };

    // Act & Assert
    ASSERT_ANY_THROW((Matrix<int>{ vec1, vec2 }));
}

TEST(TestMatrixLib, constructor_with_initializer_list_without_vectors_with_int) {
    // Arrange & Act
    int number = 1;
    Matrix<int> m{ { 1, 2, 3 }, { 4, 5, 6 } };

    // Assert
    EXPECT_EQ(2, m.rows());
    EXPECT_EQ(3, m.cols());
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.cols(); ++j) {
            EXPECT_EQ(number, m.at(i, j));
            number++;
        }
    }
}

TEST(TestMatrixLib, copy_constructor) {
    // Arrange 
    int number = 1;
    Matrix<int> m{ { 1, 2, 3 }, { 4, 5, 6 }, {7, 8, 9}, {10, 11, 12} };

    // Act
    Matrix<int> matrix(m);

    // Assert
    EXPECT_EQ(4, matrix.rows());
    EXPECT_EQ(3, matrix.cols());
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            EXPECT_EQ(number, matrix.at(i, j));
            number++;
        }
    }
}

TEST(TestMatrixLib, test_at_row_out_of_range) {
    // Arrange & Act
    Matrix<int> matrix(2, 2);

    // Assert
    ASSERT_ANY_THROW(matrix.at(2, 0));
}

TEST(TestMatrixLib, test_at_col_out_of_range) {
    // Arrange & Act
    Matrix<int> matrix(2, 2);

    // Assert
    ASSERT_ANY_THROW(matrix.at(0, 4));
}

TEST(TestMatrixLib, test_operator_equal) {
    // Arrange 
    int number = 1;
    Matrix<int> m{ { 1, 2, 3 }, { 4, 5, 6 }, {7, 8, 9}, {10, 11, 12} };

    // Act
    Matrix<int> matrix = m;

    // Assert
    EXPECT_EQ(4, matrix.rows());
    EXPECT_EQ(3, matrix.cols());
    for (size_t i = 0; i < matrix.rows(); ++i) {
        for (size_t j = 0; j < matrix.cols(); ++j) {
            EXPECT_EQ(number, matrix.at(i, j));
            number++;
        }
    }
}

TEST(TestMatrixLib, test_element_access) {
    // Arrange & Act
    Matrix<int> matrix(2, 3);
    matrix[0][0] = 10;
    matrix[0][1] = 20;
    matrix[1][2] = 30;

    // Assert
    EXPECT_EQ(10, matrix[0][0]);
    EXPECT_EQ(20, matrix[0][1]);
    EXPECT_EQ(30, matrix[1][2]);
}