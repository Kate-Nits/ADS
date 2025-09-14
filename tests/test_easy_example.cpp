// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_easy_example/easy_example.h"

#define EPSILON 0.000001

//ASSERT_... - немедленно прерывают выполнение текущего теста, если проверка не прошла
//EXPECT_... - продолжают выполнение теста после неудачи, но отмечают тест как проваленый

TEST(TestEasyExampleLib, can_div) {
  // Arrange
  int x = 10;
  int y = 2;

  // Act & Assert
  ASSERT_NO_THROW(division(x, y)); // не генерирует никаких исключений
}

TEST(TestEasyExampleLib, can_div_correctly) {
    // Arrange
    int x = 6;
    int y = 2;

    // Act
    int actual_result = division(x, y);

    // Assert
    int expected_result = 3;
    EXPECT_EQ(expected_result, actual_result); //провер€ет что два переданные значени€ равны
}
/*ѕохожие функции :
EXPECT_NE(a, b) - ѕровер€ет, что a != b
EXPECT_LT(a, b) - ѕровер€ет, что a < b(Less Than)
EXPECT_LE(a, b) - ѕровер€ет, что a <= b(Less or Equal)
EXPECT_GT(a, b) - ѕровер€ет, что a > b(Greater Than)
EXPECT_GE(a, b) - ѕровер€ет, что a >= b(Greater or Equal)
*/

TEST(TestEasyExampleLib, can_div_correctly_with_remainder) {
    // Arrange
    int x = 5;
    int y = 4;

    // Act
    float actual_result = division(x, y);

    // Assert
    float expected_result = 1.25;
    EXPECT_NEAR(expected_result, actual_result, EPSILON); //провер€ет, что два числа с плавающей точкой приблизительно равны с учетом заданной погрешности
}

TEST(TestEasyExampleLib, throw_when_try_div_by_zero) {
  // Arrange
  int x = 10;
  int y = 0;

  // Act & Assert
  ASSERT_ANY_THROW(division(x, y)); //провер€ет, что выбрасываетс€ любое исключение
}
/*
* другие полезные функции:
EXPECT_THROW(calc.Divide(10, 0), std::invalid_argument); //провер€ет, что генерирует исключение конкретного типа
EXPECT_TRUE(value > 0); //провер€ет, что условие истинно
EXPECT_FALSE(result.empty()); //провер€ет, что условие condition ложно

*/
