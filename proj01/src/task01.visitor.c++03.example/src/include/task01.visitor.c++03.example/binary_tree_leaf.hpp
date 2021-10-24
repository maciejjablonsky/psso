#pragma once

#include <task01.visitor.c++03.example/visitable.hpp>

namespace psso
{
class BinaryTreeLeaf : public Visitable
{
  protected:
    int value_;

  public:
    BinaryTreeLeaf(int value) : value_(value)
    {
    }

    void accept(BinaryTreeVisitor& visitor) override
    {
        visitor.visit(this);
    }
    int get_value() const
    {
        return value_;
    }
};
} // namespace psso
