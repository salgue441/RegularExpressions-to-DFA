/**
 * @file main.cpp
 * @author Carlos Salguero
 * @author Diego Sandoval
 * @brief Main file of the program
 * @version 0.1
 * @date 2023-05-26
 *
 * @copyright Copyright (c) 2023
 *
 */

// C++ Standard Libraries
#include <iostream>
#include <fstream>
#include <memory>

// Project files
#include "node/node.cpp"

// Main file
int main(const int argc, char const **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0]
                  << " input file with regex expression" << std::endl;
        return EXIT_FAILURE;
    }

    // Create nodes
    Node<int, char> node1(1);
    Node<int, char> node2(2);
    Node<int, char> node3(3);

    // Add edges
    node1.add_edge(std::make_shared<Node<int, char>>(node2));
    node1.add_edge(std::make_shared<Node<int, char>>(node3), 'A');
    node3.add_epsilon_transition(std::make_shared<Node<int, char>>(node2));

    // Test access methods
    std::cout << "Data of node1: " << node1.get_data() << std::endl;
    std::cout << "Edges of node1: " << std::endl;

    const auto &edges = node1.get_edges();
    for (const auto &entry : edges)
    {
        const auto &node = entry.first;
        const auto &edge = entry.second;

        std::cout << "Edge to node with data: " << node->get_data()
                  << " with edge: " << edge << std::endl;
    }
}
