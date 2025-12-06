// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_NODE_NODE_H
#define LIB_NODE_NODE_H

#include <iostream>

template <class T>
struct Node {
	T value;
	Node* next;

	explicit Node(const T& value_, Node* next_ = nullptr) : value(value_), next(next_) {}
};

#endif