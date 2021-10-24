#pragma once
#include <string>
#include <task01.visitor.c++03.example/binary_tree_leaf.hpp>
#include <task01.visitor.c++03.example/binary_tree_node.hpp>
#include <task01.visitor.c++03.example/binary_tree_visitor.hpp>

namespace psso
{
class TraversalVisitor : public BinaryTreeVisitor
{
  protected:
    std::string result_;

  public:
    void visit(BinaryTreeNode* node) override
    {
        result_ += '{';
        node->get_left().accept(*this);
        result_ += ',';
        node->get_right().accept(*this);
        result_ += '}';
    }

    void visit(BinaryTreeLeaf* node) override
    {
        result_ += fmt::format("{}", node->get_value());
    }

    std::string report() const override
    {
        return fmt::format(">>> TraversalVisitor traversed the tree to: {}",
                           result_);
    }
};
} // namespace psso
