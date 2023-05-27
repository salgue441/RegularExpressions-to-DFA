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
#include "graph/graph.cpp"

// Main file
int main(const int argc, char const **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0]
                  << " input file with regex expression" << std::endl;
        return EXIT_FAILURE;
    }

    // Graph
    Graph<int, char> graph;

    auto node1 = graph.add_node(1);
    auto node2 = graph.add_node(2);
    auto node3 = graph.add_node(3);

    // Add edges between the nodes
    graph.add_edge(node1, node2);
    graph.add_edge(node1, node3);
    graph.add_edge(node2, node3);

    // Print the adjacency list
    std::cout << "Graph adjacency list:\n";
    std::cout << graph.print_adjacency_list() << std::endl;
}