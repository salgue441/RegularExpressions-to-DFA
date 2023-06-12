/**
 * @file graph.cpp
 * @author Carlos Salguero
 * @brief Implementation of the graph class
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */

// Project files
#include "graph.h"

// Access Methods
/**
 * @brief
 * Get the nodes object
 * @return const std::unordered_map<int, std::shared_ptr<Node>>&
 *         Nodes in the graph
 */
const std::unordered_map<int, std::shared_ptr<Node>> &Graph::get_nodes() const
{
    if (m_nodes.empty())
        throw std::runtime_error("The graph is empty");

    return m_nodes;
}

// Mutators
/**
 * @brief
 * Add a transition to the graph
 * @param from Node's ID where the transition starts
 * @param symbol Symbol that triggers the transition
 * @param to Node's ID where the transition ends
 */
void Graph::add_transition(const int &from, const char &symbol, const int &to)
{
    if (m_nodes.find(from) == m_nodes.end())
        throw std::runtime_error(
            "The node " + std::to_string(from) + " does not exist");

    if (m_nodes.find(to) == m_nodes.end())
        throw std::runtime_error(
            "The node " + std::to_string(to) + " does not exist");

    m_nodes[from]->add_transition(symbol, m_nodes[to]);
}

/**
 * @brief
 * Set the nodes object
 * @param nodes Nodes to be added
 */
void Graph::set_nodes(
    const std::unordered_map<int, std::shared_ptr<Node>> &nodes)
{
    if (nodes.empty())
        throw std::runtime_error("The nodes are empty");

    m_nodes = nodes;
}

/**
 * @brief
 * Set the nodes object
 * @param id Node's ID
 * @param node Node to be added
 */
void Graph::set_nodes(const int &id, const std::shared_ptr<Node> &node)
{
    if (m_nodes.find(id) == m_nodes.end())
        throw std::runtime_error(
            "The node " + std::to_string(id) + " does not exist");

    m_nodes[id] = node;
}

// Methods
/**
 * @brief
 * Check if a node is final
 * @param id Node's ID
 * @return true If the node is final
 * @return false If the node is not final
 */
bool Graph::is_final(const int &id) const
{
    if (m_nodes.find(id) == m_nodes.end())
        throw std::runtime_error(
            "The node " + std::to_string(id) + " does not exist");

    return m_nodes.at(id)->is_final();
}

/**
 * @brief
 * Get a node from the graph
 * @param id Node's ID
 * @return const std::shared_ptr<Node> Target node from the graph
 */
const std::shared_ptr<Node> Graph::get_node(const int &id) const
{
    if (m_nodes.find(id) == m_nodes.end())
        throw std::runtime_error(
            "The node " + std::to_string(id) + " does not exist");

    return m_nodes.at(id);
}

/**
 * @brief
 * Gets the final node of the graph
 * @return const std::shared_ptr<Node> Final node of the graph
 */
const std::shared_ptr<Node> Graph::get_final_node() const
{
    for (const auto &node : m_nodes)
        if (node.second->is_final())
            return node.second;

    throw std::runtime_error("The graph does not have a final node");
}

/**
 * @brief
 * Sets the final node of the graph
 * @param id Node's ID
 */
void Graph::set_final_node(const int &id)
{
    if (m_nodes.find(id) == m_nodes.end())
        throw std::runtime_error(
            "The node " + std::to_string(id) + " does not exist");

    m_nodes.at(id)->set_final(true);
}

/**
 * @brief
 * Sets the final node of the graph
 * @param node Node to be set as final
 */
void Graph::set_final_node(const std::shared_ptr<Node> &node)
{
    if (m_nodes.find(node->get_id()) == m_nodes.end())
        throw std::runtime_error(
            "The node " + std::to_string(node->get_id()) + " does not exist");

    m_nodes.at(node->get_id())->set_final(true);
}

/**
 * @brief
 * Create a node in the graph
 * @param is_final Indicates if the node is final
 * @return std::shared_ptr<Node> Created node
 */
std::shared_ptr<Node> Graph::create_node(const bool &is_final)
{
    auto node = std::make_shared<Node>(m_next_id, is_final);
    m_nodes[m_next_id] = node;
    m_next_id++;

    return node;
}

/**
 * @brief
 * Create a node in the graph
 * @param id Node's ID
 * @param is_final Indicates if the node is final
 * @return std::shared_ptr<Node> Created node
 */
std::shared_ptr<Node> Graph::create_node(const int &id, bool is_final)
{
    if (m_nodes.find(id) != m_nodes.end())
        throw std::runtime_error(
            "The node " + std::to_string(id) + " already exists");

    auto node = std::make_shared<Node>(id, is_final);
    m_nodes[id] = node;

    if (id >= m_next_id)
        m_next_id = id + 1;

    return node;
}

/**
 * @brief
 * Merges two graphs
 * @param first_graph First graph to be merged
 * @param second_graph Second graph to be merged
 */
void Graph::merge_graphs(const std::shared_ptr<Graph> &first_graph, const std::shared_ptr<Graph> &second_graph)
{
    if (first_graph->m_nodes.empty())
        throw std::runtime_error("The first graph is empty");

    if (second_graph->m_nodes.empty())
        throw std::runtime_error("The second graph is empty");

    for (const auto &node : first_graph->m_nodes)
        m_nodes[node.first] = node.second;

    for (const auto &node : second_graph->m_nodes)
        m_nodes[node.first] = node.second;
}