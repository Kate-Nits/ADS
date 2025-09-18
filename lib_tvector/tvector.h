// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_TVECTOR_TVECTOR_H
#define LIB_TVECTOR_TVECTOR_H

#include <iostream>
#include <cstdlib> // rand()
#include <stdexcept> // std::out_of_range, std::invalid_argument

enum State { empty, busy, deleted };
template <class T>
class TVector {
	T* _data;
	State* _states;
	size_t _size;
	size_t _capacity;
	size_t _deleted;
public:
	static const size_t RESERVE_MEMORY = 15;
	static const size_t MAX_PERCENT_DELETED = 15;
};

#endif // LIB_TVECTOR
