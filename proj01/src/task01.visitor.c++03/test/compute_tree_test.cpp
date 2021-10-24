#include <gtest/gtest.h>
#include <task01.visitor.c++03/evaluate_visitor.hpp>
#include <task01.visitor.c++03/infix_print_visitor.hpp>
#include <task01.visitor.c++03/parser.hpp>


TEST(ComputeTreeTest, InfixPrintVisitor)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 3 * 4 ) / 5");
    psso::InfixPrintVisitor visitor;
    root_node->accept(visitor);

    ASSERT_EQ(visitor.report(), "(1 + ((2 - (3 * 4)) / 5))");
}

TEST(ComputeTreeTest, EvaluateVisitor)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 3 * 4 ) / 5");
    psso::EvaluateVisitor visitor;
    root_node->accept(visitor);

    ASSERT_EQ(visitor.get_value(), -1);
}
