// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_parser/parser.h"
#include "../lib_expression/expression.h"
#include "../lib_algorithms/algorithms.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

size_t count_lexems(const List<Lexem>& lexems) {
    size_t count = 0;
    for (auto it = lexems.begin(); it != lexems.end(); ++it) {
        ++count;
    }
    return count;
}

TEST(TestParser, parse_simple_expression_without_variables) {
    // Arrange & Act
    List<Lexem> lexems = Parser::parse("2 + 3");

    // Assert
    EXPECT_EQ(3, count_lexems(lexems));
    auto it = lexems.begin();
    EXPECT_EQ(TypeLexem::Constant, (*it).type);
    EXPECT_DOUBLE_EQ(2.0, (*it).value);
    ++it;
    EXPECT_EQ(TypeLexem::Operator, (*it).type);
    EXPECT_EQ("+", (*it).name);
    ++it;
    EXPECT_EQ(TypeLexem::Constant, (*it).type);
    EXPECT_DOUBLE_EQ(3.0, (*it).value);
}

TEST(TestParser, parse_simple_expression_with_variables) {
    // Arrange & Act
    List<Lexem> lexems = Parser::parse("x + y_2 * 5");

    // Assert
    EXPECT_EQ(5, count_lexems(lexems));
    auto it = lexems.begin();
    EXPECT_EQ(TypeLexem::Variable, (*it).type);
    EXPECT_EQ("x", (*it).name);
}

TEST(TestParser, parse_simple_expression_with_functions) {
    // Arrange & Act
    List<Lexem> lexems = Parser::parse("sin(x) + cos(y)");

    // Assert
    EXPECT_EQ(9, count_lexems(lexems));
    auto it = lexems.begin();
    EXPECT_EQ(TypeLexem::Function, (*it).type);
    EXPECT_EQ("sin", (*it).name);
    EXPECT_NE(nullptr, (*it).function);
}

TEST(TestParser, parse_simple_expression_with_unary_minus) {
    // Arrange & Act
    List<Lexem> lexems = Parser::parse("-x + 5");

    // Assert
    EXPECT_EQ(4, count_lexems(lexems));
    auto it = lexems.begin();
    EXPECT_EQ(TypeLexem::UnOperator, (*it).type);
    EXPECT_EQ("-", (*it).name);
}

TEST(TestParser, parse_simple_expression_with_abs) {
    // Arrange & Act
    List<Lexem> lexems = Parser::parse("|x - 5|");

    // Assert
    EXPECT_EQ(6, count_lexems(lexems));
    auto it = lexems.begin();
    EXPECT_EQ(TypeLexem::Function, (*it).type);
    EXPECT_EQ("abs", (*it).name);
}

TEST(TestParser, parse_invalid_expression_not_close_bracket) {
    // Arrange & Act & Assert
    EXPECT_ANY_THROW(Parser::parse("x + (y * 3"));
}

TEST(TestParser, parse_invalid_expression_not_open_bracket) {
    // Arrange & Act & Assert
    EXPECT_ANY_THROW(Parser::parse("x + y * 3)"));
}

TEST(TestParser, parse_invalid_expression_number_before_function) {
    // Arrange & Act & Assert
    EXPECT_ANY_THROW(Parser::parse("2sin(x)"));
}

TEST(TestParser, parse_invalid_variable_name) {
    // Arrange & Act & Assert
    EXPECT_ANY_THROW(Parser::parse("2var + 3"));
}