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
    ASSERT_ANY_THROW(a + b);
}

TEST(TestTriangleMatrixLib, test_subtraction_int_triangle_matrix_with_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(3), b(3);
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
    ASSERT_ANY_THROW(a - b);
}

TEST(TestTriangleMatrixLib, test_mult_a_int_TriangleMatrix_by_a_scalar) {
    // Arrange
    TriangleMatrix<int> A(3);
    A.at(0, 0) = 1; A.at(0, 1) = 2; A.at(0, 2) = 3; A.at(1, 1) = 4; A.at(1, 2) = 5; A.at(2, 2) = 6;

    // Act
    TriangleMatrix<int> C = A * 2;

    // Assert
    EXPECT_EQ(2, C.at(0, 0));
    EXPECT_EQ(4, C.at(0, 1));
    EXPECT_EQ(6, C.at(0, 2));
    EXPECT_EQ(0, C.at(1, 0));
    EXPECT_EQ(8, C.at(1, 1));
    EXPECT_EQ(10, C.at(1, 2));
    EXPECT_EQ(0, C.at(2, 0));
    EXPECT_EQ(0, C.at(2, 1));
    EXPECT_EQ(12, C.at(2, 2));
}

TEST(TestTriangleMatrixLib, test_mult_a_int_TriangleMatrix_by_a_vector_with_correct_equal_size) {
    // Arrange
    TriangleMatrix<int> A(3);
    A.at(0, 0) = 1; A.at(0, 1) = 2; A.at(0, 2) = 3; A.at(1, 1) = 4; A.at(1, 2) = 5; A.at(2, 2) = 6;
    MathVector<int> vec{ 7, 8, 9 };

    // Act
    MathVector<int> C = A * vec;

    // Assert
    EXPECT_EQ(50, C.at(0));
    EXPECT_EQ(77, C.at(1));
    EXPECT_EQ(54, C.at(2));
}

TEST(TestTriangleMatrixLib, test_mult_a_int_TriangleMatrix_by_a_vector_without_correct_equal_size) {
    // Arrange
    TriangleMatrix<int> A(3);
    MathVector<int> vec(4);

    // Act & Assert
    ASSERT_ANY_THROW(A * vec);
}

TEST(TestTriangleMatrixLib, test_mult_a_int_TriangleMatrix_by_a_int_TriangleMatrix_with_correct_equal_size) {
    // Arrange
    TriangleMatrix<int> A(3), B(3);
    A.at(0, 0) = 1; A.at(0, 1) = 2; A.at(0, 2) = 3; A.at(1, 1) = 4; A.at(1, 2) = 5; A.at(2, 2) = 6;
    B.at(0, 0) = 7; B.at(0, 1) = 8; B.at(0, 2) = 9; B.at(1, 1) = 10; B.at(1, 2) = 11; B.at(2, 2) = 12;

    // Act
    TriangleMatrix<int> C = A * B;

    // Assert
    EXPECT_EQ(7, C.at(0, 0));
    EXPECT_EQ(28, C.at(0, 1));
    EXPECT_EQ(67, C.at(0, 2));
    EXPECT_EQ(0, C.at(1, 0));
    EXPECT_EQ(40, C.at(1, 1));
    EXPECT_EQ(104, C.at(1, 2));
    EXPECT_EQ(0, C.at(2, 0));
    EXPECT_EQ(0, C.at(2, 1));
    EXPECT_EQ(72, C.at(2, 2));
}

TEST(TestTriangleMatrixLib, test_mult_a_int_TriangleMatrix_by_a_int_TriangleMatrix_without_correct_equal_size) {
    // Arrange
    TriangleMatrix<int> A(3), B(4);

    // Act & Assert
    ASSERT_ANY_THROW(A * B);
}

TEST(TestTriangleMatrixLib, test_addition_int_matrix_and_int_triangle_matrix_with_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(3);
    a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3; a.at(1, 1) = 4; a.at(1, 2) = 5; a.at(2, 2) = 6;
    Matrix<int> b{ {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };

    // Act
    Matrix<int> c = b + a;

    // Assert
    EXPECT_EQ(2, c.at(0, 0));
    EXPECT_EQ(3, c.at(0, 1));
    EXPECT_EQ(4, c.at(0, 2));
    EXPECT_EQ(1, c.at(1, 0));
    EXPECT_EQ(5, c.at(1, 1));
    EXPECT_EQ(6, c.at(1, 2));
    EXPECT_EQ(1, c.at(2, 0));
    EXPECT_EQ(1, c.at(2, 1));
    EXPECT_EQ(7, c.at(2, 2));
}

TEST(TestTriangleMatrixLib, test_addition_int_matrix_and_int_triangle_matrix_without_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(3);
    a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3; a.at(1, 1) = 4; a.at(1, 2) = 5; a.at(2, 2) = 6;
    Matrix<int> b{ {1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };

    // Act & Assert
    ASSERT_ANY_THROW(b + a);
}

TEST(TestTriangleMatrixLib, test_addition_int_triangle_matrix_and_int_matrix_with_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(3);
    a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3; a.at(1, 1) = 4; a.at(1, 2) = 5; a.at(2, 2) = 6;
    Matrix<int> b{ {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };

    // Act
    Matrix<int> c = a + b;

    // Assert
    EXPECT_EQ(2, c.at(0, 0));
    EXPECT_EQ(3, c.at(0, 1));
    EXPECT_EQ(4, c.at(0, 2));
    EXPECT_EQ(1, c.at(1, 0));
    EXPECT_EQ(5, c.at(1, 1));
    EXPECT_EQ(6, c.at(1, 2));
    EXPECT_EQ(1, c.at(2, 0));
    EXPECT_EQ(1, c.at(2, 1));
    EXPECT_EQ(7, c.at(2, 2));
}

TEST(TestTriangleMatrixLib, test_addition_int_triangle_matrix_and_int_matrix_without_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(3);
    a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3; a.at(1, 1) = 4; a.at(1, 2) = 5; a.at(2, 2) = 6;
    Matrix<int> b{ {1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };

    // Act & Assert
    ASSERT_ANY_THROW(a + b);
}

TEST(TestTriangleMatrixLib, test_subtraction_int_matrix_and_int_triangle_matrix_with_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(3);
    a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3; a.at(1, 1) = 4; a.at(1, 2) = 5; a.at(2, 2) = 6;
    Matrix<int> b{ {20, 20, 20}, {20, 20, 20}, {20, 20, 20} };

    // Act
    Matrix<int> c = b - a;

    // Assert
    EXPECT_EQ(19, c.at(0, 0));
    EXPECT_EQ(18, c.at(0, 1));
    EXPECT_EQ(17, c.at(0, 2));
    EXPECT_EQ(20, c.at(1, 0));
    EXPECT_EQ(16, c.at(1, 1));
    EXPECT_EQ(15, c.at(1, 2));
    EXPECT_EQ(20, c.at(2, 0));
    EXPECT_EQ(20, c.at(2, 1));
    EXPECT_EQ(14, c.at(2, 2));
}

TEST(TestTriangleMatrixLib, test_subtraction_int_matrix_and_int_triangle_matrix_without_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(4);
    Matrix<int> b{ {20, 20, 20}, {20, 20, 20}, {20, 20, 20} };

    // Act & Assert
    ASSERT_ANY_THROW(b - a);
}

TEST(TestTriangleMatrixLib, test_subtraction_int_triangle_matrix_and_int_matrix_with_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(3);
    a.at(0, 0) = 1; a.at(0, 1) = 2; a.at(0, 2) = 3; a.at(1, 1) = 4; a.at(1, 2) = 5; a.at(2, 2) = 6;
    Matrix<int> b{ {20, 20, 20}, {20, 20, 20}, {20, 20, 20} };

    // Act
    Matrix<int> c = a - b;

    // Assert
    EXPECT_EQ(-19, c.at(0, 0));
    EXPECT_EQ(-18, c.at(0, 1));
    EXPECT_EQ(-17, c.at(0, 2));
    EXPECT_EQ(-20, c.at(1, 0));
    EXPECT_EQ(-16, c.at(1, 1));
    EXPECT_EQ(-15, c.at(1, 2));
    EXPECT_EQ(-20, c.at(2, 0));
    EXPECT_EQ(-20, c.at(2, 1));
    EXPECT_EQ(-14, c.at(2, 2));
}

TEST(TestTriangleMatrixLib, test_subtraction_int_triangle_matrix_and_int_matrix_without_the_same_size) {
    // Arrange
    TriangleMatrix<int> a(4);
    Matrix<int> b{ {20, 20, 20}, {20, 20, 20}, {20, 20, 20} };

    // Act & Assert
    ASSERT_ANY_THROW(a - b);
}

TEST(TestTriangleMatrixLib, test_mult_a_int_Matrix_by_a_int_Triangle_Matrix_with_correct_equal_size) {
    // Arrange
    TriangleMatrix<int> A(3);
    A.at(0, 0) = 1; A.at(0, 1) = 2; A.at(0, 2) = 3; A.at(1, 1) = 4; A.at(1, 2) = 5; A.at(2, 2) = 6;
    Matrix<int> B{ {2, 2, 2}, {2, 2, 2}, {2, 2, 2} };

    // Act
    Matrix<int> C = B * A;

    // Assert
    EXPECT_EQ(2, C.at(0, 0));
    EXPECT_EQ(12, C.at(0, 1));
    EXPECT_EQ(28, C.at(0, 2));
    EXPECT_EQ(2, C.at(1, 0));
    EXPECT_EQ(12, C.at(1, 1));
    EXPECT_EQ(28, C.at(1, 2));
    EXPECT_EQ(2, C.at(2, 0));
    EXPECT_EQ(12, C.at(2, 1));
    EXPECT_EQ(28, C.at(2, 2));
}

TEST(TestTriangleMatrixLib, test_mult_a_int_Matrix_by_a_int_Triangle_Matrix_without_correct_equal_size) {
    // Arrange
    TriangleMatrix<int> A(4);
    A.at(0, 0) = 1; A.at(0, 1) = 2; A.at(0, 2) = 3; A.at(1, 1) = 4; A.at(1, 2) = 5; A.at(2, 2) = 6;
    Matrix<int> B{ {2, 2, 2}, {2, 2, 2}, {2, 2, 2} };

    // Act & Assert
    ASSERT_ANY_THROW(B * A);
}

TEST(TestTriangleMatrixLib, test_mult_a_int_Triangle_Matrix_by_a_int_Matrix_with_correct_equal_size) {
    // Arrange
    TriangleMatrix<int> A(3);
    A.at(0, 0) = 1; A.at(0, 1) = 2; A.at(0, 2) = 3; A.at(1, 1) = 4; A.at(1, 2) = 5; A.at(2, 2) = 6;
    Matrix<int> B{ {2, 2, 2}, {2, 2, 2}, {2, 2, 2} };

    // Act
    Matrix<int> C = A * B;

    // Assert
    EXPECT_EQ(12, C.at(0, 0));
    EXPECT_EQ(12, C.at(0, 1));
    EXPECT_EQ(12, C.at(0, 2));
    EXPECT_EQ(18, C.at(1, 0));
    EXPECT_EQ(18, C.at(1, 1));
    EXPECT_EQ(18, C.at(1, 2));
    EXPECT_EQ(12, C.at(2, 0));
    EXPECT_EQ(12, C.at(2, 1));
    EXPECT_EQ(12, C.at(2, 2));
}

TEST(TestTriangleMatrixLib, test_mult_a_int_Triangle_Matrix_by_a_int_Matrix_without_correct_equal_size) {
    // Arrange
    TriangleMatrix<int> A(4);
    A.at(0, 0) = 1; A.at(0, 1) = 2; A.at(0, 2) = 3; A.at(1, 1) = 4; A.at(1, 2) = 5; A.at(2, 2) = 6;
    Matrix<int> B{ {2, 2, 2}, {2, 2, 2}, {2, 2, 2} };

    // Act & Assert
    ASSERT_ANY_THROW(A * B);
}