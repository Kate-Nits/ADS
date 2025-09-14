// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_point/point.h"

#define EPSILON 0.000001

TEST(TestEasyExampleLib, can_div) {
	// Arrange
	int x = 10;
	int y = 2;

	// Act & Assert
	ASSERT_NO_THROW(division(x, y));
}