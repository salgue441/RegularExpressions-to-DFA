/**
 * @file graph.h
 * @author Carlos Salguero
 * @author Diego Sandoval
 * @brief Declaration of the graph class
 * @version 0.1
 * @date 2023-05-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef GRAPH_H
#define GRAPH_H

// C++ Standard Library
#include <vector>
#include <memory>
#include <string>

// Project files
#include "../node/node.cpp"

// Class
/**
 * @class Graph
 * @brief Class that represents a graph
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 */
template <class T, class E>
class Graph
{
public:
    // Constructors
    Graph() = default;

    // Destructor
    ~Graph() = default;

    // Access Methods
    const std::vector<std::shared_ptr<Node<T, E>>> &get_nodes() const;

    // Modifiers
    std::shared_ptr<Node<T, E>> add_node(const T &);
    void remove_node(const std::shared_ptr<Node<T, E>> &);

    // Methods
    void add_edge(const std::shared_ptr<Node<T, E>> &,
                  const std::shared_ptr<Node<T, E>> &);
    void add_edge(const std::shared_ptr<Node<T, E>> &,
                  const std::shared_ptr<Node<T, E>> &,
                  const E &);
    void remove_edge(const std::shared_ptr<Node<T, E>> &,
                     const std::shared_ptr<Node<T, E>> &);
    std::string print_adjacency_list() const;

private:
    std::vector<std::shared_ptr<Node<T, E>>> m_nodes;

    // Methods
    std::string print_node_adjacency_list(const std::shared_ptr<Node<T, E>> &) const;
};

#endif //! GRAPH_H