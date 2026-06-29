// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_avltree/avltree.h"

#include <algorithm>
#include <cmath>
#include <string>

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

template <class TKey, class TValue>
int real_height(AVLNode<TKey, TValue>* node) {
    if (!node) { return 0; }
    return 1 + std::max(real_height(node->left), real_height(node->right));
}

template <class TKey, class TValue>
void check_heights_and_balance(AVLNode<TKey, TValue>* node) {
    if (!node) { return; }
    int left_height = real_height(node->left);
    int right_height = real_height(node->right);
    EXPECT_EQ(1 + std::max(left_height, right_height), node->height);
    EXPECT_TRUE(std::abs(right_height - left_height) <= 1);
    check_heights_and_balance(node->left);
    check_heights_and_balance(node->right);
}

template <class TKey, class TValue>
void check_parent_links(AVLNode<TKey, TValue>* node, AVLNode<TKey, TValue>* parent = nullptr) {
    if (!node) { return; }
    EXPECT_EQ(parent, node->parent);
    check_parent_links(node->left, node);
    check_parent_links(node->right, node);
}

template <class TKey, class TValue>
void check_avl_tree(AVLTree<TKey, TValue>& tree) {
    if (!tree.root()) {
        EXPECT_TRUE(tree.is_empty());
        return;
    }
    EXPECT_EQ(nullptr, tree.root()->parent);
    check_heights_and_balance(tree.root());
    check_parent_links(tree.root());
}


TEST(TestAVLTree, default_constructor) {
    // Arrange
    AVLTree<int, int> tree;

    // Act & Assert
    EXPECT_EQ(nullptr, tree.root());
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestAVLTree, insert_root) {
    // Arrange
    AVLTree<int, int> tree;

    // Act
    tree.insert(5, 50);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(5, tree.root()->data.first);
    EXPECT_EQ(50, tree.root()->data.second);
    EXPECT_EQ(nullptr, tree.root()->left);
    EXPECT_EQ(nullptr, tree.root()->right);
    EXPECT_EQ(nullptr, tree.root()->parent);
    EXPECT_EQ(1, tree.root()->height);
    EXPECT_FALSE(tree.is_empty());
    check_avl_tree(tree);
}

TEST(TestAVLTree, insert_left_child_without_rotation) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(5, 50);

    // Act
    tree.insert(3, 30);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(5, tree.root()->data.first);
    ASSERT_NE(nullptr, tree.root()->left);
    EXPECT_EQ(3, tree.root()->left->data.first);
    EXPECT_EQ(30, tree.root()->left->data.second);
    EXPECT_EQ(tree.root(), tree.root()->left->parent);
    EXPECT_EQ(2, tree.root()->height);
    check_avl_tree(tree);
}

TEST(TestAVLTree, insert_right_child_without_rotation) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(5, 50);

    // Act
    tree.insert(7, 70);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(5, tree.root()->data.first);
    ASSERT_NE(nullptr, tree.root()->right);
    EXPECT_EQ(7, tree.root()->right->data.first);
    EXPECT_EQ(70, tree.root()->right->data.second);
    EXPECT_EQ(tree.root(), tree.root()->right->parent);
    EXPECT_EQ(2, tree.root()->height);
    check_avl_tree(tree);
}

TEST(TestAVLTree, insert_LL_rotation) {
 /*		30                         20
        /            ->            / \
      20      right_rotate(G)    10   30
     /
   10                                          */

    // Arrange
    AVLTree<int, int> tree;

    // Act
    tree.insert(30, 300);
    tree.insert(20, 200);
    tree.insert(10, 100);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(20, tree.root()->data.first);
    ASSERT_NE(nullptr, tree.root()->left);
    ASSERT_NE(nullptr, tree.root()->right);
    EXPECT_EQ(10, tree.root()->left->data.first);
    EXPECT_EQ(30, tree.root()->right->data.first);
    check_avl_tree(tree);
}

TEST(TestAVLTree, insert_RR_rotation) {
 /*	 10                           20
       \            ->            / \
       20     left_rotate(G)    10   30
         \
          30                                */

    // Arrange
    AVLTree<int, int> tree;

    // Act
    tree.insert(10, 100);
    tree.insert(20, 200);
    tree.insert(30, 300);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(20, tree.root()->data.first);
    ASSERT_NE(nullptr, tree.root()->left);
    ASSERT_NE(nullptr, tree.root()->right);
    EXPECT_EQ(10, tree.root()->left->data.first);
    EXPECT_EQ(30, tree.root()->right->data.first);
    check_avl_tree(tree);
}

TEST(TestAVLTree, insert_LR_rotation) {
/*	 G(30)                        G(30)                          C(20)
     /              ->             /              ->            /     \
   P(10)	  left_rotate(P)     C(20)     right_rotate(G)    P(10)   G(30)
     \                           /
     C(20)                     P(10)                                        */

    // Arrange
    AVLTree<int, int> tree;

    // Act
    tree.insert(30, 300);
    tree.insert(10, 100);
    tree.insert(20, 200);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(20, tree.root()->data.first);
    ASSERT_NE(nullptr, tree.root()->left);
    ASSERT_NE(nullptr, tree.root()->right);
    EXPECT_EQ(10, tree.root()->left->data.first);
    EXPECT_EQ(30, tree.root()->right->data.first);
    check_avl_tree(tree);
}

TEST(TestAVLTree, insert_RL_rotation) {
/*	  G(10)                          G(10)                           C(20)
       \                ->             \              ->            /     \
        P(30)    right_rotate(P)       C(20)    left_rotate(G)    G(10)   P(30)
       /                                 \
      C(20)                              P(30)                                */

    // Arrange
    AVLTree<int, int> tree;

    // Act
    tree.insert(10, 100);
    tree.insert(30, 300);
    tree.insert(20, 200);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(20, tree.root()->data.first);
    ASSERT_NE(nullptr, tree.root()->left);
    ASSERT_NE(nullptr, tree.root()->right);
    EXPECT_EQ(10, tree.root()->left->data.first);
    EXPECT_EQ(30, tree.root()->right->data.first);
    check_avl_tree(tree);
}

TEST(TestAVLTree, insert_several_elements) {
    // Arrange
    AVLTree<int, int> tree;
    int keys[9] = { 50, 25, 75, 10, 30, 60, 90, 5, 15 };

    // Act
    for (int i = 0; i < 9; ++i) {
        tree.insert(keys[i], keys[i] * 10);
    }

    // Assert
    EXPECT_FALSE(tree.is_empty());
    ASSERT_NE(nullptr, tree.root());
    for (int i = 0; i < 9; ++i) {
        int* value = tree.find(keys[i]);
        ASSERT_NE(nullptr, value);
        EXPECT_EQ(keys[i] * 10, *value);
    }
    check_avl_tree(tree);
}

TEST(TestAVLTree, insert_duplicate_key) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(5, 50);

    // Act & Assert
    ASSERT_ANY_THROW(tree.insert(5, 500));
}

TEST(TestAVLTree, find_in_empty_tree) {
    // Arrange
    AVLTree<int, int> tree;

    // Act & Assert
    EXPECT_EQ(nullptr, tree.find(10));
}

TEST(TestAVLTree, find_root) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(5, 50);

    // Act
    int* value = tree.find(5);

    // Assert
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(50, *value);
}

TEST(TestAVLTree, find_left_element) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(20, 200);
    tree.insert(10, 100);
    tree.insert(30, 300);
    tree.insert(5, 50);

    // Act
    int* value = tree.find(5);

    // Assert
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(50, *value);
}

TEST(TestAVLTree, find_right_element) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(20, 200);
    tree.insert(10, 100);
    tree.insert(30, 300);
    tree.insert(40, 400);

    // Act
    int* value = tree.find(40);

    // Assert
    ASSERT_NE(nullptr, value);
    EXPECT_EQ(400, *value);
}

TEST(TestAVLTree, find_not_exist_element) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);

    // Act & Assert
    EXPECT_EQ(nullptr, tree.find(100));
}

TEST(TestAVLTree, check_can_change_value_by_find_pointer) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(5, 50);

    // Act
    int* value = tree.find(5);
    *value = 500;

    // Assert
    EXPECT_EQ(500, *tree.find(5));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_from_empty_tree) {
    // Arrange
    AVLTree<int, int> tree;

    // Act & Assert
    ASSERT_ANY_THROW(tree.erase(5));
}

TEST(TestAVLTree, erase_not_exist_element) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);
    tree.insert(7, 70);

    // Act & Assert
    ASSERT_ANY_THROW(tree.erase(100));
}

TEST(TestAVLTree, erase_root) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(5, 50);

    // Act
    tree.erase(5);

    // Assert
    EXPECT_EQ(nullptr, tree.root());
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.find(5));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_left_leaf) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(20, 200);
    tree.insert(10, 100);
    tree.insert(30, 300);
    tree.insert(5, 50);
    tree.insert(15, 150);

    // Act
    tree.erase(5);

    // Assert
    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(15));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(30));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_right_leaf) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(20, 200);
    tree.insert(10, 100);
    tree.insert(30, 300);
    tree.insert(25, 250);
    tree.insert(35, 350);

    // Act
    tree.erase(35);

    // Assert
    EXPECT_EQ(nullptr, tree.find(35));
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(25));
    EXPECT_NE(nullptr, tree.find(30));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_node_with_only_left_child) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(20, 200);
    tree.insert(10, 100);
    tree.insert(30, 300);
    tree.insert(5, 50);

    // Act
    tree.erase(10);

    // Assert
    EXPECT_EQ(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(30));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_node_with_only_right_child) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(20, 200);
    tree.insert(10, 100);
    tree.insert(30, 300);
    tree.insert(15, 150);

    // Act
    tree.erase(10);

    // Assert
    EXPECT_EQ(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(15));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(30));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_root_with_only_left_child) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(3, 30);

    // Act
    tree.erase(5);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(3, tree.root()->data.first);
    EXPECT_EQ(nullptr, tree.root()->parent);
    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(3));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_root_with_only_right_child) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(5, 50);
    tree.insert(7, 70);

    // Act
    tree.erase(5);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(7, tree.root()->data.first);
    EXPECT_EQ(nullptr, tree.root()->parent);
    EXPECT_EQ(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(7));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_root_with_two_children) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(20, 200);
    tree.insert(10, 100);
    tree.insert(30, 300);

    // Act
    tree.erase(20);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(30));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_not_root_node_with_two_children) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(50, 500);
    tree.insert(30, 300);
    tree.insert(70, 700);
    tree.insert(20, 200);
    tree.insert(40, 400);
    tree.insert(60, 600);
    tree.insert(80, 800);

    // Act
    tree.erase(30);

    // Assert
    EXPECT_EQ(nullptr, tree.find(30));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(40));
    EXPECT_NE(nullptr, tree.find(50));
    EXPECT_NE(nullptr, tree.find(60));
    EXPECT_NE(nullptr, tree.find(70));
    EXPECT_NE(nullptr, tree.find(80));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_with_LL_rotation_after_deleting) {
    // Arrange
    AVLTree<int, int> tree;
    int keys[7] = { 30, 20, 40, 10, 25, 5, 15 };
    for (int i = 0; i < 7; ++i) {
        tree.insert(keys[i], keys[i] * 10);
    }

    // Act
    tree.erase(40);

    // Assert
    EXPECT_EQ(nullptr, tree.find(40));
    EXPECT_NE(nullptr, tree.find(30));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(10));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_with_RR_rotation_after_deleting) {
    // Arrange
    AVLTree<int, int> tree;
    int keys[7] = { 30, 20, 40, 35, 50, 45, 60 };
    for (int i = 0; i < 7; ++i) {
        tree.insert(keys[i], keys[i] * 10);
    }

    // Act
    tree.erase(20);

    // Assert
    EXPECT_EQ(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(30));
    EXPECT_NE(nullptr, tree.find(40));
    EXPECT_NE(nullptr, tree.find(60));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_with_LR_rotation_after_deleting) {
    // Arrange
    AVLTree<int, int> tree;
    int keys[7] = { 50, 30, 70, 20, 40, 35, 45 };
    for (int i = 0; i < 7; ++i) {
        tree.insert(keys[i], keys[i] * 10);
    }

    // Act
    tree.erase(70);

    // Assert
    EXPECT_EQ(nullptr, tree.find(70));
    EXPECT_NE(nullptr, tree.find(50));
    EXPECT_NE(nullptr, tree.find(30));
    EXPECT_NE(nullptr, tree.find(40));
    check_avl_tree(tree);
}

TEST(TestAVLTree, erase_with_RL_rotation_after_deleting) {
    // Arrange
    AVLTree<int, int> tree;
    int keys[7] = { 50, 30, 70, 60, 80, 55, 65 };
    for (int i = 0; i < 7; ++i) {
        tree.insert(keys[i], keys[i] * 10);
    }

    // Act
    tree.erase(30);

    // Assert
    EXPECT_EQ(nullptr, tree.find(30));
    EXPECT_NE(nullptr, tree.find(50));
    EXPECT_NE(nullptr, tree.find(60));
    EXPECT_NE(nullptr, tree.find(70));
    check_avl_tree(tree);
}

TEST(TestAVLTree, clear_empty_tree) {
    // Arrange
    AVLTree<int, int> tree;

    // Act
    tree.clear();

    // Assert
    EXPECT_TRUE(tree.is_empty());
    EXPECT_EQ(nullptr, tree.root());
}

TEST(TestAVLTree, clear_not_empty_tree) {
    // Arrange
    AVLTree<int, int> tree;
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

TEST(TestAVLTree, check_is_empty_return_true) {
    // Arrange
    AVLTree<int, int> tree;

    // Act & Assert
    EXPECT_TRUE(tree.is_empty());
}

TEST(TestAVLTree, check_is_empty_return_false) {
    // Arrange
    AVLTree<int, int> tree;

    // Act
    tree.insert(1, 10);

    // Assert
    EXPECT_FALSE(tree.is_empty());
}

TEST(TestAVLTree, print_lcr_not_empty_tree) {
    // Arrange
    AVLTree<int, int> tree;
    tree.insert(20, 200);
    tree.insert(10, 100);
    tree.insert(30, 300);
    tree.insert(5, 50);
    tree.insert(15, 150);

    // Act
    testing::internal::CaptureStdout();
    tree.print_lcr();
    std::string output = testing::internal::GetCapturedStdout();

    // Assert
    EXPECT_EQ("50 100 150 200 300 ", output);
    check_avl_tree(tree);
}

TEST(TestAVLTree, big_tree_insert_and_find_all_elements) {
    // Arrange
    AVLTree<int, int> tree;
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
    for (int i = 0; i < 31; ++i) {
        int* value = tree.find(keys[i]);
        ASSERT_NE(nullptr, value);
        EXPECT_EQ(keys[i] * 10, *value);
    }
    check_avl_tree(tree);
}

TEST(TestAVLTree, big_tree_erase_many_different_cases) {
    // Arrange
    AVLTree<int, int> tree;
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
    tree.erase(1);
    tree.erase(5);
    tree.erase(90);
    tree.erase(25);
    tree.erase(50);

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
    check_avl_tree(tree);
}

TEST(TestAVLTree, big_tree_clear) {
    // Arrange
    AVLTree<int, int> tree;
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

TEST(TestAVLTree, double_rotation_erase_40_and_root_becomes_80) {
    // Arrange
    AVLTree<int, int> tree;
    int keys[13] = { 50, 30, 80, 20, 40, 60, 100, 10, 55, 70, 90, 110, 120 };
    for (int i = 0; i < 13; ++i) { tree.insert(keys[i], keys[i] * 10); }

    // Act
    tree.erase(40);

    // Assert
    EXPECT_EQ(nullptr, tree.find(40));
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(80, tree.root()->data.first);
    EXPECT_EQ(nullptr, tree.root()->parent);
    ASSERT_NE(nullptr, tree.root()->left);
    ASSERT_NE(nullptr, tree.root()->right);
    EXPECT_EQ(50, tree.root()->left->data.first);
    EXPECT_EQ(100, tree.root()->right->data.first);
    ASSERT_NE(nullptr, tree.root()->left->left);
    ASSERT_NE(nullptr, tree.root()->left->right);
    EXPECT_EQ(20, tree.root()->left->left->data.first);
    EXPECT_EQ(60, tree.root()->left->right->data.first);
    ASSERT_NE(nullptr, tree.root()->left->left->left);
    ASSERT_NE(nullptr, tree.root()->left->left->right);
    EXPECT_EQ(10, tree.root()->left->left->left->data.first);
    EXPECT_EQ(30, tree.root()->left->left->right->data.first);
    ASSERT_NE(nullptr, tree.root()->left->right->left);
    ASSERT_NE(nullptr, tree.root()->left->right->right);
    EXPECT_EQ(55, tree.root()->left->right->left->data.first);
    EXPECT_EQ(70, tree.root()->left->right->right->data.first);
    ASSERT_NE(nullptr, tree.root()->right->left);
    ASSERT_NE(nullptr, tree.root()->right->right);
    EXPECT_EQ(90, tree.root()->right->left->data.first);
    EXPECT_EQ(110, tree.root()->right->right->data.first);
    ASSERT_NE(nullptr, tree.root()->right->right->right);
    EXPECT_EQ(120, tree.root()->right->right->right->data.first);
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(30));
    EXPECT_NE(nullptr, tree.find(50));
    EXPECT_NE(nullptr, tree.find(55));
    EXPECT_NE(nullptr, tree.find(60));
    EXPECT_NE(nullptr, tree.find(70));
    EXPECT_NE(nullptr, tree.find(80));
    EXPECT_NE(nullptr, tree.find(90));
    EXPECT_NE(nullptr, tree.find(100));
    EXPECT_NE(nullptr, tree.find(110));
    EXPECT_NE(nullptr, tree.find(120));
    EXPECT_EQ(100, *tree.find(10));
    EXPECT_EQ(200, *tree.find(20));
    EXPECT_EQ(300, *tree.find(30));
    EXPECT_EQ(500, *tree.find(50));
    EXPECT_EQ(550, *tree.find(55));
    EXPECT_EQ(600, *tree.find(60));
    EXPECT_EQ(700, *tree.find(70));
    EXPECT_EQ(800, *tree.find(80));
    EXPECT_EQ(900, *tree.find(90));
    EXPECT_EQ(1000, *tree.find(100));
    EXPECT_EQ(1100, *tree.find(110));
    EXPECT_EQ(1200, *tree.find(120));
    check_avl_tree(tree);
}

TEST(TestAVLTree, delayed_rotation_after_insert_5) {
    // Arrange
    AVLTree<int, int> tree;
    int keys[11] = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45 };
    for (int i = 0; i < 11; ++i) { tree.insert(keys[i], keys[i] * 10); }

    // Act
    tree.insert(5, 50);

    // Assert
    ASSERT_NE(nullptr, tree.root());
    EXPECT_EQ(30, tree.root()->data.first);
    EXPECT_EQ(nullptr, tree.root()->parent);
    ASSERT_NE(nullptr, tree.root()->left);
    ASSERT_NE(nullptr, tree.root()->right);
    EXPECT_EQ(20, tree.root()->left->data.first);
    EXPECT_EQ(50, tree.root()->right->data.first);
    ASSERT_NE(nullptr, tree.root()->left->left);
    ASSERT_NE(nullptr, tree.root()->left->right);
    EXPECT_EQ(10, tree.root()->left->left->data.first);
    EXPECT_EQ(25, tree.root()->left->right->data.first);
    ASSERT_NE(nullptr, tree.root()->left->left->left);
    EXPECT_EQ(5, tree.root()->left->left->left->data.first);
    ASSERT_NE(nullptr, tree.root()->right->left);
    ASSERT_NE(nullptr, tree.root()->right->right);
    EXPECT_EQ(40, tree.root()->right->left->data.first);
    EXPECT_EQ(70, tree.root()->right->right->data.first);
    ASSERT_NE(nullptr, tree.root()->right->left->left);
    ASSERT_NE(nullptr, tree.root()->right->left->right);
    EXPECT_EQ(35, tree.root()->right->left->left->data.first);
    EXPECT_EQ(45, tree.root()->right->left->right->data.first);
    ASSERT_NE(nullptr, tree.root()->right->right->left);
    ASSERT_NE(nullptr, tree.root()->right->right->right);
    EXPECT_EQ(60, tree.root()->right->right->left->data.first);
    EXPECT_EQ(80, tree.root()->right->right->right->data.first);
    EXPECT_NE(nullptr, tree.find(5));
    EXPECT_NE(nullptr, tree.find(10));
    EXPECT_NE(nullptr, tree.find(20));
    EXPECT_NE(nullptr, tree.find(25));
    EXPECT_NE(nullptr, tree.find(30));
    EXPECT_NE(nullptr, tree.find(35));
    EXPECT_NE(nullptr, tree.find(40));
    EXPECT_NE(nullptr, tree.find(45));
    EXPECT_NE(nullptr, tree.find(50));
    EXPECT_NE(nullptr, tree.find(60));
    EXPECT_NE(nullptr, tree.find(70));
    EXPECT_NE(nullptr, tree.find(80));
    EXPECT_EQ(50, *tree.find(5));
    EXPECT_EQ(100, *tree.find(10));
    EXPECT_EQ(200, *tree.find(20));
    EXPECT_EQ(250, *tree.find(25));
    EXPECT_EQ(300, *tree.find(30));
    EXPECT_EQ(350, *tree.find(35));
    EXPECT_EQ(400, *tree.find(40));
    EXPECT_EQ(450, *tree.find(45));
    EXPECT_EQ(500, *tree.find(50));
    EXPECT_EQ(600, *tree.find(60));
    EXPECT_EQ(700, *tree.find(70));
    EXPECT_EQ(800, *tree.find(80));
    check_avl_tree(tree);
}