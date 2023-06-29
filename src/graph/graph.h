/**
 * @file graph.h
 * @author Carlos Salguero
 * @brief Declaration of Graph class
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef GRAPH_H
#define GRAPH_H

// C++ Standard Libraries
#include <optional>
#include <set>
#include <map>
#include <string>
#include <memory>
#include <vector>

// Constants
constexpr char EPSILON = 'E';

// Class
/**
 * @class Graph
 * @brief Class that represents a graph
 */
class Graph
{
public:
    // Constructors
    Graph();
    Graph(const Graph &);

    // Destructor
    ~Graph() = default;

    // Access Methods
    const std::optional<char> &get_weight(const int &, const int &) const;
    const int &get_start() const;
    const int &get_next() const;
    const std::set<int> &get_final() const;
    const std::set<int> &get_vertexes() const;
    const std::map<int, std::map<char, std::set<int>>> &get_edges() const;

    // Mutator Methods
    void set_start(const int &);
    void add_final(const int &);
    void add_final(const std::set<int> &);

    // Methods
    bool is_empty() const;
    bool is_final(const int &) const;
    bool contains_vertex(const int &) const;

    void add_edge(const int &, const char &, const int &);

    int create_vertex();
    std::pair<int, int> connect_graph_to_vertex(const std::shared_ptr<Graph> &,
                                                const int &);
    std::string to_string() const;

    std::set<int> e_closure(const int &) const;
    std::set<int> e_closure(const int &, const std::set<int> &) const;
    std::set<int> e_closure(const std::set<int> &) const;

private:
    int m_start;
    int m_next;
    std::set<int> m_final;
    std::set<int> m_vertexes;
    std::map<int, std::map<char, std::set<int>>> m_edges;

    // Private methods
    void add_vertex(const int &);
};

#endif //! GRAPH_H