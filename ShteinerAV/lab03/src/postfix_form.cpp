#include "postfix_form.h"
#include "stack.h"
#include "string"

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
	Stack<char> stack1(expr.size());
	Stack<char> stack2(expr.size());

	for (int i = 0; i < expr.size(); i++) {
		char c = expr[i];

		if (c >= 'A' && c <= 'Z') {
			stack1.push(c);
		}
		else if (c == '(') {
			stack2.push(c);
		}
		else if (c == ')') {
			while (!stack2.isEmpty() && stack2.Top() != '(') {
				stack1.push(stack2.Top());
				stack2.pop();
			}
			stack2.pop();
		} 
		else {
			while (!stack2.isEmpty() &&stack2.Top() != '(' && GetPriority(stack2.Top()) >= GetPriority(c)) {
				stack1.push(stack2.Top());
				stack2.pop();
			}
			stack2.push(c);
		}
	}

	while (!stack2.isEmpty()) {
		stack1.push(stack2.Top());
		stack2.pop();
	}
	while (!stack1.isEmpty()) {
		postfixExpr = stack1.Top() + postfixExpr; 
		stack1.pop();
	}
}

