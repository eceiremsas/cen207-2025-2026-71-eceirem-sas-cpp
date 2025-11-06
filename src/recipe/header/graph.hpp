/**
 * @file graph.hpp
 * @brief Graph implementation for recipe dependency tracking (C++ version)
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <array>
#include <algorithm>

#include "recipe.hpp"  // Include Recipe class definition

constexpr int MAX_GRAPH_VERTICES = 100;  // Maximum number of vertices allowed in the graph

// ============================================================
//  Forward Declarations
// ============================================================
class GraphEdge;
class GraphVertex;

// ============================================================
//  Class: GraphEdge
// ============================================================
class GraphEdge {
public:
    int vertex_id;                      ///< Target vertex (recipe) ID
    std::string edge_label;             ///< Label of the edge (e.g., "dough", "sauce")
    std::shared_ptr<GraphEdge> next;    ///< Pointer to next outgoing edge

    GraphEdge(int id, const std::string& label)
        : vertex_id(id), edge_label(label), next(nullptr) {}
};

// ============================================================
//  Class: GraphVertex
// ============================================================
class GraphVertex {
public:
    int recipe_id;                      ///< Recipe ID represented by this vertex
    std::shared_ptr<GraphEdge> edges;   ///< Linked list of outgoing edges
    bool visited;                       ///< Visited flag for DFS/BFS

    explicit GraphVertex(int id)
        : recipe_id(id), edges(nullptr), visited(false) {}
};

// ============================================================
//  Class: Graph
// ============================================================
class Graph {
private:
    std::array<std::shared_ptr<GraphVertex>, MAX_GRAPH_VERTICES> vertices;
    int vertex_count;

    // Helper for cycle detection (DFS)
    bool dfsCycleHelper(int vertex_id, std::vector<int>& visited, std::vector<int>& rec_stack) const;

public:
    Graph();

    // === Vertex Operations ===
    bool addVertex(int recipe_id);
    std::shared_ptr<GraphVertex> findVertex(int recipe_id) const;

    // === Edge Operations ===
    bool addEdge(int from_recipe_id, int to_recipe_id, const std::string& label);

    // === Display Operations ===
    void displayDependencies(int recipe_id, int depth = 0);

    // === Utility ===
    void resetVisited();
    bool hasCycle() const;

    // === Getters ===
    int getVertexCount() const { return vertex_count; }

    // === Destructor ===
    void clear();
    ~Graph();
};

#endif // GRAPH_HPP
