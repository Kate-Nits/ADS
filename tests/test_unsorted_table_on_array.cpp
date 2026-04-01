// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>

#include "../lib_unsorted_table_on_array/unsorted_table_on_array.h"
#include "../lib_polynom/polynom.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0


TEST(TestUnsortedTableOnArray, table_is_empty_after_creat) {
    // Arrange
    UnsortedTableOnArray<std::string, Polynom> table;

    // Act
    bool result = table.is_empty();

    // Assert
    EXPECT_TRUE(result);
}

TEST(TestUnsortedTableOnArray, table_not_empty_after_insert) {
    // Arrange
    UnsortedTableOnArray<std::string, Polynom> table;
    Polynom p("x");

    // Act
    table.insert("A", p);

    // Assert
    EXPECT_FALSE(table.is_empty());
}

TEST(TestUnsortedTableOnArray, insert_one_element_and_find) {
    // Arrange
    UnsortedTableOnArray<std::string, Polynom> table;
    Polynom p("2x");

    // Act
    table.insert("A", p);
    const Polynom* result = table.found("A");

    // Assert
    EXPECT_NE(result, nullptr);
    std::ostringstream oss;
    oss << *result;
    EXPECT_EQ("2x", oss.str());
}

TEST(TestUnsortedTableOnArray, find_non_existing_key_returns_nullptr) {
    // Arrange
    UnsortedTableOnArray<std::string, Polynom> table;

    // Act
    const Polynom* result = table.found("X");

    // Assert
    EXPECT_EQ(nullptr, result);
}

TEST(TestUnsortedTableOnArray, insert_some_elements) {
    // Arrange
    UnsortedTableOnArray<std::string, Polynom> table;

    // Act
    table.insert("A", Polynom("x"));
    table.insert("B", Polynom("y"));
    table.insert("C", Polynom("z"));

    const Polynom* a = table.found("A");
    const Polynom* b = table.found("B");
    const Polynom* c = table.found("C");

    // Assert
    EXPECT_NE(a, nullptr);
    EXPECT_NE(b, nullptr);
    EXPECT_NE(c, nullptr);
}

TEST(TestUnsortedTableOnArray, insert_duplicate_key_should_throw) {

    // Arrange
    UnsortedTableOnArray<std::string, Polynom> table;
    Polynom p("x");

    table.insert("A", p);

    // Act & Assert
    EXPECT_ANY_THROW(table.insert("A", p));
}

TEST(TestUnsortedTableOnArray, erase_element) {
    // Arrange
    UnsortedTableOnArray<std::string, Polynom> table;
    Polynom p("x");
    table.insert("A", p);

    // Act
    table.erase("A");
    const Polynom* result = table.found("A");

    // Assert
    EXPECT_EQ(nullptr, result);
}

TEST(TestUnsortedTableOnArray, erase_should_throw) {
    // Arrange
    UnsortedTableOnArray<std::string, Polynom> table;

    // Act & Assert
    EXPECT_ANY_THROW(table.erase("X"));
}

TEST(TestUnsortedTableOnArray, table_empty_after_removing_last_element) {
    // Arrange
    UnsortedTableOnArray<std::string, Polynom> table;

    table.insert("A", Polynom("x"));

    // Act
    table.erase("A");

    // Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnArray, find_after_some_inserts) {
    // Arrange
    UnsortedTableOnArray<std::string, Polynom> table;
    table.insert("P1", Polynom("x"));
    table.insert("P2", Polynom("2x"));
    table.insert("P3", Polynom("3x"));

    // Act
    const Polynom* result = table.found("P2");

    // Assert
    EXPECT_NE(nullptr, result);
}

TEST(TestUnsortedTableOnArray, mixed_operations) {
    // Arrange
    UnsortedTableOnArray<std::string, Polynom> table;

    // Act
    table.insert("A", Polynom("x"));
    table.insert("B", Polynom("2x"));
    table.insert("C", Polynom("3x"));

    table.erase("B");

    const Polynom* a = table.found("A");
    const Polynom* b = table.found("B");
    const Polynom* c = table.found("C");

    // Assert
    EXPECT_NE(a, nullptr);
    EXPECT_EQ(b, nullptr);
    EXPECT_NE(c, nullptr);
}