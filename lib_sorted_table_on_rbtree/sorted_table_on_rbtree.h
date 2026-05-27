// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_SORTED_TABLE_ON_RBTREE_SORTED_TABLE_ON_RBTREE_H
#define LIB_SORTED_TABLE_ON_RBTREE_SORTED_TABLE_ON_RBTREE_H

#include "../lib_table/table.h"
#include "../lib_rbtree/rbtree.h"

template <class TKey, class TValue>
class SortedTableOnRBTree : public Table<TKey, TValue> {
	RBTree<TKey, TValue> _rows;
public:
	SortedTableOnRBTree();
	~SortedTableOnRBTree();

	void insert(const TKey&, const TValue&) override;
	void erase(const TKey&) override;
	const TValue* found(const TKey&) const noexcept override;
	bool is_empty() const noexcept override;
	void print(std::ostream& os = std::cout) const noexcept override;
private:
	void print_lcr_rec(RBNode<TKey, TValue>* node, std::ostream& os) const noexcept;
};

template <class TKey, class TValue>
SortedTableOnRBTree<TKey, TValue>::SortedTableOnRBTree() : _rows() {}

template <class TKey, class TValue>
SortedTableOnRBTree<TKey, TValue>::~SortedTableOnRBTree() {}

template <class TKey, class TValue>
void SortedTableOnRBTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	auto node = _rows.find(key);
	if (node) { throw std::invalid_argument("The key is already use in SortedTableOnRBTree"); }
	_rows.insert(key, value);
}

template <class TKey, class TValue>
void SortedTableOnRBTree<TKey, TValue>::erase(const TKey& key) {
	auto node = _rows.find(key);
	if (!node) { throw std::invalid_argument("The key didn't find in SortedTableOnRBTree"); }
	_rows.erase(key);
}

template <class TKey, class TValue>
const TValue* SortedTableOnRBTree<TKey, TValue>::found(const TKey& key) const noexcept {
	return _rows.find(key);
}

template <class TKey, class TValue>
bool SortedTableOnRBTree<TKey, TValue>::is_empty() const noexcept {
	return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableOnRBTree<TKey, TValue>::print_lcr_rec(RBNode<TKey, TValue>* node, std::ostream& os) const noexcept {
	if (!node) { return; }
	print_lcr_rec(node->left, os);
	os << "|";
	this->print_key(os, node->data.first, WIDTH_KEY);
	this->print_value(os, node->data.second, WIDTH_VALUE);
	os << std::endl;
	print_lcr_rec(node->right, os);
}

template <class TKey, class TValue>
void SortedTableOnRBTree<TKey, TValue>::print(std::ostream& os) const noexcept {
	this->print_line(os);
	this->print_title(os);
	this->print_line(os);
	print_lcr_rec(_rows.root(), os);
	this->print_line(os);
}

#endif // LIB_SORTED_TABLE_ON_RBTREE_SORTED_TABLE_ON_RBTREE_H