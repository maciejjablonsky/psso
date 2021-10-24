#pragma once

#include <memory>
#include <task01.visitor.c++03/visitable.hpp>

namespace psso
{
class BinaryTreeNode : public Visitable
{
  protected:
    std::unique_ptr<Visitable> left_;
    std::unique_ptr<Visitable> right_;

  public:
    BinaryTreeNode(std::unique_ptr<Visitable>&& left,
                   std::unique_ptr<Visitable>&& right)
        : left_(std::move(left)), right_(std::move(right))
    {
    }

    void accept(BinaryTreeVisitor& visitor) override
    {
        visitor.visit(this);
    }

    Visitable& get_left()
    {
        return *left_;
    }

    Visitable& get_right()
    {
        return *right_;
    }
};
} // namespace psso
