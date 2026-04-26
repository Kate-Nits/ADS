// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_PAIR_PAIR_H
#define LIB_PAIR_PAIR_H

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

#endif // LIB_PAIR_PAIR_H