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
    virtual std::string to_in_fix() = 0;
};
} // namespace psso
