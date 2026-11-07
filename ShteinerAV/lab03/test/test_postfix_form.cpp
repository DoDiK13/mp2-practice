#include "postfix_form.h"

#include <gtest\gtest.h>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>

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

TEST(TPostfixExpression, calculate_does_not_modify_operands)
{
    TPostfixExpression e("A+B");
    auto ops = MakeOperands({ {'A', 1.0}, {'B', 2.0} });
    e.Calculate(ops);
    ASSERT_EQ(2, ops.size());
    ASSERT_DOUBLE_EQ(1.0, ops[0].second);
    ASSERT_DOUBLE_EQ(2.0, ops[1].second);
}





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

TEST(TPostfixExpression, calculate_throws_when_too_few_operands)
{
    TPostfixExpression e("A+");
    auto ops = MakeOperands({ {'A', 1.0} });
    ASSERT_ANY_THROW(e.Calculate(ops));
}

TEST(TPostfixExpression, calculate_throws_when_extra_numbers_left_in_stack)
{
    TPostfixExpression e("AB");
    auto ops = MakeOperands({ {'A', 1.0}, {'B', 2.0} });
    ASSERT_ANY_THROW(e.Calculate(ops));
}