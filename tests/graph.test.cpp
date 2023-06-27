/**
 * @file graph.test.cpp
 * @author Carlos Salguero
 * @brief Implementation of GraphTest class
 * @version 0.1
 * @date 2023-06-26
 *
 * @copyright Copyright (c) 2023
 *
 */

// Project file
#include "graph.test.h"

// Methods
/**
 * @brief
 * Set up the test fixture
 */
void GraphTest::SetUp()
{
    graph = Graph();

    // Creating vertexes
    v1 = graph.create_vertex();
    v2 = graph.create_vertex();
    v3 = graph.create_vertex();

    // Set start vertex
    graph.set_start(v1);

    // Add edges
    graph.add_edge(v1, 'A', v2);
    graph.add_edge(v2, 'B', v3);
    graph.add_edge(v3, 'C', v1);
}

// Tests
// Test is_empty() on an empty graph
TEST_F(GraphTest, IsEmptyOnEmptyGraph)
{
    Graph emptyGraph;
    EXPECT_TRUE(emptyGraph.is_empty());
}

// Test is_empty() on a non-empty graph
TEST_F(GraphTest, IsEmptyOnNonEmptyGraph)
{
    EXPECT_FALSE(graph.is_empty());
}

// Test get_vertexes()
TEST_F(GraphTest, GetVertexes)
{
    const std::set<int> &vertexes = graph.get_vertexes();
    EXPECT_EQ(vertexes.size(), 3);
    EXPECT_TRUE(vertexes.count(v1) > 0);
    EXPECT_TRUE(vertexes.count(v2) > 0);
    EXPECT_TRUE(vertexes.count(v3) > 0);
}

// Test get_weight()
TEST_F(GraphTest, GetWeight)
{
    std::optional<char> weightAB = graph.get_weight(v1, v2);
    EXPECT_TRUE(weightAB.has_value());
    EXPECT_EQ(*weightAB, 'A');

    std::optional<char> weightBC = graph.get_weight(v2, v3);
    EXPECT_TRUE(weightBC.has_value());
    EXPECT_EQ(*weightBC, 'B');

    std::optional<char> weightCA = graph.get_weight(v3, v1);
    EXPECT_TRUE(weightCA.has_value());
    EXPECT_EQ(*weightCA, 'C');

    std::optional<char> weightAC = graph.get_weight(v1, v3);
    EXPECT_FALSE(weightAC.has_value());
}

// Test is_final()
TEST_F(GraphTest, IsFinal)
{
    graph.add_final(v1);
    graph.add_final(v3);

    EXPECT_TRUE(graph.is_final(v1));
    EXPECT_FALSE(graph.is_final(v2));
    EXPECT_TRUE(graph.is_final(v3));
}

// Test contains_vertex()
TEST_F(GraphTest, ContainsVertex)
{
    EXPECT_TRUE(graph.contains_vertex(v1));
    EXPECT_TRUE(graph.contains_vertex(v2));
    EXPECT_TRUE(graph.contains_vertex(v3));
    EXPECT_FALSE(graph.contains_vertex(4));
}