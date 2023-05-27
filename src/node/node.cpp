/**
 * @file node.cpp
 * @author Carlos Salguero
 * @author Diego Sandoval
 * @brief Implementation of the node class for the graph
 * @version 0.1
 * @date 2023-05-27
 *
 * @copyright Copyright (c) 2023
 *
 */

// Project Libraries
#include "node.h"

// Constructor
/**
 * @brief
 * Construct a new Node< T,  E>:: Node object
 * @tparam T Type of the node
 * @tparam E Type of the edge
 * @param data Data of the node
 */
template <class T, class E>
Node<T, E>::Node(const T &data) : m_data(data) {}

// Access Methods
/**
 * @brief
 * Get the data of the node
 * @tparam T Type of the node
 * @tparam E Type of the edge
 * @return T& Data of the node
 */
template <class T, class E>
const T &Node<T, E>::get_data() const
{
    return m_data;
}

/**
 * @brief
 * Get the neighbors of the node
 * @tparam T Type of the node
 * @tparam E Type of the edge
 * @return std::unordered_map<std::shared_ptr<Node<T>>, E>& Neighbors of the node
 */
template <class T, class E>
const std::unordered_map<
    std::shared_ptr<Node<T, E>>, E> &
Node<T, E>::get_neighbors() const
{
    return m_neighbors;
}

// Modifiers
/**
 * @brief
 * Set the data of the node
 * @tparam T Type of the node
 * @tparam E Type of the edge
 * @param data Data of the node
 */
template <class T, class E>
void Node<T, E>::set_data(const T &data)
{
    m_data = data;
}

/**
 * @brief
 * Add a neighbor to the node
 * @tparam T Type of the node
 * @tparam E Type of the edge
 * @param neighbor Neighbor to add
 */
template <class T, class E>
void Node<T, E>::add_neighbor(const std::shared_ptr<Node<T, E>> &neighbor)
{
    m_neighbors.at(neighbor) = E();
}

/**
 * @brief
 * Add a neighbor to the node
 * @tparam T Type of the node
 * @tparam E Type of the edge
 * @param neighbor Neighbor to add
 * @param edge Edge to add
 */
template <class T, class E>
void Node<T, E>::add_neighbor(
    const std::shared_ptr<Node<T, E>> &neighbor, const E &edge)
{
    m_neighbors.at(neighbor) = edge;
}

// Operators
/**
 * @brief
 * Compare two nodes
 * @tparam T Type of the node
 * @tparam E Type of the edge
 * @param other Node to compare
 * @return true If the nodes are equal
 * @return false If the nodes are not equal
 */
template <class T, class E>
bool Node<T, E>::operator==(const Node<T, E> &other) const
{
    return m_data == other.m_data;
}

/**
 * @brief
 * Compare two nodes
 * @tparam T Type of the node
 * @tparam E Type of the edge
 * @param other Node to compare
 * @return true If the nodes are not equal
 * @return false If the nodes are equal
 */
template <class T, class E>
bool Node<T, E>::operator!=(const Node<T, E> &other) const
{
    return m_data != other.m_data;
}

// Methods
/**
 * @brief
 * Check if a node is a neighbor of the current node
 * @tparam T Type of the node
 * @tparam E Type of the edge
 * @param neighbor Node to check
 * @return true If the node is a neighbor
 * @return false If the node is not a neighbor
 */
template <class T, class E>
bool Node<T, E>::is_neighbor(const std::shared_ptr<Node<T, E>> &neighbor) const
{
    return m_neighbors.find(neighbor) != m_neighbors.end();
}

/**
 * @brief
 * Check if a node is a neighbor of the current node
 * @tparam T Type of the node
 * @tparam E Type of the edge
 * @param data Data of the node to check
 * @return true If the node is a neighbor
 * @return false If the node is not a neighbor
 */
template <class T, class E>
bool Node<T, E>::is_neighbor(const T &data) const
{
    for (const auto &neighbor : m_neighbors)
        if (neighbor.first->get_data() == data)
            return true;

    return false;
}

/**
 * @brief
 * Check if the node is a neighbor of the current node
 * @tparam T Type of the node
 * @tparam E Type of the edge
 * @param node Node to check
 * @return true If the node is a neighbor
 * @return false If the node is not a neighbor
 */
template <class T, class E>
bool Node<T, E>::is_neighbor(const Node<T, E> &node) const
{
    return is_neighbor(node.get_data());
}
