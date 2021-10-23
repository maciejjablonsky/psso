#pragma once
#include <charconv>
#include <stdexcept>
#include <task01.non_visitor/tree_node.hpp>

namespace psso
{
class SimpleTreeNode : public TreeNode
{
  public:
    SimpleTreeNode(const std::string& label) : TreeNode(label)
    {
    }

    std::string to_infix() override
    {
        return label_;
    }

    std::string to_postfix() override
    {
        return label_; 
    }

    double evaluate() override
    {
        int result        = 0;
        auto parse_result = std::from_chars(
            label_.data(), label_.data() + label_.size(), result);
        if (parse_result.ec == std::errc::invalid_argument)
        {
            throw std::runtime_error(
                fmt::format("Failed to parse: {} as integer number.", label_));
        }
        return result;
    }
};
} // namespace psso
