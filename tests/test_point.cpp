// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_point/point.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestPointLib, default_constructor) {
    // Arrange
    Point a;

    EXPECT_EQ(0, a.get_oy());
    EXPECT_EQ(0, a.get_ox()); //проверяет что два переданные значения равны
}

TEST(TestPointLib, parameterized_constructor) {
    // Arrange & act
    Point a(5, 27);

    EXPECT_EQ(5, a.get_ox());
    EXPECT_EQ(27, a.get_oy());
}

TEST(TestPointLib, copy_constructor_without_throw) {
    // Arrange
    Point a(-3, 72);
   

    // Act
 Point b(a);

    EXPECT_EQ(-3, b.get_ox());
    EXPECT_EQ(72, b.get_oy()); //проверяет что два переданные значения равны
}

TEST(TestPointLib, copy_constructor_with_throw) {
    // Arrange
    Point* null_pointer = nullptr;
    // Act & Assert
    ASSERT_ANY_THROW(Point a(*null_pointer));
}

TEST(TestPointLib, can_distance_to) {
    // Arrange
    Point a(1, 2);
    Point b(4, 6);

    // Act
    // Assert
    EXPECT_NEAR(5.0, a.distance_to(b), EPSILON); //проверяет, что два числа с плавающей точкой приблизительно равны с учетом заданной погрешности
}

TEST(TestPointLib, can_compare_with_operator_two_equal_object) {
    // Arrage
    Point a(1, 2);
    Point b(1, 2);

    EXPECT_TRUE(a == b);
}

TEST(TestPointLib, can_compare_with_operator_two_not_equal_object) {
    // Arrage
    Point a(1, 2);
    Point b(4, 2);

    EXPECT_FALSE(a == b);
}