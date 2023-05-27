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
 * Construct a new Node< T>:: Node object
 * @tparam T Type of the node
 * @param data
 */
template <class T>
Node<T>::Node(const T &data) : m_data(data)
{
    this->m_neighbors = std::unordered_set<std::shared_ptr<Node<T>>>();
}

// Access Methods
/**
 * @brief
 * Get the data object
 * @tparam T Type of the node
 * @return T& Data of the node
 */
template <class T>
T &Node<T>::get_data() const
{
    return this->m_data;
}

/**
 * @brief
 * Get the neighbors object
 * @tparam T Type of the node
 * @return std::unordered_set<std::shared_ptr<Node<T>>>& Neighbors of the node
 */
template <class T>
std::unordered_set<std::shared_ptr<Node<T>>> &Node<T>::get_neighbors() const
{
    return this->m_neighbors;
}

// Modifiers
/**
 * @brief
 * Set the data object
 * @tparam T Type of the node
 * @param data Data of the node
 */
template <class T>
void Node<T>::set_data(const T &data)
{
    this->m_data = data;
}

/**
 * @brief
 * Add a neighbor to the node
 * @tparam T Type of the node
 * @param neighbor Neighbor to add
 */
template <class T>
void Node<T>::add_neighbor(const std::shared_ptr<Node<T>> &neighbor)
{
    this->m_neighbors.insert(neighbor);
}

// Operators
/**
 * @brief
 * Compare two nodes
 * @tparam T Type of the node
 * @param other Node to compare
 * @return true If the nodes are equal
 * @return false If the nodes are not equal
 */
template <class T>
bool Node<T>::operator==(const Node<T> &other) const
{
    return this->m_data == other.m_data;
}

/**
 * @brief
 * Compare two nodes
 * @tparam T Type of the node
 * @param other Node to compare
 * @return true If the nodes are not equal
 * @return false If the nodes are equal
 */
template <class T>
bool Node<T>::operator!=(const Node<T> &other) const
{
    return this->m_data != other.m_data;
}

// Methods
/**
 * @brief
 * Check if a node is a neighbor
 * @tparam T Type of the node
 * @param neighbor Node to check
 * @return true If the node is a neighbor
 * @return false If the node is not a neighbor
 */
template <class T>
bool Node<T>::is_neighbor(const std::shared_ptr<Node<T>> &neighbor) const
{
    return this->m_neighbors.find(neighbor) != this->m_neighbors.end();
}

/**
 * @brief
 * Check if a node is a neighbor
 * @tparam T Type of the node
 * @param data Data of the node to check
 * @return true If the node is a neighbor
 * @return false If the node is not a neighbor
 */
template <class T>
bool Node<T>::is_neighbor(const T &data) const
{
    for (auto neighbor : this->m_neighbors)
        if (neighbor->get_data() == data)
            return true;

    return false;
}

/**
 * @brief
 * Check if a node is a neighbor
 * @tparam T Type of the node
 * @param node Node to check
 * @return true If the node is a neighbor
 * @return false If the node is not a neighbor
 */
template <class T>
bool Node<T>::is_neighbor(const Node<T> &node) const
{
    return this->is_neighbor(node.get_data());
}
