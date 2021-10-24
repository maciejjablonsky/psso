#pragma once

#include <task01.visitor.c++03/visitor.hpp>
#include <string>

namespace psso
{
class TreeNode
{
  public:
    virtual void accept(Visitor& visitor) = 0;
    virtual std::string get_label() const = 0;
};
} // namespace psso
