#include "tmatrix.h"

#include <gtest/gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(m1);
    ASSERT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(m1);
    ASSERT_NE(&(m1[0][0]), &(m2[0][0]));
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m1(5);
    ASSERT_EQ(5u, m1.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(5);
    m[0][0] = 5;
    ASSERT_EQ(5, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(5);
    ASSERT_ANY_THROW(m[-1][0] = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(4);
    ASSERT_ANY_THROW(m[4][1] = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(5);
    TDynamicMatrix<int> m2(5);
    ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(5);
    m1 = m2;
    ASSERT_EQ(m1.size(), m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(5);
    ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(m1);
    ASSERT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m1(4);
    ASSERT_TRUE(m1 == m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(4);
    TDynamicMatrix<int> m2(5);
    ASSERT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(2);

    m1[0][0] = 1; m1[0][1] = -2; m1[1][0] = 3; m1[1][1] = 0;
    m2[0][0] = 2; m2[0][1] = -1; m2[1][0] = 4; m2[1][1] = 1;

    TDynamicMatrix<int> expected(2);
    expected[0][0] = 3; expected[0][1] = -3; expected[1][0] = 7; expected[1][1] = 1;

    TDynamicMatrix<int> res = m1 + m2;

    EXPECT_EQ(res.size(), expected.size());
    EXPECT_TRUE(res == expected);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);
    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(2);

    m1[0][0] = 5; m1[0][1] = -2; m1[1][0] = 3; m1[1][1] = 0;
    m2[0][0] = 4; m2[0][1] = 5; m2[1][0] = -6; m2[1][1] = 7;

    TDynamicMatrix<int> expected(2);
    expected[0][0] = 1; expected[0][1] = -7; expected[1][0] = 9; expected[1][1] = -7;

    TDynamicMatrix<int> res = m1 - m2;

    EXPECT_EQ(res.size(), expected.size());
    EXPECT_TRUE(res == expected);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);
    ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_add_scalar_to_matrix)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = -2;
    m[1][0] = 3; m[1][1] = 0;

    TDynamicMatrix<int> expected(2);
    expected[0][0] = 6; expected[0][1] = 3;
    expected[1][0] = 8; expected[1][1] = 5;

    TDynamicMatrix<int> res = m + 5;

    EXPECT_EQ(res.size(), m.size());
    EXPECT_TRUE(res == expected);
}

TEST(TDynamicMatrix, can_subtract_scalar_from_matrix)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = -2;
    m[1][0] = 3; m[1][1] = 0;

    TDynamicMatrix<int> expected(2);
    expected[0][0] = -4; expected[0][1] = -7;
    expected[1][0] = -2; expected[1][1] = -5;

    TDynamicMatrix<int> res = m - 5;

    EXPECT_EQ(res.size(), m.size());
    EXPECT_TRUE(res == expected);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = -2;
    m[1][0] = 3; m[1][1] = 0;

    TDynamicMatrix<int> expected(2);
    expected[0][0] = 3; expected[0][1] = -6;
    expected[1][0] = 9; expected[1][1] = 0;

    TDynamicMatrix<int> res = m * 3;

    EXPECT_EQ(res.size(), m.size());
    EXPECT_TRUE(res == expected);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    TDynamicVector<int> v(2);
    v[0] = 5;
    v[1] = 6;

    TDynamicVector<int> expected(2);

    expected[0] = 17;
    expected[1] = 39;

    TDynamicVector<int> res = m * v;

    EXPECT_EQ(res.size(), v.size());
    EXPECT_TRUE(res == expected);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    m2[0][0] = 5; m2[0][1] = 6;
    m2[1][0] = 7; m2[1][1] = 8;

    TDynamicMatrix<int> expected(2);
    expected[0][0] = 19; expected[0][1] = 22;
    expected[1][0] = 43; expected[1][1] = 50;

    TDynamicMatrix<int> res = m1 * m2;

    EXPECT_EQ(res.size(), m1.size());
    EXPECT_TRUE(res == expected);
}