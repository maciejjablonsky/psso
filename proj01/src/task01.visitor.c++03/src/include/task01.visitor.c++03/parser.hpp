#pragma once

#include <boost/tokenizer.hpp>
#include <fmt/format.h>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <task01.visitor.c++03/addition_node.hpp>
#include <task01.visitor.c++03/division_node.hpp>
#include <task01.visitor.c++03/modulo_node.hpp>
#include <task01.visitor.c++03/multiplication_node.hpp>
#include <task01.visitor.c++03/numeric_node.hpp>
#include <task01.visitor.c++03/subtraction_node.hpp>
#include <task01.visitor.c++03/tree_node.hpp>
#include <unordered_map>

namespace psso
{
class Parser
{
  private:
    std::stack<std::unique_ptr<TreeNode>> tree_stack_;
    std::stack<std::string> operator_stack_;

    const std::unordered_map<std::string, int> operators_ = {
        {"*", 2}, {"/", 2}, {"%", 2}, {"+", 1}, {"-", 1}};

  public:
    std::unique_ptr<TreeNode> parse(const std::string in_fix_expression)
    {
        tree_stack_     = {};
        operator_stack_ = {};
        boost::char_separator<char> separator{" "};
        boost::tokenizer<boost::char_separator<char>> tokenizer{
            in_fix_expression, separator};
        for (const auto& token : tokenizer)
        {
            if (token == "(")
            {
                operator_stack_.push(token);
            }
            else if (is_integer(token))
            {
                tree_stack_.emplace(
                    std::make_unique<NumericNode>(std::atoi(token.c_str())));
            }
            else if (is_operator(token))
            {
                if (operator_stack_.empty() || operator_stack_.top() == "(" ||
                    operators_.at(operator_stack_.top()) < operators_.at(token))
                {
                    operator_stack_.push(token);
                }
                else
                {
                    do
                    {
                        pop_connect_push();
                    } while (!operator_stack_.empty() &&
                             operator_stack_.top() != "(" &&
                             operators_.at(token) <
                                 operators_.at(operator_stack_.top()));
                    operator_stack_.push(token);
                }
            }
            else if (token == ")")
            {
                while (operator_stack_.top() != "(")
                {
                    pop_connect_push();
                }
                operator_stack_.pop(); // pop the opening bracket off the stack
            }
            else
            {
                fmt::print(stderr, "Error in expression\n");
            }
        }
        while (!operator_stack_.empty())
        {
            pop_connect_push();
        }
        return std::move(tree_stack_.top());
    }

  private:
    bool is_integer(const std::string& token) const
    {
        return !token.empty() &&
               std::find_if(token.begin(), token.end(), [](unsigned char c) {
                   return !std::isdigit(c);
               }) == token.end();
    }

    bool is_operator(const std::string& token) const
    {
        return operators_.find(token) != operators_.end();
    }

    void pop_connect_push()
    {
        auto right = std::move(tree_stack_.top());
        tree_stack_.pop();
        auto left = std::move(tree_stack_.top());
        tree_stack_.pop();
        auto tree = binary_operator_node_factory(
            operator_stack_.top(), std::move(left), std::move(right));
        operator_stack_.pop();
        tree_stack_.push(std::move(tree));
    }

    std::unique_ptr<BinaryOperatorNode> binary_operator_node_factory(
        const std::string& op,
        std::unique_ptr<TreeNode>&& left_node,
        std::unique_ptr<TreeNode>&& right_node)
    {
        if (op == "+")
        {
            return std::make_unique<AdditionNode>(std::move(left_node),
                                                  std::move(right_node));
        }
        else if (op == "-")
        {
            return std::make_unique<SubtractionNode>(std::move(left_node),
                                                     std::move(right_node));
        }
        else if (op == "*")
        {
            return std::make_unique<MultiplicationNode>(std::move(left_node),
                                                        std::move(right_node));
        }
        else if (op == "/")
        {
            return std::make_unique<DivisionNode>(std::move(left_node),
                                                  std::move(right_node));
        }
        else if (op == "%")
        {
            return std::make_unique<ModuloNode>(std::move(left_node),
                                                std::move(right_node));
        }
        else
        {
            throw std::runtime_error("Undefined operator");
        }
    }
};
} // namespace psso