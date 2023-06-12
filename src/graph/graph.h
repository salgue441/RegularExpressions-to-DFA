/**
 * @file graph.h
 * @author Carlos Salguero
 * @brief Declaration of the graph class
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SRC_GRAPH_GRAPH_H_
#define SRC_GRAPH_GRAPH_H_

// C++ Standard Library
#include <unordered_map>
#include <optional>
#include <memory>

// Project files
#include "../node/node.h"

/**
 * @class Graph
 * @brief Class that represents a graph for automata
 */
class Graph
{
public:
    // Constructors
    Graph() = default;

    // Destructor
    ~Graph() = default;

    // Access Methods
    const std::unordered_map<int, std::shared_ptr<Node>> &get_nodes() const;

    // Mutators
    void add_transition(const int &, const char &, const int &);
    void set_nodes(const std::unordered_map<int, std::shared_ptr<Node>> &);
    void set_nodes(const int &, const std::shared_ptr<Node> &);

    // Methods
    bool is_final(const int &) const;
    const std::shared_ptr<Node> get_node(const int &) const;
    const std::shared_ptr<Node> get_final_node() const;
    void set_final_node(const int &);
    void set_final_node(const std::shared_ptr<Node> &);
    std::shared_ptr<Node> create_node(const bool &is_final = false);
    std::shared_ptr<Node> create_node(const int &, bool is_final = false);
    void merge_graphs(const std::shared_ptr<Graph> &,
                      const std::shared_ptr<Graph> &);

private:
    std::unordered_map<int, std::shared_ptr<Node>> m_nodes;
    int m_next_id = 1;
};

#endif //! SRC_GRAPH_GRAPH_H_