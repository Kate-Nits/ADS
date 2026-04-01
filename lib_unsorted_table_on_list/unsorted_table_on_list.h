// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_UNSORTEDTABLEONLIST_UNSORTEDTABLEONLIST_H
#define LIB_UNSORTEDTABLEONLIST_UNSORTEDTABLEONLIST_H

#include "../lib_table/table.h"
#include "../lib_list/list.h"

template <class TKey, class TValue>
class UnsortedTableOnList : public Table<TKey, TValue> {

    List<Pair<TKey, TValue>> _rows;

public:

    UnsortedTableOnList() = default;
    ~UnsortedTableOnList() = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    const TValue* found(const TKey&) const noexcept override;

// protected: из-за тестов
    size_t size() const noexcept override;
    const Pair<TKey, TValue>& get_row(size_t) const override;

private:
    const Node<Pair<TKey, TValue>>* find_node_const(const TKey&) const noexcept;
    Node<Pair<TKey, TValue>>* find_node(const TKey&) noexcept;
};

template<class TKey, class TValue>
const Node<Pair<TKey, TValue>>* UnsortedTableOnList<TKey, TValue>::find_node_const(const TKey& key) const noexcept {
    const Node<Pair<TKey, TValue>>* cur = _rows.head();
    while (cur != nullptr) {
        if (cur->value.first == key)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

template<class TKey, class TValue>
Node<Pair<TKey, TValue>>* UnsortedTableOnList<TKey, TValue>::find_node(const TKey& key) noexcept {
    Node<Pair<TKey, TValue>>* cur = _rows.head();
    while (cur != nullptr) {
        if (cur->value.first == key)
            return cur;
        cur = cur->next;
    }
    return nullptr;
}

template<class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::insert(const TKey& key, const TValue& value) {
    if (find_node(key) != nullptr) { throw std::invalid_argument("Key already exists"); }
    _rows.push_back(Pair<TKey, TValue>(key, value));
}

template<class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::erase(const TKey& key) {
    Node<Pair<TKey, TValue>>* node = find_node(key);
    if (node == nullptr) { throw std::invalid_argument("Key not found"); }
    _rows.erase(node);
}

template<class TKey, class TValue>
const TValue* UnsortedTableOnList<TKey, TValue>::found(const TKey& key) const noexcept {
    const Node<Pair<TKey, TValue>>* node = find_node_const(key);
    if (node == nullptr) { return nullptr; }
    return &(node->value.second);
}

template<class TKey, class TValue>
size_t UnsortedTableOnList<TKey, TValue>::size() const noexcept {
    size_t count = 0;
    const Node<Pair<TKey, TValue>>* cur = _rows.head();
    while (cur != nullptr) {
        count++;
        cur = cur->next;
    }
    return count;
}

template<class TKey, class TValue>
const Pair<TKey, TValue>& UnsortedTableOnList<TKey, TValue>::get_row(size_t index) const {
    const Node<Pair<TKey, TValue>>* cur = _rows.head();
    size_t i = 0;
    while (cur != nullptr) {
        if (i == index) { return cur->value; }
        cur = cur->next;
        i++;
    }
    throw std::out_of_range("Index out of range");
}

#endif // LIB_UNSORTEDTABLEONLIST_UNSORTEDTABLEONLIST_H