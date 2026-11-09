#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <utility>

class TPostfixExpression {
private:
    std::string infixExpr;
    std::string postfixExpr;

    int GetPriority(char op) const; // const char op
    double ReadValue(const char name) const;
public:
    TPostfixExpression(const std::string& expr);
    std::string GetPostfix() const { return postfixExpr; }
    void SetOperandValue(std::vector<std::pair<char, double>>&) const;
    double Calculate(const std::vector<std::pair<char, double>>& operands) const;
};