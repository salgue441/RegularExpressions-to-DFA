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

    if (index < str.length())
    {
        for (const auto &transition : node->get_transitions())
        {
            if (transition.first == EPSILON)
            {
                if (dfs(transition.second, str, index))
                    return true;
            }
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

    for (const auto &character : postfix_regex)
    {
        if (is_operator(character))
        {
            if (character == '*')
            {
                auto graph = graph_stack.top();
                graph_stack.pop();

                auto new_graph = std::make_shared<Graph>();
                auto start_node = new_graph->create_node();
                auto final_node = new_graph->create_node(true);

                start_node->add_transition(EPSILON, final_node);
                start_node->add_transition(EPSILON, graph->get_node(1));

                graph->get_final_node()->add_transition(EPSILON, final_node);
                graph->get_final_node()
                    ->add_transition(EPSILON, graph->get_node(1));

                new_graph->merge_graphs(graph, new_graph);

                graph_stack.push(new_graph);
            }
            else if (character == '|')
            {
                auto graph1 = graph_stack.top();
                graph_stack.pop();

                auto graph2 = graph_stack.top();
                graph_stack.pop();

                auto new_graph = std::make_shared<Graph>();
                new_graph->merge_graphs(graph1, graph2);
                graph_stack.push(new_graph);
            }
            else if (character == '.')
            {
                auto graph1 = graph_stack.top();
                graph_stack.pop();

                auto graph2 = graph_stack.top();
                graph_stack.pop();

                auto new_graph = std::make_shared<Graph>();
                new_graph->merge_graphs(graph1, graph2);

                graph_stack.push(new_graph);
            }
        }
        else
        {
            auto new_graph = std::make_shared<Graph>();
            new_graph->create_node();
            new_graph->create_node();
            new_graph->add_transition(1, character, 2);
            graph_stack.push(new_graph);
        }
    }

    m_graph = graph_stack.top();
}
