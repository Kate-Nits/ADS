// Copyright 2025 Ekaterina Ushnitskaya

#include "../lib_expression/expression.h"

Expression::Expression(const List<Lexem>& lexems) : _lexems(lexems) {}

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
		else if (lexem.type == Operator || lexem.type == UnOperator) {
			while (!stack.is_empty() && stack.top().priority >= lexem.priority) {
				_polish_record.push_back(stack.top());
				stack.pop();
			}
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
			stack.pop();
		}
	}
	while (!stack.is_empty()) {
		_polish_record.push_back(stack.top());
		stack.pop();
	}
}

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
			double b = stack.top();
			stack.pop();
			double a = stack.top();
			stack.pop();

			if (lexem.name == "+") { stack.push(a + b); }
			if (lexem.name == "-") { stack.push(a - b); }
			if (lexem.name == "*") { stack.push(a * b); }
			if (lexem.name == "/") { stack.push(a / b); }
			if (lexem.name == "^") { stack.push(std::pow(a, b)); }
		}
		else if (lexem.type == UnOperator) {
			double a = stack.top();
			stack.pop();
			stack.push((-1.0)*a);
		}
		else if (lexem.type == Function) {
			double a = stack.top();
			stack.pop();
			stack.push(lexem.function(a));
		}
	}
	return stack.top();
}