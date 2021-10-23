#pragma once

#include <fmt/format.h>
#include <memory>
#include <string>
#include <task01.non_visitor/tree_node.hpp>

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
        return fmt::format(
            "({} {} {})", left_->to_infix(), label_, right_->to_infix());
    }

    std::string to_postfix() override
    {
        return fmt::format(
            "{} {} {}", left_->to_postfix(), right_->to_postfix(), label_);
    }

    std::string to_prefix() override
    {
        return fmt::format(
            "{} {} {}", label_, left_->to_prefix(), right_->to_prefix());
    }

    double evaluate() override
    {
        return calculate(left_->evaluate(), label_, right_->evaluate());
    }

  private:
    auto calculate(auto left, const std::string& op, auto right)
    {
        if (op == "*")
        {
            return left * right;
        }
        else if (op == "/")
        {
            return left / right;
        }
        else if (op == "+")
        {
            return left + right;
        }
        else if (op == "-")
        {
            return left - right;
        }
        throw std::runtime_error("Unknown arithmetic operation");
    }
};
} // namespace psso
