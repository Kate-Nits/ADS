// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_QUEUE_LIST_QUEUE_LIST_H
#define LIB_QUEUE_LIST_QUEUE_LIST_H

#include <stdexcept>
#include <iostream>
#include "../lib_list/list.h"

template <class T>
class QueueList {
	List<T> _list;
	size_t _capacity;
	size_t _count;
public:
	static const size_t RESERVE_MEMORY = 20;
	QueueList() : _list(), _capacity(RESERVE_MEMORY), _count(0) {}
	explicit QueueList(size_t size) : _list(), _capacity(size), _count(0) {}
	QueueList(const QueueList& other) : _list(other._list), _capacity(other._capacity), _count(other._count) {}

	inline T& tail() {
		if (is_empty()) {
			throw std::underflow_error("Queue is empty (no tail element)");
		}
		return _list.tail()->value;
	}
	inline const T& tail() const {
		if (is_empty()) {
			throw std::underflow_error("Queue is empty (no tail element)");
		}
		return _list.tail()->value;
	}
	inline T& head() {
		if (is_empty()) {
			throw std::underflow_error("Queue is empty (no head element)");
		}
		return _list.head()->value;
	}
	inline const T& head() const {
		if (is_empty()) {
			throw std::underflow_error("Queue is empty (no head element)");
		}
		return _list.head()->value;
	}
	inline size_t capacity() const noexcept {
		return _capacity;
	}
	inline size_t count() const noexcept {
		return _count;
	}
	bool is_empty() const noexcept {
		return _count == 0;
	}
	bool is_full() const noexcept {
		return _count >= _capacity;
	}
	void clear() {
		_list.clear();
		_count = 0;
	}

	void push(const T& value) {
		if (is_full()) {
			throw std::overflow_error("Queue is full (can't push element)");
		}
		_list.push_back(value);
		_count++;
	}
	void pop() {
		if (is_empty()) {
			throw std::underflow_error("Queue is empty (can't pop element)");
		}
		_list.pop_front();
		_count--;
	}
};

#endif // LIB_QUEUE_LIST_QUEUE_LIST_H