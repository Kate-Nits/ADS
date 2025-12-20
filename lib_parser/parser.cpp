// Copyright 2025 Ekaterina Ushnitskaya

#include <sstream> // std::ostringstream

#include "../lib_parser/parser.h"
#include "../lib_algorithms/algorithms.h"

bool Parser::is_digit(char symbol) {
	return symbol >= '0' && symbol <= '9';
}
bool Parser::is_alphabet(char symbol) {
	return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z');
}
bool Parser::is_digit_and_alphabet(char symbol) {
	return Parser::is_digit(symbol) || Parser::is_alphabet(symbol);
}
bool Parser::is_space(char symbol) {
	return symbol == ' ' || symbol == '\t' || symbol == '\n';
}
bool Parser::is_operator(char symbol) {
	return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^';
}
int Parser::priority(char operation) {
	if (operation == '+' || operation == '-') { return 1; }
	if (operation == '*' || operation == '/') { return 2; }
	if (operation == '^') { return 3; }
	return -1;
}
bool Parser::is_identified_symbol(char symbol) {
	return Parser::is_digit_and_alphabet(symbol) || symbol == '_';
}
double Parser::string_to_double(const std::string& str) {
	if (str.empty()) {
		throw std::invalid_argument("Empty string can not convert to double");
	}
	double result = 0.0;
	double divisor = 1.0;
	bool is_minus = false;
	bool has_digits = false;
	bool has_point = false;
	size_t i = 0;
	if (str[i] == '-') {
		is_minus = true;
		i++;
	}
	else if (str[i] == '+') {
		i++;
	}
	if (i >= str.length()) {
		throw std::invalid_argument("Not number");
	}
	for (; i < str.length(); ++i) {
		char c = str[i];
		if (is_digit(c)) {
			has_digits = true;
			int digit = c - '0';
			if (!has_point) {
				result = result * 10.0 + digit;
			}
			else {
				result += digit / divisor;
				divisor *= 10.0;
			}

		}
		else if (c == '.') {
			if (has_point) {
				throw std::invalid_argument("Number can not have more than one point");
			}
			has_point = true;
			divisor = 10.0;
		}
		++i;
	}
	if (!has_digits) {
		throw std::invalid_argument("No digits in number");
	}
	if (is_minus) {
		return (-1.0)*result;
	}
	else {
		return result;
	}
}
List<Lexem> Parser::parse(const std::string& expression) {
	if (!check_brackets(expression)) {
		throw std::logic_error("Incorrect brackets in expression");
	}
	List<Lexem> lexems;
	size_t i = 0;
	Lexem* prev = nullptr;
	while (i < expression.length()) {
		if (is_space(expression[i])) {
			++i;
			continue;
		}

		if (is_digit(expression[i])) {
			std::string number;
			while (i < expression.length() && 
				(is_digit(expression[i]) || expression[i] == '.')) {
				number += expression[i++];
			}
			lexems.push_back(Lexem(number, TypeLexem::Constant, string_to_double(number)));
			prev = &lexems.tail()->value;
			continue;
		}

		if (is_alphabet(expression[i]) || expression[i] == '_') {
			std::string name;
			while (i < expression.length() && is_identified_symbol(expression[i])) {
				name += expression[i++];
			}

			if (name == "sin") {
				lexems.push_back(Lexem(name, TypeLexem::Function, DBL_MAX, 3, std::sin));
			}
			else if (name == "cos") {
				lexems.push_back(Lexem(name, TypeLexem::Function, DBL_MAX, 3, std::cos));
			}
			else if (name == "tg") {
				lexems.push_back(Lexem(name, TypeLexem::Function, DBL_MAX, 3, std::tan));
			}
			else {
				lexems.push_back(Lexem(name, TypeLexem::Variable));
			}
			prev = &lexems.tail()->value;
			continue;
		}

		if (is_open_bracket(expression[i])) {
			lexems.push_back(Lexem(std::string(1, expression[1]), TypeLexem::OpenBracket));
			prev = &lexems.tail()->value;
			++i;
			continue;
		}
		if (is_close_bracket(expression[i])) {
			lexems.push_back(Lexem(std::string(1, expression[1]), TypeLexem::CloseBracket));
			prev = &lexems.tail()->value;
			++i;
			continue;
		}

		if (expression[i] == '-') {
			bool unar = false;
			if (prev == nullptr || prev->type == TypeLexem::Operator
				|| prev->type == TypeLexem::OpenBracket) {
				unar = true;
			}
			if (unar) {
				lexems.push_back(Lexem("-", TypeLexem::UnOperator, DBL_MAX, 4));
			}
			else {
				lexems.push_back(Lexem("-", TypeLexem::Operator, DBL_MAX, 1));
			}
			prev = &lexems.tail()->value;
			++i;
			continue;
		}

		if (is_operator(expression[i])) {
			lexems.push_back(Lexem(std::string(1, expression[i]), TypeLexem::Operator, DBL_MAX, Parser::priority(expression[i])));
			prev = &lexems.tail()->value;
			++i;
			continue;
		}

		std::ostringstream error;
		error << "Unknown symbol '" << expression[i] << "' at position " << i;
		throw std::logic_error(error.str());
	}
	return lexems;
}