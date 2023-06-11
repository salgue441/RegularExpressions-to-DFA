/**
 * @file node.cpp
 * @author Carlos Salguero
 * @brief Implementation of the node class
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */
// Project files
#include "node.h"

// C++ Standard Library
#include <utility>

// Constructors
/**
 * @brief
 * Construct a new Node:: Node object
 * @param id Node's ID
 * @param is_final Indicates if the node is final
 */
Node::Node(int id, bool is_final)
    : m_id(id), m_is_final(is_final)
{
}

// Access Methods
/**
 * @brief
 * Returns the node's ID
 * @return int Node's ID
 */
int Node::get_id() const
{
    return m_id;
}

/**
 * @brief
 * Returns if the node is final
 * @return true If the node is final
 * @return false If the node is not final
 */
bool Node::is_final() const
{
    return m_is_final;
}

/**
 * @brief
 * Returns the node's transitions
 * @return const Transition& Node's transitions
 */
const Node::Transition &Node::get_transitions() const
{
    return m_transitions;
}

// Modifiers
/**
 * @brief
 * Sets the node's ID
 * @param id Node's ID
 */
void Node::set_id(const int &id)
{
    m_id = id;
}

/**
 * @brief
 * Sets if the node is final
 * @param is_final Indicates if the node is final
 */
void Node::set_final(const bool &is_final)
{
    m_is_final = is_final;
}

/**
 * @brief
 * Adds a transition to the node
 * @param character Character that triggers the transition
 * @param target Target node
 */
void Node::add_transition(const char &character,
                          const std::shared_ptr<Node> &target)
{
    m_transitions[character] = target;
}

// Operators
/**
 * @brief
 * Compares two nodes
 * @param other Node to compare
 * @return true If the nodes are equal
 * @return false If the nodes are not equal
 */
bool Node::operator==(const Node &other) const
{
    return m_id == other.m_id &&
           m_is_final == other.m_is_final &&
           m_transitions == other.m_transitions;
}

/**
 * @brief
 * Compares two nodes
 * @param other Node to compare
 * @return true If the nodes are not equal
 * @return false If the nodes are equal
 */
bool Node::operator!=(const Node &other) const
{
    return !(*this == other);
}

// Methods
/**
 * @brief
 * Returns the target node's ID
 * @param character Character that triggers the transition
 * @return std::optional<int> Target node's ID
 * @return std::nullopt If the transition does not exist
 */
std::optional<int> Node::get_target_id(const char &character) const
{
    auto it = m_transitions.find(character);

    if (it != m_transitions.end())
        return it->second->get_id();

    throw std::runtime_error("Transition does not exist.");
}