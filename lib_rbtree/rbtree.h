// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_RBTREE_RBTREE_H
#define LIB_RBTREE_RBTREE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <cmath>

#include "../lib_pair/pair.h"
#include "../lib_tvector/tvector.h"

enum Color { red, black};

template <class TKey, class TValue>
struct RBNode {
	Pair<TKey, TValue> data;
	RBNode<TKey, TValue>* left;
	RBNode<TKey, TValue>* right;
	RBNode<TKey, TValue>* parent;
	Color color;

	RBNode();
	RBNode(const TKey& key, const TValue& value, RBNode<TKey, TValue>* l = nullptr, RBNode<TKey, TValue>* r = nullptr, RBNode<TKey, TValue>* p = nullptr, Color c = red);
};

template <class TKey, class TValue>
RBNode<TKey, TValue>::RBNode() : data(), left(nullptr), right(nullptr), parent(nullptr), color(red) {}

template <class TKey, class TValue>
RBNode<TKey, TValue>::RBNode(const TKey& key, const TValue& value, RBNode<TKey, TValue>* l, RBNode<TKey, TValue>* r, RBNode<TKey, TValue>* p, Color c) 
	: data(key, value), left(l), right(r), parent(p), color(c) {}

template <class TKey, class TValue>
class RBTree {
	RBNode<TKey, TValue>* _root;
public:
	RBTree();
	~RBTree();

	RBNode<TKey, TValue>* root() const noexcept;

	void insert(const TKey& key, const TValue& value);
	TValue* find(const TKey& key) const noexcept;
	void erase(const TKey& key);

	void clear() noexcept;
	bool is_empty() const noexcept;
	void print_lcr() const noexcept;
	void print() const noexcept;
private:
	Color color_of(RBNode<TKey, TValue>* node) const noexcept;
	void set_color(RBNode<TKey, TValue>* node, Color color) noexcept;
	bool is_red(RBNode<TKey, TValue>* node) const noexcept;
	bool is_black(RBNode<TKey, TValue>* node) const noexcept;

	RBNode<TKey, TValue>* left_of(RBNode<TKey, TValue>* node) const noexcept;
	RBNode<TKey, TValue>* right_of(RBNode<TKey, TValue>* node) const noexcept;
	RBNode<TKey, TValue>* parent_of(RBNode<TKey, TValue>* node) const noexcept;

	RBNode<TKey, TValue>* find_node(const TKey& key) const noexcept;
	RBNode<TKey, TValue>* find_max_left(RBNode<TKey, TValue>* node) const noexcept;
	void left_rotate(RBNode<TKey, TValue>* node) noexcept;
	void right_rotate(RBNode<TKey, TValue>* node) noexcept;
	void fix_after_insert(RBNode<TKey, TValue>* node) noexcept;
	void fix_after_erase(RBNode<TKey, TValue>* node, RBNode<TKey, TValue>* parent) noexcept;
	void replace(RBNode<TKey, TValue>* old_node, RBNode<TKey, TValue>* new_node) noexcept;
	void clear_rec(RBNode<TKey, TValue>* node) noexcept;
	void print_lcr_rec(RBNode<TKey, TValue>* node) const noexcept;
	int get_height_for_print(RBNode<TKey, TValue>* node) const noexcept;
	std::string node_to_string(RBNode<TKey, TValue>* node) const noexcept;
	std::string link_to_string(RBNode<TKey, TValue>* node, bool is_left_link) const noexcept;
	void matrix_for_print(RBNode<TKey, TValue>* node, TVector<TVector<std::string>>& matrix, int level, int left, int right) const noexcept;
};


template <class TKey, class TValue>
RBTree<TKey, TValue>::RBTree() : _root(nullptr) {}

template <class TKey, class TValue>
RBTree<TKey, TValue>::~RBTree() {
	clear();
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::root() const noexcept {
	return _root;
}

template <class TKey, class TValue>
Color RBTree<TKey, TValue>::color_of(RBNode<TKey, TValue>* node) const noexcept {
	if (!node) { return black; }
	return node->color;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::set_color(RBNode<TKey, TValue>* node, Color color) noexcept {
	if (node) {
		node->color = color;
	}
}

template <class TKey, class TValue>
bool RBTree<TKey, TValue>::is_red(RBNode<TKey, TValue>* node) const noexcept {
	return color_of(node) == red;
}

template <class TKey, class TValue>
bool RBTree<TKey, TValue>::is_black(RBNode<TKey, TValue>* node) const noexcept {
	return color_of(node) == black;
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::left_of(RBNode<TKey, TValue>* node) const noexcept {
	if (!node) { return nullptr; }
	return node->left;
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::right_of(RBNode<TKey, TValue>* node) const noexcept {
	if (!node) { return nullptr; }
	return node->right;
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::parent_of(RBNode<TKey, TValue>* node) const noexcept {
	if (!node) { return nullptr; }
	return node->parent;
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::find_node(const TKey& key) const noexcept {
	RBNode<TKey, TValue>* cur = this->_root;
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
TValue* RBTree<TKey, TValue>::find(const TKey& key) const noexcept {
	RBNode<TKey, TValue>* node = find_node(key);
	if (!node) { return nullptr; }
	return &node->data.second;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::left_rotate(RBNode<TKey, TValue>* node) noexcept {
/*	  G                            P
	   \            ->            / \
		P     left_rotate(G)     G   C
	   / \                        \
	  T   C                        T      */
	if (!node || !node->right) { return; }
	RBNode<TKey, TValue>* G = node;
	RBNode<TKey, TValue>* P = G->right;
	RBNode<TKey, TValue>* T = P->left;
	RBNode<TKey, TValue>* parent = G->parent;
	P->parent = parent;
	if (!parent) {
		_root = P;
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
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::right_rotate(RBNode<TKey, TValue>* node) noexcept {
/*		G                          P
	   /            ->            / \
	  P      right_rotate(G)     C   G
	 / \                            /
	C   T                          T         */
	if (!node || !node->left) { return; }
	RBNode<TKey, TValue>* G = node;
	RBNode<TKey, TValue>* P = G->left;
	RBNode<TKey, TValue>* T = P->right;
	RBNode<TKey, TValue>* parent = G->parent;
	P->parent = parent;
	if (!parent) {
		_root = P;
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
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	if (!_root) {
		_root = new RBNode<TKey, TValue>(key, value, nullptr, nullptr, nullptr, black);
		return;
	}
	RBNode<TKey, TValue>* cur = _root;
	RBNode<TKey, TValue>* parent = nullptr;
	while (cur) {
		parent = cur;
		if (cur->data.first == key) {
			throw std::invalid_argument("Key is already use in RBTree!");
		}
		else if (cur->data.first > key) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	RBNode<TKey, TValue>* new_node = new RBNode<TKey, TValue>(key, value, nullptr, nullptr, parent, red);
	if (parent->data.first > key) {
		parent->left = new_node;
	}
	else {
		parent->right = new_node;
	}
	fix_after_insert(new_node);
	_root->color = black;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::fix_after_insert(RBNode<TKey, TValue>* node) noexcept {
/*  C - child, новая красная вершина или вершина, от которой поднимаемся вверх.
    P - parent, родитель C.
    G - grandparent, дедушка C.
    U - uncle, дядя C, то есть второй ребёнок G.   */

	RBNode<TKey, TValue>* C = node;
	while (C != _root && is_red(parent_of(C))) {
		RBNode<TKey, TValue>* P = C->parent;
		RBNode<TKey, TValue>* G = P->parent;
		if (!G) { break; }
		if (P == G->left) {
			RBNode<TKey, TValue>* U = G->right;
			if (is_red(U)) {
				/* P красный и U красный (просто перекраc)
						G(B)                    G(R)
					   /   \                   /   \
					 P(R)  U(R)      ->      P(B) U(B)
					 /
				   C(R)                                             */
				P->color = black;
				U->color = black;
				G->color = red;
				C = G;
			}
			else {
				if (C == P->right) {
					/* LR:
						  G(B)                       G(B)                  C(B)
					     /                           /                     /   \
					    P(R)        ->              C(R)        ->       P(R)  G(R)
						  \   left_rotate(P)       /
						  C(R)                   P(R)                                     */
					left_rotate(P);
					C = P;
					P = C->parent;
				}
				/* LL:
						 G(B)                    P(B)
						/                       /   \
					  P(R)        ->          C(R)  G(R)
					  /     right_rotate(G)
					C(R)                                      */
				P->color = black;
				G->color = red;
				right_rotate(G);
			}
		}
		else {
			RBNode<TKey, TValue>* U = G->left;
			if (is_red(U)) { // P красный и U красный (просто перекраc)
				P->color = black;
				U->color = black;
				G->color = red;
				C = G;
			}
			else {
				if (C == P->left) {
					/* RL:
						 G(B)                       G(B)                  C(B)
							\                          \                 /   \
							P(R)        ->            C(R)     ->      G(R)  P(R)
							/      right_rotate(P)       \
						  C(R)                           P(R)                           */
					right_rotate(P);
					C = P;
					P = C->parent;
				}
				/* RR:
						G(B)                          P(B)
						   \                         /    \
						   P(R)          ->        G(R)  C(R)
							  \    left_rotate(G)
							  C(R)                                   */
				P->color = black;
				G->color = red;
				left_rotate(G);
			}
		}
	}
	if (_root) {
		_root->color = black;
	}
}

template <class TKey, class TValue>
RBNode<TKey, TValue>* RBTree<TKey, TValue>::find_max_left(RBNode<TKey, TValue>* node) const noexcept {
	if (!node || !node->left) { return nullptr; }
	RBNode<TKey, TValue>* cur = node->left;
	while (cur->right) {
		cur = cur->right;
	}
	return cur;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::replace(RBNode<TKey, TValue>* old_node, RBNode<TKey, TValue>* new_node) noexcept {
	if (!old_node->parent) {
		_root = new_node;
	}
	else if (old_node == old_node->parent->left) {
		old_node->parent->left = new_node;
	}
	else {
		old_node->parent->right = new_node;
	}
	if (new_node) {
		new_node->parent = old_node->parent;
	}
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::erase(const TKey& key) {
	if (!_root) { throw std::invalid_argument("RBTree is empty!"); }
	RBNode<TKey, TValue>* deleted_node = find_node(key);
	if (!deleted_node) { throw std::invalid_argument("Node with this key was not found!"); }
	RBNode<TKey, TValue>* f_deleted_node = deleted_node;
	RBNode<TKey, TValue>* child_for_fix = nullptr;
	RBNode<TKey, TValue>* parent_child_for_fix = nullptr;
	Color f_deleted_node_original_color = f_deleted_node->color;
	if (!deleted_node->left) {
		child_for_fix = deleted_node->right;
		parent_child_for_fix = deleted_node->parent;
		replace(deleted_node, deleted_node->right);
	}
	else if (!deleted_node->right) {
		child_for_fix = deleted_node->left;
		parent_child_for_fix = deleted_node->parent;
		replace(deleted_node, deleted_node->left);
	}
	else {
		f_deleted_node = find_max_left(deleted_node);
		f_deleted_node_original_color = f_deleted_node->color;
		child_for_fix = f_deleted_node->left;
		if (f_deleted_node->parent == deleted_node) {
			parent_child_for_fix = f_deleted_node;
			if (child_for_fix) { parent_child_for_fix = f_deleted_node; }
		}
		else {
			parent_child_for_fix = f_deleted_node->parent;
			replace(f_deleted_node, f_deleted_node->left);
			f_deleted_node->left = deleted_node->left;
			if (f_deleted_node->left) { f_deleted_node->left->parent = f_deleted_node; }
		}
		replace(deleted_node, f_deleted_node);
		f_deleted_node->right = deleted_node->right;
		if (f_deleted_node->right) { f_deleted_node->right->parent = f_deleted_node; }
		f_deleted_node->color = deleted_node->color;
	}
	delete deleted_node;
	if (f_deleted_node_original_color == black) {
		fix_after_erase(child_for_fix, parent_child_for_fix);
	}
	if (_root) {
		_root->color = black;
		_root->parent = nullptr;
	}
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::fix_after_erase(RBNode<TKey, TValue>* node, RBNode<TKey, TValue>* parent) noexcept {
	/* X - node, в которой не хватает одного чёрного цвета.
       P - parent, родитель X.
       S - sibling, брат X.
       N - near nephew, ближний племянник.
       F - far nephew, дальний племянник.                          */
	while (node != _root && is_black(node)) {
		if (!parent) { break; }
		if (node == parent->left) {
			RBNode<TKey, TValue>* S = parent->right;
			if (is_red(S)) {
				/*		P(B)                            S(B)
						/   \                          /   \
					  X(B) S(R)          ->          P(R)  F(B)
						   /   \   left_rotate(P)   /   \
						 N(B) F(B)                 X(B) N(B)            */
				S->color = black;
				parent->color = red;
				left_rotate(parent);
				S = parent->right;
			}
			if (is_black(left_of(S)) && is_black(right_of(S))) {
				/* P(?)                           P(?)
				   /   \                         /   \
				 X(B) S(B)         ->          X(B) S(R)
					  /   \  set_color(S, red)
					N(B) F(B)                                              */
				set_color(S, red);
				node = parent;
				parent = node->parent;
			}
			else {
				if (is_black(right_of(S))) {
					/*  P(?)                           P(?)
				        /   \                         /   \
					  X(B)  S(B)         ->         X(B)  N(B)
						    /   \  right_rotate(S)          \
						  N(R) F(B)                         S(R)            */
					set_color(left_of(S), black);
					set_color(S, red);
					right_rotate(S);
					
					S = parent->right;
				}
				/* P(?)                               S(?)
				   /   \                             /   \
				  X(B) S(B)           ->           P(B) F(B)
					   /   \    left_rotate(P)    /   \
					  N(?) F(R)                  X(B) N(?)                    */
				set_color(S, color_of(parent));
				parent->color = black;
				set_color(right_of(S), black);
				left_rotate(parent);

				node = _root;
				parent = nullptr;
			}
		}
		else {
			RBNode<TKey, TValue>* S = parent->left;
			if (is_red(S)) {
				/*		P(B)                            S(B)
						/   \                          /   \
					  S(R)  X(B)        ->          F(B)   P(B)
					 /   \         right_rotate(P)         /   \
				   F(B) N(B)                            N(B)   X(B)            */
				S->color = black;
				parent->color = red;
				right_rotate(parent);
				S = parent->left;
			}
			if (is_black(right_of(S)) && is_black(left_of(S))) {
				/* P(?)                           P(?)
				   /   \                         /   \
				S(B)   X(B)       ->           S(R)   X(B)
			   /   \        set_color(S, red)
			 F(B)  N(B)                                              */
				set_color(S, red);
				node = parent;
				parent = node->parent;
			}
			else {
				if (is_black(left_of(S))) {
					/*  P(?)                           P(?)
						/   \                         /   \
					  S(B)  X(B)        ->         N(B)  X(B)
					 /   \        left_rotate(S)    /
				   F(B)  N(R)                     S(R)            */
					set_color(right_of(S), black);
					set_color(S, red);
					left_rotate(S);

					S = parent->left;
				}
				/* P(?)                               S(?)
				   /   \                             /   \
				 S(B)  X(B)          ->           F(B)   P(B) 
				 /   \        right_rotate(P)           /   \
			   F(R)  N(?)                             N(?)  X(B)             */
				set_color(S, color_of(parent));
				parent->color = black;
				set_color(left_of(S), black);
				right_rotate(parent);

				node = _root;
				parent = nullptr;
			}
		}
	}
	set_color(node, black);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::clear_rec(RBNode<TKey, TValue>* node) noexcept {
	if (!node) { return; }
	clear_rec(node->left);
	clear_rec(node->right);
	delete node;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::clear() noexcept {
	clear_rec(_root);
	_root = nullptr;
}

template <class TKey, class TValue>
bool RBTree<TKey, TValue>::is_empty() const noexcept {
	return _root == nullptr;
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::print_lcr_rec(RBNode<TKey, TValue>* node) const noexcept {
	if (!node) { return; }
	print_lcr_rec(node->left);
	std::cout << node->data.second << " ";
	print_lcr_rec(node->right);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::print_lcr() const noexcept {
	print_lcr_rec(_root);
}

template <class TKey, class TValue>
std::string RBTree<TKey, TValue>::node_to_string(RBNode<TKey, TValue>* node) const noexcept {
	if (!node) { return ""; }
	std::ostringstream key_out;
	std::ostringstream value_out;
	key_out << node->data.first;
	value_out << node->data.second;
	std::string key_str = key_out.str();
	std::string value_str = value_out.str();
	if (node->color == black) {
		return "[" + key_str + ":" + value_str + "]";
	}
	else {
		return "(" + key_str + ":" + value_str + ")";
	}
}

template <class TKey, class TValue>
int RBTree<TKey, TValue>::get_height_for_print(RBNode<TKey, TValue>* node) const noexcept {
	if (!node) { return 0; }
	return 1 + (std::max)(get_height_for_print(node->left), get_height_for_print(node->right));
}

template <class TKey, class TValue>
std::string RBTree<TKey, TValue>::link_to_string(RBNode<TKey, TValue>* node, bool is_left_link) const noexcept {
	if (!node) { return "     "; }
	if (node->color == black) {
		if (is_left_link) {
			return " B/  ";
		}
		else {
			return " B\\  ";
		}
	}
	if (is_left_link) {
		return " R/  ";
	}
	else {
		return " R\\  ";
	}
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::matrix_for_print(RBNode<TKey, TValue>* node, TVector<TVector<std::string>>& matrix, int level, int left, int right) const noexcept {
	if (!node || level >= matrix.size()) { return; }
	int mid = (left + right) / 2;
	int row = level * 2;
	matrix[row][mid] = node_to_string(node);
	if (node->left) {
		int left_mid = (left + mid - 1) / 2;
		for (int i = left_mid + 1; i < mid; ++i) {
			matrix[row][i] = "_____";
		}
		if (row + 1 < matrix.size()) {
			matrix[row + 1][left_mid] = link_to_string(node->left, true);
		}
	}
	if (node->right) {
		int right_mid = (mid + right + 1) / 2;
		for (int i = mid + 1; i < right_mid; ++i) {
			matrix[row][i] = "_____";
		}
		if (row + 1 < matrix.size()) {
			matrix[row + 1][right_mid] = link_to_string(node->right, false);
		}
	}
	matrix_for_print(node->left, matrix, level + 1, left, mid - 1);
	matrix_for_print(node->right, matrix, level + 1, mid + 1, right);
}

template <class TKey, class TValue>
void RBTree<TKey, TValue>::print() const noexcept {
	if (!_root) { return; }
	int height = get_height_for_print(_root);
	int width = (int)pow(2, height+1) - 1;
	TVector<TVector<std::string>> matrix;
	for (int i = 0; i < height * 2 - 1; ++i) {
		TVector<std::string> row;
		for (int j = 0; j < width; ++j) {
			row.push_back("     ");
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

#endif // LIB_RBTREE_RBTREE_H