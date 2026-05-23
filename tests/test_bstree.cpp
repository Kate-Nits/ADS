// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_bstree/bstree.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestBSTree, default_constructor) {
    // Arrange
    BSTree<int, int> tree;

    // Act & Assert
    EXPECT_EQ(nullptr, tree.root());
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestBSTree, insert_root) {
    // Arrange
    BSTree<int, int> tree;

    // Act
    auto parent = tree.insert(5, 50);

    // Assert
    EXPECT_EQ(nullptr, parent);
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(5, tree.root()->data.first);
    EXPECT_EQ(50, tree.root()->data.second);
    EXPECT_EQ(nullptr, tree.root()->left);
    EXPECT_EQ(nullptr, tree.root()->right);
    EXPECT_FALSE(tree.is_empty());
}

TEST(TestBSTree, insert_left_child) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);

    // Act
    auto parent = tree.insert(3, 30);

    // Assert
    ASSERT_NE(nullptr, parent);
    EXPECT_EQ(5, parent->data.first);
    ASSERT_NE(nullptr, tree.root()->left);
    EXPECT_EQ(3, tree.root()->left->data.first);
    EXPECT_EQ(30, tree.root()->left->data.second);
}

TEST(TestBSTree, insert_right_child) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);

    // Act
    auto parent = tree.insert(7, 70);

    // Assert
    ASSERT_NE(nullptr, parent);
    EXPECT_EQ(5, parent->data.first);
    ASSERT_NE(nullptr, tree.root()->right);
    EXPECT_EQ(7, tree.root()->right->data.first);
    EXPECT_EQ(70, tree.root()->right->data.second);
}

TEST(TestBSTree, insert_several_elements) {
    // Arrange
    BSTree<int, int> tree;

    // Act
    tree.insert(5, 50);
    tree.insert(1, 10);
    tree.insert(3, 30);
    tree.insert(7, 70);
    tree.insert(2, 20);
    tree.insert(4, 40);
    tree.insert(6, 60);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(5, tree.root()->data.first);
    ASSERT_NE(nullptr, tree.root()->left);
    EXPECT_EQ(1, tree.root()->left->data.first);
    ASSERT_NE(nullptr, tree.root()->left->right);
    EXPECT_EQ(3, tree.root()->left->right->data.first);
    ASSERT_NE(nullptr, tree.root()->left->right->left);
    EXPECT_EQ(2, tree.root()->left->right->left->data.first);
    ASSERT_NE(nullptr, tree.root()->left->right->right);
    EXPECT_EQ(4, tree.root()->left->right->right->data.first);
    ASSERT_NE(nullptr, tree.root()->right);
    EXPECT_EQ(7, tree.root()->right->data.first);
    ASSERT_NE(nullptr, tree.root()->right->left);
    EXPECT_EQ(6, tree.root()->right->left->data.first);
}

TEST(TestBSTree, insert_duplicate_key) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);

    // Act & Assert
    ASSERT_ANY_THROW(tree.insert(5, 500));
}

TEST(TestBSTree, find_in_empty_tree) {
    // Arrange
    BSTree<int, int> tree;

    // Act & Assert
    EXPECT_EQ(nullptr, tree.find(10));
}

TEST(TestBSTree, find_root) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);

    // Act
    int* value = tree.find(5);

    // Assert
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(50, *value);
}

TEST(TestBSTree, find_left_element) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(1, 10);

    // Act
    int* value = tree.find(1);

    // Assert
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(10, *value);
}

TEST(TestBSTree, find_right_element) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(7, 70);
    tree.insert(9, 90);

    // Act
    int* value = tree.find(9);

    // Assert
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(90, *value);
}

TEST(TestBSTree, find_not_exist_element) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);

    // Act & Assert
    EXPECT_EQ(nullptr, tree.find(100));
}

TEST(TestBSTree, check_can_change_value_by_find_pointer) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);

    // Act
    int* value = tree.find(5);
    *value = 500;

    // Assert
    EXPECT_EQ(500, *tree.find(5));
}

TEST(TestBSTree, erase_from_empty_tree) {
    // Arrange
    BSTree<int, int> tree;

    // Act & Assert
    ASSERT_ANY_THROW(tree.erase(5));
}

TEST(TestBSTree, erase_not_exist_element) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);

    // Act & Assert
    ASSERT_ANY_THROW(tree.erase(100));
}

TEST(TestBSTree, erase_root) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);

    // Act
    tree.erase(5);

    // Assert
    EXPECT_EQ(nullptr, tree.root());
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.find(5));
}

TEST(TestBSTree, erase_left_leaf) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(9, 90);
    tree.insert(1, 10);
    tree.insert(4, 40);
    tree.insert(7, 70);

    // Act
    tree.erase(4);

    // Assert
    EXPECT_EQ(nullptr, tree.find(4));
    ASSERT_NE(nullptr, tree.root()->left);
    EXPECT_EQ(3, tree.root()->left->data.first);
    EXPECT_EQ(nullptr, tree.root()->left->right);
    EXPECT_NE(nullptr, tree.find(1));
    EXPECT_NE(nullptr, tree.find(3));
    EXPECT_NE(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(7));
    EXPECT_NE(nullptr, tree.find(9));
}

TEST(TestBSTree, erase_right_leaf) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(9, 90);
    tree.insert(1, 10);
    tree.insert(4, 40);
    tree.insert(10, 100);

    // Act
    tree.erase(10);

    // Assert
    EXPECT_EQ(nullptr, tree.find(10));
    ASSERT_NE(nullptr, tree.root()->right);
    EXPECT_EQ(9, tree.root()->right->data.first);
    EXPECT_EQ(nullptr, tree.root()->right->right);
}

TEST(TestBSTree, erase_node_with_only_left_child) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(9, 90);
    tree.insert(1, 10);
    tree.insert(4, 40);
    tree.insert(7, 70);
    tree.insert(6, 60);
    tree.insert(8, 80);

    // Act
    tree.erase(9);

    // Assert
    EXPECT_EQ(nullptr, tree.find(9));
    ASSERT_NE(nullptr, tree.root()->right);
    EXPECT_EQ(7, tree.root()->right->data.first);
    ASSERT_NE(nullptr, tree.root()->right->left);
    ASSERT_NE(nullptr, tree.root()->right->right);
    EXPECT_EQ(6, tree.root()->right->left->data.first);
    EXPECT_EQ(8, tree.root()->right->right->data.first);
}

TEST(TestBSTree, erase_node_with_only_right_child) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(11, 110);
    tree.insert(5, 50);
    tree.insert(13, 130);
    tree.insert(7, 70);
    tree.insert(12, 120);
    tree.insert(15, 150);
    tree.insert(6, 60);
    tree.insert(10, 100);

    // Act
    tree.erase(5);

    // Assert
    EXPECT_EQ(nullptr, tree.find(5));
    ASSERT_NE(nullptr, tree.root()->left);
    EXPECT_EQ(7, tree.root()->left->data.first);
    ASSERT_NE(nullptr, tree.root()->left->left);
    ASSERT_NE(nullptr, tree.root()->left->right);
    EXPECT_EQ(6, tree.root()->left->left->data.first);
    EXPECT_EQ(10, tree.root()->left->right->data.first);
}

TEST(TestBSTree, erase_root_with_only_left_child) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(1, 10);
    tree.insert(4, 40);

    // Act
    tree.erase(5);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(3, tree.root()->data.first);
    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(1));
    EXPECT_NE(nullptr, tree.find(4));
}

TEST(TestBSTree, erase_root_with_only_right_child) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(7, 70);
    tree.insert(6, 60);
    tree.insert(9, 90);

    // Act
    tree.erase(5);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(7, tree.root()->data.first);
    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(6));
    EXPECT_NE(nullptr, tree.find(9));
}

TEST(TestBSTree, erase_root_with_two_children) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);
    tree.insert(1, 10);
    tree.insert(4, 40);
    tree.insert(6, 60);
    tree.insert(8, 80);

    // Act
    tree.erase(5);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(4, tree.root()->data.first);
    EXPECT_EQ(40, tree.root()->data.second);
    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(1));
    EXPECT_NE(nullptr, tree.find(3));
    EXPECT_NE(nullptr, tree.find(4));
    EXPECT_NE(nullptr, tree.find(6));
    EXPECT_NE(nullptr, tree.find(7));
    EXPECT_NE(nullptr, tree.find(8));
}

TEST(TestBSTree, erase_not_root_node_with_two_children) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(10, 100);
    tree.insert(5, 50);
    tree.insert(15, 150);
    tree.insert(3, 30);
    tree.insert(7, 70);
    tree.insert(6, 60);
    tree.insert(8, 80);

    // Act
    tree.erase(5);

    // Assert
    EXPECT_EQ(nullptr, tree.find(5));
    ASSERT_NE(nullptr, tree.root()->left);
    EXPECT_EQ(3, tree.root()->left->data.first);
    EXPECT_NE(nullptr, tree.find(3));
    EXPECT_NE(nullptr, tree.find(6));
    EXPECT_NE(nullptr, tree.find(7));
    EXPECT_NE(nullptr, tree.find(8));
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(15));
}

TEST(TestBSTree, clear_empty_tree) {
    // Arrange
    BSTree<int, int> tree;

    // Act
    tree.clear();

    // Assert
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.root());
}

TEST(TestBSTree, clear_not_empty_tree) {
    // Arrange
    BSTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);
    tree.insert(1, 10);
    tree.insert(4, 40);

    // Act
    tree.clear();

    // Assert
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.root());
    EXPECT_EQ(nullptr, tree.find(5));
}

TEST(TestBSTree, check_is_empty_return_true) {
    // Arrange
    BSTree<int, int> tree;

    // Act & Assert
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestBSTree, check_is_empty_return_false) {
    // Arrange
    BSTree<int, int> tree;

    // Act
    tree.insert(1, 10);

    // Assert
    EXPECT_FALSE(tree.is_empty());
}

TEST(TestBSTree, big_tree_insert_and_find_all_elements) {
    // Arrange
    BSTree<int, int> tree;
    int keys[31] = {
        50, 25, 75, 10, 30, 60, 90,
        5, 15, 27, 35, 55, 65, 80, 95,
        1, 6, 12, 18, 26, 28, 33, 37,
        53, 57, 63, 67, 78, 82, 93, 97
    };

    // Act
    for (int i = 0; i < 31; ++i) {
        tree.insert(keys[i], keys[i] * 10);
    }

    // Assert
    EXPECT_FALSE(tree.is_empty());
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(50, tree.root()->data.first);
    for (int i = 0; i < 31; ++i) {
        int* value = tree.find(keys[i]);
        ASSERT_NE(nullptr, value);
        EXPECT_EQ(keys[i] * 10, *value);
    }
}

TEST(TestBSTree, big_tree_erase_many_different_cases) {
    // Arrange
    BSTree<int, int> tree;
    int keys[31] = {
        50, 25, 75, 10, 30, 60, 90,
        5, 15, 27, 35, 55, 65, 80, 95,
        1, 6, 12, 18, 26, 28, 33, 37,
        53, 57, 63, 67, 78, 82, 93, 97
    };

    for (int i = 0; i < 31; ++i) {
        tree.insert(keys[i], keys[i]);
    }

    // Act
    tree.erase(1);   // лист
    tree.erase(5);   // node с одним правым потомком
    tree.erase(90);  // node с двумя потомками
    tree.erase(25);  // node с двумя потомками
    tree.erase(50);  // корень с двумя потомками

    // Assert
    EXPECT_EQ(nullptr, tree.find(1));
    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_EQ(nullptr, tree.find(90));
    EXPECT_EQ(nullptr, tree.find(25));
    EXPECT_EQ(nullptr, tree.find(50));

    EXPECT_NE(nullptr, tree.find(6));
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(15));
    EXPECT_NE(nullptr, tree.find(30));
    EXPECT_NE(nullptr, tree.find(75));
    EXPECT_NE(nullptr, tree.find(97));

    testing::internal::CaptureStdout();
    tree.print_lcr();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ("6 10 12 15 18 26 27 28 30 33 35 37 53 55 57 60 63 65 67 75 78 80 82 93 95 97 ", output);
}

TEST(TestBSTree, big_tree_clear) {
    // Arrange
    BSTree<int, int> tree;

    for (int i = 0; i < 100; ++i) {
        tree.insert(i, i * 10);
    }

    // Act
    tree.clear();

    // Assert
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.root());

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(nullptr, tree.find(i));
    }
}