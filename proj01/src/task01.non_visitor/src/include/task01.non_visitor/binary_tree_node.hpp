#pragma once

#include <memory>
#include <string>
#include <task01.non_visitor/tree_node.hpp>
#include <fmt/format.h>

namespace psso
{
class BinaryTreeNode : public TreeNode
{
  private:
    std::unique_ptr<TreeNode> left_;
    std::unique_ptr<TreeNode> right_;

  public:
    BinaryTreeNode(const std::string& label,
                   std::unique_ptr<TreeNode>&& left,
                   std::unique_ptr<TreeNode>&& right)
        : TreeNode(label), left_(std::move(left)), right_(std::move(right))
    {
    }

    std::string to_infix() override
    {
        return fmt::format("({} {} {})", left_->to_infix(), label_, right_->to_infix());
    }
};
} // namespace psso
