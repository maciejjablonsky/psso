#pragma once
#include <stack>
#include <task01.visitor.c++03/addition_node.hpp>
#include <task01.visitor.c++03/division_node.hpp>
#include <task01.visitor.c++03/multiplication_node.hpp>
#include <task01.visitor.c++03/numeric_node.hpp>
#include <task01.visitor.c++03/subtraction_node.hpp>
#include <task01.visitor.c++03/visitor.hpp>

namespace psso
{
class EvaluateVisitor : public Visitor
{
  protected:
    std::stack<int> intermediate_results_;

    int get_and_pop()
    {
        auto tmp = intermediate_results_.top();
        intermediate_results_.pop();
        return tmp;
    }

  public:
    void visit(BinaryOperatorNode* node) override
    {
        node->get_left().accept(*this);
        node->get_right().accept(*this);
        auto right  = get_and_pop();
        auto left   = get_and_pop();
        auto result = node->compute(left, right);
        intermediate_results_.push(result);
    }

    int get_value()
    {
        return intermediate_results_
            .top(); // top stores result of arithmetic operations after visiting
                    // whole tree
    }

    void visit(NumericNode* node) override
    {
        intermediate_results_.push(node->get_value());
    }
};
} // namespace psso
