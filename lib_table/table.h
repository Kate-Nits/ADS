// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_TABLE_TABLE_H
#define LIB_TABLE_TABLE_H

#include <iostream>
#include <sstream>
#include <string>

#include "../lib_itable/itable.h"

#define WIDTH_KEY 10
#define WIDTH_VALUE 40
#define WIDTH_DIVIDER 3
#define WIDTH_SUM WIDTH_KEY + WIDTH_VALUE + WIDTH_DIVIDER

template <class TKey, class TValue>
class Table : public ITable<TKey, TValue> {
public:
    virtual ~Table() = default;

    virtual void insert(const TKey&, const TValue&) override = 0;
    virtual void erase(const TKey&) override = 0;
    virtual const TValue* found(const TKey&) const noexcept override = 0;
    virtual bool is_empty() const noexcept override = 0;
    virtual void print(std::ostream& os = std::cout) const noexcept override = 0;

    friend std::ostream& operator<<(std::ostream& os, const Table<TKey, TValue>& table) {
        table.print(os);
        return os;
    }

protected:
    void print_title(std::ostream& os) const noexcept;
    void print_line(std::ostream& os) const noexcept;
    void print_key(std::ostream& os, const TKey& key, int width) const noexcept;
    void print_value(std::ostream& os, const TValue& val, int width) const noexcept;
};

template <class TKey, class TValue>
void Table<TKey, TValue>::print_title(std::ostream& os) const noexcept {
    os << "|";
    os << " KEY";
    for (int i = 0; i < WIDTH_KEY - 4; i++) {
        os << " ";
    }
    os << "|";
    os << " VALUE";
    for (int i = 0; i < WIDTH_VALUE - 6; i++) {
        os << " ";
    }
    os << "|\n";
}
template <class TKey, class TValue>
void Table<TKey, TValue>::print_line(std::ostream& os) const noexcept {
    os << "+";
    for (int i = 0; i < WIDTH_SUM - 2; i++) {
        os << "-";
    }
    os << "+\n";
}
template <class TKey, class TValue>
void Table<TKey, TValue>::print_key(std::ostream& os, const TKey& key, int width) const noexcept {
    std::ostringstream out;
    out << key;
    std::string str = out.str();
    os << " " << str;
    for (int i = 0; i < width - str.length() - 1; i++) {
        os << " ";
    }
    os << "|";
}
template <class TKey, class TValue>
void Table<TKey, TValue>::print_value(std::ostream& os, const TValue& val, int width) const noexcept {
    std::ostringstream out;
    out << val;
    std::string str = out.str();
    os << " " << str;
    for (int i = 0; i < width - str.length() - 1; i++) {
        os << " ";
    }
    os << "|";
}

#endif // LIB_TABLE_TABLE_H