#pragma once
#include <task01.non_visitor/tree_node.hpp>

namespace psso
{
class SimpleTreeNode : public TreeNode
{
  public:
    SimpleTreeNode(const std::string& label) : TreeNode(label)
    {
    }

    std::string to_in_fix() override
    {
        return {};
    }
};
} // namespace psso
