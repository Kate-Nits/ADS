// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>

#include "../lib_unsorted_table_on_list/unsorted_table_on_list.h"
#include "../lib_polynom/polynom.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

static std::string polynom_to_string(const Polynom& p) {
    std::ostringstream out;
    out << p;
    return out.str();
}

TEST(TestUnsortedTableOnList, table_is_empty_after_create) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;

    // Act & Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnList, table_is_not_empty_after_insert) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;

    // Act
    table.insert("A", Polynom("x"));

    // Assert
    EXPECT_FALSE(table.is_empty());
}

TEST(TestUnsortedTableOnList, insert_one_element_and_find_it) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;

    // Act
    table.insert("A", Polynom("2x"));
    const Polynom* result = table.found("A");

    // Assert
    ASSERT_NE(nullptr, result);
    EXPECT_EQ("2x", polynom_to_string(*result));
}

TEST(TestUnsortedTableOnList, find_non_existing_key_returns_nullptr) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    table.insert("A", Polynom("x"));

    // Act
    const Polynom* result = table.found("X");

    // Assert
    EXPECT_EQ(nullptr, result);
}

TEST(TestUnsortedTableOnList, insert_several_elements_and_find_all) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;

    // Act
    table.insert("A", Polynom("x"));
    table.insert("B", Polynom("y"));
    table.insert("C", Polynom("z"));

    // Assert
    ASSERT_NE(nullptr, table.found("A"));
    ASSERT_NE(nullptr, table.found("B"));
    ASSERT_NE(nullptr, table.found("C"));

    EXPECT_EQ("x", polynom_to_string(*table.found("A")));
    EXPECT_EQ("y", polynom_to_string(*table.found("B")));
    EXPECT_EQ("z", polynom_to_string(*table.found("C")));
}

TEST(TestUnsortedTableOnList, insert_duplicate_key_should_throw) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    table.insert("A", Polynom("x"));

    // Act & Assert
    EXPECT_ANY_THROW(table.insert("A", Polynom("2x")));
}

TEST(TestUnsortedTableOnList, erase_existing_single_element) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    table.insert("A", Polynom("x"));

    // Act
    table.erase("A");

    // Assert
    EXPECT_EQ(nullptr, table.found("A"));
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnList, erase_non_existing_key_should_throw) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;

    // Act & Assert
    EXPECT_ANY_THROW(table.erase("X"));
}

TEST(TestUnsortedTableOnList, erase_first_element_keeps_other_elements) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    table.insert("A", Polynom("x"));
    table.insert("B", Polynom("2x"));
    table.insert("C", Polynom("3x"));

    // Act
    table.erase("A");

    // Assert
    EXPECT_EQ(nullptr, table.found("A"));
    ASSERT_NE(table.found("B"), nullptr);
    ASSERT_NE(table.found("C"), nullptr);

    EXPECT_EQ("2x", polynom_to_string(*table.found("B")));
    EXPECT_EQ("3x", polynom_to_string(*table.found("C")));
}

TEST(TestUnsortedTableOnList, erase_middle_element_keeps_other_elements) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    table.insert("A", Polynom("x"));
    table.insert("B", Polynom("2x"));
    table.insert("C", Polynom("3x"));

    // Act
    table.erase("B");

    // Assert
    ASSERT_NE(nullptr, table.found("A"));
    ASSERT_EQ(nullptr, table.found("B"));
    ASSERT_NE(nullptr, table.found("C"));

    EXPECT_EQ("x", polynom_to_string(*table.found("A")));
    EXPECT_EQ("3x", polynom_to_string(*table.found("C")));
}

TEST(TestUnsortedTableOnList, erase_last_element_keeps_other_elements) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    table.insert("A", Polynom("x"));
    table.insert("B", Polynom("2x"));
    table.insert("C", Polynom("3x"));

    // Act
    table.erase("C");

    // Assert
    ASSERT_NE(nullptr, table.found("A"));
    ASSERT_NE(nullptr, table.found("B"));
    ASSERT_EQ(nullptr, table.found("C"));

    EXPECT_EQ("x", polynom_to_string(*table.found("A")));
    EXPECT_EQ("2x", polynom_to_string(*table.found("B")));
}

TEST(TestUnsortedTableOnList, can_insert_again_after_erase) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;
    table.insert("A", Polynom("x"));
    table.erase("A");

    // Act
    table.insert("A", Polynom("10x"));
    const Polynom* result = table.found("A");

    // Assert
    ASSERT_NE(nullptr, result);
    EXPECT_EQ("10x", polynom_to_string(*result));
}

TEST(TestUnsortedTableOnList, mixed_operations) {
    // Arrange
    UnsortedTableOnList<std::string, Polynom> table;

    // Act
    table.insert("A", Polynom("x"));
    table.insert("B", Polynom("2x"));
    table.insert("C", Polynom("3x"));
    table.erase("B");
    table.insert("D", Polynom("4x"));

    // Assert
    ASSERT_NE(nullptr, table.found("A"));
    ASSERT_EQ(nullptr, table.found("B"));
    ASSERT_NE(nullptr, table.found("C"));
    ASSERT_NE(nullptr, table.found("D"));

    EXPECT_EQ("x", polynom_to_string(*table.found("A")));
    EXPECT_EQ("3x", polynom_to_string(*table.found("C")));
    EXPECT_EQ("4x", polynom_to_string(*table.found("D")));
}