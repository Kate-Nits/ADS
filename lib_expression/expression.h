// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_EXPRESSION_EXPRESSION_H
#define LIB_EXPRESSION_EXPRESSION_H

#include "../lib_list/list.h"
#include "../lib_stack/stack.h"
#include "../lib_tvector/tvector.h"
#include "../lib_lexem/lexem.h"

class Expression {
	List<Lexem> _lexems;
	List<Lexem> _polish_record;
	TVector<std::string> _variables;
	TVector<double> _values;
public:
	explicit Expression(const List<Lexem>& lexems);
	TVector<std::string> get_variables() {
		return _variables;
	}
	List<Lexem> get_lexems() {
		return _lexems;
	}
	TVector<double> get_values() {
		return _values;
	}
	void set_values(size_t variable, double value);
	void build_polish_record();
	double calculate() const;
};

#endif // LIB_EXPRESSION_EXPRESSION_H
