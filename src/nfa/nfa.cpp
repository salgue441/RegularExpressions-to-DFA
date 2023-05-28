/**
 * @file nfa.h
 * @author Carlos Salguero
 * @author Diego Sandoval
 * @brief Implementation of the NFA class
 * @version 0.1
 * @date 2023-05-27
 *
 * @copyright Copyright (c) 2023
 *
 */

// C++ Standard Libraries
#include <stack>

// Project files
#include "nfa.h"

// Access Methods
/**
 * @brief
 * Gets the start node of the NFA
 * @return std::shared_ptr<Node<int, char>> start node
 */
std::shared_ptr<Node<int, char>> NFA::get_start_node() const
{
    return m_start_node;
}

/**
 * @brief
 * Gets the last node of the NFA
 * @return std::shared_ptr<Node<int, char>> last node
 */
std::shared_ptr<Node<int, char>> NFA::get_end_node() const
{
    return m_end_node;
}

/**
 * @brief
 * Gets the graph implementation used in the nfa
 * @return Graph<int, char> graph
 */
const Graph<int, char> &NFA::get_graph() const
{
    return m_graph;
}

// Methods (Public)
/**
 * @brief
 * Checks if the NFA accepts a string
 * @param string to check
 * @return true if the string is accepted
 * @return false if the string is not accepted
 */
bool NFA::accepts(const std::string &str) const
{
    std::unordered_set<std::shared_ptr<Node<int, char>>> current_nodes;
    epsilon_closure(m_start_node, current_nodes);

    for (const auto &character : str)
    {
        std::unordered_set<std::shared_ptr<Node<int, char>>> next_nodes;

        for (const auto &node : current_nodes)
        {
            const auto &edges = node->get_edges();

            for (const auto &edge : edges)
                if (edge.second == character)
                    epsilon_closure(edge.first, next_nodes);
        }

        if (next_nodes.empty())
            return false;

        current_nodes.swap(next_nodes);
    }

    return current_nodes.count(m_end_node) > 0;
}

/**
 * @brief
 * Builds a NFA from a regular expression
 * @param regex regular expression
 */
void NFA::build_from_regex(const std::string &regex)
{
    std::stack<char> operators;
    std::stack<std::shared_ptr<NFA>> operands;

    for (const auto &character : regex)
    {
        if (character == '(')
            operators.push(character);

        else if (character == ')')
        {
            while (operators.top() != '(')
            {
                process_operator(operators.top());
                operators.pop();
            }

            if (!operators.empty())
                operators.pop();
        }

        else if (character == '*' || character == '+' || character == '?')
        {
            process_operator(character);
        }

        else if (character == '|' || character == '.')
        {
            while (!operators.empty() && operators.top() != '(' && precedence(operators.top()) >= precedence(character))
                process_operator(operators.top());

            operators.push(character);
        }

        else
        {
            process_character(character);
        }
    }

    while (!operators.empty())
    {
        process_operator(operators.top());
        operators.pop();
    }

    if (!operators.empty())
    {
        m_end_node = operands.top()->get_end_node();
        m_start_node = operands.top()->get_start_node();
        m_graph = operands.top()->get_graph();
    }
}

/**
 * @brief
 * Prints the NFA in adjacency matrix form
 * @return std::string adjacency matrix
 */
std::string NFA::adjacency_matrix() const
{
    return m_graph.print_adjacency_list();
}

// Methods (Private)
/**
 * @brief
 * Processes a character
 * @param character to process
 */
void NFA::process_character(char character)
{
    std::unordered_set<std::shared_ptr<Node<int, char>>> current_nodes;
    for (const auto &node : m_graph.get_nodes())
    {
        const auto &edges = node->get_edges();

        for (const auto &edge : edges)
        {
            if (edge.second == character)
                current_nodes.insert(edge.first);
        }
    }
}

/**
 * @brief
 * Processes an operator
 * @param character Operator to process
 */
void NFA::process_operator(char character)
{
    switch (character)
    {
    case '.':
        concatenate();
        break;
    case '|':
        alternate();
        break;
    case '*':
        kleene_closure();
        break;
    default:
        break;
    }
}

/**
 * @brief
 * Concatenates the last two operands
 */
void NFA::concatenate()
{
    std::vector<std::shared_ptr<Node<int, char>>>
        current_nodes = m_graph.get_nodes();

    if (current_nodes.size() >= 2)
    {
        auto last_node = current_nodes.back();
        current_nodes.pop_back();

        auto second_last_node = current_nodes.back();
        current_nodes.pop_back();

        second_last_node->add_edge(last_node, '\0');

        current_nodes.push_back(second_last_node);
        current_nodes.push_back(last_node);

        m_graph.set_nodes(current_nodes);
    }
}

/**
 * @brief
 * Alternates the last two operands
 */
void NFA::alternate()
{
    std::vector<std::shared_ptr<Node<int, char>>>
        current_nodes = m_graph.get_nodes();

    if (current_nodes.size() >= 2)
    {
        auto last_node = current_nodes.back();
        current_nodes.pop_back();

        auto second_last_node = current_nodes.back();
        current_nodes.pop_back();

        std::shared_ptr<Node<int, char>>
            new_start_node = std::make_shared<Node<int, char>>(0);
        std::shared_ptr<Node<int, char>>
            new_end_node = std::make_shared<Node<int, char>>(1);

        new_start_node->add_edge(second_last_node, '\0');
        new_start_node->add_edge(last_node, '\0');

        second_last_node->add_edge(new_end_node, '\0');
        last_node->add_edge(new_end_node, '\0');

        current_nodes.push_back(new_start_node);
        current_nodes.push_back(new_end_node);

        m_graph.set_nodes(current_nodes);
    }
}

/**
 * @brief
 * Closes the last operand
 */
void NFA::kleene_closure()
{
    std::vector<std::shared_ptr<Node<int, char>>>
        current_nodes = m_graph.get_nodes();

    if (current_nodes.size() >= 2)
    {
        auto last_node = current_nodes.back();
        current_nodes.pop_back();

        std::shared_ptr<Node<int, char>>
            new_start_node = std::make_shared<Node<int, char>>(0);
        std::shared_ptr<Node<int, char>>
            new_end_node = std::make_shared<Node<int, char>>(1);

        new_start_node->add_edge(last_node, '\0');
        new_start_node->add_edge(new_end_node, '\0');

        last_node->add_edge(new_end_node, '\0');
        last_node->add_edge(new_start_node, '\0');

        current_nodes.push_back(new_start_node);
        current_nodes.push_back(new_end_node);

        m_graph.set_nodes(current_nodes);
    }
}

/**
 * @brief
 * Epsilon closure
 */
void NFA::epsilon_closure(const std::shared_ptr<Node<int, char>> &node, std::unordered_set<std::shared_ptr<Node<int, char>>> &nodes) const
{
    nodes.insert(node);

    const auto &edges = node->get_edges();
    for (const auto &edge : edges)
        if (edge.second == '\0' && nodes.count(edge.first) == 0)
            epsilon_closure(edge.first, nodes);
}

/**
 * @brief
 * Returns the precedence of an operator
 * @param character Operator
 * @return int Precedence
 */
int NFA::precedence(char character) const
{
    switch (character)
    {
    case '.':
        return 2;
    case '|':
        return 1;
    case '*':
        return 3;
    default:
        return 0;
    }
}