#include "stack.h"

#include <gtest\gtest.h>
#include <utility>

TEST(TStack, can_create_default_stack)
{
    ASSERT_NO_THROW(TStack<int> s);
    TStack<int> s;
    ASSERT_TRUE(s.isEmpty());
    ASSERT_EQ(0, s.size());
}

TEST(TStack, can_create_stack_with_positive_length)
{
    ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, cant_create_too_large_stack)
{
    ASSERT_ANY_THROW(TStack<int> s(MAX_SIZE + 1));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
    ASSERT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, cant_create_stack_with_zero_length)
{
    ASSERT_ANY_THROW(TStack<int> s(0));
}

TEST(TStack, can_create_copied_stack)
{
    TStack<int> s(10);
    ASSERT_NO_THROW(TStack<int> s1(s));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
    TStack<int> s1(3);
    s1.push(1);
    s1.push(2);

    TStack<int> s2(s1);

    ASSERT_EQ(s2.size(), s1.size());
    while (!s1.isEmpty())
    {
        ASSERT_EQ(s1.Top(), s2.Top());
        s1.pop();
        s2.pop();
    }
    ASSERT_TRUE(s1.isEmpty());
    ASSERT_TRUE(s2.isEmpty());
}

TEST(TStack, copied_stack_has_its_own_memory)
{
    TStack<int> s1(3);
    s1.push(1);
    s1.push(2);

    TStack<int> s2(s1);

    s1.pop();
    s1.push(3);

    ASSERT_EQ(2, s2.size());
    ASSERT_EQ(2, s2.Top());
}

TEST(TStack, can_copy_empty_stack)
{
    TStack<int> s1(3);
    TStack<int> s2(s1);

    ASSERT_TRUE(s2.isEmpty());
    ASSERT_EQ(0, s2.size());
    ASSERT_FALSE(s2.isFull());
}

TEST(TStack, can_move_stack)
{
    TStack<int> s1(3);
    s1.push(1);
    s1.push(2);

    TStack<int> s2(std::move(s1));

    ASSERT_EQ(2, s2.size());
    ASSERT_EQ(2, s2.Top());
    ASSERT_TRUE(s1.isEmpty());
    ASSERT_EQ(0, s1.size());
}

TEST(TStack, can_move_empty_stack)
{
    TStack<int> s1(3);
    TStack<int> s2(std::move(s1));

    ASSERT_TRUE(s2.isEmpty());
    ASSERT_EQ(0, s2.size());
    ASSERT_TRUE(s1.isEmpty());
}

TEST(TStack, can_get_size)
{
    TStack<int> s(5);
    ASSERT_EQ(0, s.size());

    s.push(1);
    ASSERT_EQ(1, s.size());

    s.push(2);
    ASSERT_EQ(2, s.size());

    s.pop();
    ASSERT_EQ(1, s.size());
}

TEST(TStack, can_check_is_empty)
{
    TStack<int> s(1);
    ASSERT_TRUE(s.isEmpty());

    s.push(1);
    ASSERT_FALSE(s.isEmpty());

    s.pop();
    ASSERT_TRUE(s.isEmpty());
}

TEST(TStack, can_check_is_full)
{
    TStack<int> s(2);
    ASSERT_FALSE(s.isFull());

    s.push(1);
    ASSERT_FALSE(s.isFull());

    s.push(2);
    ASSERT_TRUE(s.isFull());

    s.pop();
    ASSERT_FALSE(s.isFull());
}

TEST(TStack, can_get_top)
{
    TStack<int> s(3);
    s.push(5);
    ASSERT_EQ(5, s.Top());

    s.push(10);
    ASSERT_EQ(10, s.Top());
}

TEST(TStack, throws_when_get_top_from_empty_stack)
{
    TStack<int> s(3);
    ASSERT_ANY_THROW(s.Top());
}

TEST(TStack, can_push_element)
{
    TStack<int> s(3);
    s.push(10);

    ASSERT_EQ(10, s.Top());
    ASSERT_EQ(1, s.size());
    ASSERT_FALSE(s.isEmpty());
}

TEST(TStack, throws_when_push_to_full_stack)
{
    TStack<int> s(2);
    s.push(1);
    s.push(2);
    ASSERT_ANY_THROW(s.push(3));
}

TEST(TStack, can_pop_element)
{
    TStack<int> s(3);
    s.push(10);
    s.push(20);

    s.pop();
    ASSERT_EQ(10, s.Top());
    ASSERT_EQ(1, s.size());
}

TEST(TStack, throws_when_pop_from_empty_stack)
{
    TStack<int> s(3);
    ASSERT_ANY_THROW(s.pop());
}

TEST(TStack, works_lifo)
{
    TStack<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);

    ASSERT_EQ(3, s.Top()); s.pop();
    ASSERT_EQ(2, s.Top()); s.pop();
    ASSERT_EQ(1, s.Top()); s.pop();

    ASSERT_TRUE(s.isEmpty());
}

TEST(TStack, can_assign_stack_to_itself)
{
    TStack<int> s(3);
    s.push(1);
    s.push(2);

    ASSERT_NO_THROW(s = s);
    ASSERT_EQ(2, s.size());
    ASSERT_EQ(2, s.Top());
}

TEST(TStack, can_assign_stacks_of_equal_size)
{
    TStack<int> s1(3), s2(3);
    s1.push(1); s1.push(2);
    s2.push(3); s2.push(4);

    ASSERT_NO_THROW(s1 = s2);

    ASSERT_EQ(2, s1.size());
    ASSERT_EQ(4, s1.Top());
    s1.pop();
    ASSERT_EQ(3, s1.Top());
}

TEST(TStack, assign_operator_change_stack_size)
{
    TStack<int> s1(5);
    s1.push(1); s1.push(2); s1.push(3);

    TStack<int> s2(2);
    s2.push(4);

    s1 = s2;
    ASSERT_EQ(s1.size(), s2.size());
    ASSERT_EQ(1, s1.size());
}

TEST(TStack, can_assign_stacks_of_different_size)
{
    TStack<int> s1(5), s2(2);
    s1.push(1);
    s2.push(2);

    ASSERT_NO_THROW(s1 = s2);

    s1.push(3);              
    ASSERT_TRUE(s1.isFull());
    ASSERT_ANY_THROW(s1.push(4));
}

TEST(TStack, can_assign_empty_stack)
{
    TStack<int> s1(3);
    s1.push(1);

    TStack<int> s2(3);

    s1 = s2;
    ASSERT_TRUE(s1.isEmpty());
    ASSERT_EQ(0, s1.size());
}

TEST(TStack, can_use_stack_after_assigning_empty)
{
    TStack<int> s1(3);
    s1.push(1);
    s1.push(2);

    TStack<int> s2(5);
    s1 = s2;

    ASSERT_TRUE(s1.isEmpty());
    s1.push(10);
    ASSERT_EQ(10, s1.Top());
    ASSERT_EQ(1, s1.size());
}