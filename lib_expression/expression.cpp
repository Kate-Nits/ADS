// Copyright 2025 Ekaterina Ushnitskaya

#include "../lib_expression/expression.h"

Expression::Expression(const List<Lexem>& lexems) : _lexems(lexems) {
	for (auto it = _lexems.begin(); it != _lexems.end(); ++it) {
		Lexem lexem = *it;
		if (lexem.type == Variable) {
			bool exists = false;
			for (size_t i = 0; i < _variables.size(); ++i) {
				if (_variables[i] == lexem.name) {
					exists = true;
					break;
				}
			}
			if (!exists) {
				_variables.push_back(lexem.name);
				_values.push_back(DBL_MAX);
			}
		}
	}
}

void Expression::set_values(size_t variable, double value) {
	if (variable < 0 || variable >= _variables.size()) {
		throw std::invalid_argument("There is no such variable");
	}
	_values[variable] = value;
}

void Expression::build_polish_record() {
	Stack<Lexem> stack;

	for (auto it = _lexems.begin(); it != _lexems.end(); ++it) {
		Lexem lexem = *it;

		if (lexem.type == Constant || lexem.type == Variable) {
			_polish_record.push_back(lexem);
		}
		else if (lexem.type == Function) {
			stack.push(lexem);
		}
		else if (lexem.type == Operator) {
			while (!stack.is_empty() && stack.top().priority >= lexem.priority) {
				_polish_record.push_back(stack.top());
				stack.pop();
			}
			stack.push(lexem);
		}
		else if (lexem.type == UnOperator) {
			stack.push(lexem);
		}
		else if (lexem.type == OpenBracket) {
			stack.push(lexem);
		}
		else if (lexem.type == CloseBracket) {
			while (!stack.is_empty() && stack.top().type != OpenBracket) {
				_polish_record.push_back(stack.top());
				stack.pop();
			}
			if (stack.is_empty()) {
				throw std::logic_error("A lot of brackets (Unmatched brackets)");
			}
			stack.pop();
			if (!stack.is_empty() && stack.top().type == Function) {
				_polish_record.push_back(stack.top());
				stack.pop();
			}
		}
	}
	while (!stack.is_empty()) {
		_polish_record.push_back(stack.top());
		stack.pop();
	}
}
/*
void Expression::set_variable(const std::string& name, double value) {
	for (size_t i = 0; i < _variables.size(); ++i) {
		if (_variables[i] == name) {
			_values[i] = value;
			return;
		}
	}
	_variables.push_back(name);
	_values.push_back(value);
}
*/
double Expression::calculate() const {
	Stack<double> stack;

	for (auto it = _polish_record.begin(); it != _polish_record.end(); ++it) {
		const Lexem& lexem = *it;
		if (lexem.type == Constant) {
			stack.push(lexem.value);
		}
		else if (lexem.type == Variable) {
			bool found = false;
			for (size_t i = 0; i < _variables.size(); ++i) {
				if (_variables[i] == lexem.name) {
					stack.push(_values[i]);
					found = true;
					break;
				}
			} 
			if (!found) {
				throw std::logic_error("Variable not defined: " + lexem.name);
			}
		}
		else if (lexem.type == Operator) {
			if (stack.count() < 2) {
				throw std::logic_error("Invalid expression");
			}
			double b = stack.top();
			stack.pop();
			double a = stack.top();
			stack.pop();

			if (lexem.name == "+") { stack.push(a + b); }
			if (lexem.name == "-") { stack.push(a - b); }
			if (lexem.name == "*") { stack.push(a * b); }
			if (lexem.name == "/") { 
				if (b == 0.0) { throw std::logic_error("Division by zero"); }
				stack.push(a / b); 
			}
			if (lexem.name == "^") { 
				double res = 1.0;
				for (int i = 0; i < (int)b; ++i) {
					res *= a;
				}
				stack.push(res); 
			}
		}
		else if (lexem.type == UnOperator) {
			double a = stack.top();
			stack.pop();
			stack.push((-1.0)*a);
		}
		else if (lexem.type == Function) {
			if (stack.is_empty()) {
				throw std::logic_error("Invalid function usage");
			}
			double a = stack.top();
			stack.pop();
			stack.push(lexem.function(a));
		}
	}
	if (stack.count() != 1) {
		throw std::logic_error("Invalid expression");
	}
	return stack.top();
}