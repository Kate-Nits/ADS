// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_tree/tree.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestTree, check_insert_and_find) {
    // Arrange
    Tree<int, std::string> tree;

    // Act
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    // Assert
    EXPECT_EQ("five", *tree.find(5));
    EXPECT_EQ("three", *tree.find(3));
    EXPECT_EQ("seven", *tree.find(7));
    EXPECT_EQ(nullptr, tree.find(10));
}

TEST(TestTree, check_erase_leaf) {
    // Arrange
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    // Act
    tree.erase(7);

    // Assert
    EXPECT_EQ(nullptr, tree.find(7));
    EXPECT_NE(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(3));
}

TEST(TestTree, check_erase_root) {
    // Arrange
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    // Act
    tree.erase(5);

    // Assert
    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(3));
    EXPECT_NE(nullptr, tree.find(7));
}

TEST(TestTree, check_erase_with_not_exist_key) {
    // Arrange
    Tree<int, std::string> tree;
    tree.insert(1, "one");

    // Act & Assert
    EXPECT_ANY_THROW(tree.erase(100));
}

TEST(TestTree, check_erase_in_empty_tree) {
    // Arrange
    Tree<int, std::string> tree;

    // Act & Assert
    EXPECT_ANY_THROW(tree.erase(1));
}

TEST(TestTree, check_clear) {
    // Arrange
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");

    // Act
    tree.clear();

    // Assert
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_EQ(nullptr, tree.find(3));
}

TEST(TestTree, check_print_w_lcr_lrc_clr) {
    // Arrange
    Tree<int, std::string> tree;
    tree.insert(5, "5");
    tree.insert(3, "3");
    tree.insert(7, "7");

    // Act & Assert
    EXPECT_NO_THROW(tree.print_w());
    EXPECT_NO_THROW(tree.print_lcr());
    EXPECT_NO_THROW(tree.print_lrc());
    EXPECT_NO_THROW(tree.print_clr());
    EXPECT_NO_THROW(tree.print());
}

TEST(TestTree, check_is_empty) {
    // Arrange
    Tree<int, std::string> tree;

    // Act & Assert
    EXPECT_TRUE(tree.is_empty());
    tree.insert(1, "one");
    EXPECT_FALSE(tree.is_empty());
    tree.clear();
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestTree, chech_print) {
    // Arrange
    Tree<int, std::string> tree;
    tree.insert(5, "five");
    tree.insert(3, "three");
    tree.insert(7, "seven");

    // Act & Assert
    EXPECT_NO_THROW(tree.print());
}