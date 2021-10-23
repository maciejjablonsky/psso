#pragma once

#include <string>
namespace psso
{
class TreeNode
{
  protected:
    std::string label_;

  protected:
    TreeNode(const std::string& label) : label_(label)
    {
    }

  public:
    virtual std::string to_infix() = 0;
    virtual double evaluate()      = 0;
};
} // namespace psso
