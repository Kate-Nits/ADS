// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_QUEUE_QUEUE_H
#define LIB_QUEUE_QUEUE_H

#include <stdexcept>
#include <iostream>

template <class T>
class Queue {
	T* _data;
	size_t _size;
	size_t _head; // указывает на первый элемент
	size_t _tail; // указывает на следующее свободное место
	size_t _count;
public:
	static const size_t RESERVE_MEMORY = 20;
	Queue() : _data(new T[RESERVE_MEMORY]), _size(RESERVE_MEMORY), _head(0), _tail(0), _count(0) {}
	explicit Queue(size_t size) : _data(new T[size]), _size(size), _head(0), _tail(0), _count(0) {}

	Queue(const Queue& other) : _data(new T[other._size]), _size(other._size), _head(other._head), _tail(other._tail), _count(other._count) {
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = other._data[i];
		}
	}
	~Queue() noexcept { delete[] _data; }

	T& tail();
	const T& tail() const;
	T& head();
	const T& head() const;
	inline size_t capacity() const noexcept;
	inline size_t count() const noexcept;
	bool is_empty() const noexcept;
	bool is_full() const noexcept;
	void clear() noexcept;

	void push(T value);
	void pop();
};


template <class T>
T& Queue<T>::tail() {
	if (is_empty()) {
		throw std::underflow_error("Queue is empty (no tail element)");
	}
	size_t last;
	if (_tail == 0) {
		last = _size - 1;
	}
	else {
		last = _tail - 1;
	}
	return _data[last];
}
template <class T>
const T& Queue<T>::tail() const {
	if (is_empty()) {
		throw std::underflow_error("Queue is empty (no tail element)");
	}
	size_t last;
	if (_tail == 0) {
		last = _size - 1;
	}
	else {
		last = _tail - 1;
	}
	return _data[last];
}
template <class T>
T& Queue<T>::head() {
	if (is_empty()) {
		throw std::underflow_error("Queue is empty (no head element)");
	}
	return _data[_head];
}
template <class T>
const T& Queue<T>::head() const {
	if (is_empty()) {
		throw std::underflow_error("Queue is empty (no head element)");
	}
	return _data[_head];
}
template <class T>
inline size_t Queue<T>::capacity() const noexcept {
	return _size;
}
template <class T>
inline size_t Queue<T>::count() const noexcept {
	return _count;
}
template <class T>
bool Queue<T>::is_empty() const noexcept {
	return _count == 0;
}
template <class T>
bool Queue<T>::is_full() const noexcept {
	return _count == _size;
}
template <class T>
void Queue<T>::clear() noexcept {
	_head = 0;
	_tail = 0;
	_count = 0;
}
template <class T>
void Queue<T>::push(T value) {
	if (is_full()) {
		throw std::overflow_error("Queue overflow (can't push element)");
	}
	_data[_tail] = value;
	_tail = (_tail + 1) % _size;
	++_count;
}
template <class T>
void Queue<T>::pop() {
	if (is_empty()) {
		throw std::underflow_error("Queue underflow (can't pop element)");
	}
	_head = (_head + 1) % _size;
	--_count;
}
#endif // LIB_QUEUE_QUEUE_H