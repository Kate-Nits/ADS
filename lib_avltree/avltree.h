// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_AVLTREE_AVLTREE_H
#define LIB_AVLTREE_AVLTREE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cmath>

#include "../lib_bstree/bstree.h"
#include "../lib_pair/pair.h"
#include "../lib_tvector/tvector.h"

template <class TKey, class TValue>
struct AVLNode {
	Pair<TKey, TValue> data;
	AVLNode<TKey, TValue>* left;
	AVLNode<TKey, TValue>* right;
	AVLNode<TKey, TValue>* parent;
	int height;

	AVLNode();
	AVLNode(const TKey& key, const TValue& value, AVLNode<TKey, TValue>* l = nullptr, AVLNode<TKey, TValue>* r = nullptr, AVLNode<TKey, TValue>* p = nullptr, int h = 1);
};

template <class TKey, class TValue>
AVLNode<TKey, TValue>::AVLNode() : data(), left(nullptr), right(nullptr), parent(nullptr), height(1) {}

template <class TKey, class TValue>
AVLNode<TKey, TValue>::AVLNode(const TKey& key, const TValue& value, AVLNode<TKey, TValue>* l, AVLNode<TKey, TValue>* r, AVLNode<TKey, TValue>* p, int h)
	: data(key, value), left(l), right(r), parent(p), height(h) {}

template <class TKey, class TValue>
class AVLTree {
	AVLNode<TKey, TValue>* _root;
public:
	AVLTree();
	~AVLTree();

	AVLNode<TKey, TValue>* root() const noexcept;

	void insert(const TKey& key, const TValue& value);
	TValue* find(const TKey& key) const noexcept;
	void erase(const TKey& key);
	void clear() noexcept;
	bool is_empty() const noexcept;

	void print_lcr() const noexcept;
	void print() const noexcept;
private:
	int get_height(AVLNode<TKey, TValue>* node) const noexcept;
	int get_balance(AVLNode<TKey, TValue>* node) const noexcept;
	void update_height(AVLNode<TKey, TValue>* node) noexcept;

	AVLNode<TKey, TValue>* find_node(const TKey& key) const noexcept;
	AVLNode<TKey, TValue>* find_max_left(AVLNode<TKey, TValue>* node) const noexcept;

	AVLNode<TKey, TValue>* left_rotate(AVLNode<TKey, TValue>* node) noexcept;
	AVLNode<TKey, TValue>* right_rotate(AVLNode<TKey, TValue>* node) noexcept;

	AVLNode<TKey, TValue>* RR(AVLNode<TKey, TValue>* node) noexcept;
	AVLNode<TKey, TValue>* LL(AVLNode<TKey, TValue>* node) noexcept;
	AVLNode<TKey, TValue>* RL(AVLNode<TKey, TValue>* node) noexcept;
	AVLNode<TKey, TValue>* LR(AVLNode<TKey, TValue>* node) noexcept;

	AVLNode<TKey, TValue>* recover_balance(AVLNode<TKey, TValue>* node) noexcept;
	void recover_balance_from(AVLNode<TKey, TValue>* node) noexcept;

	AVLNode<TKey, TValue>* erase_node(AVLNode<TKey, TValue>* node) noexcept;
	void clear_rec(AVLNode<TKey, TValue>* node) noexcept;
	void print_lcr_rec(AVLNode<TKey, TValue>* node) const noexcept;
	int get_height_for_print(AVLNode<TKey, TValue>* node) const noexcept;
	void matrix_for_print(AVLNode<TKey, TValue>* node, TVector<TVector<std::string>>& matrix, int level, int left, int right) const noexcept;
};

template <class TKey, class TValue>
AVLTree<TKey, TValue>::AVLTree() : _root(nullptr) {}

template <class TKey, class TValue>
AVLTree<TKey, TValue>::~AVLTree() {}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::root() const noexcept {
	return _root;
}

template <class TKey, class TValue>
void  AVLTree<TKey, TValue>::clear_rec(AVLNode<TKey, TValue>* node) noexcept {
	if (!node) { return; }
	clear_rec(node->left);
	clear_rec(node->right);
	delete node;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::clear() noexcept {
	clear_rec(_root);
	_root = nullptr;
}

template <class TKey, class TValue>
bool AVLTree<TKey, TValue>::is_empty() const noexcept {
	return _root == nullptr;
}

template <class TKey, class TValue>
int AVLTree<TKey, TValue>::get_height(AVLNode<TKey, TValue>* node) const noexcept {
	if (!node) { return 0; }
	return node->height;
}

template <class TKey, class TValue>
int AVLTree<TKey, TValue>::get_balance(AVLNode<TKey, TValue>* node) const noexcept {
	if (!node) { return 0; }
	return get_height(node->right) - get_height(node->left);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::update_height(AVLNode<TKey, TValue>* node) noexcept { //
	if (!node) { return; }
	int left_height = get_height(node->left);
	int right_height = get_height(node->right);
	node->height = 1 + (std::max)(left_height, right_height);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_node(const TKey& key) const noexcept {
	AVLNode<TKey, TValue>* cur = this->_root;
	while (cur) {
		if (cur->data.first == key) {
			return cur;
		}
		else if (cur->data.first > key) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	return nullptr;
}

template <class TKey, class TValue>
TValue* AVLTree<TKey, TValue>::find(const TKey& key) const noexcept {
	AVLNode<TKey, TValue>* node = find_node(key);
	if (!node) { return nullptr; }
	return &node->data.second;
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::left_rotate(AVLNode<TKey, TValue>* node) noexcept {
/*	  G                            P
	   \            ->            / \
		P     left_rotate(G)     G   C
	   / \                        \
	  T   C                        T      */
	AVLNode<TKey, TValue>* G = node;
	AVLNode<TKey, TValue>* P = G->right;
	AVLNode<TKey, TValue>* T = P->left;
	AVLNode<TKey, TValue>* parent = G->parent;
	P->parent = parent;
	if (!parent) {
		this->_root = P;
	}
	else if (parent->left == G) {
		parent->left = P;
	}
	else {
		parent->right = P;
	}
	G->right = T;
	if (T) { T->parent = G; }
	P->left = G;
	G->parent = P;
	update_height(G);
	update_height(P);
	return P;
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::right_rotate(AVLNode<TKey, TValue>* node) noexcept {
/*		G                          P
	   /            ->            / \
	  P      right_rotate(G)     C   G
	 / \                            /
	C   T                          T         */
	AVLNode<TKey, TValue>* G = node;
	AVLNode<TKey, TValue>* P = G->left;
	AVLNode<TKey, TValue>* T = P->right;
	AVLNode<TKey, TValue>* parent = G->parent;
	P->parent = parent;
	if (!parent) {
		this->_root = P;
	}
	else if (parent->left == G) {
		parent->left = P;
	}
	else {
		parent->right = P;
	}
	G->left = T;
	if (T) { T->parent = G; }
	P->right = G;
	G->parent = P;
	update_height(G);
	update_height(P);
	return P;
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::RR(AVLNode<TKey, TValue>* node) noexcept {
/*	  G                            P               
	   \            ->            / \
		P     left_rotate(G)     G   C
		 \
		  C                                */
	return left_rotate(node);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::LL(AVLNode<TKey, TValue>* node) noexcept {
/*		G                          P
	   /            ->            / \     
	  P      right_rotate(G)     C   G 
	 /
	C                                          */
	return right_rotate(node);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::RL(AVLNode<TKey, TValue>* node) noexcept {
/*	  G                          G                          C  
	   \            ->            \            ->          / \  
		P    right_rotate(P)       C    left_rotate(G)    G   P
	   /                            \
	  C                              P                                */
	right_rotate(node->right);
	return left_rotate(node);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::LR(AVLNode<TKey, TValue>* node) noexcept {
/*	  G                             G                          C
	 /              ->             /              ->          / \
	P	      left_rotate(P)      C       right_rotate(G)    P   G
	 \                           /
	  C                         P                                        */
	left_rotate(node->left);
	return right_rotate(node);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::recover_balance(AVLNode<TKey, TValue>* node) noexcept {
	if (!node) { return nullptr; }
	update_height(node);
	int balance = get_balance(node);
	if (balance == 2) {
		if (get_balance(node->right) >= 0) {
			return RR(node);
		}
		else {
			return RL(node);
		}
	}
	else if (balance == -2) {
		if (get_balance(node->left) <= 0) {
			return LL(node);
		}
		else {
			return LR(node);
		}
	}
	return node;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::recover_balance_from(AVLNode<TKey, TValue>* node) noexcept {
	AVLNode<TKey, TValue>* cur = node;
	while (cur) {
		AVLNode<TKey, TValue>* new_root = recover_balance(cur);
		cur = new_root->parent;
	}
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	if (!this->_root) {
		this->_root = new AVLNode<TKey, TValue>(key, value);
		return;
	}
	AVLNode<TKey, TValue>* cur = this->_root;
	AVLNode<TKey, TValue>* parent = nullptr;
	while (cur) {
		parent = cur;
		if (cur->data.first == key) {
			throw std::invalid_argument("Key is already use in AVLTree!");
		}
		else if (cur->data.first > key) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	AVLNode<TKey, TValue>* new_node = new AVLNode<TKey, TValue>(key, value);
	new_node->parent = parent;
	if (parent->data.first > key) {
		parent->left = new_node;
	}
	else {
		parent->right = new_node;
	}
	recover_balance_from(parent);
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::find_max_left(AVLNode<TKey, TValue>* node) const noexcept { //
	if (!node || !node->left) { return nullptr; }
	AVLNode<TKey, TValue>* cur = node->left;
	while (cur->right) {
		cur = cur->right;
	}
	return cur;
}

template <class TKey, class TValue>
AVLNode<TKey, TValue>* AVLTree<TKey, TValue>::erase_node(AVLNode<TKey, TValue>* node) noexcept {
	if (!node) { return nullptr; }
	AVLNode<TKey, TValue>* parent = node->parent;
	AVLNode<TKey, TValue>* child = nullptr;
	if (node->left) {
		child = node->left;
	}
	else {
		child = node->right;
	}
	if (child) { child->parent = parent; }
	if (!parent) {
		this->_root = child;
	}
	else if (parent->left == node) {
		parent->left = child;
	}
	else {
		parent->right = child;
	}
	delete node;
	if (parent) { return parent; }
	return this->_root;
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::erase(const TKey& key) {
	if (!this->_root) { throw std::invalid_argument("AVLTree is empty!"); }
	AVLNode<TKey, TValue>* deleted_node = find_node(key);
	if (!deleted_node) { throw std::invalid_argument("Node with this key was not found!"); }
	AVLNode<TKey, TValue>* start_balance = nullptr;
	if (deleted_node->left && deleted_node->right) {
		AVLNode<TKey, TValue>* replace_node = find_max_left(deleted_node);
		deleted_node->data = replace_node->data;
		start_balance = erase_node(replace_node);
	}
	else {
		start_balance = erase_node(deleted_node);
	}
	recover_balance_from(start_balance);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::print_lcr_rec(AVLNode<TKey, TValue>* node) const noexcept {
	if (!node) { return; }
	print_lcr_rec(node->left);
	std::cout << node->data.second << " ";
	print_lcr_rec(node->right);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::print_lcr() const noexcept {
	print_lcr_rec(this->_root);
}

template <class TKey, class TValue>
int AVLTree<TKey, TValue>::get_height_for_print(AVLNode<TKey, TValue>* node) const noexcept { //
	if (!node) { return 0; }
	return 1 + (std::max)(get_height_for_print(node->left), get_height_for_print(node->right));
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::matrix_for_print(AVLNode<TKey, TValue>* node, TVector<TVector<std::string>>& matrix, int level, int left, int right) const noexcept { //
	if (!node || level >= matrix.size()) { return; }
	int mid = (left + right) / 2;
	int row = level * 2;
	matrix[row][mid] = " " + std::to_string(node->data.first);
	if (node->left) {
		int left_mid = (left + mid - 1) / 2;
		for (int i = left_mid + 1; i < mid; ++i) {
			matrix[row][i] = "___";
		}
		if (row + 1 < matrix.size()) {
			matrix[row + 1][left_mid] = " / ";
		}
	}
	if (node->right) {
		int right_mid = (mid + right + 1) / 2;
		for (int i = mid + 1; i < right_mid; ++i) {
			matrix[row][i] = "___";
		}
		if (row + 1 < matrix.size()) {
			matrix[row + 1][right_mid] = "\\ ";
		}
	}
	matrix_for_print(node->left, matrix, level + 1, left, mid - 1);
	matrix_for_print(node->right, matrix, level + 1, mid + 1, right);
}

template <class TKey, class TValue>
void AVLTree<TKey, TValue>::print() const noexcept { //
	if (!this->_root) { return; }
	int height = get_height_for_print(this->_root);
	int width = (int)pow(2, height) - 1;
	TVector<TVector<std::string>> matrix;
	for (int i = 0; i < height * 2 - 1; ++i) {
		TVector<std::string> row;
		for (int j = 0; j < width; ++j) {
			row.push_back("   ");
		}
		matrix.push_back(row);
	}
	matrix_for_print(this->_root, matrix, 0, 0, width - 1);
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}
}

#endif // LIB_AVLTREE_AVLTREE_H