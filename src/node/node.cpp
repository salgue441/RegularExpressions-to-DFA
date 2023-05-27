/**
 * @file node.h
 * @author Carlos Salguero
 * @author Diego Sandoval
 * @brief Implementation of the node class for the graph
 * @version 0.1
 * @date 2023-05-27
 *
 * @copyright Copyright (c) 2023
 *
 */

// Project files
#include "node.h"

// Constructors
/**
 * @brief
 * Construct a new Node< T,  E>:: Node object
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param data Data that the node will store
 */
template <class T, class E>
Node<T, E>::Node(const T &data) : m_data(data)
{
}

// Access Methods
/**
 * @brief
 * Get the data of the node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @return const T& Data of the node
 */
template <class T, class E>
const T &Node<T, E>::get_data() const
{
    return m_data;
}

/**
 * @brief
 * Get the edges of the node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @return const std::unordered_map<std::shared_ptr<Node<T, E>>, E>& Edges of the node
 */
template <class T, class E>
const std::unordered_map<std::shared_ptr<Node<T, E>>, E> &Node<T, E>::get_edges() const
{
    return m_edges;
}

// Operators
/**
 * @brief
 * Compare two nodes
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
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
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param other Node to compare
 * @return true If the nodes are not equal
 * @return false If the nodes are equal
 */
template <class T, class E>
bool Node<T, E>::operator!=(const Node<T, E> &other) const
{
    return m_data != other.m_data;
}

// Modifiers
/**
 * @brief
 * Set the data of the node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param data Data of the node
 */
template <class T, class E>
void Node<T, E>::set_data(const T &data)
{
    m_data = data;
}

/**
 * @brief
 * Add an edge to the node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param node Node to add the edge
 */
template <class T, class E>
void Node<T, E>::add_edge(const std::shared_ptr<Node<T, E>> &node)
{
    m_edges[node] = E();
}

/**
 * @brief
 * Add an edge to the node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param node Node to add the edge
 * @param edge Edge to add
 */
template <class T, class E>
void Node<T, E>::add_edge(
    const std::shared_ptr<Node<T, E>> &node, const E &edge)
{
    m_edges[node] = edge;
}

/**
 * @brief
 * Remove an edge from the node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param node Node to remove the edge
 */
template <class T, class E>
void Node<T, E>::remove_edge(const std::shared_ptr<Node<T, E>> &node)
{
    m_edges.erase(node);
}

// Methods
/**
 * @brief
 * Check if the node has an edge with another node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param node Node to check if there is an edge
 * @return true If there is an edge
 * @return false If there is not an edge
 */
template <class T, class E>
bool Node<T, E>::has_edge(const std::shared_ptr<Node<T, E>> &node) const
{
    return m_edges.find(node) != m_edges.end();
}

/**
 * @brief
 * Checks if the node is connected to another node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param node Node to check if it is connected
 * @return true If the node is connected
 * @return false If the node is not connected
 */
template <class T, class E>
bool Node<T, E>::is_connected(const std::shared_ptr<Node<T, E>> &node) const
{
    return has_edge(node) &&
           node->has_edge(std::make_shared<Node<T, E>>(*this));
}

/**
 * @brief
 * Checks if the node has an epsilon transition with another node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param node Node to check if there is an epsilon transition
 * @return true If there is an epsilon transition
 * @return false If there is not an epsilon transition
 */
template <class T, class E>
bool Node<T, E>::has_epsilon_transition(
    const std::shared_ptr<Node<T, E>> &node) const
{
    return m_epsilon_transitions.find(node) != m_epsilon_transitions.end();
}

/**
 * @brief
 * Adds an epsilon transition to the node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param node Node to add the epsilon transition
 */
template <class T, class E>
void Node<T, E>::add_epsilon_transition(const std::shared_ptr<Node<T, E>> &node)
{
    m_epsilon_transitions.insert(std::make_pair(node, E()));
}

/**
 * @brief
 * Adds an epsilon transition to the node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param node Node to add the epsilon transition
 * @param edge Edge to add
 */
template <class T, class E>
void Node<T, E>::add_epsilon_transition(
    const std::shared_ptr<Node<T, E>> &node, const E &edge)
{
    m_edges[node] = edge;
    m_epsilon_transitions.insert(std::make_pair(node, edge));
}

/**
 * @brief
 * Removes an epsilon transition from the node
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 * @param node Node to remove the epsilon transition
 */
template <class T, class E>
void Node<T, E>::remove_epsilon_transition(
    const std::shared_ptr<Node<T, E>> &node)
{
    m_epsilon_transitions.erase(node);
}