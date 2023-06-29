/**
 * @file automata.cpp
 * @author Carlos Salguero
 * @brief Implementation of the Automata class
 * @version 0.1
 * @date 2023-06-28
 *
 * @copyright Copyright (c) 2023
 *
 */

// C++ Standard Library

// Project files
#include "automata.h"

// Constructors
/**
 * @brief
 * Construct a new Automata:: Automata object
 * @param expression Regular expression
 */
Automata::Automata(const std::string &expression)
    : m_reg_expression(expression)
{
}

// Methods (public)
/**
 * @brief
 * Builds the NFA from the regular expression
 * @return std::shared_ptr<Graph> NFA
 */
std::shared_ptr<Graph> Automata::build()
{
    TokenType last_token = TokenType::OPERATOR;

    for (const char &character : m_reg_expression)
    {
        switch (character)
        {
        case '(':
            if (last_token == TokenType::OPERAND)
                m_operators.push(CONCAT_OPERATOR);

            m_operators.push(character);
            last_token = TokenType::OPERATOR;

            break;

        case ')':
            while (!m_operators.empty())
            {
                char operator_ = m_operators.top();
                m_operators.pop();

                if (operator_ == '(')
                    break;

                apply_operator(operator_);
            }

            last_token = TokenType::OPERAND;
            break;

        case '*':
        case '+':
            apply_operator(character);
            break;

        case CONCAT_OPERATOR:
        case '|':
            m_operators.push(character);
            last_token = TokenType::OPERATOR;

            break;

        default:
            if (last_token == TokenType::OPERAND)
                m_operators.push(CONCAT_OPERATOR);

            last_token = TokenType::OPERAND;
            std::shared_ptr<Graph> graph = std::make_shared<Graph>();

            int start = graph->create_vertex();
            int end = graph->create_vertex();

            graph->set_start(start);
            graph->add_final({end});

            graph->add_edge(start, character, end);
            m_expressions.push(graph);

            if (character != EPSILON)
                m_alphabet.insert(character);

            break;
        }
    }

    while (!m_operators.empty())
    {
        char operator_ = m_operators.top();
        m_operators.pop();

        apply_operator(operator_);
    }

    m_graph = m_expressions.top();
    return std::shared_ptr<Graph>(m_graph);
}

// Methods (private)
/**
 * @brief
 * Apply the star operator to a graph. The star operator is applied to the
 * graph passed as parameter and the result is returned.
 * @param graph Graph to apply the operator
 * @return std::shared_ptr<Graph> Graph with the operator applied
 */
std::shared_ptr<Graph> Automata::star(const std::shared_ptr<Graph> &graph)
{
    int graph_start = graph->get_start();
    int graph_final = *graph->get_final().begin();

    std::shared_ptr<Graph> new_graph = std::make_shared<Graph>();
    int start = new_graph->create_vertex();
    new_graph->set_start(start);

    int next = new_graph->create_vertex();
    new_graph->add_edge(start, EPSILON, next);

    auto [new_start, new_end] = new_graph->connect_graph_to_vertex(graph, next);
    new_graph->add_edge(new_end, EPSILON, new_start);

    int end = new_graph->create_vertex();
    new_graph->add_final({end});

    new_graph->add_edge(start, EPSILON, end);
    new_graph->add_edge(new_end, EPSILON, end);

    return new_graph;
}

/**
 * @brief
 * Apply the plus operator to a graph. The plus operator is applied to the
 * graph passed as parameter and the result is returned.
 * @param graph Graph to apply the operator
 * @return std::shared_ptr<Graph> Graph with the operator applied
 */
std::shared_ptr<Graph> Automata::plus(const std::shared_ptr<Graph> &graph)
{
    int graph_start = graph->get_start();
    int graph_final = *graph->get_final().begin();

    std::shared_ptr<Graph> new_graph = std::make_shared<Graph>();
    int start = new_graph->create_vertex();
    new_graph->set_start(start);

    int next = new_graph->create_vertex();
    new_graph->add_edge(start, EPSILON, next);

    auto [new_start, new_end] = new_graph->connect_graph_to_vertex(graph, next);
    new_graph->add_edge(new_end, EPSILON, new_start);

    int end = new_graph->create_vertex();
    new_graph->add_final({end});
    new_graph->add_edge(new_end, EPSILON, end);

    return new_graph;
}

/**
 * @brief
 * Apply the concatenation operator to two graphs. The concatenation operator
 * is applied to the graphs passed as parameters and the result is returned.
 * @param left_graph First graph to concatenate
 * @param right_graph Second graph to concatenate
 * @return std::shared_ptr<Graph> Graph with the operator applied
 */
std::shared_ptr<Graph> Automata::concat(
    const std::shared_ptr<Graph> &left_graph,
    const std::shared_ptr<Graph> &right_graph)
{
    int start_left = left_graph->get_start();
    int end_left = *left_graph->get_final().begin();

    int start_right = right_graph->get_start();
    int end_right = *right_graph->get_final().begin();

    std::shared_ptr<Graph> new_graph = std::make_shared<Graph>();

    int start = new_graph->create_vertex();
    new_graph->set_start(start);

    auto [new_left_start, new_left_end] =
        new_graph->connect_graph_to_vertex(left_graph, start);

    auto [new_right_start, new_right_end] =
        new_graph->connect_graph_to_vertex(right_graph, new_left_end);

    new_graph->add_final({new_right_end});

    return new_graph;
}

/**
 * @brief
 * Applies the or operator to two graphs. The or operator is applied to the
 * graphs passed as parameters and the result is returned.
 * @param left_graph First graph to apply the operator
 * @param right_graph Second graph to apply the operator
 * @return std::shared_ptr<Graph> Graph with the operator applied
 */
std::shared_ptr<Graph> Automata::or_operator(
    const std::shared_ptr<Graph> &left_graph,
    const std::shared_ptr<Graph> &right_graph)
{
    int start_left = left_graph->get_start();
    int end_left = *left_graph->get_final().begin();

    int start_right = right_graph->get_start();
    int end_right = *right_graph->get_final().begin();

    std::shared_ptr<Graph> new_graph = std::make_shared<Graph>();
    int start = new_graph->create_vertex();
    new_graph->set_start(start);

    int next_left = new_graph->create_vertex();
    int next_right = new_graph->create_vertex();

    new_graph->add_edge(start, EPSILON, next_left);
    new_graph->add_edge(start, EPSILON, next_right);

    auto [new_left_start, new_left_end] =
        new_graph->connect_graph_to_vertex(left_graph, next_left);

    auto [new_right_start, new_right_end] =
        new_graph->connect_graph_to_vertex(right_graph, next_right);

    int end = new_graph->create_vertex();
    new_graph->add_final({end});

    new_graph->add_edge(new_left_end, EPSILON, end);
    new_graph->add_edge(new_right_end, EPSILON, end);

    return new_graph;
}

/**
 * @brief
 * Applies an operator to the expression.
 * @param operator Operator to apply
 */
void Automata::apply_operator(const char &operator_)
{
    if (operator_ == '*')
    {
        std::shared_ptr<Graph> graph = m_expressions.top();
        m_expressions.pop();

        std::shared_ptr<Graph> new_graph = star(graph);
        m_expressions.push(new_graph);
    }

    else if (operator_ == '+')
    {
        std::shared_ptr<Graph> graph = m_expressions.top();
        m_expressions.pop();

        std::shared_ptr<Graph> new_graph = plus(graph);
        m_expressions.push(new_graph);
    }

    else if (operator_ == CONCAT_OPERATOR)
    {
        std::shared_ptr<Graph> right_graph = m_expressions.top();
        m_expressions.pop();

        std::shared_ptr<Graph> left_graph = m_expressions.top();
        m_expressions.pop();

        std::shared_ptr<Graph> new_graph = concat(left_graph, right_graph);
        m_expressions.push(new_graph);
    }

    else if (operator_ == '|')
    {
        std::shared_ptr<Graph> right_graph = m_expressions.top();
        m_expressions.pop();

        std::shared_ptr<Graph> left_graph = m_expressions.top();
        m_expressions.pop();

        std::shared_ptr<Graph> new_graph = or_operator(left_graph, right_graph);
        m_expressions.push(new_graph);
    }
}