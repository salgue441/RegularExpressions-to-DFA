/**
 * @file node.h
 * @author Carlos Salguero
 * @author Diego Sandoval
 * @brief Declaration of the node class for the graph
 * @version 0.1
 * @date 2023-05-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef NODE_H
#define NODE_H

// C++ Standard Library
#include <unordered_map>
#include <memory>

// Class
/**
 * @class Node
 * @brief Class that represents a node in the graph
 * @tparam T Type of the data that the node will store
 * @tparam E Type of the data that the edge will store
 */
template <class T, class E>
class Node
{
public:
    // Constructors
    Node() = default;
    Node(const T &);

    // Destructor
    ~Node() = default;

    // Access Methods
    const T &get_data() const;
    const std::unordered_map<std::shared_ptr<Node<T, E>>, E> &get_edges() const;

    // Operators
    bool operator==(const Node<T, E> &) const;
    bool operator!=(const Node<T, E> &) const;

    // Modifiers
    void set_data(const T &);
    void add_edge(const std::shared_ptr<Node<T, E>> &);
    void add_edge(const std::shared_ptr<Node<T, E>> &, const E &);
    void remove_edge(const std::shared_ptr<Node<T, E>> &);

    // Methods
    bool has_edge(const std::shared_ptr<Node<T, E>> &) const;
    bool has_edge(const E &) const;
    bool is_connected(const std::shared_ptr<Node<T, E>> &) const;
    bool has_epsilon_transition(const std::shared_ptr<Node<T, E>> &) const;
    void add_epsilon_transition(const std::shared_ptr<Node<T, E>> &);
    void add_epsilon_transition(const std::shared_ptr<Node<T, E>> &, const E &);
    void remove_epsilon_transition(const std::shared_ptr<Node<T, E>> &);

private:
    T m_data;
    std::unordered_map<std::shared_ptr<Node<T, E>>, E> m_edges;
    std::unordered_map<std::shared_ptr<Node<T, E>>, E> m_epsilon_transitions;
};

#endif //!  NODE_H