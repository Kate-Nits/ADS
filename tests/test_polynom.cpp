// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_polynom/polynom.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestPolynomLib, default_constructor) {
    // Arrange & Act
    Polynom p;

    // Assert
    EXPECT_TRUE(p.is_zero());
}

TEST(TestPolynomLib, string_constructor_simple) {
    // Arrange & Act
    Polynom p("3x^2y^3z");

    // Assert
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ("3x^2y^3z", oss.str());
}

TEST(TestPolynomLib, string_constructor_with_spaces) {
    // Arrange & Act
    Polynom p(" 5x^2 + 3y - 7 ");

    // Assert
    std::ostringstream oss;
    oss << p;
    std::string result = oss.str();
    EXPECT_TRUE(result == "5x^2 + 3y - 7"); //EXPECT_TRUE(result == "5x^2 + 3y - 7" || result == "3y + 5x^2 - 7");
}

TEST(TestPolynomLib, string_constructor_constant) {
    // Arrange & Act
    Polynom p("42");

    // Assert
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ("42", oss.str());
}

TEST(TestPolynomLib, string_constructor_negative_coef) {
    // Arrange & Act
    Polynom p("-5x^2 + 3y");

    // Assert
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ("-5x^2 + 3y", oss.str());
}

TEST(TestPolynomLib, string_constructor_hard) {
    // Arrange & Act
    Polynom p("x^2yz^3 + 0.4xyz - 8y^2z + 1.3yz^4 - 2.4");

    // Assert
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ("x^2yz^3 + 0.4xyz - 8y^2z + 1.3yz^4 - 2.4", oss.str());
}

TEST(TestPolynomLib, copy_constructor) {
    // Arrange
    Polynom p1("3x^2 + 2y - 5");

    // Act
    Polynom p2(p1);

    // Assert
    std::ostringstream oss1, oss2;
    oss1 << p1;
    oss2 << p2;
    EXPECT_EQ(oss1.str(), oss2.str());
}

TEST(TestPolynomLib, operator_assign) {
    // Arrange
    Polynom p1("4x^3 - 2y^2 + 7");
    Polynom p2;

    // Act
    p2 = p1;

    // Assert
    std::ostringstream oss1, oss2;
    oss1 << p1;
    oss2 << p2;
    EXPECT_EQ(oss1.str(), oss2.str());
}

TEST(TestPolynomLib, operator_plus_with_similar_monoms) {
    // Arrange
    Polynom p1("3x^2y");
    Polynom p2("5x^2y");

    // Act
    Polynom result = p1 + p2;

    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ("8x^2y", oss.str());
}

TEST(TestPolynomLib, operator_plus_with_different_monoms) {
    // Arrange
    Polynom p1("3x^2y");
    Polynom p2("4xy^2");

    // Act
    Polynom result = p1 + p2;

    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_TRUE(oss.str() == "3x^2y + 4xy^2" || oss.str() == "4xy^2 + 3x^2y");
}

TEST(TestPolynomLib, operator_plus_with_abs_monoms) {
    // Arrange
    Polynom p1("5x^2y");
    Polynom p2("-5x^2y");

    // Act
    Polynom result = p1 + p2;

    // Assert
    EXPECT_TRUE(result.is_zero());
}

TEST(TestPolynomLib, operator_minus_with_similar_monoms) {
    // Arrange
    Polynom p1("7x^2y");
    Polynom p2("3x^2y");

    // Act
    Polynom result = p1 - p2;

    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ("4x^2y", oss.str());
}

TEST(TestPolynomLib, operator_minus_with_negative) {
    // Arrange
    Polynom p1("5x^2");
    Polynom p2("8x^2");

    // Act
    Polynom result = p1 - p2;

    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ("-3x^2", oss.str());
}

TEST(TestPolynomLib, operator_multiply_with_monom_and_monom) {
    // Arrange
    Polynom p1("2x^2y");
    Polynom p2("3xz^2");

    // Act
    Polynom result = p1 * p2;

    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ("6x^3yz^2", oss.str());
}

TEST(TestPolynomLib, operator_multiply_with_polynom_and_polynom) {
    // Arrange
    Polynom p1("x + y");
    Polynom p2("x - y");

    // Act
    Polynom result = p1 * p2;

    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ("x^2 - y^2", oss.str());
}

TEST(TestPolynomLib, operator_multiply_hard) {
    // Arrange
    Polynom p1("2x + 3y");
    Polynom p2("4x - 5y");

    // Act
    Polynom result = p1 * p2;

    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ("8x^2 + 2xy - 15y^2", oss.str());
}

TEST(TestPolynomLib, operator_divide_simple_with_monom) {
    // Arrange
    Polynom p1("6x^2y");
    Polynom p2("2x");

    // Act
    Polynom result = p1 / p2;

    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ("3xy", oss.str());
}

TEST(TestPolynomLib, operator_divide_with_polynom) {
    // Arrange
    Polynom p1("x^2 + 2x + 1");
    Polynom p2("x + 1");

    // Act
    Polynom result = p1 / p2;

    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ("x + 1", oss.str());
}

TEST(TestPolynomLib, operator_divide_with_remainder) {
    // Arrange
    Polynom p1("x^2 + 2x + 2");
    Polynom p2("x + 1");

    // Act
    Polynom result = p1 / p2;

    // Assert
    std::ostringstream oss;
    oss << result;
    EXPECT_EQ("x + 1", oss.str());
}

TEST(TestPolynomLib, operator_divide_by_zero) {
    // Arrange
    Polynom p1("x^2 + 2x + 1");
    Polynom p2("0");

    // Act & Assert
    EXPECT_ANY_THROW(p1 / p2);
}

TEST(TestPolynomLib, operator_plus_assign) {
    // Arrange
    Polynom p1("3x^2");
    Polynom p2("4x^2");

    // Act
    p1 += p2;

    // Assert
    std::ostringstream oss;
    oss << p1;
    EXPECT_EQ("7x^2", oss.str());
}

TEST(TestPolynomLib, operator_minus_assign) {
    // Arrange
    Polynom p1("9y^3");
    Polynom p2("4y^3");

    // Act
    p1 -= p2;

    // Assert
    std::ostringstream oss;
    oss << p1;
    EXPECT_EQ("5y^3", oss.str());
}

TEST(TestPolynomLib, operator_multiply_assign) {
    // Arrange
    Polynom p1("2x");
    Polynom p2("3x");

    // Act
    p1 *= p2;

    // Assert
    std::ostringstream oss;
    oss << p1;
    EXPECT_EQ("6x^2", oss.str());
}

TEST(TestPolynomLib, operator_divide_assign) {
    // Arrange
    Polynom p1("8x^3");
    Polynom p2("2x");

    // Act
    p1 /= p2;

    // Assert
    std::ostringstream oss;
    oss << p1;
    EXPECT_EQ("4x^2", oss.str());
}

TEST(TestPolynomLib, calculate_value_simple) {
    // Arrange
    Polynom p("3x^2y");

    // Act
    double value = p.calculate(2, 3, 1);

    // Assert
    EXPECT_NEAR(3 * 4 * 3, value, EPSILON);
}

TEST(TestPolynomLib, calculate_value_hard) {
    // Arrange
    Polynom p("x^2 + 2x + 1");

    // Act
    double value = p.calculate(3, 0, 0);

    // Assert
    EXPECT_NEAR(9 + 6 + 1, value, EPSILON);
}

TEST(TestPolynomLib, calculate_value_zero) {
    // Arrange
    Polynom p("0");

    // Act
    double value = p.calculate(10, 10, 10);

    // Assert
    EXPECT_NEAR(0, value, EPSILON);
}

TEST(TestPolynomLib, is_zero_true) {
    // Arrange
    Polynom p;

    // Act & Assert
    EXPECT_TRUE(p.is_zero());
}

TEST(TestPolynomLib, is_zero_false) {
    // Arrange
    Polynom p("5x");

    // Act & Assert
    EXPECT_FALSE(p.is_zero());
}

TEST(TestPolynomLib, ordering_of_monoms) {
    // Arrange
    Polynom p("y^2z^3 + 2y^2 + xy + 6");

    // Act
    std::ostringstream oss;
    oss << p;
    std::string result = oss.str();

    // Assert
    size_t pos_xy = result.find("xy");
    size_t pos_y2z3 = result.find("y^2z^3");
    size_t pos_2y2 = result.find("2y^2");
    size_t pos_6 = result.find("6");

    EXPECT_LT(pos_xy, pos_y2z3);
    EXPECT_LT(pos_y2z3, pos_2y2);
    EXPECT_LT(pos_2y2, pos_6);
}

TEST(TestPolynomLib, output_zero_polynom) {
    // Arrange
    Polynom p;

    // Act
    std::ostringstream oss;
    oss << p;

    // Assert
    EXPECT_EQ("0", oss.str());
}

TEST(TestPolynomLib, output_single_monom) {
    // Arrange
    Polynom p("-7.5x^3y^2z");

    // Act
    std::ostringstream oss;
    oss << p;

    // Assert
    EXPECT_EQ("-7.5x^3y^2z", oss.str());
}

TEST(TestPolynomLib, output_coeff_equal_one) {
    // Arrange
    Polynom p("x^2y");

    // Act
    std::ostringstream oss;
    oss << p;

    // Assert
    EXPECT_EQ("x^2y", oss.str());
}

TEST(TestPolynomLib, output_coeff_equal_minus_one) {
    // Arrange
    Polynom p("-x^2y");

    // Act
    std::ostringstream oss;
    oss << p;

    // Assert
    EXPECT_EQ("-x^2y", oss.str());
}

TEST(TestPolynomLib, test_add) {
    // Arrange
    Polynom a("x");
    Polynom b("y");
    Polynom c("z");

    // Act
    Polynom left = (a + b) + c;
    Polynom right = a + (b + c);

    // Assert
    std::ostringstream oss_left, oss_right;
    oss_left << left;
    oss_right << right;
    EXPECT_EQ(oss_left.str(), oss_right.str());
}

TEST(TestPolynomLib, commutativity_of_addition) {
    // Arrange
    Polynom a("2x");
    Polynom b("3y");

    // Act
    Polynom sum1 = a + b;
    Polynom sum2 = b + a;

    // Assert
    std::ostringstream oss1, oss2;
    oss1 << sum1;
    oss2 << sum2;
    EXPECT_EQ(oss1.str(), oss2.str());
}

TEST(TestPolynomLib, commutativity_of_multiplication) {
    // Arrange
    Polynom a("2x");
    Polynom b("3y");

    // Act
    Polynom prod1 = a * b;
    Polynom prod2 = b * a;

    // Assert
    std::ostringstream oss1, oss2;
    oss1 << prod1;
    oss2 << prod2;
    EXPECT_EQ(oss1.str(), oss2.str());
}

TEST(TestPolynomLib, test_distributive) {
    // Arrange
    Polynom a("x");
    Polynom b("y");
    Polynom c("z");

    // Act
    Polynom left = a * (b + c);
    Polynom right = a * b + a * c;

    // Assert
    std::ostringstream oss_left, oss_right;
    oss_left << left;
    oss_right << right;
    EXPECT_EQ(oss_left.str(), oss_right.str());
}