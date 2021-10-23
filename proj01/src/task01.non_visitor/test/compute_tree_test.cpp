#include <gtest/gtest.h>
#include <task01.non_visitor/parser.hpp>

TEST(ComputeTreeTest, InFixNotation)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 3 * 4 ) / 5");
    ASSERT_EQ(root_node->to_infix(), "(1 + ((2 - (3 * 4)) / 5))");
}

TEST(ComputeTreeTest, Evaluate)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 3 * 4 ) / 5");
    ASSERT_EQ(root_node->evaluate(), -1);
}

TEST(ComputeTreeTest, PostFixNotation)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 3 * 4 ) / 5");
    ASSERT_EQ(root_node->to_postfix(), "1 2 3 4 * - 5 / +");
}

TEST(ComputeTreeTest, PreFixNotation)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 3 * 4 ) / 5");
    ASSERT_EQ(root_node->to_prefix(), "+ 1 / - 2 * 3 4 5");
}

TEST(ComputeTreeWithModuloTest, InFixNotation)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 15 % 8 ) / 5");
    ASSERT_EQ(root_node->to_infix(), "(1 + ((2 - (15 % 8)) / 5))");
}

TEST(ComputeTreeWithModuloTest, Evaluate)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 15 % 8 ) / 5");
    ASSERT_EQ(root_node->evaluate(), 0);
}

TEST(ComputeTreeWithModuloTest, PostFixNotation)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 15 % 8 ) / 5");
    ASSERT_EQ(root_node->to_postfix(), "1 2 15 8 % - 5 / +");
}

TEST(ComputeTreeWithModuloTest, PreFixNotation)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 15 % 8 ) / 5");
    ASSERT_EQ(root_node->to_prefix(), "+ 1 / - 2 % 15 8 5");
}
