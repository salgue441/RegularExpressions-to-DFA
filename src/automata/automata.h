/**
 * @file automata.h
 * @author Carlos Salguero
 * @brief Declaration of the Automata class
 * @version 0.1
 * @date 2023-06-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef AUTOMATA_H
#define AUTOMATA_H

// C++ Standard Library
#include <string>
#include <stack>
#include <memory>

// Project files
#include "../Graph/graph.h"

// Constants
constexpr char CONCAT_OPERATOR = '.';

// Class
/**
 * @class Automata
 * @brief Class that represents an NFA or DFA
 */
class Automata
{
public:
    // Constructors
    Automata() = default;
    Automata(const std::string &expression);

    // Destructor
    ~Automata() = default;

    // Methods
    std::shared_ptr<Graph> build();
    std::shared_ptr<Graph> transform_dfa();

private:
    std::set<char> m_alphabet;
    std::stack<std::shared_ptr<Graph>> m_expressions;
    std::stack<char> m_operators;
    std::string m_reg_expression;
    std::shared_ptr<Graph> m_graph;

    // Methods
    std::shared_ptr<Graph> star(const std::shared_ptr<Graph> &);
    std::shared_ptr<Graph> plus(const std::shared_ptr<Graph> &);
    std::shared_ptr<Graph> concat(const std::shared_ptr<Graph> &,
                                  const std::shared_ptr<Graph> &);
    std::shared_ptr<Graph> or_operator(const std::shared_ptr<Graph> &,
                                       const std::shared_ptr<Graph> &);

    void apply_operator(const char &);

    // Enums
    enum class TokenType
    {
        OPERATOR,
        OPERAND
    };
};

#endif //! AUTOMATA_H