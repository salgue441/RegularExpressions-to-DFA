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
#include <unordered_set>
#include <memory>

/**
 * @class Node
 * @brief Class that represents a node in a graph
 * @tparam T Type of the node
 */
template <class T>
class Node
{
public:
    // Constructor
    Node() = default;
    Node(const T &data);

    // Destructor
    ~Node() = default;

    // Access Methods
    T &get_data() const;
    std::unordered_set<std::shared_ptr<Node<T>>> &get_neighbors() const;

    // Modifiers
    void set_data(const T &data);
    void add_neighbor(const std::shared_ptr<Node<T>> &);

    // Operators
    bool operator==(const Node<T> &) const;
    bool operator!=(const Node<T> &) const;

    // Methods
    bool is_neighbor(const std::shared_ptr<Node<T>> &) const;
    bool is_neighbor(const T &) const;
    bool is_neighbor(const Node<T> &) const;

private:
    T m_data;
    std::unordered_set<std::shared_ptr<Node<T>>> m_neighbors;
};

#endif //! NODE_H
