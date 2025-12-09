// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_DLIST_DLIST_H
#define LIB_DLIST_DLIST_H

#include <stdexcept>
#include <iostream>

#include "../lib_node/node.h"

template <class T>
class DList {
	NodeD<T>* _head;
	NodeD<T>* _tail;
public:
	DList() : _head(nullptr), _tail(nullptr) {}
	DList(const DList<T>& other) : _head(nullptr), _tail(nullptr) {
		NodeD<T>* cur = other._head;
		while (cur != nullptr) {
			push_back(cur->value);
			cur = cur->next;
		}
	}
	~DList() {
		clear();
	}
	class Iterator {
		NodeD<T>* _current;
	public:
		Iterator() : _current(nullptr) {}
		Iterator(NodeD<T>* ptr) : _current(ptr) {}

		Iterator& operator=(const Iterator& other) {
			if (this != &other) {
				_current = other._current;
			}
			return *this;
		}
		Iterator operator++(int) { //iterator++
			Iterator tmp = *this;
			if (_current != nullptr) {
				_current = _current->next;
			}
			return tmp;
		}
		Iterator& operator++() { // ++iterator
			if (_current != nullptr) {
				_current = _current->next;
			}
			return *this;
		}
		bool operator!=(const Iterator& other) const {
			return _current != other._current;
		}
		bool operator==(const Iterator& other) const {
			return !(*this != other);
		}
		T& operator*() {
			return _current->value;
		}
		Iterator& operator+=(size_t n) {
			while (n > 0 && _current != nullptr) {
				_current = _current->next;
				n--;
			}
			return *this;
		}
		Iterator operator--(int) { //iterator--
			Iterator tmp = *this;
			if (_current != nullptr) {
				_current = _current->prev;
			}
			return tmp;
		}
		Iterator& operator--() { //--iterator
			if (_current != nullptr) {
				_current = _current->prev;
			}
			return *this;
		}
		Iterator& operator-=(size_t n) {
			while (n > 0 && _current != nullptr) {
				_current = _current->prev;
				n--;
			}
			return *this;
		}
	};
	Iterator begin() { return Iterator(_head); }
	Iterator end() { return Iterator(nullptr); }
	Iterator rbegin() { return Iterator(_tail); }
	Iterator rend() { return Iterator(nullptr); }

	inline NodeD<T>* head();
	inline const NodeD<T>* head() const;
	inline NodeD<T>* tail();
	inline const NodeD<T>* tail() const;
	bool is_empty() const;
	void push_front(const T& value);
	void push_back(const T& value);
	void insert(size_t pos, const T& value);
	void insert_after(NodeD<T>* node, const T& value);
	void insert_before(NodeD<T>* node, const T& value);
	void pop_front();
	void pop_back();
	void erase(NodeD<T>* node);
	void erase(size_t pos);
	DList<T>& operator=(const DList<T>& other);
private:
	void clear();
	bool is_node_in_list(NodeD<T>* node) const;
};

template <class T>
inline NodeD<T>* DList<T>::head() { return _head; }

template <class T>
inline const NodeD<T>* DList<T>::head() const { return _head; }

template <class T>
inline NodeD<T>* DList<T>::tail() { return _tail; }
template <class T>
inline const NodeD<T>* DList<T>::tail() const { return _tail; }

template <class T>
bool DList<T>::is_empty() const { return _head == nullptr; }

template <class T>
void DList<T>::push_front(const T& value) { // O(1)
	NodeD<T>* node = new NodeD<T>(value, _head, nullptr);
	if (is_empty()) {
		_tail = node;
	}
	else {
		_head->prev = node;
	}
	_head = node;
}

template <class T>
void DList<T>::push_back(const T& value) { // O(1)
	NodeD<T>* node = new NodeD<T>(value, nullptr, _tail);
	if (is_empty()) {
		_head = node;
	}
	else {
		_tail->next = node;
	}
	_tail = node;
}

template <class T>
void DList<T>::insert(size_t pos, const T& value) { // O(n)
	if (pos == 0) {
		push_front(value);
		return;
	}
	NodeD<T>* cur = _head;
	for (size_t i = 0; i < pos; ++i) {
		if (cur == nullptr) {
			throw std::out_of_range("Position out of range");
		}
		cur = cur->next;
	}
	if (cur == nullptr) {
		push_back(value);
		return;
	}
	insert_before(cur, value);
}

template <class T>
void DList<T>::insert_after(NodeD<T>* node, const T& value) { // O(1)
	if (node == nullptr) {
		throw std::invalid_argument("Node can't be nullptr");
	}
	if (!is_node_in_list(node)) {
		throw std::invalid_argument("Node is not in List");
	}

	NodeD<T>* new_node = new NodeD<T>(value, node->next, node);
	node->next = new_node;
	if (new_node->next != nullptr) {
		new_node->next->prev = new_node;
	}
	else {
		_tail = new_node;
	}
}

template <class T>
void DList<T>::insert_before(NodeD<T>* node, const T& value) { // O(1)
	if (node == nullptr) {
		throw std::invalid_argument("Node can't be nullptr");
	}
	if (!is_node_in_list(node)) {
		throw std::invalid_argument("Node is not in List");
	}

	NodeD<T>* new_node = new NodeD<T>(value, node, node->prev);
	node->prev = new_node;
	if (new_node->prev != nullptr) {
		new_node->prev->next = new_node;
	}
	else {
		_head = new_node;
	}
}

template <class T>
void DList<T>::pop_front() { // O(1)
	if (is_empty()) {
		throw std::underflow_error("List is empty");
	}
	NodeD<T>* old_head = _head;
	_head = _head->next;
	if (_head != nullptr) {
		_head->prev = nullptr;
	}
	else {
		_tail = nullptr;
	}
	delete old_head;
}

template <class T>
void DList<T>::pop_back() { // O(1)
	if (is_empty()) {
		throw std::underflow_error("List is empty");
	}
	NodeD<T>* old_tail = _tail;
	_tail = _tail->prev;
	if (_tail != nullptr) {
		_tail->next = nullptr;
	}
	else {
		_head = nullptr;
	}
	delete old_tail;
}

template <class T>
void DList<T>::erase(NodeD<T>* node) { // O(1)
	if (node == nullptr) {
		throw std::invalid_argument("Node can't be nullptr");
	}
	if (is_empty()) {
		throw std::underflow_error("List is empty");
	}
	if (!is_node_in_list(node)) {
		throw std::invalid_argument("Node is not in List");
	}
	if (node == _head) {
		pop_front();
		return;
	}
	if (node == _tail) {
		pop_back();
		return;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
	delete node;
}


template <class T>
void DList<T>::erase(size_t pos) { // O(n)
	if (is_empty()) {
		throw std::underflow_error("List is empty");
	}
	NodeD<T>* cur = _head;
	for (size_t i = 0; i < pos; ++i) {
		if (cur == nullptr) {
			throw std::out_of_range("Position out of range");
		}
		cur = cur->next;
	}
	if (cur == nullptr) {
		throw std::out_of_range("Position out of range");
	}
	erase(cur);
}

template <class T>
DList<T>& DList<T>::operator=(const DList<T>& other) {
	if (this == &other) {
		return *this;
	}
	clear();
	NodeD<T>* other_cur = other._head;
	while (other_cur != nullptr) {
		push_back(other_cur->value);
		other_cur = other_cur->next;
	}
	return *this;
}

template <class T>
void DList<T>::clear() {
	NodeD<T>* cur = _head;
	while (cur != nullptr) {
		NodeD<T>* next_node = cur->next;
		delete cur;
		cur = next_node;
	}
	_head = nullptr;
	_tail = nullptr;
}

template <class T>
bool DList<T>::is_node_in_list(NodeD<T>* node) const {
	NodeD<T>* cur = _head;
	while (cur != nullptr) {
		if (cur == node) {
			return true;
		}
		cur = cur->next;
	}
	return false;
}

#endif