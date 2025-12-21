// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_LIST_LIST_H
#define LIB_LIST_LIST_H

#include <stdexcept>
#include <iostream>

#include "../lib_node/node.h"

template <class T>
class List {
	Node<T>* _head;
	Node<T>* _tail;
public:
	List() : _head(nullptr), _tail(nullptr) {}
	List(const List<T>& other) : _head(nullptr), _tail(nullptr) {
		Node<T>* cur = other._head;
		while (cur != nullptr) {
			push_back(cur->value);
			cur = cur->next;
		}
	}
	~List() {
		clear();
	}
	class Iterator {
		Node<T>* _current;
	public:
		Iterator() : _current(nullptr) {}
		Iterator(Node<T>* ptr) : _current(ptr) {}

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
	};
	Iterator begin() { return Iterator(_head); }
	Iterator end() { return Iterator(nullptr); }
	const Iterator begin() const { return Iterator(_head); }  
	const Iterator end() const { return Iterator(nullptr); }

	inline Node<T>* head();
	inline const Node<T>* head() const;
	inline Node<T>* tail();
	inline const Node<T>* tail() const;
	bool is_empty() const;
	void push_front(const T& value);
	void push_back(const T& value);
	void insert(size_t pos, const T& value);
	void insert(Node<T>* node, const T& value);
	void pop_front();
	void pop_back();
	void erase(size_t pos);
	void erase(Node<T>* node);
	List<T>& operator=(const List<T>& other);
	void clear();
private:
	bool is_node_in_list(Node<T>* node) const;
};

template <class T>
inline Node<T>* List<T>::head() { return _head; }

template <class T>
inline const Node<T>* List<T>::head() const { return this->_head; }

template <class T>
inline Node<T>* List<T>::tail() { return _tail; }

template <class T>
inline const Node<T>* List<T>::tail() const { return this->_tail; }

template <class T>
bool List<T>::is_empty() const {
	return _head == nullptr;
}

template <class T>
void List<T>::push_front(const T& value) {
	Node<T>* node = new Node<T>(value, _head);
	if (is_empty()) {
		_tail = node;
	}
	_head = node;
}

template <class T>
void List<T>::push_back(const T& value) {
	Node<T>* node = new Node<T>(value, nullptr);
	if (is_empty()) {
		_head = node;
		_tail = node;
	}
	else {
		_tail->next = node;
		_tail = node;
	}
}

template <class T>
void List<T>::insert(size_t pos, const T& value) {
	if (pos == 0) {
		push_front(value);
		return;
	}
	Node<T>* cur = _head;
	for (size_t i = 0; i < pos - 1; ++i) {
		if (cur == nullptr) {
			throw std::out_of_range("Position out of range");
		}
		cur = cur->next;
	}
	if (cur == nullptr) {
		throw std::out_of_range("Position out of range");
	}
	if (cur == _tail) {
		push_back(value);
	}
	else {
		Node<T>* node = new Node<T>(value, cur->next);
		cur->next = node;
	}
}

template <class T>
void List<T>::insert(Node<T>* node, const T& value) {
	if (node == nullptr) {
		throw std::invalid_argument("Node can't be nullptr");
	}
	if (!is_node_in_list(node)) {
		throw std::invalid_argument("Node is not in List");
	}
	Node<T>* new_node = new Node<T>(value, node->next);
	node->next = new_node;
	if (node == _tail) {
		_tail = new_node;
	}
}

template <class T>
void List<T>::pop_front() {
	if (is_empty()) {
		throw std::underflow_error("List is empty");
	}
	Node<T>* old_head = _head;
	_head = _head->next;
	if (old_head == _tail) {
		_tail = nullptr;
	}
	delete old_head;
}

template <class T>
void List<T>::pop_back() {
	if (is_empty()) {
		throw std::underflow_error("List is empty");
	}
	if (_head == _tail) {
		Node<T>* node_to_delete = _head;
		_head = nullptr;
		_tail = nullptr;
		delete node_to_delete;
		return;
	}
	Node<T>* cur = _head;
	while (cur->next != _tail) {
		cur = cur->next;
	}
	Node<T>* node_to_delete = _tail;
	_tail = cur;
	cur->next = nullptr;
	delete node_to_delete;
}

template <class T>
void List<T>::erase(size_t pos) {
	if (is_empty()) {
		throw std::underflow_error("List is empty");
	}
	if (pos == 0) {
		pop_front();
		return;
	}
	Node<T>* cur = _head;
	for (size_t i = 0; i < pos - 1; ++i) {
		if (cur == nullptr) {
			throw std::out_of_range("Position out of range");
		}
		cur = cur->next;
	}
	if (cur == nullptr || cur->next == nullptr) {
		throw std::out_of_range("Position out of range");
	}
	Node<T>* node_to_delete = cur->next;
	if (node_to_delete == _tail) {
		_tail = cur;
	}
	cur->next = node_to_delete->next;
	delete node_to_delete;
}

template <class T>
void List<T>::erase(Node<T>* node) {
	if (node == nullptr) {
		throw std::invalid_argument("Node can't be nullptr");
	}
	if (!is_node_in_list(node)) {
		throw std::invalid_argument("Node is not in List");
	}
	if (node == _head) {
		pop_front();
		return;
	}
	Node<T>* cur = _head;
	while (cur->next != node) {
		cur = cur->next;
	}
	Node<T>* node_to_delete = cur->next;
	if (node_to_delete == _tail) {
		_tail = cur;
	}
	cur->next = node_to_delete->next;
	delete node_to_delete;
}

template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
	if (this == &other) {
		return *this;
	}
	clear();
	Node<T>* other_cur = other._head;
	while (other_cur != nullptr) {
		push_back(other_cur->value);
		other_cur = other_cur->next;
	}
	return *this;
}

template <class T>
void List<T>::clear() {
	Node<T>* cur = _head;
	while (cur != nullptr) {
		Node<T>* next_node = cur->next;
		delete cur;
		cur = next_node;
	}
	_head = nullptr;
	_tail = nullptr;
}

template <class T>
bool List<T>::is_node_in_list(Node<T>* node) const {
	Node<T>* cur = _head;
	while (cur != nullptr) {
		if (cur == node) {
			return true;
		}
		cur = cur->next;
	}
	return false;
}

#endif