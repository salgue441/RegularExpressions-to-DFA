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
#include <unordered_map>
#include <memory>

// Project Libraries
#include "../node/node.h"

/**
 * @class graph
 * @brief Class that represents a graph
 * @tparam T Type of the nodes
 * @tparam E Type of the edges
 */
template <class T, class E>
class Graph
{
public:
    // Constructor
    Graph() = default;

    // Destructor
    ~Graph() = default;

    // Access Methods
    const std::unordered_map<T, std::shared_ptr<Node<T, E>>> &get_nodes() const;

    // Modifiers
    void add_node(const T &);
    void add_edge(const T &, const T &, const E &);

    // Operators
    bool operator==(const Graph<T, E> &) const;
    bool operator!=(const Graph<T, E> &) const;

    // Methods
    bool has_node(const T &) const;
    bool has_edge(const T &, const T &) const;

private:
    std::unordered_map<T, std::shared_ptr<Node<T, E>>> m_nodes;
};

#endif //! GRAPH_H