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
    ASSERT_EQ(root_node->to_postfix(), "(1 + ((2 - (3 * 4)) / 5))");
}

