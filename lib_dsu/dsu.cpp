// Copyright 2025 Ekaterina Ushnitskaya

#include <iostream>
#include <stdexcept>

#include "../lib_dsu/dsu.h"

void DSU::my_union(int x, int y) {
	int parent_x = find(x);
	int parent_y = find(y);
	if (parent_x != parent_y) {
		_parent[parent_y] = parent_x;
	}
}
int DSU::find(int x) {
	if (x >= _size || x < 0) { throw std::invalid_argument("There is no such element"); }
	while (x != _parent[x]) {
		x = _parent[x];
	}
	return x;
}
