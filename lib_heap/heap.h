// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_HEAP_HEAP_H
#define LIB_HEAP_HEAP_H

#include <stdexcept>

template <class T>
class Heap {
	T* _data;
	size_t _size;
	size_t _capacity;
public:
	Heap() : _data(nullptr), _size(0), _capacity(0) {}
	Heap(size_t capacity) : _data(nullptr), _size(0), _capacity(0) {
		if (capacity > 0) {
			_data = new T[capacity];
			_capacity = capacity;
		}
	}
	Heap(const Heap<T>& other) : _data(nullptr), _size(other._size), _capacity(other._capacity) {
		if (_capacity > 0) {
			_data = new T[_capacity];
			for (size_t i = 0; i < _size; ++i) {
				_data[i] = other._data[i];
			}
		}
	}
	~Heap() {
		delete[] _data;
	}

	Heap<T>& operator=(const Heap<T>& other) {
		if (this == &other) {
			return *this;
		}
		delete[] _data;
		_data = nullptr;
		_size = other._size;
		_capacity = other._capacity;
		if (_capacity > 0) {
			_data = new T[_capacity];
			for (size_t i = 0; i < _size; ++i) {
				_data[i] = other._data[i];
			}
		}
		return *this;
	}
	bool is_empty() const {
		return _size == 0;
	}
	size_t size() const {
		return _size;
	}
	const T& get_min() const {
		if (is_empty()) {
			throw std::underflow_error("Heap is empty");
		}
		return _data[0];
	}

	void insert(const T& value) {
		if (_size == _capacity) {
			if (_capacity == 0) {
				reserve(1);
			}
			else {
				reserve(_capacity * 2);
			}
		}
		_data[_size] = value;
		sift_up(_size);
		_size++;
	}

	T get_and_delete_min() {
		if (is_empty()) {
			throw std::underflow_error("Heap is empty!");
		}
		T min_value = _data[0];
		_data[0] = _data[_size - 1];
		_size--;
		if (!is_empty()) {
			sift_down(0);
		}
		return min_value;
	}
	void clear() {
		delete[] _data;
		_data = nullptr;
		_size = 0;
		_capacity = 0;
	}
private:
	size_t left(size_t i) {
		return 2 * i + 1;
	}
	size_t right(size_t i) {
		return 2 * i + 2;
	}
	size_t parent(size_t i) {
		return (i - 1) / 2;
	}
	void swap(T& a, T& b) {
		T tmp = a;
		a = b;
		b = tmp;
	}
	void reserve(size_t new_capacity) {
		if (new_capacity <= _capacity) { return; }
		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < _size; ++i) {
			new_data[i] = _data[i];
		}
		delete[] _data;
		_data = new_data;
		_capacity = new_capacity;
	}
	void sift_up(size_t index) {
		while (index > 0) {
			size_t parent_index = parent(index);
			if (_data[parent_index] <= _data[index]) { break; }
			swap(_data[parent_index], _data[index]);
			index = parent_index;
		}
	}
	void sift_down(size_t index) {
		while (1) {
			size_t left_index = left(index);
			size_t right_index = right(index);
			size_t smallest = index;
			if (left_index < _size && _data[left_index] < _data[smallest]) { smallest = left_index; }
			if (right_index < _size && _data[right_index] < _data[smallest]) { smallest = right_index; }
			if (smallest == index) { break; }
			swap(_data[index], _data[smallest]);
			index = smallest;
		}
	}
};

template <class T>
void heap_sort(T* mass, size_t size) {
	if (mass == mullptr && size > 0) { throw std::invalid_argument("Mass can't be nullptr"); }
	Heap<T> heap(size);
	for (size_t i = 0; i < size; ++i) { heap.insert(mass[i]); }
	for (size_t i = 0; i < size; ++i) {
		mass[i] = heap.get_and_delete_min();
	}
}

#endif // LIB_HEAP_HEAP_H