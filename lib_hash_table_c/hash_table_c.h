// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_HASH_TABLE_C_HASH_TABLE_C_H
#define LIB_HASH_TABLE_C_HASH_TABLE_C_H

#include <string>
#include <stdexcept>

#include "../lib_tvector/tvector.h"
#include "../lib_list/list.h"
#include "../lib_table/table.h"

#define SIMPLE_NUMBER 31
#define DEFAULT_SIZE 15

template <class TValue>
class HashTableC : public Table<std::string, TValue> {
	TVector<List<Pair<std::string, TValue>>> _rows;
	size_t _size;
	size_t _count;
public:
	HashTableC(size_t value_size = DEFAULT_SIZE);
	~HashTableC() = default;

	void insert(const std::string& key, const TValue& value) override;
	void erase(const std::string& key) override;
	const TValue* found(const std::string& key) const noexcept override;
	bool is_empty() const noexcept override;
	void print(std::ostream& os = std::cout) const noexcept override;
	template <class U>
	friend HashTableC<U> merge_dictionaries(const HashTableC<U>& first, const HashTableC<U>& second);
private:
	size_t h(const std::string& key) const noexcept;
};

template<class TValue>
HashTableC<TValue>::HashTableC(size_t value_size) : _rows(value_size), _size(value_size), _count(0) {
	if (value_size < 2) { 
		throw std::invalid_argument("Size for HashTable must be more than 1"); 
	}
}

template<class TValue>
void HashTableC<TValue>::insert(const std::string& key, const TValue& value) {
	size_t hash = h(key);
	const Node<Pair<std::string, TValue>>* found_node = _rows[hash].find(Pair<std::string, TValue>(key, value));
	if (found_node != nullptr) {
		throw std::invalid_argument("Key already exists");
	}
	_rows[hash].push_back(Pair<std::string, TValue>(key, value));
	_count++;
}

template<class TValue>
void HashTableC<TValue>::erase(const std::string& key) {
	size_t hash = h(key);
	if (_rows[hash].is_empty()) {
		throw std::invalid_argument("Key not found");
	}
	Node<Pair<std::string, TValue>>* current = _rows[hash].head();
	Node<Pair<std::string, TValue>>* prev = nullptr;
	while (current != nullptr) {
		if (current->value.first == key) {
			if (prev == nullptr) {
				_rows[hash].pop_front();
			}
			else {
				_rows[hash].erase(current);
			}
			_count--;
			return;
		}
		prev = current;
		current = current->next;
	}
	throw std::invalid_argument("Key not found");
}

template<class TValue>
const TValue* HashTableC<TValue>::found(const std::string& key) const noexcept {
	size_t hash = h(key);
	Pair<std::string, TValue> find_pair(key, TValue());
	const Node< Pair<std::string, TValue>>* find_node = _rows[hash].find(find_pair);
	if (find_node == nullptr) {
		return nullptr;
	}
	return &find_node->value.second;
}

template<class TValue>
bool HashTableC<TValue>::is_empty() const noexcept {
	return _count == 0;
}

template<class TValue>
void HashTableC<TValue>::print(std::ostream& os) const noexcept {
	this->print_line(os);
	this->print_title(os);
	this->print_line(os);
	for (size_t i = 0; i < _rows.size(); ++i) {
		for (auto it = _rows[i].begin(); it != _rows[i].end(); ++it) {
			os << "|";
			this->print_key(os, (*it).first, WIDTH_KEY);
			this->print_value(os, (*it).second, WIDTH_VALUE);
			os << "\n";
		}
	}
	this->print_line(os);
}

template<class TValue>
size_t HashTableC<TValue>::h(const std::string& key) const noexcept {
	size_t hash = 0;
	for (size_t i = 0; i < key.length(); ++i) {
		hash += key[i];
	}
	return hash % _size;
}

template <class U>
HashTableC<U> merge_dictionaries(const HashTableC<U>& first, const HashTableC<U>& second) {
	size_t new_size = first._size + second._size;
	if (new_size < 2) { new_size = DEFAULT_SIZE; }
	HashTableC<U> result(new_size);
	for (size_t i = 0; i < first._size; ++i) {
		const List<Pair<std::string, U>>& list1 = first._rows[i];
		for (auto it = list1.begin(); it != list1.end(); ++it) {
			const Pair<std::string, U>& pair = *it;
			result.insert(pair.first, pair.second);
		}
	}
	for (size_t i = 0; i < second._size; ++i) {
		const List<Pair<std::string, U>>& list2 = second._rows[i];
		for (auto it = list2.begin(); it != list2.end(); ++it) {
			const Pair<std::string, U>& pair = *it;
			const U* is_exist = result.found(pair.first);
			if (is_exist == nullptr) {
				result.insert(pair.first, pair.second);
			}
		}
	}
	return result;
}

#endif LIB_HASH_TABLE_C_HASH_TABLE_C_H