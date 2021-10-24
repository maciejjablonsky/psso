#pragma once

#include <memory>
#include <task01.visitor.c++03/tree_node.hpp>

namespace psso
{
class BinaryOperatorNode : public TreeNode
{
  protected:
    std::unique_ptr<TreeNode> left_;
    std::unique_ptr<TreeNode> right_;

  public:

    BinaryOperatorNode(std::unique_ptr<TreeNode>&& left,
                       std::unique_ptr<TreeNode>&& right)
        : left_(std::move(left)), right_(std::move(right))
    {
    }

    void accept(Visitor& visitor) override
    {
        visitor.visit(this); 
    }

    virtual int compute(int left, int right) = 0;

    TreeNode& get_left()
    {
        return *left_; 
    }

    TreeNode& get_right()
    {
        return *right_; 
    }

};
} // namespace psso
