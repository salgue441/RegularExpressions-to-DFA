/**
 * @file main.cpp
 * @author Carlos Salguero
 * @author Diego Sandoval
 * @brief Main file of the program
 * @version 0.1
 * @date 2023-05-26
 *
 * @copyright Copyright (c) 2023
 *
 */

// C++ Standard Libraries
#include <iostream>
#include <fstream>
#include <memory>

// Project files

// Main file
int main(const int argc, char const **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0]
                  << " input file with regex expression" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream input_file(argv[1], std::ios::in | std::ios::binary);
}
