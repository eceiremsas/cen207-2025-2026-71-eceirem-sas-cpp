/**
 * @file graph.cpp
 * @brief Graph implementation using adjacency lists for recipe dependency tracking (C++ version).
 */

#include "graph.hpp"
#include <algorithm>
#include <vector>

// === Graph::addVertex ===
bool Graph::addVertex(int recipe_id) {
    if (vertices.size() >= MAX_GRAPH_VERTICES) {
        std::cerr << "WARNING: Maximum number of vertices reached!\n";
        return false;
    }

    if (findVertex(recipe_id)) return true; // Already exists

    vertices[vertex_count] = std::make_shared<GraphVertex>(recipe_id);
    vertex_count++;
    return true;
}

// === Graph::addEdge ===
bool Graph::addEdge(int from_id, int to_id, const std::string& label) {
    auto fromVertex = findVertex(from_id);
    if (!fromVertex) {
        std::cerr << "WARNING: Source recipe not found (ID: " << from_id << ")\n";
        return false;
    }

    if (!findVertex(to_id)) addVertex(to_id);

    auto edge = std::make_shared<GraphEdge>(to_id, label);
    edge->next = fromVertex->edges;
    fromVertex->edges = edge;

    return true;
}

// === Graph Constructor ===
Graph::Graph() : vertex_count(0) {
}

// === Graph::findVertex ===
std::shared_ptr<GraphVertex> Graph::findVertex(int recipe_id) const {
    for (int i = 0; i < vertex_count; i++) {
        if (vertices[i] && vertices[i]->recipe_id == recipe_id) {
            return vertices[i];
        }
    }
    return nullptr;
}

// === Graph::resetVisited ===
void Graph::resetVisited() {
    for (int i = 0; i < vertex_count; i++) {
        if (vertices[i]) {
            vertices[i]->visited = false;
        }
    }
}

// === Graph::displayDependencies ===
void Graph::displayDependencies(int recipe_id, int depth) {
    auto vertex = findVertex(recipe_id);
    if (!vertex) {
        std::cout << "Recipe not found (ID: " << recipe_id << ")\n";
        return;
    }

    vertex->visited = true;

    for (int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << "└─ Recipe ID: " << recipe_id << "\n";

    auto edge = vertex->edges;
    while (edge) {
        for (int i = 0; i <= depth; i++) std::cout << "  ";
        std::cout << "(" << (edge->edge_label.empty() ? "no label" : edge->edge_label) << ")\n";

        auto target = findVertex(edge->vertex_id);
        if (target && !target->visited) {
            displayDependencies(edge->vertex_id, depth + 1);
        }

        edge = edge->next;
    }
}

// === Graph::hasCycle ===
bool Graph::hasCycle() const {
    std::vector<int> visited(MAX_GRAPH_VERTICES, 0);
    std::vector<int> recStack(MAX_GRAPH_VERTICES, 0);

    for (int i = 0; i < vertex_count; i++) {
        if (vertices[i] && visited[vertices[i]->recipe_id] == 0) {
            if (dfsCycleHelper(vertices[i]->recipe_id, visited, recStack)) {
                return true;
            }
        }
    }
    return false;
}

// === Graph::dfsCycleHelper ===
bool Graph::dfsCycleHelper(int vertex_id, std::vector<int>& visited, std::vector<int>& recStack) const {
    auto vertex = findVertex(vertex_id);
    if (!vertex) return false;

    visited[vertex_id] = 1;
    recStack[vertex_id] = 1;

    auto edge = vertex->edges;
    while (edge) {
        int neighbor = edge->vertex_id;
        if (visited[neighbor] == 0 && dfsCycleHelper(neighbor, visited, recStack)) {
            return true;
        }
        else if (recStack[neighbor] == 1) {
            return true;
        }
        edge = edge->next;
    }

    recStack[vertex_id] = 0;
    return false;
}

// === Graph::clear ===
void Graph::clear() {
    for (int i = 0; i < vertex_count; i++) {
        vertices[i].reset();
    }
    vertex_count = 0;
}

// === Graph Destructor ===
Graph::~Graph() {
    clear();
}
