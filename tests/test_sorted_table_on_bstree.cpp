// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_sorted_table_on_bstree/sorted_table_on_bstree.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestSortedTableOnBSTree, default_constructor) {
    // Arrange
    SortedTableOnBSTree<int, int> table;

    // Act & Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnBSTree, insert_one_element) {
    // Arrange
    SortedTableOnBSTree<int, int> table;

    // Act
    table.insert(5, 50);

    // Assert
    EXPECT_FALSE(table.is_empty());
    ASSERT_NE(nullptr, table.found(5));
    EXPECT_EQ(50, *table.found(5));
}

TEST(TestSortedTableOnBSTree, insert_several_elements) {
    // Arrange
    SortedTableOnBSTree<int, int> table;

    // Act
    table.insert(5, 50);
    table.insert(1, 10);
    table.insert(3, 30);
    table.insert(7, 70);
    table.insert(2, 20);
    table.insert(4, 40);
    table.insert(6, 60);

    // Assert
    EXPECT_EQ(50, *table.found(5));
    EXPECT_EQ(10, *table.found(1));
    EXPECT_EQ(30, *table.found(3));
    EXPECT_EQ(70, *table.found(7));
    EXPECT_EQ(20, *table.found(2));
    EXPECT_EQ(40, *table.found(4));
    EXPECT_EQ(60, *table.found(6));
}

TEST(TestSortedTableOnBSTree, insert_duplicate_key) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(5, 50);

    // Act & Assert
    ASSERT_ANY_THROW(table.insert(5, 500));
}

TEST(TestSortedTableOnBSTree, found_in_empty_table) {
    // Arrange
    SortedTableOnBSTree<int, int> table;

    // Act & Assert
    EXPECT_EQ(nullptr, table.found(5));
}

TEST(TestSortedTableOnBSTree, found_root_element) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(5, 50);

    // Act
    const int* value = table.found(5);

    // Assert
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(50, *value);
}

TEST(TestSortedTableOnBSTree, found_left_element) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(1, 10);

    // Act
    const int* value = table.found(1);

    // Assert
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(10, *value);
}

TEST(TestSortedTableOnBSTree, found_right_element) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(5, 50);
    table.insert(7, 70);
    table.insert(9, 90);

    // Act
    const int* value = table.found(9);

    // Assert
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(90, *value);
}

TEST(TestSortedTableOnBSTree, found_not_exist_element) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);

    // Act & Assert
    EXPECT_EQ(nullptr, table.found(100));
}

TEST(TestSortedTableOnBSTree, check_is_empty_return_true) {
    // Arrange
    SortedTableOnBSTree<int, int> table;

    // Act & Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnBSTree, check_is_empty_return_false) {
    // Arrange
    SortedTableOnBSTree<int, int> table;

    // Act
    table.insert(1, 10);

    // Assert
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnBSTree, erase_from_empty_table) {
    // Arrange
    SortedTableOnBSTree<int, int> table;

    // Act & Assert
    ASSERT_ANY_THROW(table.erase(5));
}

TEST(TestSortedTableOnBSTree, erase_not_exist_element) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);

    // Act & Assert
    ASSERT_ANY_THROW(table.erase(100));
}

TEST(TestSortedTableOnBSTree, erase_single_element) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(5, 50);

    // Act
    table.erase(5);

    // Assert
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(nullptr, table.found(5));
}

TEST(TestSortedTableOnBSTree, erase_leaf) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(9, 90);
    table.insert(1, 10);
    table.insert(4, 40);
    table.insert(7, 70);

    // Act
    table.erase(4);

    // Assert
    EXPECT_EQ(nullptr, table.found(4));
    EXPECT_NE(nullptr, table.found(1));
    EXPECT_NE(nullptr, table.found(3));
    EXPECT_NE(nullptr, table.found(5));
    EXPECT_NE(nullptr, table.found(7));
    EXPECT_NE(nullptr, table.found(9));
}

TEST(TestSortedTableOnBSTree, erase_node_with_only_left_child) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(9, 90);
    table.insert(1, 10);
    table.insert(4, 40);
    table.insert(7, 70);
    table.insert(6, 60);
    table.insert(8, 80);

    // Act
    table.erase(9);

    // Assert
    EXPECT_EQ(nullptr, table.found(9));
    EXPECT_NE(nullptr, table.found(7));
    EXPECT_NE(nullptr, table.found(6));
    EXPECT_NE(nullptr, table.found(8));
    EXPECT_NE(nullptr, table.found(5));
    EXPECT_EQ(70, *table.found(7));
}

TEST(TestSortedTableOnBSTree, erase_node_with_only_right_child) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(11, 110);
    table.insert(5, 50);
    table.insert(13, 130);
    table.insert(7, 70);
    table.insert(12, 120);
    table.insert(15, 150);
    table.insert(6, 60);
    table.insert(10, 100);

    // Act
    table.erase(5);

    // Assert
    EXPECT_EQ(nullptr, table.found(5));
    EXPECT_NE(nullptr, table.found(7));
    EXPECT_NE(nullptr, table.found(6));
    EXPECT_NE(nullptr, table.found(10));
    EXPECT_NE(nullptr, table.found(11));
    EXPECT_NE(nullptr, table.found(13));
}

TEST(TestSortedTableOnBSTree, erase_root_with_two_children) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);
    table.insert(1, 10);
    table.insert(4, 40);
    table.insert(6, 60);
    table.insert(8, 80);

    // Act
    table.erase(5);

    // Assert
    EXPECT_EQ(nullptr, table.found(5));
    EXPECT_NE(nullptr, table.found(1));
    EXPECT_NE(nullptr, table.found(3));
    EXPECT_NE(nullptr, table.found(4));
    EXPECT_NE(nullptr, table.found(6));
    EXPECT_NE(nullptr, table.found(7));
    EXPECT_NE(nullptr, table.found(8));
}

TEST(TestSortedTableOnBSTree, erase_not_root_node_with_two_children) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    table.insert(10, 100);
    table.insert(5, 50);
    table.insert(15, 150);
    table.insert(3, 30);
    table.insert(7, 70);
    table.insert(6, 60);
    table.insert(8, 80);

    // Act
    table.erase(5);

    // Assert
    EXPECT_EQ(nullptr, table.found(5));
    EXPECT_NE(nullptr, table.found(3));
    EXPECT_NE(nullptr, table.found(6));
    EXPECT_NE(nullptr, table.found(7));
    EXPECT_NE(nullptr, table.found(8));
    EXPECT_NE(nullptr, table.found(10));
    EXPECT_NE(nullptr, table.found(15));
}

TEST(TestSortedTableOnBSTree, big_table_insert_and_found_all_elements) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    int keys[31] = {
        50, 25, 75, 10, 30, 60, 90,
        5, 15, 27, 35, 55, 65, 80, 95,
        1, 6, 12, 18, 26, 28, 33, 37,
        53, 57, 63, 67, 78, 82, 93, 97
    };

    // Act
    for (int i = 0; i < 31; ++i) {
        table.insert(keys[i], keys[i] * 10);
    }

    // Assert
    EXPECT_FALSE(table.is_empty());

    for (int i = 0; i < 31; ++i) {
        const int* value = table.found(keys[i]);
        ASSERT_NE(nullptr, value);
        EXPECT_EQ(keys[i] * 10, *value);
    }
}

TEST(TestSortedTableOnBSTree, big_table_erase_many_different) {
    // Arrange
    SortedTableOnBSTree<int, int> table;
    int keys[31] = {
        50, 25, 75, 10, 30, 60, 90,
        5, 15, 27, 35, 55, 65, 80, 95,
        1, 6, 12, 18, 26, 28, 33, 37,
        53, 57, 63, 67, 78, 82, 93, 97
    };

    for (int i = 0; i < 31; ++i) {
        table.insert(keys[i], keys[i]);
    }
    // Act
    table.erase(1);
    table.erase(5);
    table.erase(90);
    table.erase(25);
    table.erase(50);

    // Assert
    EXPECT_EQ(nullptr, table.found(1));
    EXPECT_EQ(nullptr, table.found(5));
    EXPECT_EQ(nullptr, table.found(90));
    EXPECT_EQ(nullptr, table.found(25));
    EXPECT_EQ(nullptr, table.found(50));

    EXPECT_NE(nullptr, table.found(6));
    EXPECT_NE(nullptr, table.found(10));
    EXPECT_NE(nullptr, table.found(15));
    EXPECT_NE(nullptr, table.found(30));
    EXPECT_NE(nullptr, table.found(75));
    EXPECT_NE(nullptr, table.found(97));
}