// Copyright 2025 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_parser/parser.h"
#include "../lib_expression/expression.h"
#include "../lib_algorithms/algorithms.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestPolishRecord, build_polish_record_simple) {
    // Arrange
    List<Lexem> lexems = Parser::parse("2 + 3 * 4");
    Expression expr(lexems);

    // Act
    expr.build_polish_record();
    List<Lexem> polish = expr.get_polish_record();
    auto it = polish.begin();

    // Assert
    EXPECT_EQ("2", (*it).name);
    EXPECT_EQ(TypeLexem::Constant, (*it).type);
    ++it;
    EXPECT_EQ("3", (*it).name);
    EXPECT_EQ(TypeLexem::Constant, (*it).type);
    ++it;
    EXPECT_EQ("4", (*it).name);
    EXPECT_EQ(TypeLexem::Constant, (*it).type);
    ++it;
    EXPECT_EQ("*", (*it).name);
    EXPECT_EQ(TypeLexem::Operator, (*it).type);
    ++it;
    EXPECT_EQ("+", (*it).name);
    EXPECT_EQ(TypeLexem::Operator, (*it).type);
}
