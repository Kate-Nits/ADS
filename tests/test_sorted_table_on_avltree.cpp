// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_sorted_table_on_avltree/sorted_table_on_avltree.h"

#include <sstream>
#include <string>

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestSortedTableOnAVLTree, default_constructor) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;

    // Act & Assert
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(nullptr, table.found(1));
}

TEST(TestSortedTableOnAVLTree, insert_one_element) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;

    // Act
    table.insert(5, 50);

    // Assert
    EXPECT_FALSE(table.is_empty());
    ASSERT_NE(nullptr, table.found(5));
    EXPECT_EQ(50, *table.found(5));
}

TEST(TestSortedTableOnAVLTree, insert_several_elements) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;

    // Act
    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);
    table.insert(1, 10);
    table.insert(4, 40);

    // Assert
    EXPECT_FALSE(table.is_empty());

    ASSERT_NE(nullptr, table.found(5));
    ASSERT_NE(nullptr, table.found(3));
    ASSERT_NE(nullptr, table.found(7));
    ASSERT_NE(nullptr, table.found(1));
    ASSERT_NE(nullptr, table.found(4));

    EXPECT_EQ(50, *table.found(5));
    EXPECT_EQ(30, *table.found(3));
    EXPECT_EQ(70, *table.found(7));
    EXPECT_EQ(10, *table.found(1));
    EXPECT_EQ(40, *table.found(4));
}

TEST(TestSortedTableOnAVLTree, insert_duplicate_key) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(5, 50);

    // Act & Assert
    ASSERT_ANY_THROW(table.insert(5, 500));
}

TEST(TestSortedTableOnAVLTree, insert_after_LL_rotation) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;

    // Act
    table.insert(30, 300);
    table.insert(20, 200);
    table.insert(10, 100);

    // Assert
    ASSERT_NE(nullptr, table.found(10));
    ASSERT_NE(nullptr, table.found(20));
    ASSERT_NE(nullptr, table.found(30));

    EXPECT_EQ(100, *table.found(10));
    EXPECT_EQ(200, *table.found(20));
    EXPECT_EQ(300, *table.found(30));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, insert_after_RR_rotation) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;

    // Act
    table.insert(10, 100);
    table.insert(20, 200);
    table.insert(30, 300);

    // Assert
    ASSERT_NE(nullptr, table.found(10));
    ASSERT_NE(nullptr, table.found(20));
    ASSERT_NE(nullptr, table.found(30));

    EXPECT_EQ(100, *table.found(10));
    EXPECT_EQ(200, *table.found(20));
    EXPECT_EQ(300, *table.found(30));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, insert_after_LR_rotation) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;

    // Act
    table.insert(30, 300);
    table.insert(10, 100);
    table.insert(20, 200);

    // Assert
    ASSERT_NE(nullptr, table.found(10));
    ASSERT_NE(nullptr, table.found(20));
    ASSERT_NE(nullptr, table.found(30));

    EXPECT_EQ(100, *table.found(10));
    EXPECT_EQ(200, *table.found(20));
    EXPECT_EQ(300, *table.found(30));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, insert_after_RL_rotation) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;

    // Act
    table.insert(10, 100);
    table.insert(30, 300);
    table.insert(20, 200);

    // Assert
    ASSERT_NE(nullptr, table.found(10));
    ASSERT_NE(nullptr, table.found(20));
    ASSERT_NE(nullptr, table.found(30));

    EXPECT_EQ(100, *table.found(10));
    EXPECT_EQ(200, *table.found(20));
    EXPECT_EQ(300, *table.found(30));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, found_in_empty_table) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;

    // Act & Assert
    EXPECT_EQ(nullptr, table.found(10));
}

TEST(TestSortedTableOnAVLTree, found_exist_key) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);

    // Act
    const int* value = table.found(3);

    // Assert
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(30, *value);
}

TEST(TestSortedTableOnAVLTree, found_root_key) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(5, 50);

    // Act
    const int* value = table.found(5);

    // Assert
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(50, *value);
}

TEST(TestSortedTableOnAVLTree, found_not_exist_key) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);

    // Act & Assert
    EXPECT_EQ(nullptr, table.found(100));
}

TEST(TestSortedTableOnAVLTree, erase_from_empty_table) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;

    // Act & Assert
    ASSERT_ANY_THROW(table.erase(5));
}

TEST(TestSortedTableOnAVLTree, erase_not_exist_key) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);

    // Act & Assert
    ASSERT_ANY_THROW(table.erase(100));
}

TEST(TestSortedTableOnAVLTree, erase_only_one_element) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(5, 50);

    // Act
    table.erase(5);

    // Assert
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(nullptr, table.found(5));
}

TEST(TestSortedTableOnAVLTree, erase_left_leaf) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(20, 200);
    table.insert(10, 100);
    table.insert(30, 300);
    table.insert(5, 50);
    table.insert(15, 150);

    // Act
    table.erase(5);

    // Assert
    EXPECT_EQ(nullptr, table.found(5));
    EXPECT_NE(nullptr, table.found(10));
    EXPECT_NE(nullptr, table.found(15));
    EXPECT_NE(nullptr, table.found(20));
    EXPECT_NE(nullptr, table.found(30));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, erase_right_leaf) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(20, 200);
    table.insert(10, 100);
    table.insert(30, 300);
    table.insert(25, 250);
    table.insert(35, 350);

    // Act
    table.erase(35);

    // Assert
    EXPECT_EQ(nullptr, table.found(35));
    EXPECT_NE(nullptr, table.found(10));
    EXPECT_NE(nullptr, table.found(20));
    EXPECT_NE(nullptr, table.found(25));
    EXPECT_NE(nullptr, table.found(30));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, erase_node_with_only_left_child) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(20, 200);
    table.insert(10, 100);
    table.insert(30, 300);
    table.insert(5, 50);

    // Act
    table.erase(10);

    // Assert
    EXPECT_EQ(nullptr, table.found(10));
    EXPECT_NE(nullptr, table.found(5));
    EXPECT_NE(nullptr, table.found(20));
    EXPECT_NE(nullptr, table.found(30));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, erase_node_with_only_right_child) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(20, 200);
    table.insert(10, 100);
    table.insert(30, 300);
    table.insert(15, 150);

    // Act
    table.erase(10);

    // Assert
    EXPECT_EQ(nullptr, table.found(10));
    EXPECT_NE(nullptr, table.found(15));
    EXPECT_NE(nullptr, table.found(20));
    EXPECT_NE(nullptr, table.found(30));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, erase_node_with_two_children) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(50, 500);
    table.insert(30, 300);
    table.insert(70, 700);
    table.insert(20, 200);
    table.insert(40, 400);
    table.insert(60, 600);
    table.insert(80, 800);

    // Act
    table.erase(30);

    // Assert
    EXPECT_EQ(nullptr, table.found(30));
    EXPECT_NE(nullptr, table.found(20));
    EXPECT_NE(nullptr, table.found(40));
    EXPECT_NE(nullptr, table.found(50));
    EXPECT_NE(nullptr, table.found(60));
    EXPECT_NE(nullptr, table.found(70));
    EXPECT_NE(nullptr, table.found(80));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, erase_root_with_two_children) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(20, 200);
    table.insert(10, 100);
    table.insert(30, 300);

    // Act
    table.erase(20);

    // Assert
    EXPECT_EQ(nullptr, table.found(20));
    EXPECT_NE(nullptr, table.found(10));
    EXPECT_NE(nullptr, table.found(30));
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, erase_many_elements) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    int keys[10] = { 50, 25, 75, 10, 30, 60, 90, 5, 15, 27 };

    for (int i = 0; i < 10; ++i) {
        table.insert(keys[i], keys[i] * 10);
    }

    // Act
    table.erase(5);
    table.erase(75);
    table.erase(25);

    // Assert
    EXPECT_EQ(nullptr, table.found(5));
    EXPECT_EQ(nullptr, table.found(75));
    EXPECT_EQ(nullptr, table.found(25));

    EXPECT_NE(nullptr, table.found(10));
    EXPECT_NE(nullptr, table.found(15));
    EXPECT_NE(nullptr, table.found(27));
    EXPECT_NE(nullptr, table.found(30));
    EXPECT_NE(nullptr, table.found(50));
    EXPECT_NE(nullptr, table.found(60));
    EXPECT_NE(nullptr, table.found(90));
}

TEST(TestSortedTableOnAVLTree, check_is_empty_return_true) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;

    // Act & Assert
    EXPECT_TRUE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, check_is_empty_return_false) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;

    // Act
    table.insert(1, 10);

    // Assert
    EXPECT_FALSE(table.is_empty());
}

TEST(TestSortedTableOnAVLTree, check_is_empty_after_erase_all_elements) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    table.insert(1, 10);
    table.insert(2, 20);
    table.insert(3, 30);

    // Act
    table.erase(1);
    table.erase(2);
    table.erase(3);

    // Assert
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(nullptr, table.found(1));
    EXPECT_EQ(nullptr, table.found(2));
    EXPECT_EQ(nullptr, table.found(3));
}

TEST(TestSortedTableOnAVLTree, big_table_insert_and_found_all_elements) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    int keys[32] = {
        50, 25, 75, 10, 30, 60, 90, 2,
        5, 15, 27, 35, 55, 65, 80, 95,
        1, 6, 12, 18, 26, 28, 33, 37,
        53, 57, 63, 67, 78, 82, 93, 97
    };

    // Act
    for (int i = 0; i < 32; ++i) {
        table.insert(keys[i], keys[i] * 10);
    }

    // Assert
    EXPECT_FALSE(table.is_empty());

    for (int i = 0; i < 32; ++i) {
        const int* value = table.found(keys[i]);
        ASSERT_NE(nullptr, value);
        EXPECT_EQ(keys[i] * 10, *value);
    }
}

TEST(TestSortedTableOnAVLTree, big_table_erase_many_different_cases) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
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

TEST(TestSortedTableOnAVLTree, print_empty_table) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    std::ostringstream out;

    // Act & Assert
    EXPECT_NO_THROW(table.print(out));
}

TEST(TestSortedTableOnAVLTree, print_not_empty_table) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    std::ostringstream out;

    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);

    // Act
    table.print(out);

    // Assert
    EXPECT_FALSE(out.str().empty());
    EXPECT_NE(std::string::npos, out.str().find("5"));
    EXPECT_NE(std::string::npos, out.str().find("50"));
    EXPECT_NE(std::string::npos, out.str().find("3"));
    EXPECT_NE(std::string::npos, out.str().find("30"));
    EXPECT_NE(std::string::npos, out.str().find("7"));
    EXPECT_NE(std::string::npos, out.str().find("70"));
}

TEST(TestSortedTableOnAVLTree, print_after_erase) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    std::ostringstream out;

    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);
    table.erase(3);

    // Act
    table.print(out);

    // Assert
    EXPECT_FALSE(out.str().empty());
    EXPECT_NE(std::string::npos, out.str().find("5"));
    EXPECT_NE(std::string::npos, out.str().find("50"));
    EXPECT_NE(std::string::npos, out.str().find("7"));
    EXPECT_NE(std::string::npos, out.str().find("70"));
    EXPECT_EQ(std::string::npos, out.str().find("30"));
}

TEST(TestSortedTableOnAVLTree, check_print_table) {
    // Arrange
    SortedTableOnAVLTree<int, int> table;
    std::stringstream out;
    std::string line;

    table.insert(5, 50);
    table.insert(3, 30);
    table.insert(7, 70);

    // Act
    table.print(out);

    // Assert
    ASSERT_TRUE(static_cast<bool>(std::getline(out, line)));
    EXPECT_EQ("+---------------------------------------------------+", line);
    ASSERT_TRUE(static_cast<bool>(std::getline(out, line)));
    EXPECT_EQ("| KEY      | VALUE                                  |", line);
    ASSERT_TRUE(static_cast<bool>(std::getline(out, line)));
    EXPECT_EQ("+---------------------------------------------------+", line);
    ASSERT_TRUE(static_cast<bool>(std::getline(out, line)));
    EXPECT_EQ("| 3        | 30                                     |", line);
    ASSERT_TRUE(static_cast<bool>(std::getline(out, line)));
    EXPECT_EQ("| 5        | 50                                     |", line);
    ASSERT_TRUE(static_cast<bool>(std::getline(out, line)));
    EXPECT_EQ("| 7        | 70                                     |", line);
    ASSERT_TRUE(static_cast<bool>(std::getline(out, line)));
    EXPECT_EQ("+---------------------------------------------------+", line);
    EXPECT_FALSE(static_cast<bool>(std::getline(out, line)));
}