// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_point3d/point3d.h"

//#define EXAMPLE

#define EPSILON 0.000001

#ifdef EXAMPLE
TEST(TestEasyExampleLib, can_div) {
	// Arrange
	int x = 10;
	int y = 2;

	// Act & Assert
	ASSERT_NO_THROW(division(x, y));
}
#endif // EXAMPLE