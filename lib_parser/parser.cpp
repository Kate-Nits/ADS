// Copyright 2025 Ekaterina Ushnitskaya

#include <sstream> // std::ostringstream

#include "../lib_parser/parser.h"

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

bool Parser::is_valid_variable_name(const std::string& name) {
	if (name.empty()) { return false; }
	if (!is_alphabet(name[0]) && name[0] != '_') { return false; }
	for (char c : name) {
		if (!is_identified_symbol(c)) {
			return false;
		}
	}
	if (name == "sin" || name == "cos" || name == "tg" || name == "abs") {
		return false;
	}
	return true;
}

List<Lexem> Parser::parse(const std::string& expression) {
	if (!check_brackets(expression)) {
		throw std::logic_error("Incorrect brackets in expression");
	}
	List<Lexem> lexems;
	size_t i = 0;
	Lexem* prev = nullptr;
	int abs_count = 0;
	while (i < expression.length()) {
		if (is_space(expression[i])) {
			++i;
			continue;
		}

		if (is_digit(expression[i])) {
			std::string number;
			bool has_digit = false;
			while (i < expression.length() && 
				(is_digit(expression[i]) || expression[i] == '.')) {
				number += expression[i++];
				has_digit = true;
			}
			if (i < expression.length() && (is_alphabet(expression[i]) || expression[i] == '_')) {
				std::ostringstream error;
				error << "Invalid number format: number cannot be immediately followed by letter or underscore at position " << i;
				throw std::logic_error(error.str());
			}
			if (!has_digit) { throw std::invalid_argument("No digits in number"); }
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
				lexems.push_back(Lexem(name, TypeLexem::Function, DBL_MAX, 4, my_sin));
				prev = &lexems.tail()->value;
				continue;
			}
			else if (name == "cos") {
				lexems.push_back(Lexem(name, TypeLexem::Function, DBL_MAX, 4, my_cos));
				prev = &lexems.tail()->value;
				continue;
			}
			else if (name == "tg") {
				lexems.push_back(Lexem(name, TypeLexem::Function, DBL_MAX, 4, my_tg));
				prev = &lexems.tail()->value;
				continue;
			}
			else if (name == "abs") {
				lexems.push_back(Lexem(name, TypeLexem::Function, DBL_MAX, 4, my_abs));
				prev = &lexems.tail()->value;
				continue;
			}
			else {
				if (!is_valid_variable_name(name)) {
					std::ostringstream error;
					error << "Invalid variable name '" << name << "' at position " << (i - name.length());
					throw std::logic_error(error.str());
				}
				lexems.push_back(Lexem(name, TypeLexem::Variable));
				prev = &lexems.tail()->value;
				continue;
			}
		}

		if (expression[i] == '|') {
			bool is_open = true;
			if (prev != nullptr) {
				if (prev->type == TypeLexem::Constant ||
					prev->type == TypeLexem::Variable ||
					prev->type == TypeLexem::CloseBracket) {
					is_open = false;
				}
			}
			if (is_open) {
				lexems.push_back(Lexem("abs", TypeLexem::Function, DBL_MAX, 4, my_abs));
				lexems.push_back(Lexem("(", TypeLexem::OpenBracket));
				abs_count++;
			}
			else {
				lexems.push_back(Lexem(")", TypeLexem::CloseBracket));
				abs_count--;
				if (abs_count < 0) { throw std::logic_error("Too many closing |"); }
			}
			prev = &lexems.tail()->value;
			++i;
			continue;
			/*bool open_abs = (prev == nullptr || prev->type == Operator || prev->type == OpenBracket);
			if (open_abs) {
				lexems.push_back(Lexem("abs", Function, 0, 4, my_abs));
				lexems.push_back(Lexem("(", OpenBracket));
				abs_count++;
			}
			else {
				lexems.push_back(Lexem(")", CloseBracket));
				abs_count--;
				if (abs_count < 0) {
					throw std::logic_error("A lot of closing |");
				}
			}
			prev = &lexems.tail()->value;
			++i;
			continue;*/
		}

		if (is_open_bracket(expression[i])) {
			lexems.push_back(Lexem(std::string(1, expression[i]), TypeLexem::OpenBracket));
			prev = &lexems.tail()->value;
			++i;
			continue;
		}
		if (is_close_bracket(expression[i])) {
			lexems.push_back(Lexem(std::string(1, expression[i]), TypeLexem::CloseBracket));
			prev = &lexems.tail()->value;
			++i;
			continue;
		}

		if (expression[i] == '-') {
			bool unar = false;
			if (prev == nullptr || prev->type == TypeLexem::Operator
				|| prev->type == TypeLexem::OpenBracket ||
				prev->type == TypeLexem::Function ||
				prev->type == TypeLexem::UnOperator) {
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
	if (abs_count > 0) { throw std::logic_error("Unclosed | (missing closing |)"); }
	return lexems;
}