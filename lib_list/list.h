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
	inline Node<T>* head() { return _head; }
	inline const Node<T>* head() const {
		return this->_head;
	}
	inline Node<T>* tail() { return _tail; }
	inline const Node<T>* tail() const {
		return this->_tail;
	}
	bool is_empty() const {
		return _head == nullptr;
	}
	void push_front(const T& value) {
		Node<T>* node = new Node<T>(value, _head);
		if (is_empty()) {
			_tail = node;
		}
		_head = node;
	}
	void push_back(const T& value) {
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
	void insert(size_t pos, const T& value) {
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
	void insert(Node<T>* node, const T& value) {
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
	void pop_front() {
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
	void pop_back() {
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
	void erase(size_t pos) {
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
	void erase(Node<T>* node) {
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
	List<T>& operator=(const List<T>& other) {
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
private:
	void clear() {
		Node<T>* cur = _head;
		while (cur != nullptr) {
			Node<T>* next_node = cur->next;
			delete cur;
			cur = next_node;
		}
		_head = nullptr;
		_tail = nullptr;
	}
	bool is_node_in_list(Node<T>* node) const {
		Node<T>* cur = _head;
		while (cur != nullptr) {
			if (cur == node) {
				return true;
			}
			cur = cur->next;
		}
		return false;
	}
};

#endif