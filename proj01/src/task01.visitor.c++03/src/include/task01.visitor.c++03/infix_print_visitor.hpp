#pragma once

#include <string>
#include <task01.visitor.c++03/addition_node.hpp>
#include <task01.visitor.c++03/division_node.hpp>
#include <task01.visitor.c++03/multiplication_node.hpp>
#include <task01.visitor.c++03/numeric_node.hpp>
#include <task01.visitor.c++03/subtraction_node.hpp>
#include <task01.visitor.c++03/visitor.hpp>

namespace psso
{
class InfixPrintVisitor : public Visitor
{
  private:
    std::string result_;

  public:
    void visit(BinaryOperatorNode* node) override
    {
        result_ += '(';
        node->get_left().accept(*this);
        result_ += fmt::format(" {} ", node->get_label());
        node->get_right().accept(*this);
        result_ += ')';
    }

    void visit(NumericNode* node)
    {
        result_ += node->get_label();
    }

    std::string report() const
    {
        return result_;
    }
};
} // namespace psso
