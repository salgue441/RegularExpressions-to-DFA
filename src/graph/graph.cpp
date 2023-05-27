/**
 * @file graph.cpp
 * @author Carlos Salguero
 * @author Diego Sandoval
 * @brief Implementation of the graph class
 * @version 0.1
 * @date 2023-05-27
 *
 * @copyright Copyright (c) 2023
 *
 */
// C++ Standard Library
#include <stdexcept>

// Project Libraries
#include "graph.h"

// Access Methods
/**
 * @brief
 * Get the nodes of the graph
 * @tparam T Type of the nodes
 * @tparam E Type of the edges
 * @return const std::unordered_map<T, std::shared_ptr<Node<T, E>>>& Nodes of the graph
 */
template <class T, class E>
const std::unordered_map<T, std::shared_ptr<Node<T, E>>> &Graph<T, E>::get_nodes() const
{
    return m_nodes;
}

// Modifiers
/**
 * @brief
 * Add a node to the graph
 * @tparam T Type of the nodes
 * @tparam E Type of the edges
 * @param data Data of the node
 * @throw std::invalid_argument If the node already exists
 */
template <class T, class E>
void Graph<T, E>::add_node(const T &data)
{
    if (has_node(data))
        throw std::invalid_argument("The node already exists");

    m_nodes[data] = std::make_shared<Node<T, E>>(data);
}

/**
 * @brief
 * Add an edge to the graph
 * @tparam T Type of the nodes
 * @tparam E Type of the edges
 * @param data1 Data of the first node
 * @param data2 Data of the second node
 * @param weight Weight of the edge
 * @throw std::invalid_argument If the nodes don't exist
 */
template <class T, class E>
void Graph<T, E>::add_edge(const T &data1, const T &data2, const E &weight)
{
    if (!has_node(data1) || !has_node(data2))
        throw std::invalid_argument("The nodes don't exist");

    m_nodes.at(data1)->add_neighbor(m_nodes.at(data2), weight);
}

// Operators
/**
 * @brief
 * Compare two graphs
 * @tparam T Type of the nodes
 * @tparam E Type of the edges
 * @param graph Graph to compare
 * @return true If the graphs are equal
 * @return false If the graphs are not equal
 */
template <class T, class E>
bool Graph<T, E>::operator==(const Graph<T, E> &graph) const
{
    if (m_nodes.size() != graph.m_nodes.size())
        return false;

    for (const auto &node : m_nodes)
    {
        if (!graph.has_node(node.first))
            return false;

        if (node.second->get_neighbors().size() !=
            graph.m_nodes.at(node.first)->get_neighbors().size())
            return false;

        for (const auto &neighbor : node.second->get_neighbors())
        {
            if (!graph.has_edge(node.first, neighbor.first->get_data()))
                return false;

            if (neighbor.second != graph.m_nodes.at(node.first)
                                       ->get_neighbors()
                                       .at(neighbor.first)
                                       ->get_data())
                return false;
        }
    }

    return true;
}

/**
 * @brief
 * Compare two graphs
 * @tparam T Type of the nodes
 * @tparam E Type of the edges
 * @param graph Graph to compare
 * @return true If the graphs are not equal
 * @return false If the graphs are equal
 */
template <class T, class E>
bool Graph<T, E>::operator!=(const Graph<T, E> &graph) const
{
    return !(*this == graph);
}

// Methods
/**
 * @brief
 * Check if the graph has a node
 * @tparam T Type of the nodes
 * @tparam E Type of the edges
 * @param data Data of the node
 * @return true If the graph has the node
 * @return false If the graph doesn't have the node
 */
template <class T, class E>
bool Graph<T, E>::has_node(const T &data) const
{
    return m_nodes.find(data) != m_nodes.end();
}

/**
 * @brief
 * Check if the graph has an edge
 * @tparam T Type of the nodes
 * @tparam E Type of the edges
 * @param data1 Data of the first node
 * @param data2 Data of the second node
 * @return true If the graph has the edge
 * @return false If the graph doesn't have the edge
 */
template <class T, class E>
bool Graph<T, E>::has_edge(const T &data1, const T &data2) const
{
    if (!has_node(data1) || !has_node(data2))
        return false;

    return m_nodes.at(data1)->has_neighbor(m_nodes.at(data2));
}
