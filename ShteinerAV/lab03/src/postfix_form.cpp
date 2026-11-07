#include "postfix_form.h"
#include "stack.h"
#include "string"
#include <iostream>
#include <limits>
#include <sstream>

int TPostfixExpression :: GetPriority(char op) const {
	switch (op) {
	case '*': return 3;
	case '/': return 3;
	case '+': return 2;
	case '-': return 2;
	case ')': return 1;
	default: return 0;
	}
}

TPostfixExpression::TPostfixExpression(const std::string& expr) : infixExpr(expr) {
	TStack<char> TStack1(expr.size() + 1);
	TStack<char> TStack2(expr.size() + 1);
	int balance = 0;

	for (char c : expr) {
		if (c == ' ') continue;
		else if (c >= 'A' && c <= 'Z') TStack1.push(c);
		else if (c == '(') {
			TStack2.push(c);
			balance++; 
		}
		else if (c == ')') {
			balance--;
			if (balance < 0) {
				throw std::runtime_error("Ошибка: лишняя закрывающая скобка ')'");
			}

			while (!TStack2.isEmpty() && TStack2.Top() != '(') {
				TStack1.push(TStack2.Top());
				TStack2.pop();
			}
			TStack2.pop();

		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			while (!TStack2.isEmpty() && TStack2.Top() != '(' && GetPriority(TStack2.Top()) >= GetPriority(c)) {
				TStack1.push(TStack2.Top());
				TStack2.pop();
			}
			TStack2.push(c);
		}
		else {
			throw std::runtime_error("Ошибка: недопустимый символ");
		}
	}

	if (balance != 0) {
		throw std::runtime_error("Ошибка: не равное кол-во открытых/закрытых скобок");
	}

	while (!TStack2.isEmpty()) {
		TStack1.push(TStack2.Top());
		TStack2.pop();
	}

	while (!TStack1.isEmpty()) {
		postfixExpr = TStack1.Top() + postfixExpr;
		TStack1.pop();
	}
}

double ReadValue(const char name) {
	while (true) {
		std::cout << "Введите значение для операнда " << name << ": ";
		std::string line;
		std::getline(std::cin, line);
		std::istringstream iss(line);
		double val; char extra;
		if ((iss >> val) && !(iss >> extra))
			return val;
		std::cout << "\nОшибка! Введите корректное значение.\n";
	}
}

void TPostfixExpression::SetOperandValue(std::vector<std::pair<char, double>>& operands) const {
	for (char c : postfixExpr) {
		if (c >= 'A' && c <= 'Z') {
			bool flag_duplicate = false;
			for (const std::pair<char, double>& operand : operands) {
				if (operand.first == c) { flag_duplicate = true; break; }
			}
			if (flag_duplicate) { continue; }

			double val = ReadValue(c);
			operands.push_back({ c, val });
		}
	}
}

double TPostfixExpression::Calculate(const std::vector<std::pair<char, double>>& operands) const {
	if (postfixExpr.empty()) throw std::runtime_error("Ошибка: выражение пустое");

	TStack<double> st(postfixExpr.size()+1);

	for (char c : postfixExpr) {
		if (c >= 'A' && c <= 'Z') {
			double val = 0.0;
			bool found = false;
			for (const std::pair<char, double>& p : operands) {
				if (p.first == c) {
					val = p.second;
					found = true;
					break;
				}
			}

			if (!found) throw std::runtime_error("Ошибка: операнд не имеет значения");
			st.push(val);
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			if (st.isEmpty()) throw std::runtime_error("Ошибка: недостаточно операндов");
			double b = st.Top(); st.pop();

			if (st.isEmpty()) throw std::runtime_error("Ошибка: недостаточно операндов");
			double a = st.Top(); st.pop();

			double res = 0;
			switch (c) {
			case '+': res = a + b; break;
			case '-': res = a - b; break;
			case '*': res = a * b; break;
			case '/':
				if (b == 0.0) throw std::runtime_error("Ошибка: деление на ноль");
				res = a / b;
				break;
			}
			st.push(res);
		}
	}

	if (st.isEmpty()) throw std::runtime_error("Ошибка вычисления");
	double result = st.Top(); st.pop();

	if (!st.isEmpty()) throw std::runtime_error("Ошибка: в стеке остались лишние числа");

	return result;
}