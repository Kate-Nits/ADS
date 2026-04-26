// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_ITABLE_ITABLE_H
#define LIB_ITABLE_ITABLE_H

#include <iostream>
#include <stdexcept>
#include "../lib_pair/pair.h"

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

#endif // LIB_ITABLE_ITABLE_H