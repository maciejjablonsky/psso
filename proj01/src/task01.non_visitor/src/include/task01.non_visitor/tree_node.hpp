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
    virtual std::string to_infix()   = 0;
    virtual std::string to_postfix() = 0;
    virtual std::string to_prefix()  = 0;
    virtual int evaluate()           = 0;
};
} // namespace psso
