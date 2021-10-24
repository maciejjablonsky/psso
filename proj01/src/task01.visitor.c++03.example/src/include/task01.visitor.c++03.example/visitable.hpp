#pragma once

#include <task01.visitor.c++03.example/binary_tree_visitor.hpp>

namespace psso
{
class Visitable
{
  public:
    virtual void accept(BinaryTreeVisitor& visitor) = 0;
};
}; // namespace psso
