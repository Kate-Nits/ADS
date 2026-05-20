// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_UNSORTED_TABLE_ON_TREE_UNSORTED_TABLE_ON_TREE_H
#define LIB_UNSORTED_TABLE_ON_TREE_UNSORTED_TABLE_ON_TREE_H

#include "../lib_table/table.h"
#include "../lib_tree/tree.h"
#include "../lib_queue/queue.h"

template <class TKey, class TValue>
class UnsortedTableOnTree : public Table<TKey, TValue> {
	Tree<TKey, TValue> _rows;
public:
	UnsortedTableOnTree();
	~UnsortedTableOnTree();

	void insert(const TKey&, const TValue&) override;
	void erase(const TKey&) override;
	const TValue* found(const TKey&) const noexcept override;
	bool is_empty() const noexcept override;
	void print(std::ostream& os = std::cout) const noexcept override;
};

template <class TKey, class TValue>
UnsortedTableOnTree<TKey, TValue>::UnsortedTableOnTree() : _rows() {}

template <class TKey, class TValue>
UnsortedTableOnTree<TKey, TValue>::~UnsortedTableOnTree() {}

template <class TKey, class TValue>
void UnsortedTableOnTree<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	auto node = _rows.find(key);
	if (node) { throw std::invalid_argument("The key is already use in UnsortedTableOnTree"); }
	_rows.insert(key, value);
}

template <class TKey, class TValue>
void UnsortedTableOnTree<TKey, TValue>::erase(const TKey& key) {
	auto node = _rows.find(key);
	if (!node) { throw std::invalid_argument("The key didn't find in UnsortedTableOnTree"); }
	_rows.erase(key);
}

template <class TKey, class TValue>
const TValue* UnsortedTableOnTree<TKey, TValue>::found(const TKey& key) const noexcept {
	return _rows.find(key);
}

template <class TKey, class TValue>
bool UnsortedTableOnTree<TKey, TValue>::is_empty() const noexcept {
	return _rows.is_empty();
}
template <class TKey, class TValue>
void UnsortedTableOnTree<TKey, TValue>::print(std::ostream& os) const noexcept {
	this->print_line(os);
	this->print_title(os);
	this->print_line(os);

	Queue<TreeNode<TKey, TValue>*> q;
	TreeNode<TKey, TValue>* cur = nullptr;
	q.push(_rows.root());
	while (!q.is_empty()) {
		cur = q.head();
		os << "|";
		this->print_key(os, cur->data.first, WIDTH_KEY);
		this->print_value(os, cur->data.second, WIDTH_VALUE);
		os << std::endl;
		q.pop();
		if (cur->left) { q.push(cur->left); }
		if (cur->right) { q.push(cur->right); }
	}
	this->print_line(os);
}

#endif // LIB_UNSORTED_TABLE_ON_TREE_UNSORTED_TABLE_ON_TREE_H