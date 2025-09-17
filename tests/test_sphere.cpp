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
    // Act
    int actual_result = FALSE;
    if (A.get_center() == b && A.get_radius() == 1) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestSphereLib, parameterized_constructor_with_normal_radius) {
    // Arrange
    Point3D a(5, 27, 14);
    Sphere C(a, 6);

    // Act
    int actual_result = FALSE;
    if (C.get_center() == a && C.get_radius() == 6) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}
TEST(TestSphereLib, parameterized_constructor_with_radius_less_than_zero) {
    // Arrange
    Point3D a(7, 6, 14);
    // Act & Assert
    EXPECT_THROW({ Sphere C(a, -1); }, std::logic_error);
}

TEST(TestSphereLib, copy_constructor_without_throw) {
    // Arrange
    Sphere A(Point3D(-4, 10, 54), 7);
    Sphere B(A);

    // Act
    int actual_result = FALSE;
    if (B.get_center() == A.get_center() && B.get_radius() == A.get_radius()) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestSphereLib, copy_constructor_with_throw) {
    // Arrange
    Sphere* null_pointer = nullptr;
    // Act & Assert
    EXPECT_THROW({ Sphere & bad_reference = *null_pointer; Sphere a(bad_reference); }, std::logic_error);
}