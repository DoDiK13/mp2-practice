#pragma once
#include <iostream>
#include <string>


class TPostfixExpression {
private:
    std::string infixExpr;   
    std::string postfixExpr; 
    
    int GetPriority(char op) const;

public:
    
    TPostfixExpression(const std::string& expr) {}

    
    std::string GetPostfix() const { return postfixExpr; }
};