// Copyright 2025 Ekaterina Ushnitskaya

#ifndef LIB_PARSER_PARSER_H
#define LIB_PARSER_PARSER_H

#include <iostream>
#include "../lib_list/list.h"
#include "../lib_lexem/lexem.h"

namespace Parser {
	List<Lexem> parse(const std::string& expression);
	bool is_digit(char c);
	bool is_alphabet(char c);
	bool is_digit_and_alphabet(char c);
	bool is_space(char c);
	bool is_operator(char c);
	int priority(char operation);
	bool is_identified_symbol(char c);
	double string_to_double(const std::string& str);
}

#endif // LIB_PARSER_PARSER_H