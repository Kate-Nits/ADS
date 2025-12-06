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
	List();
	List(const List<T>&);
	~List();
	Node<T>* head();
	Node<T>* tail();
	bool is_empty();
	void push_front(const T& value) noexcept;
	void push_back(const T& value) noexcept;
	void insert(size_t pos, const T& value);
	void insert(Node<T>* node, const T& value);
};

#endif