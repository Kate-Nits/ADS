// Copyright 2026 Ekaterina Ushnitskaya

#ifndef LIB_MONOM_MONOM_H
#define LIB_MONOM_MONOM_H

#include <iostream>
#include <stdexcept>

#include "../lib_algorithms/algorithms.h"

class Monom {
	double _coef;
	int _px;
	int _py;
	int _pz;

public:
	Monom() : _coef(0.0), _px(0), _py(0), _pz(0) {}
	Monom(double value_coef, int value_px, int value_py, int value_pz) : _coef(value_coef), _px(value_px), _py(value_py), _pz(value_pz) {}
	Monom(const Monom& other) {
		if (&other == NULL) {
			throw std::logic_error("Error!");
		}
		_coef = other._coef;
		_px = other._px;
		_py = other._py;
		_pz = other._pz;
	}
	double coef() { return _coef; }
	int px() { return _px; }
	int py() { return _py; }
	int pz() { return _pz; }
	Monom& operator=(const Monom& other);
	bool operator==(const Monom& other) const;
	bool operator!=(const Monom& other) const;
	Monom operator+(const Monom& other) const;
	Monom operator-(const Monom& other) const;
	Monom operator*(const Monom& other) const;
	Monom operator*(double value) const;
	Monom operator/(const Monom& other) const;
	Monom operator/(double value) const;
	Monom operator-() const;
	Monom& operator+=(const Monom& other);
	Monom& operator-=(const Monom& other);
	Monom& operator*=(const Monom& other);
	Monom& operator/=(const Monom& other);
	double calculate(double x, double y, double z) const;
	friend std::ostream& operator<<(std::ostream& s, const Monom& monom);
	friend std::istream& operator >>(std::istream& s, Monom& monom);
};

#endif // LIB_MONOM_MONOM_H