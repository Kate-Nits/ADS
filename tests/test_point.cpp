// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_point/point.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestPointLib, default_constructor) {
    // Arrange
    Point a;

    // Act
    int actual_result = FALSE;
    if (a.get_ox() == 0 && a.get_oy() == 0) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestPointLib, parameterized_constructor) {
    // Arrange
    Point a(5, 27);

    // Act
    int actual_result = FALSE;
    if (a.get_ox() == 5 && a.get_oy() == 27) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestPointLib, copy_constructor) {
    // Arrange
    Point a(-3, 72);
    Point b(a);

    // Act
    int actual_result = FALSE;
    if (a.get_ox() == b.get_ox() && a.get_oy() == b.get_oy()) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestPointLib, can_distance_to) {
    // Arrange
    Point a(1, 2);
    Point b(4, 6);

    // Act
    float actual_result = a.distance_to(b);

    // Assert
    float expected_result = 5.0;
    EXPECT_NEAR(expected_result, actual_result, EPSILON); //проверяет, что два числа с плавающей точкой приблизительно равны с учетом заданной погрешности
}