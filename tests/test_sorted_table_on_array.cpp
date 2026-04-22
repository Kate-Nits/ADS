// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>

#include "../lib_sorted_table_on_array/sorted_table_on_array.h"
#include "../lib_polynom/polynom.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

static std::string polynom_to_string(const Polynom& p) {
    std::ostringstream out;
    out << p;
    return out.str();
}

TEST(TestSortedTableOnArray, table_is_empty_after_create) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;

    // Act + Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnArray, table_is_not_empty_after_insert) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;

    // Act
    table.insert("B", Polynom("x"));

    // Assert
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnArray, insert_one_element_and_find_it) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;

    // Act
    table.insert("A", Polynom("2x"));
    const Polynom* result = table.found("A");

    // Assert
    ASSERT_NE(nullptr, result);
    EXPECT_EQ("2x", polynom_to_string(*result));
}

TEST(TestSortedTableOnArray, find_non_existing_key_returns_nullptr) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;
    table.insert("A", Polynom("x"));

    // Act
    const Polynom* result = table.found("X");

    // Assert
    EXPECT_EQ(nullptr, result);
}

TEST(TestSortedTableOnArray, insert_several_elements_and_find_all) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;

    // Act
    table.insert("C", Polynom("z"));
    table.insert("A", Polynom("x"));
    table.insert("B", Polynom("y"));

    // Assert
    ASSERT_NE(nullptr, table.found("A"));
    ASSERT_NE(nullptr, table.found("B"));
    ASSERT_NE(nullptr, table.found("C"));

    EXPECT_EQ("x", polynom_to_string(*table.found("A")));
    EXPECT_EQ("y", polynom_to_string(*table.found("B")));
    EXPECT_EQ("z", polynom_to_string(*table.found("C")));
}

TEST(TestSortedTableOnArray, insert_duplicate_key_should_throw) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;
    table.insert("A", Polynom("x"));

    // Act + Assert
    EXPECT_ANY_THROW(table.insert("A", Polynom("2x")));
}

TEST(TestSortedTableOnArray, erase_existing_element) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;
    table.insert("A", Polynom("x"));

    // Act
    table.erase("A");

    // Assert
    EXPECT_EQ(nullptr, table.found("A"));
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnArray, erase_non_existing_key_should_throw) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;

    // Act + Assert
    EXPECT_ANY_THROW(table.erase("X"));
}

TEST(TestSortedTableOnArray, after_erasing_one_element_other_elements_are_saved) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;
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

TEST(TestSortedTableOnArray, can_insert_again_after_erase) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;
    table.insert("A", Polynom("x"));
    table.erase("A");

    // Act
    table.insert("A", Polynom("5x"));
    const Polynom* result = table.found("A");

    // Assert
    ASSERT_NE(nullptr, result);
    EXPECT_EQ("5x", polynom_to_string(*result));
}

TEST(TestSortedTableOnArray, mixed_operations) {
    // Arrange
    SortedTableOnArray<std::string, Polynom> table;

    // Act
    table.insert("C", Polynom("3x"));
    table.insert("A", Polynom("x"));
    table.insert("B", Polynom("2x"));
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

    std::ostringstream out;
    table.print(out);
    std::string result = out.str();

    size_t posA = result.find("A");
    size_t posC = result.find("C");
    size_t posD = result.find("D");
}