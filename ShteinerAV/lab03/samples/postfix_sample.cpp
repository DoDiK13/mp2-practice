#include <iostream>
#include "stack.h"
#include "postfix_form.h"
#include <locale>

int main() {
    setlocale(LC_ALL, "RUS");
    try {
        std::cout << "Введите выражение: ";
        std::string input;
        std::getline(std::cin >> std::ws, input);

        TPostfixExpression expr(input);

        std::vector<std::pair<char, double>> my_operands;
        expr.SetOperandValue(my_operands);

        double result = expr.Calculate(my_operands);

        std::cout << "Постфиксная форма: " << expr.GetPostfix() << "\n";
        std::cout << "Результат: " << result << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
    return 0;
}