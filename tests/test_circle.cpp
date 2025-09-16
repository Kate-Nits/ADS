// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_circle/circle.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestCircleLib, default_constructor) {
    // Arrange
    Circle A;
    Point b;
    // Act
    int actual_result = FALSE;
    if (A.get_center() == b && A.get_radius() == 1) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestCircleLib, parameterized_constructor) {
    // Arrange
    Point a(5, 27);
    Circle C(a, 6);

    // Act
    int actual_result = FALSE;
    if (C.get_center() == a && C.get_radius() == 6) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestCircleLib, copy_constructor_without_throw) {
    // Arrange
    Circle A(Point(-4, 10), 7);
    Circle B(A);

    // Act
    int actual_result = FALSE;
    if (B.get_center() == A.get_center() && B.get_radius() == A.get_radius()) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestCircleLib, copy_constructor_with_throw) {
    // Arrange
    Circle* null_pointer = nullptr;
    // Act & Assert
    EXPECT_THROW({ Circle & bad_reference = *null_pointer; Circle a(bad_reference); }, std::logic_error);
}


