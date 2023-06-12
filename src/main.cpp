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
#include "./nfa/nfa.h"

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
    try
    {
        std::string postfix_regex = "ab(c+)";
        NFA nfa(postfix_regex);

        std::cout << "NFA:\n";
        std::cout << "  Postfix regex: " << postfix_regex << '\n';
        std::cout << "  Accepts \"ab\": " << nfa.accepts("ab") << '\n';
        std::cout << "  Accepts \"abc\": " << nfa.accepts("abc") << '\n';
        std::cout << "  Accepts \"abcccc\": " << nfa.accepts("abcccc") << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
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
            while (!operators.empty() && operators.top() != '(')
            {
                postfix += operators.top();
                operators.pop();
            }

            if (!operators.empty())
                operators.pop();
        }

        else
        {
            while (!operators.empty() && operators.top() != '(' &&
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
