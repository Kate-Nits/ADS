// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_BSTREE_BSTREE_H
#define LIB_BSTREE_BSTREE_H

#include <iostream>
#include <stdexcept>
#include <cmath>

#include "../lib_tree/tree.h"
#include "../lib_pair/pair.h"

template <class TKey, class TValue, class TNode = TreeNode<TKey, TValue>>
class BSTree {
protected:
	TNode* _root;
public:
	BSTree();
	~BSTree();

	TNode* root() const noexcept;

	TNode* insert(const TKey& key, const TValue& value);
	TValue* find(const TKey& key) const noexcept;
	TNode* erase(const TKey& key);
	void clear() noexcept;
	bool is_empty() const noexcept;

	void print_lcr() const noexcept;
	void print() const noexcept;
protected:
	TNode* find_parent(const TKey& key) const noexcept;
	TNode* find_max_left(TNode* node) const noexcept;
private:
	void print_lcr_rec(TNode* node) const noexcept;
	void clear_rec(TNode* node) noexcept;
	TNode* erase_node(TNode*& node, TNode* parent) noexcept;

	int get_height(TreeNode<TKey, TValue>* node) const noexcept;
	void matrix_for_print(TNode* node, TVector<TVector<std::string>>& matrix, int level, int left, int right) const noexcept;
};

template <class TKey, class TValue, class TNode>
BSTree<TKey, TValue, TNode>::BSTree() : _root(nullptr) {}

template <class TKey, class TValue, class TNode>
BSTree<TKey, TValue, TNode>::~BSTree() {
	clear_rec(_root);
}

template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::root() const noexcept {
	return _root;
}

template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::insert(const TKey& key, const TValue& value) {
	if (!_root) {
		_root = new TNode(key, value);
		return nullptr;
	}
	TNode* parent = find_parent(key);
	if (parent->data.first > key && !parent->left) {
		parent->left = new TNode(key, value);
		return parent;
	}
	else if (parent->data.first < key && !parent->right) {
		parent->right = new TNode(key, value);
		return parent;
	}
	throw std::invalid_argument("The key is already use in BSTree!");
}

template <class TKey, class TValue, class TNode>
TValue* BSTree<TKey, TValue, TNode>::find(const TKey& key) const noexcept {
	if (!_root) { return nullptr; }
	TNode* parent = find_parent(key);
	if (parent->left && parent->left->data.first == key) {
		return &parent->left->data.second;
	}
	else if (parent->right && parent->right->data.first == key) {
		return &parent->right->data.second;
	}
	else if (parent == _root && _root->data.first == key) {
		return &_root->data.second;
	}
	return nullptr;
}

template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::erase(const TKey& key) {
	if (!_root) { throw std::invalid_argument("BSTree is empty!"); }
	TNode* parent = find_parent(key);
	TNode* changed_parent = nullptr;
	if (parent->data.first > key) {
		if (!parent->left || parent->left->data.first != key) {
			throw std::invalid_argument("The element was not found!");
		}
		changed_parent = erase_node(parent->left, parent);
	}
	else if (parent->data.first < key) {
		if (!parent->right || parent->right->data.first != key) {
			throw std::invalid_argument("The element was not found!");
		}
		changed_parent = erase_node(parent->right, parent);
	}
	else {
		TNode* prev_root = _root;
		changed_parent = erase_node(_root, nullptr);
		if (_root != prev_root) {
			return _root;
		}
	}
	return changed_parent;
}

template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::clear() noexcept {
	clear_rec(_root);
	_root = nullptr;
}

template <class TKey, class TValue, class TNode>
bool BSTree<TKey, TValue, TNode>::is_empty() const noexcept {
	return _root == nullptr;
}

template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::print_lcr() const noexcept {
	print_lcr_rec(_root);
}

template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::print_lcr_rec(TNode* node) const noexcept {
	if (!node) { return; }
	print_lcr_rec(node->left);
	std::cout << node->data.second << " ";
	print_lcr_rec(node->right);
}

template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::find_parent(const TKey& key) const noexcept {
	if (!_root) { return nullptr; }
	if (_root->data.first == key) { return _root; }
	TNode* cur = _root;
	while (1) {
		if (cur->data.first > key) {
			if (!cur->left || cur->left->data.first == key) {
				return cur;
			}
			cur = cur->left;
		}
		else if (cur->data.first < key) {
			if (!cur->right || cur->right->data.first == key) {
				return cur;
			}
			cur = cur->right;
		}
	}
}

template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::find_max_left(TNode* node) const noexcept {
	if (!node || !node->left) { return nullptr; }
	TNode* cur = node->left;
	while (cur->right) {
		cur = cur->right;
	}
	return cur;
}

template <class TKey, class TValue, class TNode>
TNode* BSTree<TKey, TValue, TNode>::erase_node(TNode*& node, TNode* parent) noexcept {
	if (!node->left && !node->right) {
		delete node;
		node = nullptr;
		return parent;
	}
	else if (!node->left) {
		TNode* tmp = node;
		node = node->right;
		delete tmp;
		return parent;
	}
	else if (!node->right) {
		TNode* tmp = node;
		node = node->left;
		delete tmp;
		return parent;
	}
	else {
		TNode* replace_node = find_max_left(node);
		Pair<TKey, TValue> tmp_data = replace_node->data;
		TNode* parent_replace_node = find_parent(replace_node->data.first);
		if (parent_replace_node->left == replace_node) {
			erase_node(parent_replace_node->left, parent_replace_node);
		}
		else {
			erase_node(parent_replace_node->right, parent_replace_node);
		}
		node->data = tmp_data;
		return parent_replace_node;
	}
	
}

template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::clear_rec(TNode* node) noexcept {
	if (!node) { return; }
	clear_rec(node->left);
	clear_rec(node->right);
	delete node;
}

template <class TKey, class TValue, class TNode>
int BSTree<TKey, TValue, TNode>::get_height(TreeNode<TKey, TValue>* node) const noexcept {
	if (!node) { return 0; }
	return 1 + (std::max)(get_height(node->left), get_height(node->right));
}

template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::matrix_for_print(TNode* node, TVector<TVector<std::string>>& matrix, int level, int left, int right) const noexcept {
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

template <class TKey, class TValue, class TNode>
void BSTree<TKey, TValue, TNode>::print() const noexcept {
	if (!_root) { return; }
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

#endif // LIB_BSTREE_BSTREE_H