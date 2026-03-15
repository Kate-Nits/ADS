// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_ITABLE_ITABLE_H
#define LIB_ITABLE_ITABLE_H

#include <iostream>
#include <stdexcept>

template <class TFirst, class TSecond>
struct Pair {
    TFirst first;
    TSecond second;

    Pair();
    Pair(const TFirst& f, const TSecond& s);

    Pair& operator=(const Pair& other) noexcept;

    bool operator==(const Pair<TFirst, TSecond>& other) const;
    bool operator<(const Pair<TFirst, TSecond>& other) const;
    bool operator>(const Pair<TFirst, TSecond>& other) const;

    friend std::ostream& operator<<(std::ostream& s, const Pair<TFirst, TSecond>& pair) {
        s << pair.first << ":" << pair.second;
        return s;
    }
};

template <class TKey, class TValue>
class ITable {
public:
    virtual ~ITable() = default;

    virtual void insert(const TKey&, const TValue&) = 0;
    virtual void erase(const TKey&) = 0;
    virtual const TValue* found(const TKey&) const noexcept = 0;

    virtual bool is_empty() const noexcept = 0;
    virtual void print(std::ostream& os = std::cout) const noexcept = 0;
};

template <class TFirst, class TSecond>
Pair<TFirst, TSecond>::Pair() {
    first = TFirst();
    second = TSecond();
}
template <class TFirst, class TSecond>
Pair<TFirst, TSecond>::Pair(const TFirst& f, const TSecond& s) {
    first = f;
    second = s;
}
template <class TFirst, class TSecond>
Pair<TFirst, TSecond>& Pair<TFirst, TSecond>::operator=(const Pair& other) noexcept {
    if (this != &other) {
        first = other.first;
        second = other.second;
    }
    return *this;
}
template <class TFirst, class TSecond>
bool Pair<TFirst, TSecond>::operator==(const Pair<TFirst, TSecond>& other) const {
    return first == other.first;
}
template <class TFirst, class TSecond>
bool Pair<TFirst, TSecond>::operator<(const Pair<TFirst, TSecond>& other) const {
    return first < other.first;
}
template <class TFirst, class TSecond>
bool Pair<TFirst, TSecond>::operator>(const Pair<TFirst, TSecond>& other) const {
    return first > other.first;
}

#endif // LIB_ITABLE_ITABLE_H