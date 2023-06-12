/**
 * @file node.h
 * @author Carlos Salguero
 * @brief Declaration of the node class
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SRC_NODE_NODE_H_
#define SRC_NODE_NODE_H_

#include <unordered_map>
#include <optional>
#include <memory>
#include <vector>

/**
 * @class Node
 * @brief
 * Class that represents a node in the automata's graph
 */
class Node
{
public:
    // Character and target node ID
    using Transition = std::unordered_map<char, std::shared_ptr<Node>>;

    // Constructors
    Node() = default;
    explicit Node(int id, bool is_final = false);

    // Destructor
    ~Node() = default;

    // Access Methods
    int get_id() const;
    bool is_final() const;
    const Transition &get_transitions() const;

    // Modifiers
    void set_id(const int &);
    void set_final(const bool &);
    void add_transition(const char &, const std::shared_ptr<Node> &);

    // Operators
    bool operator==(const Node &) const;
    bool operator!=(const Node &) const;

    // Methods
    bool has_transition(const char &) const;
    const Transition::const_iterator get_transition(const char &) const;
    std::optional<int> get_target_id(const char &) const;

private:
    int m_id;
    Transition m_transitions;
    bool m_is_final;
};

#endif //! SRC_NODE_NODE_H_
