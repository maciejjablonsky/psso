#include <fmt/format.h>
#include <task01.visitor.c++03.example/binary_tree_leaf.hpp>
#include <task01.visitor.c++03.example/summation_visitor.hpp>
#include <task01.visitor.c++03.example/traversal_visitor.hpp>

int main()
{
    fmt::print("Building the tree (1): leaves\n");

    auto one   = std::make_unique<psso::BinaryTreeLeaf>(1);
    auto two   = std::make_unique<psso::BinaryTreeLeaf>(2);
    auto three = std::make_unique<psso::BinaryTreeLeaf>(3);

    fmt::print("Build the tree (1): regular nodes\n");

    auto regN =
        std::make_unique<psso::BinaryTreeNode>(std::move(one), std::move(two));
    auto root = std::make_unique<psso::BinaryTreeNode>(std::move(regN),
                                                       std::move(three));

    fmt::print("The tree now looks like this: \n");
    fmt::print("         regN                 \n");
    fmt::print("        /    \\               \n");
    fmt::print("    regN      3               \n");
    fmt::print("   /    \\                    \n");
    fmt::print("  1      2                    \n");

    fmt::print("Visitor 1: SumVisitor, collects the sum of leaf\n");
    fmt::print("values. Result should be 6.\n");

    psso::SummationVisitor sum_visitor;
    root->accept(sum_visitor);
    fmt::print("{}\n", sum_visitor.report());

    psso::TraversalVisitor traversal_visitor;
    root->accept(traversal_visitor);
    fmt::print("{}\n", traversal_visitor.report());
}
