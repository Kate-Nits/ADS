// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_unsorted_table_on_tree/unsorted_table_on_tree.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestUnsortedTableOnTree, check_insert_and_found) {
    // Arrange
    UnsortedTableOnTree<int, std::string> table;

    // Act
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");

    // Assert
    EXPECT_EQ("five", *table.found(5));
    EXPECT_EQ("three", *table.found(3));
    EXPECT_EQ("seven", *table.found(7));
    EXPECT_EQ(nullptr, table.found(10));
}

TEST(TestUnsortedTableOnTree, insert_duplicate_key) {
    // Arrange
    UnsortedTableOnTree<int, std::string> table;
    table.insert(1, "one");

    // Act & Assert
    EXPECT_ANY_THROW(table.insert(1, "another"));
}

TEST(TestUnsortedTableOnTree, check_erase_root) {
    // Arrange
    UnsortedTableOnTree<int, std::string> table;
    table.insert(2, "two");
    table.insert(4, "four");

    // Act
    table.erase(2);

    // Assert
    EXPECT_EQ(nullptr, table.found(2));
    ASSERT_NE(nullptr, table.found(4));
    EXPECT_EQ("four", *table.found(4));
}

TEST(TestUnsortedTableOnTree, erase_not_exist_key) {
    // Arrange
    UnsortedTableOnTree<int, std::string> table;

    // Act & Assert
    EXPECT_THROW(table.erase(100), std::invalid_argument);
}

TEST(TestUnsortedTableOnTree, check_is_empty) {
    // Arrange
    UnsortedTableOnTree<int, std::string> table;

    // Act & Assert
    EXPECT_TRUE(table.is_empty());
    table.insert(1, "one");
    EXPECT_FALSE(table.is_empty());
    table.erase(1);
    EXPECT_TRUE(table.is_empty());
}

TEST(TestUnsortedTableOnTree, chech_print) {
    // Arrange
    UnsortedTableOnTree<int, std::string> table;
    table.insert(5, "five");
    table.insert(3, "three");
    table.insert(7, "seven");

    // Act & Assert
    EXPECT_NO_THROW(table.print());
}