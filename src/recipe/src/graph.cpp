/**
 * @file graph.cpp
 * @brief Graph implementation using adjacency lists for recipe dependency tracking (C++ version).
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

constexpr int MAX_GRAPH_VERTICES = 100;

// Forward declarations
struct GraphEdge;
struct GraphVertex;

// Represents an edge (directed connection)
struct GraphEdge {
    int vertex_id;
    std::string edge_label;
    std::shared_ptr<GraphEdge> next;

    GraphEdge(int id, const std::string& label)
        : vertex_id(id), edge_label(label), next(nullptr) {
    }
};

// Represents a vertex (recipe)
struct GraphVertex {
    int recipe_id;
    std::shared_ptr<GraphEdge> edges;
    bool visited;

    explicit GraphVertex(int id)
        : recipe_id(id), edges(nullptr), visited(false) {
    }
};

// Represents the graph structure
class Graph {
private:
    std::vector<std::shared_ptr<GraphVertex>> vertices;

    std::shared_ptr<GraphVertex> findVertex(int recipe_id) const {
        for (auto& v : vertices) {
            if (v->recipe_id == recipe_id) {
                return v;
            }
        }
        return nullptr;
    }

    bool dfsCycleHelper(int vertex_id, std::vector<bool>& visited, std::vector<bool>& recStack) const {
        auto vertex = findVertex(vertex_id);
        if (!vertex) return false;

        visited[vertex_id] = true;
        recStack[vertex_id] = true;

        auto edge = vertex->edges;
        while (edge) {
            int neighbor = edge->vertex_id;
            if (!visited[neighbor] && dfsCycleHelper(neighbor, visited, recStack)) {
                return true;
            }
            else if (recStack[neighbor]) {
                return true;
            }
            edge = edge->next;
        }

        recStack[vertex_id] = false;
        return false;
    }

public:
    Graph() = default;

    bool addVertex(int recipe_id) {
        if (vertices.size() >= MAX_GRAPH_VERTICES) {
            std::cerr << "WARNING: Maximum number of vertices reached!\n";
            return false;
        }

        if (findVertex(recipe_id)) return true; // Already exists

        vertices.push_back(std::make_shared<GraphVertex>(recipe_id));
        return true;
    }

    bool addEdge(int from_id, int to_id, const std::string& label) {
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

    void resetVisited() {
        for (auto& v : vertices) {
            v->visited = false;
        }
    }

    void displayDependencies(int recipe_id, int depth = 0) {
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

    bool hasCycle() const {
        std::vector<bool> visited(MAX_GRAPH_VERTICES, false);
        std::vector<bool> recStack(MAX_GRAPH_VERTICES, false);

        for (auto& v : vertices) {
            if (!visited[v->recipe_id]) {
                if (dfsCycleHelper(v->recipe_id, visited, recStack)) {
                    return true;
                }
            }
        }
        return false;
    }
};
