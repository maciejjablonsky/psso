#include <gtest/gtest.h>
#include <task01.visitor.c++03/evaluate_visitor.hpp>
#include <task01.visitor.c++03/infix_print_visitor.hpp>
#include <task01.visitor.c++03/parser.hpp>
#include <task01.visitor.c++03/posfix_print_visitor.hpp>
#include <task01.visitor.c++03/prefix_print_visitor.hpp>

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

TEST(ComputeTreeTest, PostfixPrintVisitor)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 3 * 4 ) / 5");
    psso::PostfixPrintVisitor visitor;
    root_node->accept(visitor);

    ASSERT_EQ(visitor.report(), "1 2 3 4 * - 5 / +");
}

TEST(ComputeTreeTest, PrefixPrintVisitor)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 3 * 4 ) / 5");
    psso::PrefixPrintVisitor visitor;
    root_node->accept(visitor);

    ASSERT_EQ(visitor.report(), "+ 1 / - 2 * 3 4 5");
}

TEST(ComputeTreeWithModuloTest, InfixPrintVisitor)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 15 % 8 ) / 5");
    psso::InfixPrintVisitor visitor;
    root_node->accept(visitor);

    ASSERT_EQ(visitor.report(), "(1 + ((2 - (15 % 8)) / 5))");
}

TEST(ComputeTreeWithModuloTest, EvaluateVisitor)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 15 % 8 ) / 5");
    psso::EvaluateVisitor visitor;
    root_node->accept(visitor);

    ASSERT_EQ(visitor.get_value(), 0);
}

TEST(ComputeTreeWithModuloTest, PostfixPrintVisitor)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 15 % 8 ) / 5");
    psso::PostfixPrintVisitor visitor;
    root_node->accept(visitor);

    ASSERT_EQ(visitor.report(), "1 2 15 8 % - 5 / +");
}

TEST(ComputeTreeWithModuloTest, PrefixPrintVisitor)
{
    psso::Parser parser;
    auto root_node = parser.parse("1 + ( 2 - 15 % 8 ) / 5");
    psso::PrefixPrintVisitor visitor;
    root_node->accept(visitor);

    ASSERT_EQ(visitor.report(), "+ 1 / - 2 % 15 8 5");
}
