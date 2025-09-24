// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_sphere/sphere.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestSphereLib, default_constructor) {
    // Arrange
    Sphere A;
    Point3D b;

    // Act & Assert
    EXPECT_EQ(b, A.get_center()); //проверяет что два переданные значения равны
    EXPECT_EQ(1, A.get_radius());
}

TEST(TestSphereLib, parameterized_constructor_with_normal_radius) {
    // Arrange
    Point3D A(5, 27, 14);
    Sphere C(A, 6);

    // Act & Assert
    EXPECT_EQ(A, C.get_center()); //проверяет что два переданные значения равны
    EXPECT_EQ(6, C.get_radius());
}
TEST(TestSphereLib, parameterized_constructor_with_radius_less_than_zero) {
    // Arrange
    Point3D a(7, 6, 14);

    // Act & Assert
    ASSERT_ANY_THROW( Sphere C(a, -1));
}

TEST(TestSphereLib, copy_constructor_without_throw) {
    // Arrange
    Point3D C(-4, 10, 54);
    Sphere A(C, 7);

    // Act
    Sphere B(A);

    // Assert
    EXPECT_EQ(C, B.get_center()); //проверяет что два переданные значения равны
    EXPECT_EQ(7, B.get_radius());
}

TEST(TestSphereLib, copy_constructor_with_throw) {
    // Arrange
    Sphere* null_pointer = nullptr;
    // Act & Assert
    ASSERT_ANY_THROW( Sphere C(*null_pointer));
}