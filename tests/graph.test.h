/**
 * @file graph.test.h
 * @author Carlos Salguero
 * @brief Tests for Graph class
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef GRAPH_TEST_H
#define GRAPH_TEST_H

// Google Test
#include <gtest/gtest.h>

// Project file
#include "../src/Graph/graph.h"

// Test class
/**
 * @class GraphTest
 * @brief Tests for Graph class
 * @extends ::testing::Test
 */
class GraphTest : public ::testing::Test
{
protected:
    Graph graph;
    int v1, v2, v3;

    // Methods
    void SetUp() override;
};

#endif //! GRAPH_TEST_H