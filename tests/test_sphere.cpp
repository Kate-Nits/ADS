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
    if (A.get_center3D() == b && A.get_radius() == 1) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestSphereLib, parameterized_constructor) {
    // Arrange
    Point3D a(5, 27, 14);
    Sphere C(a, 6);

    // Act
    int actual_result = FALSE;
    if (C.get_center3D() == a && C.get_radius() == 6) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestSphereLib, copy_constructor) {
    // Arrange
    Sphere A(Point3D(-4, 10, 54), 7);
    Sphere B(A);

    // Act
    int actual_result = FALSE;
    if (B.get_center3D() == A.get_center3D() && B.get_radius() == A.get_radius()) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}