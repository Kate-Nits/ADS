// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_point3d/point3d.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestPoint3dLib, default_constructor) {
    // Arrange (Настройка)
    Point3D a;

    // Assert & Act
    EXPECT_EQ(0, a.get_ox()); //проверяет что два переданные значения равны
    EXPECT_EQ(0, a.get_oy());
    EXPECT_EQ(0, a.get_oz());
}

TEST(TestPoint3dLib, parameterized_constructor) {
    // Arrange
    Point3D a(5, 27, -45);

    // Assert & Act
    EXPECT_EQ(5, a.get_ox()); //проверяет что два переданные значения равны
    EXPECT_EQ(27, a.get_oy());
    EXPECT_EQ(-45, a.get_oz());
}

TEST(TestPoint3dLib, copy_constructor_without_throw) {
    // Arrange
    Point3D a(-3, 72, 15);

    // Act
    Point3D b(a);

    // Assert
    EXPECT_EQ(-3, b.get_ox()); //проверяет что два переданные значения равны
    EXPECT_EQ(72, b.get_oy());
    EXPECT_EQ(15, b.get_oz());
}

TEST(TestPoint3dLib, copy_constructor_with_throw) {
    // Arrange
    Point3D* null_pointer = nullptr;

    // Act & Assert
    ASSERT_ANY_THROW(Point3D a(*null_pointer));
}

TEST(TestPoint3dLib, can_compare_with_operator_two_equal_object) {
    // Arrange
    Point3D a(1, 2, 3);
    Point3D b(1, 2, 3);

    // Act & Assert
    EXPECT_TRUE(a == b);
}

TEST(TestPoint3dLib, can_compare_with_operator_two_not_equal_object) {
    // Arrange
    Point3D a(1, 2, 7);
    Point3D b(4, 2, 7);

    // Act & Assert
    EXPECT_FALSE(a == b);
}

TEST(TestPoint3dLib, can_distance_to) {
    // Arrange
    Point3D a(0, -3, 3);
    Point3D b(3, 1, 3);

    // Act & Assert
    EXPECT_NEAR(5.0, a.distance_to(b), EPSILON); //проверяет, что два числа с плавающей точкой приблизительно равны с учетом заданной погрешности
}