
#ifndef MAX_GRAPH_VERTICES
#define MAX_GRAPH_VERTICES 100  // Graf için maksimum düğüm sayısı
#endif

#ifndef GRAPH_H  // Include guard başlangıcı
#define GRAPH_H  // GRAPH_H makrosunu tanımla

#include "recipe.h"  // Recipe veri yapısı için


typedef struct GraphEdge {
    int vertex_id;             // Hedef vertex (tarif) ID'si
    char edge_label[50];       // Kenar etiketi (örn: "hamur", "sos")
    struct GraphEdge* next;    // Aynı vertex'ten çıkan bir sonraki kenar
} GraphEdge;

typedef struct GraphVertex {
    int recipe_id;        // Bu vertex'in temsil ettiği tarif ID'si
    GraphEdge* edges;     // Bu vertex'ten çıkan kenarların listesi
    int visited;          // DFS/BFS için ziyaret edilme durumu (0: ziyaret edilmedi, 1: ziyaret edildi)
} GraphVertex;

typedef struct {
    GraphVertex* vertices[MAX_GRAPH_VERTICES];  // Vertex dizisi
    int vertex_count;                            // Mevcut vertex sayısı
} Graph;

Graph* graph_create(void);


int graph_add_vertex(Graph* graph, int recipe_id);

int graph_add_edge(Graph* graph, int from_recipe_id, int to_recipe_id, const char* label);

GraphVertex* graph_find_vertex(Graph* graph, int recipe_id);

void graph_display_dependencies(Graph* graph, int recipe_id, int depth);

int graph_has_cycle(Graph* graph);

int graph_dfs_cycle_helper(Graph* graph, int vertex_id, int visited[], int rec_stack[]);

void graph_reset_visited(Graph* graph);

void graph_destroy(Graph* graph);

#endif // GRAPH_H - Include guard sonu
