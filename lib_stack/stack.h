// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_STACK_STACK_H
#define LIB_STACK_STACK_H

#include <stdexcept>
#include <iostream>
#include "../lib_tvector/tvector.h"


template <class T>
class Stack {
	TVector<T> _data;
	size_t _max_capacity; // для ограничения размеров стека
public:
	Stack() : _data(), _max_capacity(0) {}
	explicit Stack(size_t size) : _data(0), _max_capacity(size) {}
	Stack(const Stack<T>& other) : _data(other._data), _max_capacity(other._max_capacity) {}

	size_t size() const noexcept {
		return _data.size() - _data.deleted();
	}
	bool is_full() const noexcept {
		return _max_capacity > 0 && this->size() >= _max_capacity;
	}
	bool is_empty() const noexcept {
		return _data.is_empty();
	}
	void clear() noexcept {
		_data.clear();
	}

	void push(const T& value) {
		if (is_full()) {
			throw std::overflow_error("Stack overflow: cannot push, because stack is full");
		}
		_data.push_back(value);
	}

	T& top() {
		if (is_empty()) {
			throw std::underflow_error("Stack is empty (no top element");
		}
		return _data.back();
	}
	const T& top() const {
		if (is_empty()) {
			throw std::underflow_error("Stack is empty (no top element");
		}
		return _data.back();
	}
};


#endif // LIB_STACK_STACK_H