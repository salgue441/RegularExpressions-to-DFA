/**
 * @file graph.h
 * @author Carlos Salguero
 * @author Diego Sandoval
 * @brief Implementation of the graph class
 * @version 0.1
 * @date 2023-05-27
 *
 * @copyright Copyright (c) 2023
 *
 */

// Project files
#include "graph.h"

// Access Methods
/**
 * @brief
 * Get the nodes of the graph
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @return const std::vector<std::shared_ptr<Node<T, E>>>& Nodes of the graph
 */
template <class T, class E>
const std::vector<std::shared_ptr<Node<T, E>>> &Graph<T, E>::get_nodes() const
{
    return m_nodes;
}

// Modifiers
/**
 * @brief
 * Add a node to the graph
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param data Data that the node will store
 * @return std::shared_ptr<Node<T, E>> Node that was added
 */
template <class T, class E>
std::shared_ptr<Node<T, E>> Graph<T, E>::add_node(const T &data)
{
    auto node = std::make_shared<Node<T, E>>(data);
    m_nodes.push_back(node);

    return node;
}

/**
 * @brief
 * Remove a node from the graph
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param node Node that will be removed
 */
template <class T, class E>
void Graph<T, E>::remove_node(const std::shared_ptr<Node<T, E>> &node)
{
    for (auto &n : m_nodes)
        n->remove_edge(node);

    m_nodes.erase(
        std::remove(m_nodes.begin(), m_nodes.end(), node), m_nodes.end());
}

// Methods (public)
/**
 * @brief
 * Adds an edge between two nodes
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the edge that the node will store
 * @param node1 First node
 * @param node2 Second node
 */
template <class T, class E>
void Graph<T, E>::add_edge(
    const std::shared_ptr<Node<T, E>> &node1,
    const std::shared_ptr<Node<T, E>> &node2)
{
    node1->add_edge(node2);
    node2->add_edge(node1);
}

/**
 * @brief
 * Adds an edge between two nodes
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the edge that the node will store
 * @param node1 First node
 * @param node2 Second node
 * @param symbol
 */
template <class T, class E>
void Graph<T, E>::add_edge(
    const std::shared_ptr<Node<T, E>> &node1,
    const std::shared_ptr<Node<T, E>> &node2,
    const E &symbol)
{
    node1->add_edge(node2, symbol);
    node2->add_edge(node1, symbol);
}

/**
 * @brief
 * Removes an edge from two nodes
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the edge that the node will store
 * @param node1 First node
 * @param node2 Second node
 */
template <class T, class E>
void Graph<T, E>::remove_edge(
    const std::shared_ptr<Node<T, E>> &node1,
    const std::shared_ptr<Node<T, E>> &node2)
{
    node1->remove_edge(node1);
    node2->remove_edge(node2);
}

/**
 * @brief
 * Prints the graph in adjacency list\
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the edge that the node will store
 * @return adjacency_list
 */
template <class T, class E>
std::string Graph<T, E>::print_adjacency_list() const
{
    std::string adjacency_list;

    for (const auto &node : m_nodes)
        adjacency_list += print_node_adjacency_list(node) + '\n';

    return adjacency_list;
}

// Methods (private)
/**
 * @brief
 * Helper method for printing the graph in adjacency list format.
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the edge that the node will store
 * @param node Node that will be printed
 */
template <class T, class E>
std::string Graph<T, E>::print_node_adjacency_list(
    const std::shared_ptr<Node<T, E>> &node) const
{
    std::string adjacencyList = std::to_string(node->get_data()) + ": ";

    const auto &edges = node->get_edges();

    for (const auto &entry : edges)
    {
        const auto &connectedNode = entry.first;
        adjacencyList += std::to_string(connectedNode->get_data()) + " ";
    }

    return adjacencyList;
}
