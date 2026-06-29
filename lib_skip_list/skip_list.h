// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_SKIP_LIST_SKIP_LIST_H
#define LIB_SKIP_LIST_SKIP_LIST_H

#include <iostream>
#include <ctime>

#include "../lib_pair/pair.h"

#define NULL_LEVEL 0
#define DEFAULT_MAX_LEVEL_FOR_SKIP_LIST 4

template <class TKey, class TValue>
struct SNode {
	Pair<TKey, TValue> data;
	SNode<TKey, TValue>** next;
	size_t level;

	SNode(size_t value_level = 0);
	SNode(const TKey& key, const TValue& value, size_t value_level = 0);
	~SNode();
};

template <class TKey, class TValue>
SNode<TKey, TValue>::SNode(size_t value_level) : data(), level(value_level) {
	next = new SNode<TKey, TValue>* [level + 1];
	for (size_t i = 0; i < level + 1; ++i) {
		next[i] = nullptr;
	}
}

template <class TKey, class TValue>
SNode<TKey, TValue>::SNode(const TKey& key, const TValue& value, size_t value_level) : data(key, value), level(value_level) {
	next = new SNode<TKey, TValue>* [level + 1];
	for (size_t i = 0; i < level + 1; ++i) {
		next[i] = nullptr;
	}
}

template <class TKey, class TValue>
SNode<TKey, TValue>::~SNode() {
	delete[] next;
}

template <class TKey, class TValue>
class SkipList {
	SNode<TKey, TValue>* _head;
	size_t _max_level;
	size_t _level;
public:
	SkipList(size_t value_max_level = DEFAULT_MAX_LEVEL_FOR_SKIP_LIST);
	~SkipList();
	void insert(const TKey& key, const TValue& value);
	void print() const noexcept;
private:
	size_t random_level() const noexcept;
	SNode<TKey, TValue>** find_nearest(const TKey& key) const;
};

template <class TKey, class TValue>
SkipList<TKey, TValue>::SkipList(size_t value_max_level) : _head(nullptr), _max_level(value_max_level), _level(NULL_LEVEL) {
	srand(time(0));
	_head = new SNode<TKey, TValue>(_max_level);
}

template <class TKey, class TValue>
SkipList<TKey, TValue>::~SkipList() { 
	SNode<TKey, TValue>* cur = _head->next[0];
	while (cur != nullptr) {
		SNode<TKey, TValue>* node_to_delete = cur;
		cur = cur->next[0];
		delete node_to_delete;
	}
	delete _head;
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
	SNode<TKey, TValue>** prev_nodes = find_nearest(key);

	SNode<TKey, TValue>* found = prev_nodes[0]->next[0];
	if (found != nullptr && found->data.first == key) {
		found->data.second = value;
		delete[] prev_nodes;
		return;
	}

	size_t level_new_node = random_level();
	if (level_new_node > _level) {
		for (size_t i = _level + 1; i <= level_new_node; ++i) {
			prev_nodes[i] = _head;
		}
		_level = level_new_node;
	}

	SNode<TKey, TValue>* new_node = new SNode<TKey, TValue>(key, value, level_new_node);
	for (size_t i = 0; i <= level_new_node; ++i) {
		new_node->next[i] = prev_nodes[i]->next[i];
		prev_nodes[i]->next[i] = new_node;
	}
	delete[] prev_nodes;
}

template <class TKey, class TValue>
void SkipList<TKey, TValue>::print() const noexcept {
	for (int i = (int)_level; i >= 0; --i) {
		std::cout << "Level " << i << ": head -> ";
		SNode<TKey, TValue>* cur = _head->next[i];
		while (cur != nullptr) {
			std::cout << "[" << cur->data << "] -> ";
			cur = cur->next[i];
		}
		std::cout << "nullptr" << std::endl;
	}
}

template <class TKey, class TValue>
size_t SkipList<TKey, TValue>::random_level() const noexcept {
	size_t level = 0;
	while (level < _max_level && std::rand() % 2 == 1) {
		++level;
	}
	return level;
}

template <class TKey, class TValue>
SNode<TKey, TValue>** SkipList<TKey, TValue>::find_nearest(const TKey& key) const {
	SNode<TKey, TValue>** prev_nodes = new SNode<TKey, TValue>* [_max_level + 1];
	for (size_t i = 0; i < _max_level + 1; ++i) {
		prev_nodes[i] = nullptr;
	}
	SNode<TKey, TValue>* cur = _head;
	for (int i = (int)_level; i >= 0; --i) {
		while (cur->next[i] != nullptr && cur->next[i]->data.first < key) {
			cur = cur->next[i];
		}
		prev_nodes[i] = cur;
	}
	return prev_nodes;
}

#endif // LIB_SKIP_LIST_SKIP_LIST_H