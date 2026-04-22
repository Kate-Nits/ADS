// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H
#define LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H

#include <stdexcept>
#include "../lib_heap/heap.h"

template <class T>
struct PriorityQueueNode {
	T value;
	int priority;
	size_t number_when_come;

	PriorityQueueNode() : value(), priority(0), number_when_come(1) {}
	PriorityQueueNode(const T& value_value, int value_priority, size_t value_number_when_come) : value(value_value), priority(value_priority), number_when_come(value_number_when_come) {}

	bool operator>(const PriorityQueueNode<T>& other) const {
		if (priority != other.priority) {
			return priority > other.priority;
		}
		else {
			return number_when_come > other.number_when_come;
		}
	}
};

template <class T>
class PriorityQueue {
	Heap< PriorityQueueNode<T>> _heap;
	size_t number_when_come = 1;
public:
	PriorityQueue() : _heap() {}
	PriorityQueue(size_t capacity) : _heap(capacity) {}

	bool is_empty() const {
		return _heap.is_empty();
	}
	size_t size() const {
		return _heap.size();
	}
	const T& top_value() const {
		return _heap.get_min().value;
	}
	const T& top_priority() const {
		return _heap.get_min().priority;
	}

	void push(const T& value, int priority) {
		_heap.insert(PriorityQueueNode<T>(value, priority, number_when_come++));
	}
	void pop() {
		if (is_empty()) { throw std::underflow_error("PriorityQueue is empty! Can't pop"); }
		_heap.get_and_delete_min();
	}
	void get_top_value_and_pop() {
		if (is_empty()) { throw std::underflow_error("PriorityQueue is empty! Can't pop"); }
		return _heap.get_and_delete_min().value;
	}
	void clear() {
		_heap.clear();
	}
};

template <class T>
T* find_k_most_priority(const PriorityQueueNode<T>* mass, size_t size, size_t k) {
	if (mass == nullptr) { throw std::invalid_argument("Mass can't be nullptr"); }
	if (k > size) { throw std::invalid_argument("k can't be greater than size"); }
	if (k == 0) { throw std::logic_error("k can't be equal 0"); }

	PriorityQueue<T> queue(k);
	for (size_t i = 0; i < size_t; ++i) {
		queue.push(mass[i]);
	}
	
	T* result = new T[k];
	for (size_t i = 0; i < k; ++i) {
		result[i] = queue.get_top_value_and_pop();
	}
	return result;
	/*
	for (size_t i = 0; i < k; ++i) {
		heap.insert(mass[i]);
	}
	for (size_t i = k; i < size; ++i) {
		if (mass[i] > heap.get_min()) {
			heap.get_and_delete_min();
			heap.insert(mass[i]);
		}
	}
	T* result = new T[k];
	for (size_t i = k; i > 0; --i) {
		result[i - 1] = heap.get_and_delete_min();
	}
	return result;
	*/
	
}

#endif // LIB_PRIORITY_QUEUE_PRIORITY_QUEUE_H