// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_DSU_DSU_H
#define LIB_DSU_DSU_H

#include <iostream>
#include <stdexcept>

class DSU {
	int* _parent;
	size_t _size;
public:
	DSU(size_t size) : _size(size) {
		_parent = new int[size];
		for (size_t i = 0; i < size; ++i) {
			_parent[i] = i;
		}
	}
	~DSU() {
		delete[] _parent;
	}
	void my_union(int x, int y);
	int find(int x);
};

#endif // LIB_DSU_DSU_H