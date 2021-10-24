#pragma once

#include <string>

namespace psso
{
class BinaryTreeNode;
class BinaryTreeLeaf;

class BinaryTreeVisitor
{

  public:
    virtual void visit(BinaryTreeNode* node) = 0;
    virtual void visit(BinaryTreeLeaf* node) = 0;
    virtual std::string report() const       = 0;
};
} // namespace psso
