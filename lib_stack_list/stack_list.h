// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_STACK_LIST_STACK_LIST_H
#define LIB_STACK_LIST_STACK_LIST_H

#include <stdexcept>
#include <iostream>
#include "../lib_list/list.h"

template <class T>
class StackList {
	List<T> _list;
	size_t _count;
	size_t _max_capacity;
public:
	static const size_t RESERVE_MEMORY = 20;
	StackList() : _list(), _count(0), _max_capacity(RESERVE_MEMORY) {}
	explicit StackList(size_t size) : _list(), _count(0), _max_capacity(size) {}
	StackList(const StackList& other) : _list(other._list), _count(other._count), _max_capacity(other._max_capacity) {}

	inline size_t count() const noexcept {
		return _count;
	}
	inline size_t capacity() const noexcept {
		return _max_capacity;
	}
	bool is_full() const noexcept {
		return _count >= _max_capacity;
	}
	bool is_empty() const noexcept {
		return _count == 0;
	}
	void clear() noexcept {
		_list.clear();
		_count = 0;
	}

	void push(const T& value) {
		if (is_full()) {
			throw std::overflow_error("Stack overflow: cannot push, because stack is full");
		}
		_list.push_front(value);
		_count++;
	}
	void pop() {
		if (is_empty()) {
			throw std::underflow_error("Stack is empty");
		}
		_list.pop_front();
		_count--;
	}
	T& top() {
		if (is_empty()) {
			throw std::underflow_error("Stack is empty");
		}
		return _list.head()->value;
	}
	const T& top() const {
		if (is_empty()) {
			throw std::underflow_error("Stack is empty");
		}
		return _list.head()->value;
	}
};
#endif // LIB_STACK_LIST_STACK_LIST_H