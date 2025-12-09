// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_NODE_NODE_H
#define LIB_NODE_NODE_H

template <class T>
struct Node {
	T value;
	Node* next;

	explicit Node(const T& value_, Node* next_ = nullptr) : value(value_), next(next_) {}
};

template <class T>
struct NodeD {
	T value;
	NodeD* next;
	NodeD* prev;

	explicit NodeD(const T& value_, NodeD* next_ = nullptr, NodeD* prev_ = nullptr)
		: value(value_), next(next_), prev(prev_) {}
};

#endif