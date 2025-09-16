// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_point3d/point3d.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestPoint3dLib, default_constructor) {
    // Arrange
    Point3D a;

    // Act
    int actual_result = FALSE;
    if (a.get_ox() == 0 && a.get_oy() == 0 && a.get_oz() == 0) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestPoint3dLib, parameterized_constructor) {
    // Arrange
    Point3D a(5, 27, -45);

    // Act
    int actual_result = FALSE;
    if (a.get_ox() == 5 && a.get_oy() == 27 && a.get_oz() == -45) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestPoint3dLib, copy_constructor_without_throw) {
    // Arrange
    Point3D a(-3, 72, 15);
    Point3D b(a);

    // Act
    int actual_result = FALSE;
    if (a.get_ox() == b.get_ox() && a.get_oy() == b.get_oy() && a.get_oz() == b.get_oz()) {
        actual_result = TRUE;
    }

    // Assert
    int expected_result = TRUE;
    EXPECT_EQ(expected_result, actual_result); //проверяет что два переданные значения равны
}

TEST(TestPoint3dLib, copy_constructor_with_throw) {
    // Arrange
    Point3D* null_pointer = nullptr;
    // Act & Assert
    EXPECT_THROW({ Point3D & bad_reference = *null_pointer; Point3D a(bad_reference); }, std::logic_error);
}

TEST(TestPoint3dLib, can_distance_to) {
    // Arrange
    Point3D a(0, -3, 3);
    Point3D b(3, 1, 3);

    // Act
    float actual_result = a.distance_to(b);

    // Assert
    float expected_result = 5.0;
    EXPECT_NEAR(expected_result, actual_result, EPSILON); //проверяет, что два числа с плавающей точкой приблизительно равны с учетом заданной погрешности
}