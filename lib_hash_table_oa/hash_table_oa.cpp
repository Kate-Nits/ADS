// Copyright 2026 Ekaterina Ushnitskaya

#include "../lib_hash_table_oa/hash_table_oa.h"

bool is_mutually_simple(size_t first, size_t second) noexcept {
	return nod(first, second) == 1;
}

size_t nod(size_t first, size_t second) noexcept {
	while (second != 0) {
		size_t tmp = second;
		second = first % second;
		first = tmp;
	}
	return first;
}