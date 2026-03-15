// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_POLYNOM_POLYNOM_H
#define LIB_POLYNOM_POLYNOM_H

#include <string>
#include <iostream>

#include "../lib_list/list.h"
#include "../lib_parser/parser.h"
#include "../lib_monom/monom.h"

class Polynom {
	List<Monom> monoms;
public:
	Polynom();
	Polynom(const Polynom& other) : monoms(other.monoms) {}
	Polynom(const std::string& str);
	Polynom& operator=(const Polynom& other);
	bool is_zero() const;
	Polynom operator+(const Polynom& other) const;
	Polynom operator-(const Polynom& other) const;
	Polynom operator*(const Polynom& other) const;
	Polynom operator/(const Polynom& divisor) const;
	Polynom& operator+=(const Polynom& other);
	Polynom& operator-=(const Polynom& other);
	Polynom& operator*=(const Polynom& other);
	Polynom& operator/=(const Polynom& other);
	double calculate(double x, double y, double z) const;
	friend std::ostream& operator<<(std::ostream& s, const Polynom& polynom);
private:
	bool greater(const Monom& monom1, const Monom& monom2);
	void add_monom(const Monom& new_monom);
	Monom leading_term() const;
};

#endif //  LIB_POLYNOM_POLYNOM_H