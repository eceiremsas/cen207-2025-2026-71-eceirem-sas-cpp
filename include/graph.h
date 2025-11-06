#ifndef MAX_GRAPH_VERTICES
#define MAX_GRAPH_VERTICES 100  // Maximum number of vertices allowed in the graph
#endif

#ifndef GRAPH_H  // Include guard start
#define GRAPH_H  // Define GRAPH_H macro

#include "recipe.h"  // For the Recipe data structure

// === Structure Definitions ===

// Represents an edge in the graph (e.g., "dough", "sauce" connection between recipes)
typedef struct GraphEdge {
    int vertex_id;             // Target vertex (recipe) ID
    char edge_label[50];       // Label of the edge (e.g., "dough", "sauce")
    struct GraphEdge* next;    // Pointer to the next outgoing edge from the same vertex
} GraphEdge;

// Represents a vertex in the graph
typedef struct GraphVertex {
    int recipe_id;        // The recipe ID represented by this vertex
    GraphEdge* edges;     // List of outgoing edges from this vertex
    int visited;          // Visited flag for DFS/BFS (0: not visited, 1: visited)
} GraphVertex;

// Represents the overall graph structure
typedef struct {
    GraphVertex* vertices[MAX_GRAPH_VERTICES];  // Array of vertex pointers
    int vertex_count;                           // Current number of vertices
} Graph;

// === Function Declarations ===

// Creates and initializes a new Graph object
Graph* graph_create(void);

// Adds a new vertex (recipe) to the graph
int graph_add_vertex(Graph* graph, int recipe_id);

// Adds a directed edge between two recipes with a given label
int graph_add_edge(Graph* graph, int from_recipe_id, int to_recipe_id, const char* label);

// Finds and returns a vertex pointer by its recipe ID
GraphVertex* graph_find_vertex(Graph* graph, int recipe_id);

// Recursively displays all dependencies of a recipe (for visualization)
void graph_display_dependencies(Graph* graph, int recipe_id, int depth);

// Checks if the graph contains any cycle (e.g., circular dependency between recipes)
int graph_has_cycle(Graph* graph);

// Helper function for DFS-based cycle detection
int graph_dfs_cycle_helper(Graph* graph, int vertex_id, int visited[], int rec_stack[]);

// Resets the 'visited' flag for all vertices
void graph_reset_visited(Graph* graph);

// Frees all allocated memory associated with the graph
void graph_destroy(Graph* graph);

// === Binary File Operations ===

// Saves the graph to a binary file
int graph_save_binary(const Graph* graph, const char* filename);

// Loads a graph from a binary file
Graph* graph_load_binary(const char* filename);

// === Graph Traversal Algorithms ===

// Performs Breadth-First Search (BFS) traversal
void graph_bfs(Graph* graph, int start_vertex_id, void (*visit)(int vertex_id));

// Performs Depth-First Search (DFS) traversal
void graph_dfs(Graph* graph, int start_vertex_id, void (*visit)(int vertex_id));

#endif // GRAPH_H - Include guard end
