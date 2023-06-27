/**
 * @file main.cpp
 * @author Carlos Salguero
 * @brief Declaration of main function
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023
 *
 */

// Google Test
#include <gtest/gtest.h>

// Tests
#include "../tests/graph.test.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}