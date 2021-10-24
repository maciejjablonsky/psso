#pragma once

namespace psso
{
class BinaryOperatorNode;
class NumericNode;

class Visitor
{
  public:
    virtual void visit(BinaryOperatorNode* node) = 0;
    virtual void visit(NumericNode* node)        = 0;
};
} // namespace psso
