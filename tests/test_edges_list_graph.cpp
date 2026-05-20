// Copyright 2026 Ekaterina Ushnitskaya

#include <gtest/gtest.h>
#include "../lib_edges_list_graph/edges_list_graph.h"

#define EPSILON 0.000001
#define TRUE 1
#define FALSE 0

TEST(TestEdgesListGraph, default_constructor) {
    // Arrange
    EdgesListGraph<int> graph;

    // Act
    graph.add_edge(1, 2);

    // Assert
    EXPECT_NO_THROW(graph.delete_edge(1, 2));
}

TEST(TestEdgesListGraph, constructor_with_isDirected_and_isWeighted) {
    // Arrange
    EdgesListGraph<int> graph(true, true);

    // Act
    graph.add_edge(1, 2, 10);

    // Assert
    EXPECT_NO_THROW(graph.delete_edge(1, 2));
}

TEST(TestEdgesListGraph, constructor_with_TVector) {
    // Arrange
    TVector<Pair<Pair<int, int>, int>> edges;
    edges.push_back(Pair<Pair<int, int>, int>(Pair<int, int>(1, 2), 5));
    edges.push_back(Pair<Pair<int, int>, int>(Pair<int, int>(2, 3), 10));
    edges.push_back(Pair<Pair<int, int>, int>(Pair<int, int>(1, 3), 7));

    // Act
    EdgesListGraph<int> graph(edges, false, true);

    // Assert
    EXPECT_NO_THROW(graph.delete_edge(1, 2));
    EXPECT_NO_THROW(graph.delete_edge(2, 3));
    EXPECT_NO_THROW(graph.delete_edge(1, 3));
}

TEST(TestEdgesListGraph, add_edge_simple_undirected_unweighted) {
    // Arrange
    EdgesListGraph<int> graph(false, false);

    // Act
    graph.add_edge(1, 2);

    // Assert
    EXPECT_NO_THROW(graph.delete_edge(1, 2));
    graph.add_edge(1, 2);
    EXPECT_NO_THROW(graph.delete_edge(2, 1));
}

TEST(TestEdgesListGraph, add_edge_duplicate) {
    // Arrange
    EdgesListGraph<int> graph(false, true);

    // Act
    graph.add_edge(1, 2, 5);
    graph.add_edge(1, 2, 10);

    // Assert
    graph.delete_edge(1, 2);
    EXPECT_ANY_THROW(graph.delete_edge(2, 1));
}

TEST(TestEdgesListGraph, add_edge_directed_no_back_edge) {
    // Arrange
    EdgesListGraph<int> graph(true, false);

    // Act
    graph.add_edge(1, 2);

    // Assert
    EXPECT_NO_THROW(graph.delete_edge(1, 2));
    EXPECT_ANY_THROW(graph.delete_edge(2, 1));
}

TEST(TestEdgesListGraph, add_edge_loop_undirected) {
    // Arrange
    EdgesListGraph<int> graph(false, false);

    // Act
    graph.add_edge(1, 1);

    // Assert
    EXPECT_NO_THROW(graph.delete_edge(1, 1));
}

TEST(TestEdgesListGraph, add_edge_loop_directed) {
    // Arrange
    EdgesListGraph<int> graph(true, false);

    // Act
    graph.add_edge(1, 1);

    // Assert
    EXPECT_NO_THROW(graph.delete_edge(1, 1));
}

TEST(TestEdgesListGraph, add_edge_weighted_set_weight) {
    // Arrange
    EdgesListGraph<int> graph(false, true);

    // Act
    graph.add_edge(1, 2, 42);

    // Assert
    EXPECT_NO_THROW(graph.delete_edge(1, 2));
}

TEST(TestEdgesListGraph, delete_edge_existing) {
    // Arrange
    EdgesListGraph<int> graph(false, false);
    graph.add_edge(1, 2);

    // Act
    graph.delete_edge(1, 2);

    // Assert
    EXPECT_ANY_THROW(graph.delete_edge(1, 2));
}

TEST(TestEdgesListGraph, delete_edge_not_existing) {
    // Arrange
    EdgesListGraph<int> graph(false, false);
    graph.add_edge(1, 2);

    // Act & Assert
    EXPECT_ANY_THROW(graph.delete_edge(1, 3));
}

TEST(TestEdgesListGraph, delete_edge_empty_graph) {
    // Arrange
    EdgesListGraph<int> graph;

    // Act & Assert
    EXPECT_ANY_THROW(graph.delete_edge(1, 2));
}

TEST(TestEdgesListGraph, delete_edge_directed) {
    // Arrange
    EdgesListGraph<int> graph(true, false);
    graph.add_edge(1, 2);
    graph.add_edge(2, 1);

    // Act
    graph.delete_edge(1, 2);

    // Assert
    EXPECT_ANY_THROW(graph.delete_edge(1, 2));
    EXPECT_NO_THROW(graph.delete_edge(2, 1));
}

TEST(TestEdgesListGraph, delete_edge_undirected) {
    // Arrange
    EdgesListGraph<int> graph(false, false);
    graph.add_edge(1, 2);

    // Act
    graph.delete_edge(1, 2);

    // Assert
    EXPECT_ANY_THROW(graph.delete_edge(1, 2));
    EXPECT_ANY_THROW(graph.delete_edge(2, 1));
}

TEST(TestEdgesListGraph, delete_edge_after_delete_vertex) {
    // Arrange
    EdgesListGraph<int> graph(false, false);
    graph.add_edge(1, 2);

    // Act
    graph.delete_vertex(1);

    // Assert
    EXPECT_ANY_THROW(graph.delete_edge(1, 2));
    EXPECT_ANY_THROW(graph.delete_edge(2, 1));
}

TEST(TestEdgesListGraph, delete_vertex_existing_with_edges) {
    // Arrange
    EdgesListGraph<int> graph(false, false);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);
    graph.add_edge(2, 3);

    // Act
    graph.delete_vertex(1);

    // Assert
    EXPECT_ANY_THROW(graph.delete_edge(1, 2));
    EXPECT_ANY_THROW(graph.delete_edge(1, 3));
    EXPECT_NO_THROW(graph.delete_edge(2, 3));
}

TEST(TestEdgesListGraph, delete_vertex_existing_isolated) {
    // Arrange
    EdgesListGraph<int> graph(false, false);
    graph.add_edge(1, 2);

    // Act & Assert
    EXPECT_NO_THROW(graph.delete_vertex(1));
}

TEST(TestEdgesListGraph, delete_vertex_not_existing) {
    // Arrange
    EdgesListGraph<int> graph(false, false);
    graph.add_edge(1, 2);

    // Act & Assert
    EXPECT_ANY_THROW(graph.delete_vertex(3));
}

TEST(TestEdgesListGraph, delete_vertex_empty_graph) {
    // Arrange
    EdgesListGraph<int> graph;

    // Act & Assert
    EXPECT_ANY_THROW(graph.delete_vertex(1));
}

TEST(TestEdgesListGraph, delete_vertex_loop) {
    // Arrange
    EdgesListGraph<int> graph(false, false);
    graph.add_edge(1, 1);

    // Act
    graph.delete_vertex(1);

    // Assert
    EXPECT_ANY_THROW(graph.delete_edge(1, 1));
}

TEST(TestEdgesListGraph, delete_vertex_multiple_edges_same_vertex) {
    // Arrange
    EdgesListGraph<int> graph(false, false);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);
    graph.add_edge(1, 4);
    graph.add_edge(2, 3);

    // Act
    graph.delete_vertex(1);

    // Assert
    EXPECT_ANY_THROW(graph.delete_edge(1, 2));
    EXPECT_ANY_THROW(graph.delete_edge(1, 3));
    EXPECT_ANY_THROW(graph.delete_edge(1, 4));
    EXPECT_NO_THROW(graph.delete_edge(2, 3));
}

TEST(TestEdgesListGraph, delete_vertex_twice) {
    // Arrange
    EdgesListGraph<int> graph(false, false);
    graph.add_edge(1, 2);

    // Act
    graph.delete_vertex(1);

    // Assert
    EXPECT_ANY_THROW(graph.delete_vertex(1));
}

TEST(TestEdgesListGraph, print_empty_graph) {
    // Arrange
    EdgesListGraph<int> graph;

    // Act & Assert
    EXPECT_NO_THROW(graph.print());
}

TEST(TestEdgesListGraph, print_graph_with_edges) {
    // Arrange
    EdgesListGraph<int> graph(false, true);
    graph.add_edge(1, 2, 5);
    graph.add_edge(2, 3, 10);

    // Act & Assert
    EXPECT_NO_THROW(graph.print());
}

TEST(TestEdgesListGraph, works_with_string) {
    // Arrange
    EdgesListGraph<std::string> graph(false, false);

    // Act
    graph.add_edge("A", "B");
    graph.add_edge("B", "C");

    // Assert
    EXPECT_NO_THROW(graph.delete_edge("A", "B"));
    EXPECT_NO_THROW(graph.delete_edge("B", "C"));
}

TEST(TestEdgesListGraph, works_with_double) {
    // Arrange
    EdgesListGraph<double> graph(false, true);

    // Act
    graph.add_edge(1.5, 2.7, 3);
    graph.add_edge(2.7, 3.9, 5);

    // Assert
    EXPECT_NO_THROW(graph.delete_edge(1.5, 2.7));
    EXPECT_NO_THROW(graph.delete_edge(2.7, 3.9));
}

TEST(TestEdgesListGraph, unweighted_ignore_weight) {
    // Arrange
    EdgesListGraph<int> graph(false, false);

    // Act
    graph.add_edge(1, 2, 100);

    // Assert
    EXPECT_NO_THROW(graph.delete_edge(1, 2));
}

TEST(TestEdgesListGraph, weighted_not_ignore_weight) {
    // Arrange
    EdgesListGraph<int> graph(false, true);

    // Act
    graph.add_edge(1, 2, 42);

    // Assert
    EXPECT_NO_THROW(graph.add_edge(1, 2, 100));
}