#include "postfix_form.h"

#include <gtest\gtest.h>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>

// ============================================================
//  Блок 1. Конструктор: перевод инфикса в постфикс (GetPostfix)
// ============================================================

TEST(TPostfixExpression, can_create_from_simple_expression)
{
    ASSERT_NO_THROW(TPostfixExpression e("A+B"));
}

TEST(TPostfixExpression, converts_single_operand)
{
    TPostfixExpression e("A");
    ASSERT_EQ("A", e.GetPostfix());
}

TEST(TPostfixExpression, converts_addition)
{
    TPostfixExpression e("A+B");
    ASSERT_EQ("AB+", e.GetPostfix());
}

TEST(TPostfixExpression, converts_subtraction_and_multiplication_by_priority)
{
    TPostfixExpression e("A+B*C");
    ASSERT_EQ("ABC*+", e.GetPostfix());
}

TEST(TPostfixExpression, converts_expression_with_operator_at_start)
{
    TPostfixExpression e("A*B+C");
    ASSERT_EQ("AB*C+", e.GetPostfix());
}

TEST(TPostfixExpression, respects_left_associativity)
{
    TPostfixExpression e("A-B-C");
    ASSERT_EQ("AB-C-", e.GetPostfix());
}

TEST(TPostfixExpression, respects_parentheses)
{
    TPostfixExpression e("(A+B)*C");
    ASSERT_EQ("AB+C*", e.GetPostfix());
}

TEST(TPostfixExpression, respects_nested_parentheses)
{
    TPostfixExpression e("((A+B))");
    ASSERT_EQ("AB+", e.GetPostfix());
}

TEST(TPostfixExpression, converts_complex_expression)
{
    TPostfixExpression e("(A+B)*(C-D)");
    ASSERT_EQ("AB+CD-*", e.GetPostfix());
}

TEST(TPostfixExpression, ignores_spaces)
{
    TPostfixExpression e("  A +  B * C  ");
    ASSERT_EQ("ABC*+", e.GetPostfix());
}

TEST(TPostfixExpression, empty_expression_produces_empty_postfix)
{
    TPostfixExpression e("");
    ASSERT_EQ("", e.GetPostfix());
}

TEST(TPostfixExpression, whitespace_only_expression_produces_empty_postfix)
{
    TPostfixExpression e("   ");
    ASSERT_EQ("", e.GetPostfix());
}

TEST(TPostfixExpression, copied_expression_has_same_postfix)
{
    TPostfixExpression e1("(A+B)*C");
    TPostfixExpression e2(e1);
    ASSERT_EQ(e1.GetPostfix(), e2.GetPostfix());
}

// ============================================================
//  Блок 2. Ошибки на этапе построения
// ============================================================

TEST(TPostfixExpression, throws_on_extra_closing_bracket)
{
    ASSERT_THROW(TPostfixExpression e("A+B)"), std::runtime_error);
}

TEST(TPostfixExpression, throws_on_missing_closing_bracket)
{
    ASSERT_THROW(TPostfixExpression e("A+(B"), std::runtime_error);
}

TEST(TPostfixExpression, throws_on_only_opening_bracket)
{
    ASSERT_THROW(TPostfixExpression e("("), std::runtime_error);
}

TEST(TPostfixExpression, throws_on_only_closing_bracket)
{
    ASSERT_THROW(TPostfixExpression e(")"), std::runtime_error);
}

TEST(TPostfixExpression, throws_on_lowercase_letter)
{
    ASSERT_THROW(TPostfixExpression e("a+b"), std::runtime_error);
}

TEST(TPostfixExpression, throws_on_digit)
{
    ASSERT_THROW(TPostfixExpression e("A+1"), std::runtime_error);
}

TEST(TPostfixExpression, throws_on_special_character)
{
    ASSERT_THROW(TPostfixExpression e("A$B"), std::runtime_error);
}

// ============================================================
//  Блок 3. Calculate — корректные вычисления
// ============================================================

namespace {
    std::vector<std::pair<char, double>> MakeOperands(std::initializer_list<std::pair<char, double>> xs)
    {
        return std::vector<std::pair<char, double>>(xs);
    }
}

TEST(TPostfixExpression, calculate_addition)
{
    TPostfixExpression e("A+B");
    auto ops = MakeOperands({ {'A', 2.0}, {'B', 3.0} });
    ASSERT_DOUBLE_EQ(5.0, e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_subtraction)
{
    TPostfixExpression e("A-B");
    auto ops = MakeOperands({ {'A', 2.0}, {'B', 3.0} });
    ASSERT_DOUBLE_EQ(-1.0, e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_multiplication)
{
    TPostfixExpression e("A*B");
    auto ops = MakeOperands({ {'A', 2.0}, {'B', 3.0} });
    ASSERT_DOUBLE_EQ(6.0, e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_division)
{
    TPostfixExpression e("A/B");
    auto ops = MakeOperands({ {'A', 6.0}, {'B', 3.0} });
    ASSERT_DOUBLE_EQ(2.0, e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_single_operand)
{
    TPostfixExpression e("A");
    auto ops = MakeOperands({ {'A', 42.0} });
    ASSERT_DOUBLE_EQ(42.0, e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_respects_priority)
{
    TPostfixExpression e("A+B*C");
    auto ops = MakeOperands({ {'A', 1.0}, {'B', 2.0}, {'C', 3.0} });
    ASSERT_DOUBLE_EQ(7.0, e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_respects_parentheses)
{
    TPostfixExpression e("(A+B)*C");
    auto ops = MakeOperands({ {'A', 1.0}, {'B', 2.0}, {'C', 3.0} });
    ASSERT_DOUBLE_EQ(9.0, e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_complex_expression)
{
    TPostfixExpression e("(A+B)*(C-D)");
    auto ops = MakeOperands({ {'A', 1.0}, {'B', 2.0}, {'C', 5.0}, {'D', 3.0} });
    ASSERT_DOUBLE_EQ(6.0, e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_ignores_extra_operands_in_list)
{
    TPostfixExpression e("A+B");
    auto ops = MakeOperands({ {'A', 1.0}, {'B', 2.0}, {'C', 100.0} });
    ASSERT_DOUBLE_EQ(3.0, e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_does_not_modify_operands)
{
    TPostfixExpression e("A+B");
    auto ops = MakeOperands({ {'A', 1.0}, {'B', 2.0} });
    e.Calculate(ops);
    ASSERT_EQ(2u, ops.size());
    ASSERT_DOUBLE_EQ(1.0, ops[0].second);
    ASSERT_DOUBLE_EQ(2.0, ops[1].second);
}

// ============================================================
//  Блок 4. Calculate — ошибки
// ============================================================

TEST(TPostfixExpression, calculate_throws_on_empty_expression)
{
    TPostfixExpression e("");
    std::vector<std::pair<char, double>> ops;
    ASSERT_ANY_THROW(e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_throws_on_division_by_zero)
{
    TPostfixExpression e("A/B");
    auto ops = MakeOperands({ {'A', 1.0}, {'B', 0.0} });
    ASSERT_ANY_THROW(e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_throws_when_operand_has_no_value)
{
    TPostfixExpression e("A+B");
    auto ops = MakeOperands({ {'A', 1.0} });  // нет B
    ASSERT_ANY_THROW(e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_throws_when_too_few_operands)
{
    // Инфикс "A+" даёт постфикс "A+": на '+' операндов не хватает
    TPostfixExpression e("A+");
    auto ops = MakeOperands({ {'A', 1.0} });
    ASSERT_ANY_THROW(e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_throws_when_extra_numbers_left_in_stack)
{
    // Инфикс "AB" даёт постфикс "AB": два числа, ни одного оператора
    TPostfixExpression e("AB");
    auto ops = MakeOperands({ {'A', 1.0}, {'B', 2.0} });
    ASSERT_ANY_THROW(e.Calculate(ops));
}

// ============================================================
//  Блок 5. SetOperandValue (ввод из cin с подменой потока)
// ============================================================

TEST(TPostfixExpression, set_operand_value_reads_unique_operands)
{
    TPostfixExpression e("A+B+A");

    std::istringstream input("2 3\n");
    std::ostringstream output;
    std::streambuf* oldIn = std::cin.rdbuf(input.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(output.rdbuf());

    std::vector<std::pair<char, double>> operands;
    e.SetOperandValue(operands);

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    ASSERT_EQ(2u, operands.size());          // A и B, без дубликата A
    ASSERT_EQ('A', operands[0].first);
    ASSERT_DOUBLE_EQ(2.0, operands[0].second);
    ASSERT_EQ('B', operands[1].first);
    ASSERT_DOUBLE_EQ(3.0, operands[1].second);
}

TEST(TPostfixExpression, set_operand_value_skips_already_present_operands)
{
    TPostfixExpression e("A+B");

    std::istringstream input("7\n");          // должно запроситься только B
    std::ostringstream output;
    std::streambuf* oldIn = std::cin.rdbuf(input.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(output.rdbuf());

    std::vector<std::pair<char, double>> operands{ {'A', 5.0} };
    e.SetOperandValue(operands);

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    ASSERT_EQ(2u, operands.size());
    ASSERT_DOUBLE_EQ(5.0, operands[0].second);
    ASSERT_EQ('B', operands[1].first);
    ASSERT_DOUBLE_EQ(7.0, operands[1].second);
}

//TEST(TPostfixExpression, set_operand_value_recovers_from_invalid_input)
//{
//    TPostfixExpression e("A");
//
//    std::istringstream input("not_a_number 42\n");
//    std::ostringstream output;
//    std::streambuf* oldIn = std::cin.rdbuf(input.rdbuf());
//    std::streambuf* oldOut = std::cout.rdbuf(output.rdbuf());
//
//    std::vector<std::pair<char, double>> operands;
//    e.SetOperandValue(operands);
//
//    std::cin.rdbuf(oldIn);
//    std::cout.rdbuf(oldOut);
//
//    ASSERT_EQ(1u, operands.size());
//    ASSERT_EQ('A', operands[0].first);
//    ASSERT_DOUBLE_EQ(42.0, operands[0].second);
//}

TEST(TPostfixExpression, set_operand_value_does_nothing_for_empty_postfix)
{
    TPostfixExpression e("");

    std::istringstream input("");
    std::ostringstream output;
    std::streambuf* oldIn = std::cin.rdbuf(input.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(output.rdbuf());

    std::vector<std::pair<char, double>> operands;
    ASSERT_NO_THROW(e.SetOperandValue(operands));

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    ASSERT_TRUE(operands.empty());
}

// ============================================================
//  Блок 6. Интеграция: SetOperandValue + Calculate
// ============================================================

TEST(TPostfixExpression, full_cycle_input_and_calculate)
{
    TPostfixExpression e("(A+B)*C");

    std::istringstream input("1 2 3\n");
    std::ostringstream output;
    std::streambuf* oldIn = std::cin.rdbuf(input.rdbuf());
    std::streambuf* oldOut = std::cout.rdbuf(output.rdbuf());

    std::vector<std::pair<char, double>> operands;
    e.SetOperandValue(operands);
    double result = e.Calculate(operands);

    std::cin.rdbuf(oldIn);
    std::cout.rdbuf(oldOut);

    ASSERT_DOUBLE_EQ(9.0, result);
}