// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_monom/monom.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestMonomLib, default_constructor) {
	// Arrange & Act
	Monom m;

	// Assert
	EXPECT_NEAR(0, m.coef(), EPSILON);
	EXPECT_EQ(0, m.px());
	EXPECT_EQ(0, m.py());
	EXPECT_EQ(0, m.pz());
}

TEST(TestMonomLib, ini_constructor) {
	// Arrange & Act
	Monom m(5.5, 2, 1, 3);

	// Assert
	EXPECT_NEAR(5.5, m.coef(), EPSILON);
	EXPECT_EQ(2, m.px());
	EXPECT_EQ(1, m.py());
	EXPECT_EQ(3, m.pz());
}

TEST(TestMonomLib, copy_constructor) {
	// Arrange
	Monom m1(4, 2, 3, 1);

	// Act
	Monom m2(m1);

	// Assert
	EXPECT_NEAR(m1.coef(), m2.coef(), EPSILON);
	EXPECT_EQ(m1.px(), m2.px());
	EXPECT_EQ(m1.py(), m2.py());
	EXPECT_EQ(m1.pz(), m2.pz());
}

TEST(TestMonomLib, operator_assign) {
	// Arrange
	Monom m1(7, 1, 2, 3);
	Monom m2;

	// Act
	m2 = m1;

	// Assert
	EXPECT_NEAR(7.0, m2.coef(), EPSILON);
	EXPECT_EQ(1, m2.px());
	EXPECT_EQ(2, m2.py());
	EXPECT_EQ(3, m2.pz());
}

TEST(TestMonomLib, operator_equal) {
	// Arrange
	Monom a(2, 2, 1, 0);
	Monom b(5, 2, 1, 0);

	// Act & Assert
	EXPECT_TRUE(a == b);
}

TEST(TestMonomLib, operator_not_equal) {
	// Arrange
	Monom a(2, 2, 1, 0);
	Monom b(5, 3, 1, 0);

	// Act & Assert
	EXPECT_TRUE(a != b);
}

TEST(TestMonomLib, operator_plus_without_throw) {
	// Arrange
	Monom a(3, 2, 0, 0);
	Monom b(4, 2, 0, 0);

	// Act
	Monom c = a + b;

	// Assert
	EXPECT_NEAR(7.0, c.coef(), EPSILON);
	EXPECT_EQ(2, c.px());
}

TEST(TestMonomLib, operator_plus_with_throw) {
	// Arrange
	Monom a(3, 3, 0, 0);
	Monom b(4, 2, 0, 0);

	// Act & Assert
	EXPECT_ANY_THROW(a + b);
}

TEST(TestMonomLib, operator_minus_without_throw) {
	// Arrange
	Monom a(9, 2, 1, 0);
	Monom b(4, 2, 1, 0);

	// Act
	Monom c = a - b;

	// Assert
	EXPECT_NEAR(5.0, c.coef(), EPSILON);
	EXPECT_EQ(2, c.px());
	EXPECT_EQ(1, c.py());
	EXPECT_EQ(0, c.pz());
}

TEST(TestMonomLib, operator_minus_with_throw) {
	// Arrange
	Monom a(3, 2, 1, 0);
	Monom b(4, 2, 0, 0);

	// Act & Assert
	EXPECT_ANY_THROW(a - b);
}

TEST(TestMonomLib, operator_multiply) {
	// Arrange
	Monom a(2, 1, 1, 0);
	Monom b(3, 2, 0, 1);

	// Act
	Monom c = a * b;

	// Assert
	EXPECT_NEAR(6.0, c.coef(), EPSILON);
	EXPECT_EQ(3, c.px());
	EXPECT_EQ(1, c.py());
	EXPECT_EQ(1, c.pz());
}

TEST(TestMonomLib, multiply_constant) {
	// Arrange
	Monom m(3, 1, 0, 0);

	// Act
	Monom r = m * 5;

	// Assert
	EXPECT_NEAR(15.0, r.coef(), EPSILON);
}

TEST(TestMonomLib, operator_div_without_throw) {
	// Arrange
	Monom a(8, 3, 2, 1);
	Monom b(2, 1, 1, 1);

	// Act
	Monom c = a / b;

	// Assert
	EXPECT_NEAR(4.0, c.coef(), EPSILON);
	EXPECT_EQ(2, c.px());
	EXPECT_EQ(1, c.py());
	EXPECT_EQ(0, c.pz());
}

TEST(TestMonomLib, operator_div_with_throw) {
	// Arrange
	Monom a(8, 3, 2, 1);
	Monom b(0, 1, 1, 1);

	// Act & Assert
	EXPECT_ANY_THROW(a / b);
}

TEST(TestMonomLib, divide_constant_without_throw) {
	// Arrange
	Monom m(10, 2, 0, 0);

	// Act
	Monom r = m / 5;

	// Assert
	EXPECT_NEAR(2.0, r.coef(), EPSILON);
}

TEST(TestMonomLib, divide_constant_with_throw) {
	// Arrange
	Monom m(10, 2, 0, 0);

	// Act & Assert
	EXPECT_ANY_THROW(m / 0.0);
}

TEST(TestMonomLib, unary_minus) {
	// Arrange
	Monom m(3, 2, 5, 0);

	// Act
	Monom r = -m;

	// Assert
	EXPECT_NEAR(-3.0, r.coef(), EPSILON);
	EXPECT_EQ(2, r.px());
	EXPECT_EQ(5, r.py());
	EXPECT_EQ(0, r.pz());
}

TEST(TestMonomLib, operator_plus_assign_without_throw) {
	// Arrange
	Monom a(2, 1, 3, 0);
	Monom b(3, 1, 3, 0);

	// Act
	a += b;

	// Assert
	EXPECT_NEAR(5.0, a.coef(), EPSILON);
	EXPECT_EQ(1, a.px());
	EXPECT_EQ(3, a.py());
	EXPECT_EQ(0, a.pz());
}

TEST(TestMonomLib, operator_plus_assign_with_throw) {
	// Arrange
	Monom a(2, 1, 3, 0);
	Monom b(3, 0, 3, 0);

	// Act & Assert
	EXPECT_ANY_THROW(a += b);
}

TEST(TestMonomLib, operator_minus_assign_without_throw) {
	// Arrange
	Monom a(9, 2, 1, 0);
	Monom b(4, 2, 1, 0);

	// Act
	a -= b;

	// Assert
	EXPECT_NEAR(5.0, a.coef(), EPSILON);
	EXPECT_EQ(2, a.px());
	EXPECT_EQ(1, a.py());
	EXPECT_EQ(0, a.pz());
}

TEST(TestMonomLib, operator_minus_assign_with_throw) {
	// Arrange
	Monom a(3, 2, 1, 0);
	Monom b(4, 2, 0, 0);

	// Act & Assert
	EXPECT_ANY_THROW(a -= b);
}

TEST(TestMonomLib, operator_multiply_assign) {
	// Arrange
	Monom a(2, 1, 0, 0);
	Monom b(3, 2, 0, 0);

	// Act
	a *= b;

	// Assert
	EXPECT_NEAR(6.0, a.coef(), EPSILON);
	EXPECT_EQ(3, a.px());
	EXPECT_EQ(0, a.py());
	EXPECT_EQ(0, a.pz());
}

TEST(TestMonomLib, operator_div_assign_without_throw) {
	// Arrange
	Monom a(8, 3, 2, 1);
	Monom b(2, 1, 1, 1);

	// Act
	a /= b;

	// Assert
	EXPECT_NEAR(4.0, a.coef(), EPSILON);
	EXPECT_EQ(2, a.px());
	EXPECT_EQ(1, a.py());
	EXPECT_EQ(0, a.pz());
}

TEST(TestMonomLib, operator_div_assign_with_throw) {
	// Arrange
	Monom a(8, 3, 2, 1);
	Monom b(0, 1, 1, 1);

	// Act & Assert
	EXPECT_ANY_THROW(a /= b);
}

TEST(TestMonomLib, calculate_value) {
	// Arrange
	Monom m(2, 2, 1, 0);

	// Act
	double value = m.calculate(3, 2, 0);

	// Assert
	EXPECT_NEAR(36, value, EPSILON);
}