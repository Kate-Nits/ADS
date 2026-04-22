// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_UNSORTEDTABLEONARRAY_UNSORTEDTABLEONARRAY_H
#define LIB_UNSORTEDTABLEONARRAY_UNSORTEDTABLEONARRAY_H

#include "../lib_table/table.h"
#include "../lib_tvector/tvector.h"

template <class TKey, class TValue>
class UnsortedTableOnArray : public Table<TKey, TValue> {
    TVector<Pair<TKey, TValue>> _rows;
public:
    UnsortedTableOnArray();
    ~UnsortedTableOnArray();

    void insert(const TKey& key, const TValue& value) override;
    void erase(const TKey& key) override;
    const TValue* found(const TKey& key) const noexcept override;
    bool is_empty() const noexcept override;
    void print(std::ostream& os = std::cout) const noexcept override;
private:
    int find_index(const TKey& key) const noexcept;
};

template <class TKey, class TValue>
UnsortedTableOnArray<TKey, TValue>::UnsortedTableOnArray() : _rows() {}
template <class TKey, class TValue>
UnsortedTableOnArray<TKey, TValue>::~UnsortedTableOnArray() {}

template <class TKey, class TValue>
int UnsortedTableOnArray<TKey, TValue>::find_index(const TKey& key) const noexcept {
    for (size_t i = 0; i < _rows.size(); i++) {
        if (_rows.state(i) == busy && _rows[i].first == key) { return i; }
    }
    return -1;
}

template <class TKey, class TValue>
void UnsortedTableOnArray<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (find_index(key) != -1) { throw std::invalid_argument("Key already exists"); }
    _rows.push_back(Pair<TKey, TValue>(key, value));
}

template <class TKey, class TValue>
void UnsortedTableOnArray<TKey, TValue>::erase(const TKey& key) {
    int index = find_index(key);
    if (index == -1) { throw std::invalid_argument("Key not found"); }
    _rows.erase(index);
    _rows.shrink_to_fit();
}

template <class TKey, class TValue>
const TValue* UnsortedTableOnArray<TKey, TValue>::found(const TKey& key) const noexcept {
    int index = find_index(key);
    if (index == -1) { return nullptr; }
    return &_rows[index].second;
}

template <class TKey, class TValue>
bool UnsortedTableOnArray<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template <class TKey, class TValue>
void UnsortedTableOnArray<TKey, TValue>::print(std::ostream& os) const noexcept {
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

#endif // LIB_UNSORTEDTABLEONARRAY_UNSORTEDTABLEONARRAY_H