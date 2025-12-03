// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_STACK_STACK_H
#define LIB_STACK_STACK_H

#include <stdexcept>
#include <iostream>
#include "../lib_tvector/tvector.h"


template <class T>
class Stack {
	TVector<T> _data;
	size_t _count; // счётчик реально добавленных элементов
	size_t _max_capacity; // для ограничения размеров стека
public:
	static const size_t RESERVE_MEMORY = 20;
	Stack() : _data(), _count(0), _max_capacity(RESERVE_MEMORY) {
		_data.reserve(_max_capacity);
	}
	explicit Stack(size_t size) : _data(), _count(0), _max_capacity(size) {
		_data.reserve(_max_capacity);
	}
	Stack(const Stack<T>& other) : _data(other._data), _count(other._count), _max_capacity(other._max_capacity) {}

	inline size_t count() const noexcept;
	inline size_t capacity() const noexcept;
	bool is_full() const noexcept;
	bool is_empty() const noexcept;
	void clear() noexcept;

	void push(const T& value);
	void pop();
	T& top();
	const T& top() const;
};


template <class T>
inline size_t Stack<T>::count() const noexcept {
	return _count;
}
template <class T>
inline size_t Stack<T>::capacity() const noexcept {
	return _max_capacity;
}
template <class T>
bool Stack<T>::is_full() const noexcept {
	return _count >= _max_capacity;
}
template <class T>
bool Stack<T>::is_empty() const noexcept {
	return _count == 0;
}
template <class T>
void Stack<T>::clear() noexcept {
	_count = 0;
	_data.clear();
}
template <class T>
void Stack<T>::push(const T& value) {
	if (is_full()) {
		throw std::overflow_error("Stack overflow: cannot push, because stack is full");
	}
	if (_data.size() >= _data.capacity()) {
		throw std::overflow_error("Stack overflow: stack is full");
	}
	_data.push_back(value);
	++_count;
}
template <class T>
void Stack<T>::pop() {
	if (is_empty()) {
		throw std::underflow_error("Stack is empty (can't pop from empty stack)");
	}
	_data.pop_back();
	--_count;
}
template <class T>
T& Stack<T>::top() {
	if (is_empty()) {
		throw std::underflow_error("Stack is empty (no top element)");
	}
	return _data.back();
}
template <class T>
const T& Stack<T>::top() const {
	if (is_empty()) {
		throw std::underflow_error("Stack is empty (no top element");
	}
	return _data.back();
}

#endif // LIB_STACK_STACK_H