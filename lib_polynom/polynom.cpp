// Copyright 2026 Ekaterina Ushnitskaya

#include "../lib_polynom/polynom.h"

Polynom::Polynom() {}
Polynom::Polynom(const std::string& str) {
	std::string s;
	for (size_t k = 0; k < str.size(); k++) {
		char c = str[k];
		if (c != ' ') { s += c; }
	}
	size_t i = 0;
	while (i < s.size()) {
		double coef = 1.0;
		int px = 0, py = 0, pz = 0;
		int sign = 1;
		if (s[i] == '+') { i++; }
		else if (s[i] == '-') {
			sign = -1;
			i++;
		}
		size_t start = i;
		bool has_digit = false;
		while (i < s.size() && (Parser::is_digit(s[i]) || s[i] == '.')) {  // проверить не поднимался ли flag иначе ..
			has_digit = true; 
			i++;
		}
		if (has_digit) {
			std::string number;
			for (size_t j = start; j < i; j++) { number += s[j]; }
			// coef = Parser::string_to_double(number);
			coef = std::stod(number);
		}
		coef *= sign;
		while (i < s.size()) {
			if (s[i] != 'x' && s[i] != 'y' && s[i] != 'z') { break; }
			char var = s[i];
			i++;
			int power = 1;
			if (i < s.size() && s[i] == '^') {
				i++;
				size_t p_start = i;
				while (i < s.size() && Parser::is_digit(s[i])) { i++; }
				std::string str_power;
				for (size_t j = p_start; j < i; j++) { str_power += s[j]; }
				power = 0;
				for (size_t j = 0; j < str_power.size(); j++) { power = power * 10 + (str_power[j] - '0'); }
			}
			if (var == 'x') { px = power; }
			if (var == 'y') { py = power; }
			if (var == 'z') { pz = power; }
		}
		add_monom(Monom(coef, px, py, pz));
	}
}
Polynom& Polynom::operator=(const Polynom& other) {
	if (this != &other) { monoms = other.monoms; }
	return *this;
}
bool Polynom::is_zero() const {
	return monoms.is_empty();
}
Polynom Polynom::operator+(const Polynom& other) const {
	Polynom result(*this);
	const Node<Monom>* cur = other.monoms.head();
	while (cur != nullptr) {
		result.add_monom(cur->value);
		cur = cur->next;
	}
	return result;
}
Polynom Polynom::operator-(const Polynom& other) const {
	Polynom result(*this);
	const Node<Monom>* cur = other.monoms.head();
	while (cur != nullptr) {
		result.add_monom(-cur->value);
		cur = cur->next;
	}
	return result;
}
Polynom Polynom::operator*(const Polynom& other) const {
	Polynom result;
	const Node<Monom>* polynom1 = monoms.head();
	while (polynom1 != nullptr) {
		const Node<Monom>* polynom2 = other.monoms.head();
		while (polynom2 != nullptr) {
			Monom m = polynom1->value * polynom2->value;
			result.add_monom(m);
			polynom2 = polynom2->next;
		}
		polynom1 = polynom1->next;
	}
	return result;
}
Polynom Polynom::operator/(const Polynom& divisor) const { // 
	if (divisor.is_zero()) { throw std::logic_error("Can't, because division by zero"); }
	Polynom remainder(*this); // остаток
	Polynom result;
	while (!remainder.is_zero()) {
		Monom m1 = remainder.leading_term();
		Monom m2 = divisor.leading_term();
		if (m1.px() < m2.px() || m1.py() < m2.py() || m1.pz() < m2.pz()) { break; }
		Monom div = m1 / m2;
		Polynom tmp;
		tmp.add_monom(div);
		result += tmp;
		remainder -= tmp * divisor;
	}
	return result;
}
Polynom& Polynom::operator+=(const Polynom& other) {
	*this = (*this) + other;
	return *this;
}
Polynom& Polynom::operator-=(const Polynom& other) {
	*this = (*this) - other;
	return *this;
}
Polynom& Polynom::operator*=(const Polynom& other) {
	*this = (*this) * other;
	return *this;
}
Polynom& Polynom::operator/=(const Polynom& other) {
	*this = (*this) / other;
	return *this;
}
double Polynom::calculate(double x, double y, double z) const {
	double result = 0;
	const Node<Monom>* cur = monoms.head();
	while (cur != nullptr) {
		result += cur->value.calculate(x, y, z);
		cur = cur->next;
	}
	return result;
}
std::ostream& operator<<(std::ostream& s, const Polynom& polynom) {
	const Node<Monom>* cur = polynom.monoms.head();
	if (cur == nullptr) {
		s << "0";
		return s;
	}
	bool first = true;
	while (cur != nullptr) {
		double coef = cur->value.coef();
		int px = cur->value.px();
		int py = cur->value.py();
		int pz = cur->value.pz();
		if (!first) {
			if (coef >= 0) { s << " + "; }
			else {
				s << " - ";
			}
		}
		else {
			if (coef < 0) { s << "-"; }
			first = false;
		}
		double abs_coef = (coef < 0) ? -coef : coef;
		bool has_variable = (px != 0 || py != 0 || pz != 0);
		if (!has_variable || abs_coef != 1.0) { s << abs_coef; }
		if (px > 0) {
			s << "x";
			if (px > 1) { s << "^" << px; }
		}
		if (py > 0) {
			s << "y";
			if (py > 1) { s << "^" << py; }
		}
		if (pz > 0) {
			s << "z";
			if (pz > 1) { s << "^" << pz; }
		}
		cur = cur->next;
	}
	return s;
}

bool Polynom::greater(const Monom& monom1, const Monom& monom2) {
	if (monom1.px() != monom2.px()) { return monom1.px() > monom2.px(); }
	if (monom1.py() != monom2.py()) { return monom1.py() > monom2.py(); }
	return monom1.pz() > monom2.pz();
}
void Polynom::add_monom(const Monom& new_monom) {
	if (new_monom.coef() == 0) { return; }
	Node<Monom>* cur = monoms.head();
	Node<Monom>* prev = nullptr;
	while (cur != nullptr) {
		if (cur->value == new_monom) {
			Monom sum = cur->value + new_monom;
			if (sum.coef() == 0) {
				if (prev == nullptr) {
					monoms.pop_front();
				}
				else {
					monoms.erase(cur);
				}
			}
			else {
				cur->value = sum;
			}
			return;
		}
		if (greater(new_monom, cur->value)) { break; }
		prev = cur;
		cur = cur->next;
	}
	if (prev == nullptr) { monoms.push_front(new_monom); }
	else { monoms.insert(prev, new_monom); }
}
Monom Polynom::leading_term() const {
	const Node<Monom>* node = monoms.head();
	return Monom(node->value.coef(), node->value.px(),
		node->value.py(), node->value.pz());
}