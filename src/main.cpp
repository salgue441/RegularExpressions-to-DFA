/**
 * @file main.cpp
 * @author Carlos Salguero
 * @brief Declaration of main function
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023
 *
 */

// C++ Standard Library
#include <iostream>
#include <memory>

// Project files
#include "Graph/graph.h"
#include "automata/automata.h"

int main(int argc, char **argv)
{
    std::shared_ptr<Automata> automata =
        std::make_shared<Automata>("a+b*");

    std::shared_ptr<Graph> NFA_graph = automata->build();

    std::cout << "NFA GRAPH: " << std::endl;
    std::cout << NFA_graph->to_string() << std::endl;
}