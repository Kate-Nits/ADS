// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_SORTEDTABLEONARRAY_SORTEDTABLEONARRAY_H
#define LIB_SORTEDTABLEONARRAY_SORTEDTABLEONARRAY_H

#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"

template <class TKey, class TValue>
class SortedTableOnArray : public Table<TKey, TValue> {
    TVector<Pair<TKey, TValue>> _rows;
public:
    SortedTableOnArray() = default;
    ~SortedTableOnArray() = default;

    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;
    const TValue* found(const TKey& key) const noexcept override;
    bool is_empty() const noexcept override;
    void print(std::ostream& os = std::cout) const noexcept override;

private:
    int binary_search(const TKey& key) const noexcept;
    int find_insert_pos(const TKey& key) const noexcept;
};

template <class TKey, class TValue>
int SortedTableOnArray<TKey, TValue>::binary_search(const TKey& key) const noexcept {
    int left = 0;
    int right = (int)_rows.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (_rows[mid].first == key) { return mid; }
        else if (_rows[mid].first < key) { left = mid + 1; }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

template <class TKey, class TValue>
int SortedTableOnArray<TKey, TValue>::find_insert_pos(const TKey& key) const noexcept { // лучше бинарным
    int left = 0;
    int right = (int)_rows.size();
    while (left < right) {
        int mid = (left + right) / 2;

        if (_rows[mid].first < key) { 
            left = mid + 1; 
        }
        else {
            right = mid;
        }
    }
    return left;
}

template <class TKey, class TValue>
void SortedTableOnArray<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (binary_search(key) != -1) { throw std::invalid_argument("Key already exists"); }
    int pos = find_insert_pos(key);
    _rows.push_back(Pair<TKey, TValue>(key, value));
    for (int i = _rows.size() - 1; i > pos; --i) {
        std::swap(_rows[i], _rows[i - 1]);
    }
}

template <class TKey, class TValue>
void SortedTableOnArray<TKey, TValue>::erase(const TKey& key) {
    int index = binary_search(key);
    if (index == -1) { throw std::invalid_argument("Key not found"); }
    _rows.erase(index);
    _rows.shrink_to_fit();
}

template <class TKey, class TValue>
const TValue* SortedTableOnArray<TKey, TValue>::found(const TKey& key) const noexcept {
    int index = binary_search(key);
    if (index == -1) { return nullptr; }
    return &_rows[index].second;
}

template <class TKey, class TValue>
bool SortedTableOnArray<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void SortedTableOnArray<TKey, TValue>::print(std::ostream& os) const noexcept {
    this->print_line(os);
    this->print_title(os);
    this->print_line(os);

    for (size_t i = 0; i < _rows.size(); i++) {
        os << "|";
        this->print_key(os, _rows[i].first, WIDTH_KEY);
        this->print_value(os, _rows[i].second, WIDTH_VALUE);
        os << "\n";
    }
    this->print_line(os);
}

#endif // LIB_SORTEDTABLEONARRAY_SORTEDTABLEONARRAY_H