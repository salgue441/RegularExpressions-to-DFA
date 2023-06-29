/**
 * @file graph.cpp
 * @author Carlos Salguero
 * @brief Implementation of Graph class
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023
 *
 */
// C++ Standard Libraries
#include <stack>
#include <sstream>

// Project file
#include "graph.h"

// Constructors
/**
 * @brief
 * Construct a new Graph:: Graph object
 */
Graph::Graph()
{
    this->m_next = 0;
}

/**
 * @brief
 * Construct a new Graph:: Graph object
 * @param other Graph to be copied
 */
Graph::Graph(const Graph &other)
{
    this->m_start = other.m_start;
    this->m_next = other.m_next;
    this->m_final = other.m_final;
    this->m_vertexes = other.m_vertexes;
    this->m_edges = other.m_edges;
}

// Access Methods
/**
 * @brief
 * Get the weight of an edge
 * @param from Origin vertex
 * @param to Destination vertex
 * @return const weight of the edge
 * @return const std::optional<char> no_weight if the edge does not exist
 */
const std::optional<char> &Graph::get_weight(
    const int &from, const int &to) const
{
    auto it = this->m_edges.find(from);

    if (it != this->m_edges.end())
    {
        const std::map<char, std::set<int>> &edges_map = it->second;

        for (const auto &weight_it : edges_map)
        {
            const std::set<int> &destinations = weight_it.second;

            if (destinations.count(to) > 0)
            {
                static const std::optional<char> weight(weight_it.first);
                return weight;
            }
        }
    }

    static const std::optional<char> no_weight;
    return no_weight;
}

/**
 * @brief
 * Get the start vertex
 * @return const int& start vertex
 */
const int &Graph::get_start() const
{
    return this->m_start;
}

/**
 * @brief
 * Get the next vertex
 * @return const int& next vertex
 */
const int &Graph::get_next() const
{
    return this->m_next;
}

/**
 * @brief
 * Get the final vertexes
 * @return const std::set<int>& final vertexes
 */
const std::set<int> &Graph::get_final() const
{
    return this->m_final;
}

/**
 * @brief
 * Get the vertexes
 * @return const std::set<int>& vertexes
 */
const std::set<int> &Graph::get_vertexes() const
{
    return this->m_vertexes;
}

/**
 * @brief
 * Get the edges
 * @return const std::map<int, std::map<char, std::set<int>>>& edges
 */
const std::map<int, std::map<char, std::set<int>>> &Graph::get_edges() const
{
    return this->m_edges;
}

// Mutator Methods
/**
 * @brief
 * Set the start vertex
 * @param start start vertex
 */
void Graph::set_start(const int &start)
{
    this->m_start = start;
}

/**
 * @brief
 * Add a final vertex
 * @param final final vertex
 */
void Graph::add_final(const int &final)
{
    this->m_final.insert(final);
}

/**
 * @brief
 * Adds a final vertex
 * @param final final vertex
 */
void Graph::add_final(const std::set<int> &final)
{
    this->m_final.insert(final.begin(), final.end());
}

// Methods (Public)
/**
 * @brief
 * Check if the graph is empty
 * @return true if the graph is empty
 * @return false if the graph is not empty
 */
bool Graph::is_empty() const
{
    auto it = this->m_edges.find(this->m_start);

    if (it != this->m_edges.end())
    {
        const std::map<char, std::set<int>> &edges_map = it->second;

        for (const auto &weight_it : edges_map)
        {
            const std::set<int> &destinations = weight_it.second;

            if (!destinations.empty())
                return false;
        }
    }

    return true;
}

/**
 * @brief
 * Checks if the value is final
 * @param value value to be checked
 * @return true if the value is final
 * @return false if the value is not final
 */
bool Graph::is_final(const int &value) const
{
    return this->m_final.count(value) > 0;
}

/**
 * @brief
 * Checks if the graph contains a specific vertex
 * @param vertex vertex to be checked
 * @return true if the graph contains the vertex
 * @return false if the graph does not contain the vertex
 */
bool Graph::contains_vertex(const int &vertex) const
{
    return this->m_vertexes.count(vertex) > 0;
}

/**
 * @brief
 * Adds an edge to the graph
 * @param from Origin vertex
 * @param value Value of the edge
 * @param to Destination vertex
 */
void Graph::add_edge(const int &from, const char &value, const int &to)
{
    this->m_vertexes.insert(from);
    this->m_vertexes.insert(to);

    auto it = this->m_edges.find(from);

    if (it != this->m_edges.end())
    {
        std::map<char, std::set<int>> &edges_map = it->second;
        auto weight_it = edges_map.find(value);

        if (weight_it != edges_map.end())
        {
            std::set<int> &destinations = weight_it->second;
            destinations.insert(to);
        }

        else
        {
            std::set<int> destinations;
            destinations.insert(to);
            edges_map.insert(std::make_pair(value, destinations));
        }
    }

    else
    {
        std::map<char, std::set<int>> edges_map;
        std::set<int> destinations;

        destinations.insert(to);
        edges_map.insert(std::make_pair(value, destinations));

        this->m_edges.insert(std::make_pair(from, edges_map));
    }
}

/**
 * @brief
 * Creates a new vertex
 * @return int new vertex
 */
int Graph::create_vertex()
{
    int vertex = this->m_next;
    this->m_next++;

    return vertex;
}

/**
 * @brief
 * Connects a graph to a vertex through an edge
 * @param graph graph to be connected
 * @param value value of the edge
 * @return std::pair<int, int> origin and destination of the edge
 */
std::pair<int, int> Graph::connect_graph_to_vertex(
    const std::shared_ptr<Graph> &graph, const int &value)
{
    int from = this->create_vertex();
    int to = graph->get_start();

    this->add_edge(from, value, to);

    for (const int &final : graph->get_final())
        this->add_final(final);

    for (const auto &it : graph->get_edges())
    {
        const std::map<char, std::set<int>> &edges_map = it.second;

        for (const auto &weight_it : edges_map)
        {
            const std::set<int> &destinations = weight_it.second;

            for (const int &destination : destinations)
                this->add_edge(it.first, weight_it.first,
                               destination);
        }
    }

    return std::make_pair(from, to);
}

/**
 * @brief
 * Prints the graph in string format
 */
std::string Graph::to_string() const
{
    std::string str = "";

    str += "Start: " + std::to_string(this->m_start) + "\n";
    str += "Final: ";

    for (const int &final : this->m_final)
        str += std::to_string(final) + " ";

    str += "\n";

    for (const auto &it : this->m_edges)
    {
        const std::map<char, std::set<int>> &edges_map = it.second;

        for (const auto &weight_it : edges_map)
        {
            const std::set<int> &destinations = weight_it.second;

            for (const int &destination : destinations)
                str += std::to_string(it.first) + " " + weight_it.first +
                       " " + std::to_string(destination) + "\n";
        }
    }

    return str;
}

/**
 * @brief
 * Handles the e closure of a vertex
 * @param vertex vertex to be handled
 * @return std::set<int> e closure of the vertex
 */
std::set<int> Graph::e_closure(const int &vertex) const
{
    std::set<int> closure;
    std::stack<int> stack;

    stack.push(vertex);

    while (!stack.empty())
    {
        int current = stack.top();
        stack.pop();

        closure.insert(current);

        auto it = this->m_edges.find(current);

        if (it != this->m_edges.end())
        {
            const std::map<char, std::set<int>> &edges_map = it->second;

            for (const auto &weight_it : edges_map)
            {
                if (weight_it.first == 'e')
                {
                    const std::set<int> &destinations = weight_it.second;

                    for (const int &destination : destinations)
                    {
                        if (closure.count(destination) == 0)
                            stack.push(destination);
                    }
                }
            }
        }
    }

    return closure;
}

/**
 * @brief
 * Handles the e closure of a set of vertexes
 * @param vertexes vertexes to be handled
 * @return std::set<int> e closure of the vertexes
 */
std::set<int> Graph::e_closure(const std::set<int> &vertexes) const
{
    std::set<int> closure;

    for (const int &vertex : vertexes)
    {
        std::set<int> vertex_closure = this->e_closure(vertex);
        closure.insert(vertex_closure.begin(), vertex_closure.end());
    }

    return closure;
}

/**
 * @brief
 * Handles the e closure of a set of vertexes
 * @param vertex vertex to be handled
 * @param vertexes vertexes to be handled
 * @return std::set<int> e closure of the vertexes
 */
std::set<int> Graph::e_closure(const int &vertex,
                               const std::set<int> &vertexes) const
{
    std::set<int> closure = this->e_closure(vertex);
    closure.insert(vertexes.begin(), vertexes.end());

    return closure;
}

// Methods (private)
/**
 * @brief
 * Adds a new vertex to the graph
 * @param vertex vertex to be added
 */
void Graph::add_vertex(const int &vertex)
{
    this->m_vertexes.insert(vertex);
}