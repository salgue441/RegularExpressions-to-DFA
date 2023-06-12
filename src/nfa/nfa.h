/**
 * @file nfa.h
 * @author Carlos Salguero
 * @brief Declaration of the NFA class
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SRC_NFA_NFA_H_
#define SRC_NFA_NFA_H_

// C++ Standard Library
#include <memory>

// Project files
#include "../graph/graph.h"

/**
 * @class NFA
 * @brief Class that represents a NFA
 */
class NFA
{
public:
    // Constructors
    NFA() = default;
    NFA(const std::string &);

    // Destructor
    ~NFA() = default;

    // Access Methods
    const std::shared_ptr<Graph> &get_graph() const;

    // Methods
    bool accepts(const std::string &) const;

private:
    std::shared_ptr<Graph> m_graph;
    static constexpr char EPSILON = '\0';

    // Methods
    bool dfs(const std::shared_ptr<Node> &, const std::string &,
             const int &) const;
    bool is_operator(const char &) const;
    void build_nfa(const std::string &);
};

#endif //! SRC_NFA_NFA_H_