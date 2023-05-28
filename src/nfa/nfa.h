/**
 * @file nfa.h
 * @author Carlos Salguero
 * @author Diego Sandoval
 * @brief Declaration of the NFA class
 * @version 0.1
 * @date 2023-05-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef NFA_H
#define NFA_H

// C++ Standard Libraries
#include <unordered_set>

// Project files
#include "../graph/graph.cpp"

// Class
/**
 * @class NFA
 * @brief Represent a NFA (Non Finite Automata)
 */
class NFA
{
public:
    // Constructor
    NFA() = default;

    // Destructor
    ~NFA() = default;

    // Access Methods
    std::shared_ptr<Node<int, char>> get_start_node() const;
    std::shared_ptr<Node<int, char>> get_end_node() const;
    const Graph<int, char> &get_graph() const;

    // Methods
    bool accepts(const std::string &) const;
    void build_from_regex(const std::string &);
    std::string adjacency_matrix() const;

private:
    std::shared_ptr<Node<int, char>> m_start_node;
    std::shared_ptr<Node<int, char>> m_end_node;
    Graph<int, char> m_graph;

    // Methods
    void process_character(char);
    void process_operator(char);
    void concatenate();
    void alternate();
    void kleene_closure();
    void epsilon_closure(const std::shared_ptr<Node<int, char>> &,
                         std::unordered_set<std::shared_ptr<Node<int, char>>> &) const;
    int precedence(char) const;
};

#endif //! NFA_H