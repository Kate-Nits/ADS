// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_easy_example/easy_example.h"

#define EPSILON 0.000001

//ASSERT_... - ���������� ��������� ���������� �������� �����, ���� �������� �� ������
//EXPECT_... - ���������� ���������� ����� ����� �������, �� �������� ���� ��� ����������

TEST(TestEasyExampleLib, can_div) {
  // Arrange
  int x = 10;
  int y = 2;

  // Act & Assert
  ASSERT_NO_THROW(division(x, y)); // �� ���������� ������� ����������
}

TEST(TestEasyExampleLib, can_div_correctly) {
    // Arrange
    int x = 6;
    int y = 2;

    // Act
    int actual_result = division(x, y);

    // Assert
    int expected_result = 3;
    EXPECT_EQ(expected_result, actual_result); //��������� ��� ��� ���������� �������� �����
}
/*������� ������� :
EXPECT_NE(a, b) - ���������, ��� a != b
EXPECT_LT(a, b) - ���������, ��� a < b(Less Than)
EXPECT_LE(a, b) - ���������, ��� a <= b(Less or Equal)
EXPECT_GT(a, b) - ���������, ��� a > b(Greater Than)
EXPECT_GE(a, b) - ���������, ��� a >= b(Greater or Equal)
*/

TEST(TestEasyExampleLib, can_div_correctly_with_remainder) {
    // Arrange
    int x = 5;
    int y = 4;

    // Act
    float actual_result = division(x, y);

    // Assert
    float expected_result = 1.25;
    EXPECT_NEAR(expected_result, actual_result, EPSILON); //���������, ��� ��� ����� � ��������� ������ �������������� ����� � ������ �������� �����������
}

TEST(TestEasyExampleLib, throw_when_try_div_by_zero) {
  // Arrange
  int x = 10;
  int y = 0;

  // Act & Assert
  ASSERT_ANY_THROW(division(x, y)); //���������, ��� ������������� ����� ����������
}
/*
* ������ �������� �������:
EXPECT_THROW(calc.Divide(10, 0), std::invalid_argument); //���������, ��� ���������� ���������� ����������� ����
EXPECT_TRUE(value > 0); //���������, ��� ������� �������
EXPECT_FALSE(result.empty()); //���������, ��� ������� condition �����

*/
