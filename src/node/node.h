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

/**
 * @class Node
 * @brief Class that represents a node in a graph
 * @tparam T Type of the node
 * @tparam E Type of the edge
 */
template <class T, class E>
class Node
{
public:
    // Constructor
    Node() = default;
    Node(const T &);

    // Destructor
    ~Node() = default;

    // Access Methods
    const T &get_data() const;
    const std::unordered_map<
        std::shared_ptr<Node<T, E>>, E> &
    get_neighbors() const;

    // Modifiers
    void set_data(const T &data);
    void add_neighbor(const std::shared_ptr<Node<T, E>> &);
    void add_neighbor(const std::shared_ptr<Node<T, E>> &, const E &);

    // Operators
    bool operator==(const Node<T, E> &) const;
    bool operator!=(const Node<T, E> &) const;

    // Methods
    bool is_neighbor(const std::shared_ptr<Node<T, E>> &) const;
    bool is_neighbor(const T &) const;
    bool is_neighbor(const Node<T, E> &) const;

private:
    T m_data;
    std::unordered_map<std::shared_ptr<Node<T, E>>, E> m_neighbors;
};

#endif //! NODE_H
