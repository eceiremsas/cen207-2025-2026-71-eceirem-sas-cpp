/**
 * @file graph.c
 * @brief Graph implementation with adjacency lists for recipe dependency tracking
 * @details Supports BFS/DFS traversal and cycle detection
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// Queue structure for BFS
typedef struct {
    int items[MAX_GRAPH_VERTICES];
    int front;
    int rear;
} BFSQueue;

static BFSQueue* bfs_queue_create(void) {
    BFSQueue* q = (BFSQueue*)malloc(sizeof(BFSQueue));
    if (!q) return NULL;
    q->front = -1;
    q->rear = -1;
    return q;
}

static void bfs_queue_enqueue(BFSQueue* q, int value) {
    if (q->rear == MAX_GRAPH_VERTICES - 1) return;
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

static int bfs_queue_dequeue(BFSQueue* q) {
    if (q->front == -1) return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

static int bfs_queue_is_empty(BFSQueue* q) {
    return q->front == -1;
}

/**
 * @brief Creates and initializes a new Graph object
 * @return Pointer to the created graph, or NULL on failure
 */
Graph* graph_create(void) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (!graph) {
        return NULL;
    }

    graph->vertex_count = 0;
    for (int i = 0; i < MAX_GRAPH_VERTICES; i++) {
        graph->vertices[i] = NULL;
    }

    return graph;
}

/**
 * @brief Finds and returns a vertex pointer by its recipe ID
 * @param graph Pointer to the graph
 * @param recipe_id Recipe ID to find
 * @return Pointer to the vertex, or NULL if not found
 */
GraphVertex* graph_find_vertex(Graph* graph, int recipe_id) {
    if (!graph) {
        return NULL;
    }

    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->vertices[i] && graph->vertices[i]->recipe_id == recipe_id) {
            return graph->vertices[i];
        }
    }

    return NULL;
}

/**
 * @brief Adds a new vertex (recipe) to the graph
 * @param graph Pointer to the graph
 * @param recipe_id Recipe ID
 * @return 1 on success, 0 on failure
 */
int graph_add_vertex(Graph* graph, int recipe_id) {
    if (!graph) {
        return 0;
    }

    if (graph_find_vertex(graph, recipe_id)) {
        return 1; // Already exists
    }

    if (graph->vertex_count >= MAX_GRAPH_VERTICES) {
        return 0;
    }

    GraphVertex* vertex = (GraphVertex*)malloc(sizeof(GraphVertex));
    if (!vertex) {
        return 0;
    }

    vertex->recipe_id = recipe_id;
    vertex->edges = NULL;
    vertex->visited = 0;

    graph->vertices[graph->vertex_count] = vertex;
    graph->vertex_count++;

    return 1;
}

/**
 * @brief Adds a directed edge between two recipes with a given label
 * @param graph Pointer to the graph
 * @param from_recipe_id Source recipe ID
 * @param to_recipe_id Target recipe ID
 * @param label Edge label
 * @return 1 on success, 0 on failure
 */
int graph_add_edge(Graph* graph, int from_recipe_id, int to_recipe_id, const char* label) {
    if (!graph || !label) {
        return 0;
    }

    GraphVertex* from_vertex = graph_find_vertex(graph, from_recipe_id);
    if (!from_vertex) {
        graph_add_vertex(graph, from_recipe_id);
        from_vertex = graph_find_vertex(graph, from_recipe_id);
    }

    if (!graph_find_vertex(graph, to_recipe_id)) {
        graph_add_vertex(graph, to_recipe_id);
    }

    GraphEdge* new_edge = (GraphEdge*)malloc(sizeof(GraphEdge));
    if (!new_edge) {
        return 0;
    }

    new_edge->vertex_id = to_recipe_id;
    strncpy(new_edge->edge_label, label, 49);
    new_edge->edge_label[49] = '\0';
    new_edge->next = from_vertex->edges;
    from_vertex->edges = new_edge;

    return 1;
}

/**
 * @brief Resets the 'visited' flag for all vertices
 * @param graph Pointer to the graph
 */
void graph_reset_visited(Graph* graph) {
    if (!graph) {
        return;
    }

    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->vertices[i]) {
            graph->vertices[i]->visited = 0;
        }
    }
}

/**
 * @brief Helper function for DFS-based cycle detection
 * @param graph Pointer to the graph
 * @param vertex_id Current vertex ID
 * @param visited Visited array
 * @param rec_stack Recursion stack array
 * @return 1 if cycle found, 0 otherwise
 */
int graph_dfs_cycle_helper(Graph* graph, int vertex_id, int visited[], int rec_stack[]) {
    GraphVertex* vertex = graph_find_vertex(graph, vertex_id);
    if (!vertex) {
        return 0;
    }

    visited[vertex_id] = 1;
    rec_stack[vertex_id] = 1;

    GraphEdge* edge = vertex->edges;
    while (edge) {
        int neighbor = edge->vertex_id;
        if (!visited[neighbor] && graph_dfs_cycle_helper(graph, neighbor, visited, rec_stack)) {
            return 1;
        } else if (rec_stack[neighbor]) {
            return 1;
        }
        edge = edge->next;
    }

    rec_stack[vertex_id] = 0;
    return 0;
}

/**
 * @brief Checks if the graph contains any cycle
 * @param graph Pointer to the graph
 * @return 1 if cycle found, 0 otherwise
 */
int graph_has_cycle(Graph* graph) {
    if (!graph) {
        return 0;
    }

    int visited[MAX_GRAPH_VERTICES] = {0};
    int rec_stack[MAX_GRAPH_VERTICES] = {0};

    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->vertices[i] && !visited[graph->vertices[i]->recipe_id]) {
            if (graph_dfs_cycle_helper(graph, graph->vertices[i]->recipe_id, visited, rec_stack)) {
                return 1;
            }
        }
    }

    return 0;
}

/**
 * @brief Recursively displays all dependencies of a recipe
 * @param graph Pointer to the graph
 * @param recipe_id Recipe ID to display
 * @param depth Current depth level
 */
void graph_display_dependencies(Graph* graph, int recipe_id, int depth) {
    if (!graph) {
        return;
    }

    GraphVertex* vertex = graph_find_vertex(graph, recipe_id);
    if (!vertex) {
        printf("Recipe not found (ID: %d)\n", recipe_id);
        return;
    }

    vertex->visited = 1;

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("└─ Recipe ID: %d\n", recipe_id);

    GraphEdge* edge = vertex->edges;
    while (edge) {
        for (int i = 0; i <= depth; i++) {
            printf("  ");
        }
        printf("(%s)\n", edge->edge_label);

        GraphVertex* target = graph_find_vertex(graph, edge->vertex_id);
        if (target && !target->visited) {
            graph_display_dependencies(graph, edge->vertex_id, depth + 1);
        }

        edge = edge->next;
    }
}

/**
 * @brief Performs Breadth-First Search (BFS) traversal
 * @param graph Pointer to the graph
 * @param start_vertex_id Starting vertex ID
 * @param visit Function pointer to call for each visited vertex
 */
void graph_bfs(Graph* graph, int start_vertex_id, void (*visit)(int vertex_id)) {
    if (!graph || !visit) {
        return;
    }

    graph_reset_visited(graph);
    BFSQueue* queue = bfs_queue_create();
    if (!queue) {
        return;
    }

    GraphVertex* start = graph_find_vertex(graph, start_vertex_id);
    if (!start) {
        free(queue);
        return;
    }

    start->visited = 1;
    bfs_queue_enqueue(queue, start_vertex_id);
    visit(start_vertex_id);

    while (!bfs_queue_is_empty(queue)) {
        int current_id = bfs_queue_dequeue(queue);
        GraphVertex* current = graph_find_vertex(graph, current_id);
        if (!current) continue;

        GraphEdge* edge = current->edges;
        while (edge) {
            GraphVertex* neighbor = graph_find_vertex(graph, edge->vertex_id);
            if (neighbor && !neighbor->visited) {
                neighbor->visited = 1;
                bfs_queue_enqueue(queue, edge->vertex_id);
                visit(edge->vertex_id);
            }
            edge = edge->next;
        }
    }

    free(queue);
}

/**
 * @brief Helper function for DFS recursive traversal
 */
static void graph_dfs_helper(Graph* graph, int vertex_id, void (*visit)(int vertex_id)) {
    GraphVertex* vertex = graph_find_vertex(graph, vertex_id);
    if (!vertex || vertex->visited) {
        return;
    }

    vertex->visited = 1;
    visit(vertex_id);

    GraphEdge* edge = vertex->edges;
    while (edge) {
        graph_dfs_helper(graph, edge->vertex_id, visit);
        edge = edge->next;
    }
}

/**
 * @brief Performs Depth-First Search (DFS) traversal
 * @param graph Pointer to the graph
 * @param start_vertex_id Starting vertex ID
 * @param visit Function pointer to call for each visited vertex
 */
void graph_dfs(Graph* graph, int start_vertex_id, void (*visit)(int vertex_id)) {
    if (!graph || !visit) {
        return;
    }

    graph_reset_visited(graph);
    graph_dfs_helper(graph, start_vertex_id, visit);
}

/**
 * @brief Frees all allocated memory associated with the graph
 * @param graph Pointer to the graph
 */
void graph_destroy(Graph* graph) {
    if (!graph) {
        return;
    }

    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->vertices[i]) {
            GraphEdge* edge = graph->vertices[i]->edges;
            while (edge) {
                GraphEdge* next = edge->next;
                free(edge);
                edge = next;
            }
            free(graph->vertices[i]);
        }
    }

    free(graph);
}

/**
 * @brief Saves the graph to a binary file
 * @param graph Pointer to the graph
 * @param filename Name of the binary file
 * @return 1 on success, 0 on failure
 */
int graph_save_binary(const Graph* graph, const char* filename) {
    if (!graph || !filename) {
        return 0;
    }

    FILE* file = fopen(filename, "wb");
    if (!file) {
        return 0;
    }

    if (fwrite(&graph->vertex_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }

    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->vertices[i]) {
            if (fwrite(&graph->vertices[i]->recipe_id, sizeof(int), 1, file) != 1) {
                fclose(file);
                return 0;
            }

            // Count edges
            int edge_count = 0;
            GraphEdge* edge = graph->vertices[i]->edges;
            while (edge) {
                edge_count++;
                edge = edge->next;
            }

            if (fwrite(&edge_count, sizeof(int), 1, file) != 1) {
                fclose(file);
                return 0;
            }

            edge = graph->vertices[i]->edges;
            while (edge) {
                if (fwrite(&edge->vertex_id, sizeof(int), 1, file) != 1) {
                    fclose(file);
                    return 0;
                }
                if (fwrite(edge->edge_label, sizeof(char), 50, file) != 50) {
                    fclose(file);
                    return 0;
                }
                edge = edge->next;
            }
        }
    }

    fclose(file);
    return 1;
}

/**
 * @brief Loads a graph from a binary file
 * @param filename Name of the binary file
 * @return Pointer to the loaded graph, or NULL on failure
 */
Graph* graph_load_binary(const char* filename) {
    if (!filename) {
        return NULL;
    }

    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    Graph* graph = graph_create();
    if (!graph) {
        fclose(file);
        return NULL;
    }

    int vertex_count;
    if (fread(&vertex_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        graph_destroy(graph);
        return NULL;
    }

    for (int i = 0; i < vertex_count; i++) {
        int recipe_id;
        if (fread(&recipe_id, sizeof(int), 1, file) != 1) {
            break;
        }

        graph_add_vertex(graph, recipe_id);

        int edge_count;
        if (fread(&edge_count, sizeof(int), 1, file) != 1) {
            break;
        }

        for (int j = 0; j < edge_count; j++) {
            int to_id;
            char label[50];
            if (fread(&to_id, sizeof(int), 1, file) != 1) {
                break;
            }
            if (fread(label, sizeof(char), 50, file) != 50) {
                break;
            }
            graph_add_edge(graph, recipe_id, to_id, label);
        }
    }

    fclose(file);
    return graph;
}

