/**
 * @file main.cpp
 * @author Carlos Salguero
 * @brief Main file of the program
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */

// C++ Standard Libraries
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

// Project files
#include "./graph/graph.h"

// Function prototypes
std::string infix_to_postfix(const std::string &);

/**
 * @brief
 * Main function of the program
 * @param argc Number of arguments
 * @param argv Arguments
 * @return int Exit code
 */
int main(int argc, char const **argv)
{
    try
    {
        Graph graph;

        auto node1 = graph.create_node();
        auto node2 = graph.create_node();
        auto node3 = graph.create_node(true);

        graph.add_transition(node1->get_id(), 'a', node2->get_id());
        graph.add_transition(node2->get_id(), 'b', node3->get_id());
        graph.add_transition(node3->get_id(), 'c', node1->get_id());

        const auto &nodes = graph.get_nodes();
        std::cout << "Number of nodes: " << nodes.size() << '\n';

        for (const auto &[id, node] : nodes)
        {
            std::cout << "Node " << id << ": "
                      << (node->is_final() ? "Final" : "Not final")
                      << std::endl;
        }

        std::cout << "Node 3 is final: "
                  << (graph.is_final(node3->get_id()) ? "Yes" : "No") << std::endl;

        // Test get_node method
        const auto &target_node = graph.get_node(node1->get_id());
        std::cout
            << "Target node of transition from Node 1 with symbol 'a': "
            << target_node->get_id() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

/**
 * @brief
 * Converts an infix regular expression to a postfix regular expression
 * @param infix Infix regular expression
 * @return std::string Postfix regular expression
 */
std::string infix_to_postfix(const std::string &infix)
{
    std::unordered_map<char, int> precedence{
        {'*', 3}, {'.', 2}, {'|', 1}, {'(', 0}};

    std::string postfix;
    std::stack<char> operators;

    for (const char &character : infix)
    {
        if (std::isalpha(character))
            postfix += character;

        else if (character == '(')
            operators.push(character);

        else if (character == ')')
        {
            while (operators.top() != '(')
            {
                postfix += operators.top();
                operators.pop();
            }

            operators.pop();
        }

        else
        {
            while (!operators.empty() &&
                   precedence[operators.top()] >= precedence[character])
            {
                postfix += operators.top();
                operators.pop();
            }

            operators.push(character);
        }
    }

    while (!operators.empty())
    {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}
