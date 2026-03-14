// Copyright 2026 Ekaterina Ushnitskaya

#include "../lib_monom/monom.h"

Monom& Monom::operator=(const Monom& other) {
	if (this != &other) {
		_coef = other._coef;
		_px = other._px;
		_py = other._py;
		_pz = other._pz;
	}
	return *this;
}
bool Monom::operator==(const Monom& other) const {
	return _px == other._px && _py == other._py && _pz == other._pz;
}
bool Monom::operator!=(const Monom& other) const {
	return !(*this == other);
}
Monom Monom::operator+(const Monom& other) const {
	if (*this != other) {
		throw std::logic_error("Monoms are not similar");
	}
	return Monom(_coef + other._coef, _px, _py, _pz);
}
Monom Monom::operator-(const Monom& other) const {
	if (*this != other) {
		throw std::logic_error("Monoms are not similar");
	}
	return Monom(_coef - other._coef, _px, _py, _pz);
}
Monom Monom::operator*(const Monom& other) const {
	return Monom(_coef * other._coef, _px + other._px, _py + other._py, _pz + other._pz);
}
Monom Monom::operator*(double value) const {
	return Monom(value * _coef, _px, _py, _pz);
}
Monom Monom::operator/(const Monom& other) const {
	if (other._coef == 0.0) {
		throw std::logic_error("Can't because division by zero");
	}
	return Monom(_coef / other._coef, _px - other._px, _py - other._py, _pz - other._pz);
}
Monom Monom::operator/(double value) const {
	if (value == 0.0) {
		throw std::logic_error("Can't because division by zero");
	}
	return Monom(_coef / value, _px, _py, _pz);
}
Monom Monom::operator-() const {
	return Monom(-_coef, _px, _py, _pz);
}
Monom& Monom::operator+=(const Monom& other) {
	*this = *this + other;
	return *this;
}
Monom& Monom::operator-=(const Monom& other) {
	*this = *this - other;
	return *this;
}
Monom& Monom::operator*=(const Monom& other) {
	*this = *this * other;
	return *this;
}
Monom& Monom::operator/=(const Monom& other) {
	*this = *this / other;
	return *this;
}
double Monom::calculate(double x, double y, double z) const {
	return _coef * my_pow(x, _px) * my_pow(y, _py) * my_pow(z, _pz);
}
std::ostream& operator<<(std::ostream& s, const Monom& monom) {
	s << monom._coef;
	if (monom._px != 0) { s << "x^" << monom._px; }
	if (monom._py != 0) { s << "y^" << monom._py; }
	if (monom._pz != 0) { s << "z^" << monom._pz; }
	return s;
}
std::istream& operator >>(std::istream& s, Monom& monom) {
	s >> monom._coef >> monom._px >> monom._py >> monom._pz;
	return s;
}