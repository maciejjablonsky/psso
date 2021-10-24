#pragma once

#include <fmt/format.h>
#include <string>
#include <task01.visitor.c++03/tree_node.hpp>

namespace psso
{
class NumericNode : public TreeNode
{
  private:
    int value_;

  public:
    NumericNode(int value) : value_(value)
    {
    }

    void accept(Visitor& visitor) override
    {
        visitor.visit(this);
    }

    std::string get_label() const override
    {
        return fmt::format("{}", get_value());
    }

    int get_value() const
    {
        return value_;
    }
};

} // namespace psso
