#pragma once

#include <task01.visitor.c++03/binary_operator_node.hpp>

namespace psso
{
class AdditionNode : public BinaryOperatorNode
{
  public:
    AdditionNode(std::unique_ptr<TreeNode>&& left,
                 std::unique_ptr<TreeNode>&& right)
        : BinaryOperatorNode(std::move(left), std::move(right))
    {
    }

    int compute(int left, int right) override
    {
        return left + right;
    }

    std::string get_label() const override
    {
        return "+";
    }
};
} // namespace psso
