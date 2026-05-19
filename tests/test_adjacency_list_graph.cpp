// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_adjacency_list_graph/adjacency_list_graph.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestAdjacencyListGraph, default_constructor_directed_unweighted) {
    // Arrange & Act
    AdjacencyListGraph<int> graph(true, false);

    // Assert
    EXPECT_EQ(0, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, default_constructor_undirected_weighted) {
    // Arrange & Act
    AdjacencyListGraph<int> graph(false, true);

    // Assert
    EXPECT_EQ(0, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, constructor_edges_unweighted) {
    // Arrange & Act
    TVector<Pair<Pair<int, int>, int>> edges;
    edges.push_back(Pair<Pair<int, int>, int>(Pair<int, int>(0, 1), 1));
    edges.push_back(Pair<Pair<int, int>, int>(Pair<int, int>(1, 2), 1));
    edges.push_back(Pair<Pair<int, int>, int>(Pair<int, int>(2, 0), 1));
    AdjacencyListGraph<int> graph(edges, false, false);

    // Assert
    EXPECT_EQ(3, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, constructor_edges_weighted) {
    // Arrange & Act
    TVector<Pair<Pair<int, int>, int>> edges;
    edges.push_back(Pair<Pair<int, int>, int>(Pair<int, int>(0, 1), 5));
    edges.push_back(Pair<Pair<int, int>, int>(Pair<int, int>(1, 2), 10));
    edges.push_back(Pair<Pair<int, int>, int>(Pair<int, int>(2, 0), 15));
    AdjacencyListGraph<int> graph(edges, true, true);

    // Assert
    EXPECT_EQ(3, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, constructor_from_edges_undirected) {
    // Arrange & Act
    TVector<Pair<Pair<int, int>, int>> edges;
    edges.push_back(Pair<Pair<int, int>, int>(Pair<int, int>(0, 1), 1));
    edges.push_back(Pair<Pair<int, int>, int>(Pair<int, int>(1, 2), 1));
    AdjacencyListGraph<int> graph(edges, false, false);

    // Assert
    EXPECT_EQ(3, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, add_edge_directed_unweighted) {
    // Arrange
    AdjacencyListGraph<int> graph(true, false);

    // Act
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);

    // Assert
    EXPECT_EQ(3, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, add_edge_undirected) {
    // Arrange
    AdjacencyListGraph<int> graph(false, false);

    // Act
    graph.add_edge(0, 1);

    // Assert
    EXPECT_EQ(2, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, add_edge_one_vertex_undirected) {
    // Arrange
    AdjacencyListGraph<int> graph(false, false);

    // Act
    graph.add_edge(0, 0);

    // Assert
    EXPECT_EQ(1, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, add_edge_vertex_directed) {
    // Arrange
    AdjacencyListGraph<int> graph(true, false);

    // Act
    graph.add_edge(0, 0);

    // Assert
    EXPECT_EQ(1, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, add_edge_update_weight_weighted) {
    // Arrange
    AdjacencyListGraph<int> graph(true, true);

    // Act
    graph.add_edge(0, 1, 5);
    graph.add_edge(0, 1, 10);

    // Assert
    EXPECT_EQ(2, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, add_edge_ignore_weight_if_unweighted) {
    // Arrange
    AdjacencyListGraph<int> graph(true, false);

    // Act
    graph.add_edge(0, 1, 100);
    graph.add_edge(0, 2, 200);

    // Assert
    EXPECT_EQ(3, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, add_edge_reweight) {
    // Arrange
    AdjacencyListGraph<int> graph(true, true);

    // Act
    graph.add_edge(0, 1, 5);
    graph.add_edge(0, 1, 10);

    // Assert
    EXPECT_EQ(2, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, add_edge_after_delete_vertex) {
    // Arrange
    AdjacencyListGraph<int> graph(false, false);

    // Act
    graph.add_edge(0, 1);
    graph.delete_vertex(0);
    graph.add_edge(0, 2);

    // Assert
    EXPECT_EQ(3, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, delete_edge_directed) {
    // Arrange
    AdjacencyListGraph<int> graph(true, false);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);

    // Act
    graph.delete_edge(0, 1);

    // Assert
    EXPECT_EQ(3, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, delete_edge_undirected) {
    // Arrange
    AdjacencyListGraph<int> graph(false, false);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);

    // Act
    graph.delete_edge(0, 1);

    // Assert
    EXPECT_EQ(3, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, delete_edge_nonexistent_throws) {
    // Arrange
    AdjacencyListGraph<int> graph(true, false);
    graph.add_edge(0, 1);

    // Act & Assert
    EXPECT_ANY_THROW(graph.delete_edge(0, 2));
    EXPECT_ANY_THROW(graph.delete_edge(1, 0));
}

TEST(TestAdjacencyListGraph, delete_edge_which_add) {
    // Arrange
    AdjacencyListGraph<int> graph(false, false);
    graph.add_edge(0, 0);

    // Act
    graph.delete_edge(0, 0);

    // Assert
    EXPECT_EQ(1, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, delete_vertex_simple) {
    // Arrange
    AdjacencyListGraph<int> graph(false, false);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);

    // Act
    graph.delete_vertex(1);

    // Assert
    EXPECT_EQ(2, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, delete_vertex_with_edges) {
    // Arrange
    AdjacencyListGraph<int> graph(false, false);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(0, 3);
    graph.add_edge(1, 2);

    // Act
    graph.delete_vertex(0);

    // Assert
    EXPECT_EQ(3, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, delete_vertex_with_throws) {
    // Arrange
    AdjacencyListGraph<int> graph(false, false);
    graph.add_edge(0, 1);

    // Act & Assert
    EXPECT_ANY_THROW(graph.delete_vertex(5));
}

TEST(TestAdjacencyListGraph, delete_all_vertices) {
    // Arrange
    AdjacencyListGraph<int> graph(false, false);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    // Act
    graph.delete_vertex(0);
    graph.delete_vertex(1);
    graph.delete_vertex(2);

    // Assert
    EXPECT_EQ(0, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, delete_edge_after_delete_vertex) {
    // Arrange
    AdjacencyListGraph<int> graph(false, false);

    // Act
    graph.add_edge(0, 1);
    graph.delete_vertex(0);

    // Assert
    EXPECT_ANY_THROW(graph.delete_edge(0, 1));
}

TEST(TestAdjacencyListGraph, count_vertex_empty) {
    // Arrange & Act
    AdjacencyListGraph<int> graph;

    // Assert
    EXPECT_EQ(0, graph.count_vertex());
}

TEST(TestAdjacencyListGraph, count_vertex_after_a_lot_of_operations) {
    // Arrange & Act & Assert
    AdjacencyListGraph<int> graph(false, false);

    graph.add_edge(0, 1);
    EXPECT_EQ(2, graph.count_vertex());

    graph.add_edge(2, 3);
    EXPECT_EQ(4, graph.count_vertex());

    graph.add_edge(1, 2);
    EXPECT_EQ(4, graph.count_vertex());

    graph.delete_vertex(1);
    EXPECT_EQ(3, graph.count_vertex());

    graph.delete_edge(2, 3);
    EXPECT_EQ(3, graph.count_vertex());
}