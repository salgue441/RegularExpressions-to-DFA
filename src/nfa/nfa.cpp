/**
 * @file nfa.cpp
 * @author Carlos Salguero
 * @brief Implementation of the NFA class
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */
// C++ Standard Library
#include <stack>
#include <iterator>
#include <iostream>

// Project files
#include "nfa.h"

// Constructors
/**
 * @brief
 * Construct a new NFA object from a postfix regular expression
 * @param postfix_regex Postfix regular expression
 */
NFA::NFA(const std::string &postfix_regex)
{
    build_nfa(postfix_regex);
}

// Access Methods
/**
 * @brief
 * Get the graph object
 * @return const std::shared_ptr<Graph>& Graph
 */
const std::shared_ptr<Graph> &NFA::get_graph() const
{
    return m_graph;
}

// Methods
/**
 * @brief
 * Check if a string is accepted by the NFA
 * @param str String to check
 * @return true If the string is accepted
 * @return false If the string is not accepted
 */
bool NFA::accepts(const std::string &str) const
{
    return dfs(m_graph->get_node(1), str, 0);
}

// Private Methods
/**
 * @brief
 * Depth-first search algorithm
 * @param node Current node
 * @param str String to check
 * @param index Current index of the string
 * @return true If the string is accepted
 * @return false If the string is not accepted
 */
bool NFA::dfs(const std::shared_ptr<Node> &node,
              const std::string &str, const int &index) const
{
    if (index == str.length())
        return node->is_final();

    std::vector<std::shared_ptr<Node>> next_nodes;
    for (const auto &transition : node->get_transitions())
    {
        if (transition.first == str[index] || transition.first == EPSILON)
        {
            next_nodes.push_back(transition.second);
        }
    }

    for (const auto &next_node : next_nodes)
    {
        if (dfs(next_node, str, index + 1))
            return true;
    }

    // Handle the '*' operator
    for (const auto &transition : node->get_transitions())
    {
        if (transition.first == EPSILON)
        {
            if (dfs(transition.second, str, index))
                return true;
        }
    }

    return false;
}

/**
 * @brief
 * Check if a character is an operator in the regular expression
 * @param character Character to check
 * @return true If the character is an operator
 * @return false If the character is not an operator
 */
bool NFA::is_operator(const char &character) const
{
    return character == '*' || character == '|' || character == '.';
}

/**
 * @brief
 * Build the NFA based on the postfix regular expression
 * @param postfix_regex Postfix regular expression
 */
void NFA::build_nfa(const std::string &postfix_regex)
{
    std::stack<std::shared_ptr<Graph>> graph_stack;

    for (const char &character : postfix_regex)
    {
        if (!is_operator(character))
        {
            auto graph = std::make_shared<Graph>();
            auto start_node = graph->create_node();
            auto final_node = graph->create_node(true);

            start_node->add_transition(character, final_node);

            graph_stack.push(graph);
        }
        else
        {
            if (character == '*')
            {
                auto graph = std::make_shared<Graph>();
                auto start_node = graph->create_node();
                auto final_node = graph->create_node(true);

                auto previous_graph = graph_stack.top();
                graph_stack.pop();

                start_node->add_transition(EPSILON, previous_graph->get_node(1));
                start_node->add_transition(EPSILON, final_node);

                previous_graph->get_final_node()->add_transition(EPSILON, previous_graph->get_node(1));
                previous_graph->get_final_node()->add_transition(EPSILON, final_node);

                graph_stack.push(graph);
            }
            else if (character == '|')
            {
                auto graph = std::make_shared<Graph>();
                auto start_node = graph->create_node();
                auto final_node = graph->create_node(true);

                auto previous_graph_2 = graph_stack.top();
                graph_stack.pop();

                auto previous_graph_1 = graph_stack.top();
                graph_stack.pop();

                start_node->add_transition(EPSILON, previous_graph_1->get_node(1));
                start_node->add_transition(EPSILON, previous_graph_2->get_node(1));

                previous_graph_1->get_final_node()->add_transition(EPSILON, final_node);
                previous_graph_2->get_final_node()->add_transition(EPSILON, final_node);

                graph_stack.push(graph);
            }
            else if (character == '.')
            {
                auto graph = std::make_shared<Graph>();

                auto previous_graph_2 = graph_stack.top();
                graph_stack.pop();

                auto previous_graph_1 = graph_stack.top();
                graph_stack.pop();

                graph->merge_graphs(previous_graph_1, previous_graph_2);

                graph_stack.push(graph);
            }
        }
    }

    if (!graph_stack.empty())
        m_graph = graph_stack.top();
    else
        throw std::runtime_error("Invalid regular expression");
}
