#include <gtest/gtest.h>
#include <task01.visitor.c++03/parser.hpp>

TEST(ComputeTreeTest, ParseTest)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 3 * 4 ) / 5");
    //ASSERT_EQ(root_node->to_infix(), "(1 + ((2 - (3 * 4)) / 5))");
}