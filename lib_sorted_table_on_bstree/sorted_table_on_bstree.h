// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_SORTED_TABLE_ON_BSTREE_SORTED_TABLE_ON_BSTREE_H
#define LIB_SORTED_TABLE_ON_BSTREE_SORTED_TABLE_ON_BSTREE_H

#include "../lib_table/table.h"
#include "../lib_bstree/bstree.h"

template <class TKey, class TValue>
class SortedTableOnBSTree : public Table<TKey, TValue> {
	BSTree<TKey, TValue> _rows;
public:
	SortedTableOnBSTree();
	~SortedTableOnBSTree();

	void insert(const TKey&, const TValue&) override;
	void erase(const TKey&) override;
	const TValue* found(const TKey&) const noexcept override;
	bool is_empty() const noexcept override;
	void print(std::ostream& os = std::cout) const noexcept override;
private:
	void print_lcr_rec(TreeNode<TKey, TValue>* node, std::ostream& os) const noexcept;
};

template <class TKey, class TValue>
SortedTableOnBSTree<TKey, TValue>::SortedTableOnBSTree() : _rows() {}

template <class TKey, class TValue>
SortedTableOnBSTree<TKey, TValue>::~SortedTableOnBSTree() {}

template <class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	auto node = _rows.find(key);
	if (node) { throw std::invalid_argument("The key is already use in SortedTableOnBSTree"); }
	_rows.insert(key, value);
}

template <class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::erase(const TKey& key) {
	auto node = _rows.find(key);
	if (!node) { throw std::invalid_argument("The key didn't find in SortedTableOnBSTree"); }
	_rows.erase(key);
}

template <class TKey, class TValue>
const TValue* SortedTableOnBSTree<TKey, TValue>::found(const TKey& key) const noexcept {
	return _rows.find(key);
}

template <class TKey, class TValue>
bool SortedTableOnBSTree<TKey, TValue>::is_empty() const noexcept {
	return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::print(std::ostream& os) const noexcept {
	this->print_line(os);
	this->print_title(os);
	this->print_line(os);
	print_lcr_rec(_rows.root(), os);
	this->print_line(os);
}

template <class TKey, class TValue>
void SortedTableOnBSTree<TKey, TValue>::print_lcr_rec(TreeNode<TKey, TValue>* node, std::ostream& os) const noexcept {
	if (!node) { return; }
	print_lcr_rec(node->left, os);
	os << "|";
	this->print_key(os, node->data.first, WIDTH_KEY);
	this->print_value(os, node->data.second, WIDTH_VALUE);
	os << std::endl;
	print_lcr_rec(node->right, os);
}

#endif // LIB_SORTED_TABLE_ON_BSTREE_SORTED_TABLE_ON_BSTREE_H