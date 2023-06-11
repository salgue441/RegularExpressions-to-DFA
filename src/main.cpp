/**
 * @file main.cpp
 * @author Carlos Salguero
 * @brief Main file of the program
 * @version 0.1
 * @date 2023-06-11
 *
 * @copyright Copyright (c) 2023
 *
 */

// C++ Standard Libraries
#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

// Project files
#include "./node/node.h"

// Function prototypes
std::string infix_to_postfix(const std::string &);

/**
 * @brief
 * Main function of the program
 * @param argc Number of arguments
 * @param argv Arguments
 * @return int Exit code
 */
int main(int argc, char const **argv)
{
    Node node1(1);
    Node node2(2);
    Node node3(3);

    // Add transitions
    node1.add_transition('a', std::make_shared<Node>(node2));
    node1.add_transition('b', std::make_shared<Node>(node3));

    // Test get_target_id function
    std::optional<int> targetIdA = node1.get_target_id('a');

    if (targetIdA.has_value())
        std::cout << "Target ID for transition 'a': "
                  << targetIdA.value() << std::endl;

    else
        std::cout << "Transition 'a' does not exist." << std::endl;

    std::optional<int> targetIdB = node1.get_target_id('b');
    if (targetIdB.has_value())
        std::cout << "Target ID for transition 'b': "
                  << targetIdB.value() << std::endl;

    else
        std::cout << "Transition 'b' does not exist." << std::endl;

    std::optional<int> targetIdC = node1.get_target_id('c');
    if (targetIdC.has_value())
        std::cout << "Target ID for transition 'c': "
                  << targetIdC.value() << std::endl;

    else
        std::cout << "Transition 'c' does not exist." << std::endl;
}

/**
 * @brief
 * Converts an infix regular expression to a postfix regular expression
 * @param infix Infix regular expression
 * @return std::string Postfix regular expression
 */
std::string infix_to_postfix(const std::string &infix)
{
    std::unordered_map<char, int> precedence{
        {'*', 3}, {'.', 2}, {'|', 1}, {'(', 0}};

    std::string postfix;
    std::stack<char> operators;

    for (const char &character : infix)
    {
        if (std::isalpha(character))
            postfix += character;

        else if (character == '(')
            operators.push(character);

        else if (character == ')')
        {
            while (operators.top() != '(')
            {
                postfix += operators.top();
                operators.pop();
            }

            operators.pop();
        }

        else
        {
            while (!operators.empty() &&
                   precedence[operators.top()] >= precedence[character])
            {
                postfix += operators.top();
                operators.pop();
            }

            operators.push(character);
        }
    }

    while (!operators.empty())
    {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}
