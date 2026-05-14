// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_HASH_TABLE_OA_HASH_TABLE_OA_H
#define LIB_HASH_TABLE_OA_HASH_TABLE_OA_H

#include <string>
#include <stdexcept>

#include "../lib_tvector/tvector.h"
#include "../lib_table/table.h"

#define SIMPLE_NUMBER 31

template <class TValue>
struct HashData {
	State state;
	Pair<std::string, TValue> pair;

	HashData(const std::string& value_key = "", const TValue& value_value = TValue(), State value_state = State::empty);
	HashData& operator=(const HashData& other);
	bool operator==(const HashData<TValue>& other) const noexcept;
};

template <class TValue>
HashData<TValue>::HashData(const std::string& value_key, const TValue& value_value, State value_state) {
	state = value_state;
	pair = Pair<std::string, TValue>(value_key, value_value);
}

template <class TValue>
HashData<TValue>& HashData<TValue>::operator=(const HashData& other) {
	if (this == &other) {
		return *this;
	}
	else {
		state = other.state;
		pair = other.pair;
	}
	return *this;
}

template <class TValue>
bool HashData<TValue>::operator==(const HashData<TValue>& other) const noexcept {
	return state == other.state && pair == other.pair;
}

bool is_mutually_simple(size_t first, size_t second) noexcept;
size_t nod(size_t first, size_t second) noexcept;

template <class TValue>
class HashTableOA : public Table<std::string, TValue> {
	TVector<HashData<TValue>> _rows;
	size_t _size;
	size_t _count;
public:
	HashTableOA(size_t value_size = 15);
	~HashTableOA() = default;

	void insert(const std::string& key, const TValue& value) override;
	void erase(const std::string& key) override;
	const TValue* found(const std::string& key) const noexcept override;
	bool is_empty() const noexcept override;
	bool is_full() const noexcept;
	void print(std::ostream& os = std::cout) const noexcept override;
private:
	size_t h(const std::string& key) const noexcept;
	size_t hh(const std::string& key) const noexcept;
	size_t next(size_t hash, size_t step) const noexcept;
};

template <class TValue>
HashTableOA<TValue>::HashTableOA(size_t value_size) : _rows(value_size), _size(value_size), _count(0) {
	if (value_size < 2) {
		throw std::invalid_argument("Size for HashTable must be more than 1");
	}
}

template <class TValue>
void HashTableOA<TValue>::insert(const std::string& key, const TValue& value) {
	if (is_full()) {
		throw std::invalid_argument("Hash table is full");
	}
	size_t hash = h(key);
	size_t step = hh(key);
	size_t first_deleted = _size;
	for (size_t i = 0; i < _size; ++i) {
		if (_rows[hash].state == busy) {
			if (_rows[hash].pair.first == key) { throw std::invalid_argument("Key already exists"); }
		}
		else if (_rows[hash].state == deleted) {
			if (first_deleted == _size) {
				first_deleted = hash;
			}
		}
		else {
			size_t index;
			if (first_deleted == _size) {
				index = hash;
			}
			else {
				index = first_deleted;
			}
			_rows[index] = HashData<TValue>(key, value, busy);
			_count++;
			return;
		}
		hash = next(hash, step);
	}
	if (first_deleted != _size) {
		_rows[first_deleted] = HashData<TValue>(key, value, busy);
		_count++;
		return;
	}
	throw std::invalid_argument("HashTableOA is full");
}

template <class TValue>
void HashTableOA<TValue>::erase(const std::string& key) {
	size_t hash = h(key);
	size_t step = hh(key);
	for (size_t i = 0; i < _size; ++i) {
		if (_rows[hash].state == empty) { break; }
		if (_rows[hash].state == busy && _rows[hash].pair.first == key) {
			_rows[hash].state = deleted;
			_count--;
			return;
		}
		hash = next(hash, step);
	}
	throw std::invalid_argument("Key not found");
}

template <class TValue>
const TValue* HashTableOA<TValue>::found(const std::string& key) const noexcept {
	size_t hash = h(key);
	size_t step = hh(key);
	for (size_t i = 0; i < _size; ++i) {
		if (_rows[hash].state == empty) { return nullptr; }
		if (_rows[hash].state == busy && _rows[hash].pair.first == key) {
			return &_rows[hash].pair.second;
		}
		hash = next(hash, step);
	}
	return nullptr;
}

template <class TValue>
bool HashTableOA<TValue>::is_empty() const noexcept {
	return _count == 0;
}

template <class TValue>
bool HashTableOA<TValue>::is_full() const noexcept {
	return _count == _size;
}

template <class TValue>
void HashTableOA<TValue>::print(std::ostream& os) const noexcept {
	this->print_line(os);
	this->print_title(os);
	this->print_line(os);
	for (size_t i = 0; i < _rows.size(); ++i) {
		if (_rows[i].state == busy) {
			os << "|";
			this->print_key(os, _rows[i].pair.first, WIDTH_KEY);
			this->print_value(os, _rows[i].pair.second, WIDTH_VALUE);
			os << "\n";
		}
	}
	this->print_line(os);
}

template <class TValue>
size_t HashTableOA<TValue>::h(const std::string& key) const noexcept {
	size_t hash = 0;
	for (size_t i = 0; i < key.length(); ++i) {
		hash += (size_t)key[i];
	}
	return hash % _size;
}

template <class TValue>
size_t HashTableOA<TValue>::hh(const std::string& key) const noexcept {
	size_t hash = 0;
	for (size_t i = 0; i < key.length(); ++i) {
		hash = hash * SIMPLE_NUMBER + (size_t)key[i];
	}
	size_t step = 1 + hash % (_size - 1);
	while (!is_mutually_simple(step, _size)) {
		++step;
		if (step == _size) {
			step = 1;
		}
	}
	return step;
}

template <class TValue>
size_t HashTableOA<TValue>::next(size_t hash, size_t step) const noexcept {
	return (hash + step) % _size;
}

#endif // LIB_HASH_TABLE_OA_HASH_TABLE_OA_H