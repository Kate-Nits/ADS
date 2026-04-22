// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_UNSORTEDTABLEONLIST_UNSORTEDTABLEONLIST_H
#define LIB_UNSORTEDTABLEONLIST_UNSORTEDTABLEONLIST_H

#include "../lib_table/table.h"
#include "../lib_list/list.h"
#include "../lib_node/node.h"

template <class TKey, class TValue>
class UnsortedTableOnList : public Table<TKey, TValue> {

    List<Pair<TKey, TValue>> _rows;

public:
    UnsortedTableOnList() = default;
    ~UnsortedTableOnList() = default;

    void insert(const TKey&, const TValue&) override;
    void erase(const TKey&) override;
    const TValue* found(const TKey&) const noexcept override;
    bool is_empty() const noexcept override;
    void print(std::ostream& os = std::cout) const noexcept override;

private:
    const Node<Pair<TKey, TValue>>* find_node_const(const TKey&) const noexcept;
    Node<Pair<TKey, TValue>>* find_node(const TKey&) noexcept;
    Node<Pair<TKey, TValue>>* find_prev(const TKey&) noexcept;
};

template<class TKey, class TValue>
const Node<Pair<TKey, TValue>>* UnsortedTableOnList<TKey, TValue>::find_node_const(const TKey& key) const noexcept {
    const Node<Pair<TKey, TValue>>* cur = _rows.head();
    while (cur != nullptr) {
        if (cur->value.first == key) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

template<class TKey, class TValue>
Node<Pair<TKey, TValue>>* UnsortedTableOnList<TKey, TValue>::find_node(const TKey& key) noexcept {
    Node<Pair<TKey, TValue>>* cur = _rows.head();
    while (cur != nullptr) {
        if (cur->value.first == key) {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

template<class TKey, class TValue>
Node<Pair<TKey, TValue>>* UnsortedTableOnList<TKey, TValue>::find_prev(const TKey& key) noexcept {
    Node<Pair<TKey, TValue>>* cur = _rows.head();
    if (cur == nullptr || cur->value.first == key) {
        return nullptr;
    }
    while (cur->next != nullptr) {
        if (cur->next->value.first == key) {
            return cur;
        }
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
void UnsortedTableOnList<TKey, TValue>::erase(const TKey& key) { // точно ли правильно работает???
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
bool UnsortedTableOnList<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template<class TKey, class TValue>
void UnsortedTableOnList<TKey, TValue>::print(std::ostream& os) const noexcept {
    this->print_line(os);
    this->print_title(os);
    this->print_line(os);

    const Node<Pair<TKey, TValue>>* cur = _rows.head();
    while (cur != nullptr) {
        os << "|";
        this->print_key(os, cur->value.first, WIDTH_KEY);
        this->print_value(os, cur->value.second, WIDTH_VALUE);
        os << "\n";
        cur = cur->next;
    }
    this->print_line(os);
}

#endif // LIB_UNSORTEDTABLEONLIST_UNSORTEDTABLEONLIST_H