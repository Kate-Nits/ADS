// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_rbtree/rbtree.h"

#include <algorithm>
#include <cmath>
#include <string>

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

template <class TKey, class TValue>
int real_height(RBNode<TKey, TValue>* node) {
	if (!node) { return 0; }
	return 1 + std::max(real_height(node->left), real_height(node->right));
}

template <class TKey, class TValue>
int check_black_height(RBNode<TKey, TValue>* node) {
	if (!node) { return 1; }
	int left_black_height = check_black_height(node->left);
	int right_black_height = check_black_height(node->right);
	EXPECT_EQ(left_black_height, right_black_height);
	if (node->color == black) { return left_black_height + 1; }
	return left_black_height;
}

template <class TKey, class TValue>
void check_red_nodes_have_black_children(RBNode<TKey, TValue>* node) {
	if (!node) { return; }
	if (node->color == red) {
		if (node->left) {
			EXPECT_EQ(black, node->left->color);
		}
		if (node->right) {
			EXPECT_EQ(black, node->right->color);
		}
	}
	check_red_nodes_have_black_children(node->left);
	check_red_nodes_have_black_children(node->right);
}

template <class TKey, class TValue>
void check_parent_links(RBNode<TKey, TValue>* node, RBNode<TKey, TValue>* parent = nullptr) {
	if (!node) { return; }
	EXPECT_EQ(parent, node->parent);
	check_parent_links(node->left, node);
	check_parent_links(node->right, node);
}

template <class TKey, class TValue>
void check_on_bst(RBNode<TKey, TValue>* node, const TKey* min_key = nullptr, const TKey* max_key = nullptr) {
	if (!node) { return; }
	if (min_key) {
		EXPECT_TRUE(*min_key < node->data.first);
	}
	if (max_key) {
		EXPECT_TRUE(node->data.first < *max_key);
	}
	check_on_bst(node->left, min_key, &node->data.first);
	check_on_bst(node->right, &node->data.first, max_key);
}

template <class TKey, class TValue>
void check_rb_tree(RBTree<TKey, TValue>& tree) {
	if (!tree.root()) {
		EXPECT_TRUE(tree.is_empty());
		return;
	}
	EXPECT_EQ(black, tree.root()->color);
	EXPECT_EQ(nullptr, tree.root()->parent);
	check_on_bst(tree.root());
	check_parent_links(tree.root());
	check_red_nodes_have_black_children(tree.root());
	check_black_height(tree.root());
}

TEST(TestRBTree, default_constructor) {
	// Arrange
	RBTree<int, int> tree;

	// Act & Assert
	EXPECT_EQ(nullptr, tree.root());
	EXPECT_TRUE(tree.is_empty());
}

TEST(TestRBTree, insert_root) {
	// Arrange
	RBTree<int, int> tree;

	// Act
	tree.insert(5, 50);

	// Assert
	ASSERT_NE(nullptr, tree.root());
	EXPECT_EQ(5, tree.root()->data.first);
	EXPECT_EQ(50, tree.root()->data.second);
	EXPECT_EQ(nullptr, tree.root()->left);
	EXPECT_EQ(nullptr, tree.root()->right);
	EXPECT_EQ(nullptr, tree.root()->parent);
	EXPECT_EQ(black, tree.root()->color);
	EXPECT_FALSE(tree.is_empty());
	check_rb_tree(tree);
}

TEST(TestRBTree, insert_left_child) {
	// Arrange
	RBTree<int, int> tree;
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
	check_rb_tree(tree);
}

TEST(TestRBTree, insert_right_child) {
	// Arrange
	RBTree<int, int> tree;
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
	check_rb_tree(tree);
}

TEST(TestRBTree, insert_duplicate_key) {
	// Arrange
	RBTree<int, int> tree;
	tree.insert(5, 50);

	// Act & Assert
	ASSERT_ANY_THROW(tree.insert(5, 500));
}

TEST(TestRBTree, insert_LL_rotation) {
	// Arrange
	RBTree<int, int> tree;

	// Act
	tree.insert(30, 300);
	tree.insert(20, 200);
	tree.insert(10, 100);

	// Assert
	ASSERT_NE(nullptr, tree.root());
	EXPECT_EQ(20, tree.root()->data.first);
	EXPECT_NE(nullptr, tree.find(10));
	EXPECT_NE(nullptr, tree.find(20));
	EXPECT_NE(nullptr, tree.find(30));
	check_rb_tree(tree);
}

TEST(TestRBTree, insert_RR_rotation) {
	// Arrange
	RBTree<int, int> tree;

	// Act
	tree.insert(10, 100);
	tree.insert(20, 200);
	tree.insert(30, 300);

	// Assert
	ASSERT_NE(nullptr, tree.root());
	EXPECT_EQ(20, tree.root()->data.first);
	EXPECT_NE(nullptr, tree.find(10));
	EXPECT_NE(nullptr, tree.find(20));
	EXPECT_NE(nullptr, tree.find(30));
	check_rb_tree(tree);
}

TEST(TestRBTree, insert_LR_rotation) {
	// Arrange
	RBTree<int, int> tree;

	// Act
	tree.insert(30, 300);
	tree.insert(10, 100);
	tree.insert(20, 200);

	// Assert
	ASSERT_NE(nullptr, tree.root());
	EXPECT_EQ(20, tree.root()->data.first);
	EXPECT_NE(nullptr, tree.find(10));
	EXPECT_NE(nullptr, tree.find(20));
	EXPECT_NE(nullptr, tree.find(30));
	check_rb_tree(tree);
}

TEST(TestRBTree, insert_RL_rotation) {
	// Arrange
	RBTree<int, int> tree;

	// Act
	tree.insert(10, 100);
	tree.insert(30, 300);
	tree.insert(20, 200);

	// Assert
	ASSERT_NE(nullptr, tree.root());
	EXPECT_EQ(20, tree.root()->data.first);
	EXPECT_NE(nullptr, tree.find(10));
	EXPECT_NE(nullptr, tree.find(20));
	EXPECT_NE(nullptr, tree.find(30));
	check_rb_tree(tree);
}

TEST(TestRBTree, insert_recolor_case) {
	// Arrange
	RBTree<int, int> tree;

	// Act
	tree.insert(10, 100);
	tree.insert(5, 50);
	tree.insert(15, 150);
	tree.insert(3, 30);

	// Assert
	EXPECT_NE(nullptr, tree.find(10));
	EXPECT_NE(nullptr, tree.find(5));
	EXPECT_NE(nullptr, tree.find(15));
	EXPECT_NE(nullptr, tree.find(3));
	check_rb_tree(tree);
}

TEST(TestRBTree, insert_several_elements) {
	// Arrange
	RBTree<int, int> tree;
	int keys[9] = { 50, 25, 75, 10, 30, 60, 90, 5, 15 };

	// Act
	for (int i = 0; i < 9; ++i) {
		tree.insert(keys[i], keys[i] * 10);
	}

	// Assert
	EXPECT_FALSE(tree.is_empty());
	for (int i = 0; i < 9; ++i) {
		int* value = tree.find(keys[i]);
		ASSERT_NE(nullptr, value);
		EXPECT_EQ(keys[i] * 10, *value);
	}
	check_rb_tree(tree);
}

TEST(TestRBTree, find_in_empty_tree) {
	// Arrange
	RBTree<int, int> tree;

	// Act & Assert
	EXPECT_EQ(nullptr, tree.find(10));
}

TEST(TestRBTree, find_root) {
	// Arrange
	RBTree<int, int> tree;
	tree.insert(5, 50);

	// Act
	int* value = tree.find(5);

	// Assert
	ASSERT_NE(nullptr, value);
	EXPECT_EQ(50, *value);
}

TEST(TestRBTree, find_left_element) {
	// Arrange
	RBTree<int, int> tree;
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

TEST(TestRBTree, find_right_element) {
	// Arrange
	RBTree<int, int> tree;
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

TEST(TestRBTree, find_not_exist_element) {
	// Arrange
	RBTree<int, int> tree;
	tree.insert(5, 50);
	tree.insert(3, 30);
	tree.insert(7, 70);

	// Act & Assert
	EXPECT_EQ(nullptr, tree.find(100));
}

TEST(TestRBTree, erase_from_empty_tree) {
	// Arrange
	RBTree<int, int> tree;

	// Act & Assert
	ASSERT_ANY_THROW(tree.erase(5));
}

TEST(TestRBTree, erase_not_exist_element) {
	// Arrange
	RBTree<int, int> tree;
	tree.insert(5, 50);
	tree.insert(3, 30);
	tree.insert(7, 70);

	// Act & Assert
	ASSERT_ANY_THROW(tree.erase(100));
}

TEST(TestRBTree, erase_root) {
	// Arrange
	RBTree<int, int> tree;
	tree.insert(5, 50);

	// Act
	tree.erase(5);

	// Assert
	EXPECT_EQ(nullptr, tree.root());
	EXPECT_TRUE(tree.is_empty());
	EXPECT_EQ(nullptr, tree.find(5));
	check_rb_tree(tree);
}

TEST(TestRBTree, erase_red_leaf) {
	// Arrange
	RBTree<int, int> tree;
	tree.insert(10, 100);
	tree.insert(5, 50);
	tree.insert(15, 150);

	// Act
	tree.erase(5);
	// Assert
	EXPECT_EQ(nullptr, tree.find(5));
	EXPECT_NE(nullptr, tree.find(10));
	EXPECT_NE(nullptr, tree.find(15));
	check_rb_tree(tree);
}

TEST(TestRBTree, erase_black_leaf_with_fix) {
	// Arrange
	RBTree<int, int> tree;
	int keys[7] = { 10, 5, 15, 3, 7, 12, 18 };

	for (int i = 0; i < 7; ++i) {
		tree.insert(keys[i], keys[i] * 10);
	}

	// Act
	tree.erase(3);
	tree.erase(7);
	tree.erase(5);

	// Assert
	EXPECT_EQ(nullptr, tree.find(3));
	EXPECT_EQ(nullptr, tree.find(7));
	EXPECT_EQ(nullptr, tree.find(5));
	EXPECT_NE(nullptr, tree.find(10));
	EXPECT_NE(nullptr, tree.find(15));
	check_rb_tree(tree);
}

TEST(TestRBTree, erase_node_with_only_left_child) {
	// Arrange
	RBTree<int, int> tree;
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
	check_rb_tree(tree);
}

TEST(TestRBTree, erase_node_with_only_right_child) {
	// Arrange
	RBTree<int, int> tree;
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
	check_rb_tree(tree);
}

TEST(TestRBTree, erase_node_with_two_children) {
	// Arrange
	RBTree<int, int> tree;
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
	check_rb_tree(tree);
}

TEST(TestRBTree, erase_root_with_only_left_child) {
	// Arrange
	RBTree<int, int> tree;
	tree.insert(5, 50);
	tree.insert(3, 30);

	// Act
	tree.erase(5);

	// Assert
	ASSERT_NE(nullptr, tree.root());
	EXPECT_EQ(3, tree.root()->data.first);
	EXPECT_EQ(black, tree.root()->color);
	EXPECT_EQ(nullptr, tree.root()->parent);
	EXPECT_EQ(nullptr, tree.find(5));
	EXPECT_NE(nullptr, tree.find(3));
	check_rb_tree(tree);
}

TEST(TestRBTree, erase_root_with_only_right_child) {
	// Arrange
	RBTree<int, int> tree;
	tree.insert(5, 50);
	tree.insert(7, 70);

	// Act
	tree.erase(5);

	// Assert
	ASSERT_NE(nullptr, tree.root());
	EXPECT_EQ(7, tree.root()->data.first);
	EXPECT_EQ(black, tree.root()->color);
	EXPECT_EQ(nullptr, tree.root()->parent);
	EXPECT_EQ(nullptr, tree.find(5));
	EXPECT_NE(nullptr, tree.find(7));
	check_rb_tree(tree);
}

TEST(TestRBTree, erase_root_with_two_children) {
	// Arrange
	RBTree<int, int> tree;
	tree.insert(20, 200);
	tree.insert(10, 100);
	tree.insert(30, 300);

	// Act
	tree.erase(20);

	// Assert
	EXPECT_EQ(nullptr, tree.find(20));
	EXPECT_NE(nullptr, tree.find(10));
	EXPECT_NE(nullptr, tree.find(30));
	check_rb_tree(tree);
}

TEST(TestRBTree, erase_many_elements) {
	// Arrange
	RBTree<int, int> tree;
	int keys[15] = { 50, 25, 75, 10, 30, 60, 90, 5, 15, 27, 35, 55, 65, 80, 95 };

	for (int i = 0; i < 15; ++i) {
		tree.insert(keys[i], keys[i]);
	}

	// Act
	tree.erase(5);
	tree.erase(75);
	tree.erase(25);
	tree.erase(50);

	// Assert
	EXPECT_EQ(nullptr, tree.find(5));
	EXPECT_EQ(nullptr, tree.find(75));
	EXPECT_EQ(nullptr, tree.find(25));
	EXPECT_EQ(nullptr, tree.find(50));
	EXPECT_NE(nullptr, tree.find(10));
	EXPECT_NE(nullptr, tree.find(15));
	EXPECT_NE(nullptr, tree.find(27));
	EXPECT_NE(nullptr, tree.find(30));
	EXPECT_NE(nullptr, tree.find(60));
	EXPECT_NE(nullptr, tree.find(90));
	check_rb_tree(tree);
}

TEST(TestRBTree, clear_empty_tree) {
	// Arrange
	RBTree<int, int> tree;

	// Act
	tree.clear();

	// Assert
	EXPECT_TRUE(tree.is_empty());
	EXPECT_EQ(nullptr, tree.root());
}

TEST(TestRBTree, clear_not_empty_tree) {
	// Arrange
	RBTree<int, int> tree;
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

TEST(TestRBTree, check_is_empty_return_true) {
	// Arrange
	RBTree<int, int> tree;

	// Act & Assert
	EXPECT_TRUE(tree.is_empty());
}

TEST(TestRBTree, check_is_empty_return_false) {
	// Arrange
	RBTree<int, int> tree;

	// Act
	tree.insert(1, 10);

	// Assert
	EXPECT_FALSE(tree.is_empty());
}

TEST(TestRBTree, print_lcr_not_empty_tree) {
	// Arrange
	RBTree<int, int> tree;
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
	check_rb_tree(tree);
}

TEST(TestRBTree, big_tree_insert_and_find_all_elements) {
	// Arrange
	RBTree<int, int> tree;
	int keys[31] = {
	 50, 25, 75, 10, 30, 60, 90,
	 5, 15, 27, 35, 55, 65, 80, 95,
	 1, 6, 12, 18, 26, 28, 33, 37,
	 53, 57, 63, 67, 78, 82, 93, 97
	};

	// Act
	for (int i = 0; i < 31; ++i) {
		tree.insert(keys[i], keys[i] * 10);
		check_rb_tree(tree);
	}

	// Assert
	EXPECT_FALSE(tree.is_empty());
	for (int i = 0; i < 31; ++i) {
		int* value = tree.find(keys[i]);
		ASSERT_NE(nullptr, value);
		EXPECT_EQ(keys[i] * 10, *value);
	}
	check_rb_tree(tree);
}

TEST(TestRBTree, big_tree_erase_many_different_cases) {
	// Arrange
	RBTree<int, int> tree;
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
	check_rb_tree(tree);

	tree.erase(5);
	check_rb_tree(tree);

	tree.erase(90);
	check_rb_tree(tree);

	tree.erase(25);
	check_rb_tree(tree);

	tree.erase(50);
	check_rb_tree(tree);

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
	check_rb_tree(tree);
}

TEST(TestRBTree, big_tree_clear) {
	// Arrange
	RBTree<int, int> tree;

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

TEST(TestRBTree, double_rotations_erase_10_and_root_becomes_60) {
	// Arrange
	RBTree<int, int> tree;
	int keys[7] = { 10, 15, 115, 60, 30, 50, 45 };
	for (int i = 0; i < 7; ++i) { tree.insert(keys[i], keys[i] * 10); }

	// Act
	tree.erase(10);

	// Assert
	EXPECT_EQ(nullptr, tree.find(10));
	ASSERT_NE(nullptr, tree.root());
	EXPECT_EQ(60, tree.root()->data.first);
	EXPECT_EQ(black, tree.root()->color);
	EXPECT_EQ(nullptr, tree.root()->parent);
	ASSERT_NE(nullptr, tree.root()->left);
	ASSERT_NE(nullptr, tree.root()->right);
	EXPECT_EQ(45, tree.root()->left->data.first);
	EXPECT_EQ(115, tree.root()->right->data.first);
	EXPECT_EQ(red, tree.root()->left->color);
	EXPECT_EQ(black, tree.root()->right->color);
	EXPECT_NE(nullptr, tree.find(15));
	EXPECT_NE(nullptr, tree.find(30));
	EXPECT_NE(nullptr, tree.find(45));
	EXPECT_NE(nullptr, tree.find(50));
	EXPECT_NE(nullptr, tree.find(60));
	EXPECT_NE(nullptr, tree.find(115));
	EXPECT_EQ(150, *tree.find(15));
	EXPECT_EQ(300, *tree.find(30));
	EXPECT_EQ(450, *tree.find(45));
	EXPECT_EQ(500, *tree.find(50));
	EXPECT_EQ(600, *tree.find(60));
	EXPECT_EQ(1150, *tree.find(115));
	check_rb_tree(tree);
}

TEST(TestRBTree, delayed_rotation_after_insert_5_and_root_becomes_30) {
	// Arrange
	RBTree<int, int> tree;
	int keys[11] = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45 };
	for (int i = 0; i < 11; ++i) { tree.insert(keys[i], keys[i] * 10); }

	// Act
	tree.insert(5, 50);

	// Assert
	ASSERT_NE(nullptr, tree.root());
	EXPECT_EQ(30, tree.root()->data.first);
	EXPECT_EQ(black, tree.root()->color);
	EXPECT_EQ(nullptr, tree.root()->parent);
	ASSERT_NE(nullptr, tree.root()->left);
	ASSERT_NE(nullptr, tree.root()->right);
	EXPECT_EQ(20, tree.root()->left->data.first);
	EXPECT_EQ(50, tree.root()->right->data.first);
	EXPECT_EQ(red, tree.root()->left->color);
	EXPECT_EQ(red, tree.root()->right->color);
	EXPECT_EQ(tree.root(), tree.root()->left->parent);
	EXPECT_EQ(tree.root(), tree.root()->right->parent);
	ASSERT_NE(nullptr, tree.root()->left->left);
	ASSERT_NE(nullptr, tree.root()->left->right);
	EXPECT_EQ(10, tree.root()->left->left->data.first);
	EXPECT_EQ(25, tree.root()->left->right->data.first);
	EXPECT_EQ(black, tree.root()->left->left->color);
	EXPECT_EQ(black, tree.root()->left->right->color);
	ASSERT_NE(nullptr, tree.root()->left->left->left);
	EXPECT_EQ(5, tree.root()->left->left->left->data.first);
	EXPECT_EQ(red, tree.root()->left->left->left->color);
	ASSERT_NE(nullptr, tree.root()->right->left);
	ASSERT_NE(nullptr, tree.root()->right->right);
	EXPECT_EQ(40, tree.root()->right->left->data.first);
	EXPECT_EQ(70, tree.root()->right->right->data.first);
	EXPECT_EQ(black, tree.root()->right->left->color);
	EXPECT_EQ(black, tree.root()->right->right->color);
	ASSERT_NE(nullptr, tree.root()->right->left->left);
	ASSERT_NE(nullptr, tree.root()->right->left->right);
	EXPECT_EQ(35, tree.root()->right->left->left->data.first);
	EXPECT_EQ(45, tree.root()->right->left->right->data.first);
	EXPECT_EQ(red, tree.root()->right->left->left->color);
	EXPECT_EQ(red, tree.root()->right->left->right->color);
	ASSERT_NE(nullptr, tree.root()->right->right->left);
	ASSERT_NE(nullptr, tree.root()->right->right->right);
	EXPECT_EQ(60, tree.root()->right->right->left->data.first);
	EXPECT_EQ(80, tree.root()->right->right->right->data.first);
	EXPECT_EQ(red, tree.root()->right->right->left->color);
	EXPECT_EQ(red, tree.root()->right->right->right->color);
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
	check_rb_tree(tree);
}