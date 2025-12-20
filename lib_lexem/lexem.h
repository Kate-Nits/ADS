// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_LEXEM_LEXEM_H
#define LIB_LEXEM_LEXEM_H

#include <iostream>
#include <cmath>

enum TypeLexem { Constant, Variable, OpenBracket, CloseBracket, Function, Operator, UnOperator };

struct Lexem {
	std::string name;
	TypeLexem type;
	double value; // значение (только для констант)
	int priority; // приоритет оператора
	double (*function)(double); // указатель на функцию (для sin, cos и т.д.)

	Lexem(const std::string& _name, TypeLexem _type, double _value = DBL_MAX, int _priority = -1, double (*_function)(double) = nullptr) :
		name(_name), type(_type), value(_value), priority(_priority), function(_function) {}
};
#endif // LIB_LEXEM_LEXEM_H