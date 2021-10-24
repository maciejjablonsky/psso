#pragma once
#include <fmt/format.h>
#include <task01.visitor.c++03/binary_tree_leaf.hpp>
#include <task01.visitor.c++03/binary_tree_node.hpp>
#include <task01.visitor.c++03/binary_tree_visitor.hpp>

namespace psso
{
class SummationVisitor : public BinaryTreeVisitor
{
  protected:
    int sum_ = 0;

  public:
    void visit(BinaryTreeNode* node) override
    {
        node->get_left().accept(*this);
        node->get_right().accept(*this);
    }

    void visit(BinaryTreeLeaf* leaf) override
    {
        sum_ += leaf->get_value();
    }

    std::string report() const override
    {
        return fmt::format(">>> SummationVisitor collected a sum of: {}", sum_);
    }
};
} // namespace psso
