// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_TREE_TREE_H
#define LIB_TREE_TREE_H

#include <iostream>
#include <string>
#include <cmath>

#include "../lib_queue/queue.h"
#include "../lib_tvector/tvector.h"
#include "../lib_pair/pair.h"

template <class TKey, class TValue>
struct TreeNode {
	Pair<TKey, TValue> data;
	TreeNode<TKey, TValue>* left;
	TreeNode<TKey, TValue>* right;

	TreeNode() : data(), left(nullptr), right(nullptr) {}
	TreeNode(const TKey& key, const TValue& value, TreeNode<TKey, TValue>* l = nullptr, TreeNode<TKey, TValue>* r = nullptr)
		: data(key, value), left(l), right(r) {}
};

template <class TKey, class TValue>
class Tree {
	TreeNode<TKey, TValue>* _root;
public:
	Tree();
	~Tree();

	TreeNode<TKey, TValue>* root() const noexcept;

	void insert(const TKey& key, const TValue& value) noexcept;
	TValue* find(const TKey& key) const noexcept;
	void erase(const TKey& key);
	void clear() noexcept;
	bool is_empty() const noexcept;

	void print_w() const noexcept;
	void print_lcr() const noexcept;
	void print_lrc() const noexcept;
	void print_clr() const noexcept;
	void print() const noexcept;
private:
	void print_lcr_rec(TreeNode<TKey, TValue>* node) const noexcept;
	void print_lrc_rec(TreeNode<TKey, TValue>* node) const noexcept;
	void print_clr_rec(TreeNode<TKey, TValue>* node) const noexcept;

	void clear_rec(TreeNode<TKey, TValue>* node);
	TreeNode<TKey, TValue>* find_parent(TreeNode<TKey, TValue>* node) const noexcept;
	int get_height(TreeNode<TKey, TValue>* node) const noexcept;
	void matrix_for_print(TreeNode<TKey, TValue>* node, TVector<TVector<std::string>>& matrix, int level, int left, int right) const noexcept;
};

template <class TKey, class TValue>
Tree<TKey, TValue>::Tree() {
	_root = nullptr;
}

template <class TKey, class TValue>
Tree<TKey, TValue>::~Tree() {
	clear();
}

template <class TKey, class TValue>
TreeNode<TKey, TValue>* Tree<TKey, TValue>::root() const noexcept { return _root; }

template <class TKey, class TValue>
void Tree<TKey, TValue>::insert(const TKey& key, const TValue& value) noexcept {
	auto node = new TreeNode<TKey, TValue>(key, value);
	if (is_empty()) {
		_root = node;
		return;
	}
	TreeNode<TKey, TValue>* cur = nullptr;
	Queue<TreeNode<TKey, TValue>*> q;
	q.push(_root);
	while (1) {
		cur = q.head();
		q.pop();
		if (!cur->left) {
			cur->left = node;
			return;
		}
		if (!cur->right) {
			cur->right = node;
			return;
		}
		q.push(cur->left);
		q.push(cur->right);
	}
}

template <class TKey, class TValue>
TValue* Tree<TKey, TValue>::find(const TKey& key) const noexcept {
	if (is_empty()) { return nullptr; }
	Queue<TreeNode<TKey, TValue>*> q;
	q.push(_root);
	while (!q.is_empty()) {
		TreeNode<TKey, TValue>* cur = q.head();
		q.pop();
		if (cur->data.first == key) { return &cur->data.second; }
		if (cur->left) { q.push(cur->left); }
		if (cur->right) { q.push(cur->right); }
	}
	return nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::erase(const TKey& key) {
	if (is_empty()) { throw std::invalid_argument("Tree is empty!"); }
	Queue<TreeNode<TKey, TValue>*> q;
	q.push(_root);
	TreeNode<TKey, TValue>* cur = nullptr;
	TreeNode<TKey, TValue>* deleted_node = nullptr;
	while (!q.is_empty()) {
		cur = q.head();
		q.pop();
		if (!deleted_node && cur->data.first == key) { deleted_node = cur; }
		if (cur->left) { q.push(cur->left); }
		if (cur->right) { q.push(cur->right); }
	}
	if (!deleted_node) { throw std::invalid_argument("Key not found"); }
	if (deleted_node != cur) { deleted_node->data = cur->data; }
	TreeNode<TKey, TValue>* parent = find_parent(cur);
	if (!parent) {
		_root = nullptr;
	}
	else if (parent->left == cur) {
		parent->left = nullptr;
	}
	else {
		parent->right = nullptr;
	}
	delete cur;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear() noexcept {
	clear_rec(_root);
	_root = nullptr;
}

template <class TKey, class TValue>
bool Tree<TKey, TValue>::is_empty() const noexcept { return _root == nullptr; }

template <class TKey, class TValue>
void Tree<TKey, TValue>::clear_rec(TreeNode<TKey, TValue>* node) {
	if (!node) { return; }
	clear_rec(node->left);
	clear_rec(node->right);
	delete node;
}

template <class TKey, class TValue>
TreeNode<TKey, TValue>* Tree<TKey, TValue>::find_parent(TreeNode<TKey, TValue>* node) const noexcept {
	if (is_empty() || node == _root) { return nullptr; }
	Queue<TreeNode<TKey, TValue>*> q;
	q.push(_root);
	while (!q.is_empty()) {
		TreeNode<TKey, TValue>* cur = q.head();
		q.pop();
		if (cur->left == node || cur->right == node) { return cur; }
		if (cur->left) { q.push(cur->left); }
		if (cur->right) { q.push(cur->right); }
	}
	return nullptr;
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_w() const noexcept {
	if (is_empty()) { return; }
	Queue<TreeNode<TKey, TValue>*> q;
	q.push(_root);
	while (!q.is_empty()) {
		TreeNode<TKey, TValue>* cur = q.head();
		q.pop();
		std::cout << cur->data.second << " ";
		if (cur->left) { q.push(cur->left); }
		if (cur->right) { q.push(cur->right); }
	}
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lcr() const noexcept {
	print_lcr_rec(_root);
}
template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lrc() const noexcept {
	print_lrc_rec(_root);
}
template <class TKey, class TValue>
void Tree<TKey, TValue>::print_clr() const noexcept {
	print_clr_rec(_root);
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lcr_rec(TreeNode<TKey, TValue>* node) const noexcept {
	if (!node) { return; }
	print_lcr_rec(node->left);
	std::cout << node->data.second << " ";
	print_lcr_rec(node->right);
}
template <class TKey, class TValue>
void Tree<TKey, TValue>::print_lrc_rec(TreeNode<TKey, TValue>* node) const noexcept {
	if (!node) { return; }
	print_lrc_rec(node->left);
	print_lrc_rec(node->right);
	std::cout << node->data.second << " ";
}
template <class TKey, class TValue>
void Tree<TKey, TValue>::print_clr_rec(TreeNode<TKey, TValue>* node) const noexcept {
	if (!node) { return; }
	std::cout << node->data.second << " ";
	print_clr_rec(node->left);
	print_clr_rec(node->right);
}

template <class TKey, class TValue>
int Tree<TKey, TValue>::get_height(TreeNode<TKey, TValue>* node) const noexcept {
	if (!node) { return 0; }
	return 1 + (std::max)(get_height(node->left), get_height(node->right));
}

template <class TKey, class TValue>
void Tree<TKey, TValue>::matrix_for_print(TreeNode<TKey, TValue>* node, TVector<TVector<std::string>>& matrix, int level, int left, int right) const noexcept {
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
void Tree<TKey, TValue>::print() const noexcept {
	if (is_empty()) { return; }
	int height = get_height(_root);
	int width = (int)pow(2, height) - 1;
	TVector<TVector<std::string>> matrix;
	for (int i = 0; i < height * 2 - 1; ++i) {
		TVector<std::string> row;
		for (int j = 0; j < width; ++j) {
			row.push_back("   ");
		}
		matrix.push_back(row);
	}
	matrix_for_print(_root, matrix, 0, 0, width - 1);
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}
}

#endif // LIB_TREE_TREE_H