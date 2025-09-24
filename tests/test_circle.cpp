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

    // Act & Assert
    EXPECT_EQ(1, A.get_radius()); //проверяет что два переданные значения равны
    EXPECT_EQ(b, A.get_center());
}

TEST(TestCircleLib, parameterized_constructor_with_normal_radius) {
    // Arrange
    Point a(5, 27);
    Circle C(a, 6);

    // Act & Assert
    EXPECT_EQ(6, C.get_radius()); //проверяет что два переданные значения равны
    EXPECT_EQ(a, C.get_center());
}
TEST(TestCircleLib, parameterized_constructor_with_radius_less_than_zero) {
    // Arrange
    Point a(-3, 15);

    // Act & Assert
    ASSERT_ANY_THROW(Circle C(a, -8));
}

TEST(TestCircleLib, copy_constructor_without_throw) {
    // Arrange
    Point M(-4, 10);
    Circle A(M, 7);
    

    // Act
    Circle B(A);

    // Assert
    EXPECT_EQ(M, B.get_center()); //проверяет что два переданные значения равны
    EXPECT_EQ(7, B.get_radius());
}

TEST(TestCircleLib, copy_constructor_with_throw) {
    // Arrange
    Circle* null_pointer = nullptr;
    // Act & Assert
    ASSERT_ANY_THROW(Circle C(*null_pointer));
}


