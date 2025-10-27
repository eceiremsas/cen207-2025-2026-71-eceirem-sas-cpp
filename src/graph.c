/**
 * @file graph.c
 * @brief Graph implementasyonu - Alt tarif bağımlılıkları için adjacency list
 */
#include <string.h>
#include "graph.h"  // Graph header

// Boş graf oluştur
Graph* graph_create(void) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));  // Bellek ayır
    if (graph == NULL) {
        printf("HATA: Graph olusturulamadi!\n");
        return NULL;
    }
    for (int i = 0; i < MAX_GRAPH_VERTICES; i++) {
        graph->vertices[i] = NULL;  // Tüm vertex'leri NULL yap
    }
    graph->vertex_count = 0;  // Başlangıçta vertex yok
    return graph;
}

// Grafa yeni vertex ekle (tarif)
int graph_add_vertex(Graph* graph, int recipe_id) {
    if (graph == NULL) { return 0; }
    if (graph->vertex_count >= MAX_GRAPH_VERTICES) {
        printf("UYARI: Maksimum vertex sayisina ulasildi!\n");
        return 0;
    }
    
    // Vertex zaten var mı kontrol et
    if (graph_find_vertex(graph, recipe_id) != NULL) {
        return 1;  // Zaten var, sorun değil
    }
    
    // Yeni vertex oluştur
    GraphVertex* vertex = (GraphVertex*)malloc(sizeof(GraphVertex));
    if (vertex == NULL) { return 0; }
    
    vertex->recipe_id = recipe_id;  // ID'yi ata
    vertex->edges = NULL;           // Henüz edge yok
    vertex->visited = 0;            // Ziyaret edilmedi
    
    graph->vertices[graph->vertex_count] = vertex;  // Diziye ekle
    graph->vertex_count++;  // Sayıyı artır
    return 1;
}

// Vertex bul
GraphVertex* graph_find_vertex(Graph* graph, int recipe_id) {
    if (graph == NULL) { return NULL; }
    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->vertices[i]->recipe_id == recipe_id) {
            return graph->vertices[i];  // Bulundu
        }
    }
    return NULL;  // Bulunamadı
}

// İki vertex arasına yönlü edge ekle (from → to)
int graph_add_edge(Graph* graph, int from_recipe_id, int to_recipe_id, const char* label) {
    if (graph == NULL) { return 0; }
    
    // Kaynak vertex'i bul
    GraphVertex* from_vertex = graph_find_vertex(graph, from_recipe_id);
    if (from_vertex == NULL) {
        printf("UYARI: Kaynak tarif bulunamadi (ID: %d)\n", from_recipe_id);
        return 0;
    }
    
    // Hedef vertex var mı kontrol et (yoksa ekle)
    GraphVertex* to_vertex = graph_find_vertex(graph, to_recipe_id);
    if (to_vertex == NULL) {
        graph_add_vertex(graph, to_recipe_id);  // Yeni vertex ekle
    }
    
    // Yeni edge oluştur
    GraphEdge* edge = (GraphEdge*)malloc(sizeof(GraphEdge));
    if (edge == NULL) { return 0; }
    
    edge->vertex_id = to_recipe_id;  // Hedef ID
    strncpy(edge->edge_label, label, 49);  // Etiket (örn: "hamur")
    edge->edge_label[49] = '\0';
    edge->next = from_vertex->edges;  // Listenin başına ekle
    from_vertex->edges = edge;        // Yeni edge artık baş
    
    return 1;
}

// Tüm visited flag'lerini sıfırla
void graph_reset_visited(Graph* graph) {
    if (graph == NULL) { return; }
    for (int i = 0; i < graph->vertex_count; i++) {
        graph->vertices[i]->visited = 0;  // Ziyaret edilmedi olarak işaretle
    }
}

// DFS ile bağımlılıkları göster (rekürsif)
void graph_display_dependencies(Graph* graph, int recipe_id, int depth) {
    if (graph == NULL) { return; }
    
    // Vertex'i bul
    GraphVertex* vertex = graph_find_vertex(graph, recipe_id);
    if (vertex == NULL) {
        printf("Tarif bulunamadi (ID: %d)\n", recipe_id);
        return;
    }
    
    // Ziyaret edildi olarak işaretle (sonsuz döngü önleme)
    vertex->visited = 1;
    
    // Girintileme (depth kadar boşluk)
    for (int i = 0; i < depth; i++) {
        printf("  ");  // Her seviye için 2 boşluk
    }
    printf("└─ Tarif ID: %d\n", recipe_id);
    
    // Bu vertex'in tüm edge'lerini (bağımlılıklarını) dolaş
    GraphEdge* edge = vertex->edges;
    while (edge != NULL) {
        // Alt tarif için girintileme
        for (int i = 0; i <= depth; i++) {
            printf("  ");
        }
        printf("(%s)\n", edge->edge_label);  // Edge etiketi (örn: "hamur")
        
        // Hedef vertex ziyaret edilmediyse rekürsif çağrı
        GraphVertex* target = graph_find_vertex(graph, edge->vertex_id);
        if (target != NULL && !target->visited) {
            graph_display_dependencies(graph, edge->vertex_id, depth + 1);
        }
        
        edge = edge->next;  // Bir sonraki edge
    }
}

// Döngü tespiti için DFS helper (rekürsif)
int graph_dfs_cycle_helper(Graph* graph, int vertex_id, int visited[], int rec_stack[]) {
    GraphVertex* vertex = graph_find_vertex(graph, vertex_id);
    if (vertex == NULL) { return 0; }
    
    visited[vertex_id] = 1;     // Ziyaret edildi
    rec_stack[vertex_id] = 1;   // Rekürsyon stack'inde
    
    // Tüm komşuları kontrol et
    GraphEdge* edge = vertex->edges;
    while (edge != NULL) {
        int neighbor = edge->vertex_id;
        
        if (!visited[neighbor]) {  // Henüz ziyaret edilmediyse
            if (graph_dfs_cycle_helper(graph, neighbor, visited, rec_stack)) {
                return 1;  // Döngü bulundu
            }
        } else if (rec_stack[neighbor]) {  // Rekürsyon stack'inde varsa
            return 1;  // Döngü bulundu! (back edge)
        }
        
        edge = edge->next;
    }
    
    rec_stack[vertex_id] = 0;  // Stack'ten çıkar
    return 0;  // Döngü yok
}

// Grafta döngü var mı kontrol et
int graph_has_cycle(Graph* graph) {
    if (graph == NULL) { return 0; }
    
    int visited[MAX_GRAPH_VERTICES] = {0};     // Ziyaret dizisi
    int rec_stack[MAX_GRAPH_VERTICES] = {0};   // Rekürsyon stack
    
    // Tüm vertex'lerden DFS başlat (disconnected graph için)
    for (int i = 0; i < graph->vertex_count; i++) {
        int vertex_id = graph->vertices[i]->recipe_id;
        if (!visited[vertex_id]) {
            if (graph_dfs_cycle_helper(graph, vertex_id, visited, rec_stack)) {
                return 1;  // Döngü bulundu
            }
        }
    }
    
    return 0;  // Döngü yok
}

// Grafı temizle
void graph_destroy(Graph* graph) {
    if (graph == NULL) { return; }
    
    // Tüm vertex'leri dolaş
    for (int i = 0; i < graph->vertex_count; i++) {
        GraphVertex* vertex = graph->vertices[i];
        if (vertex != NULL) {
            // Bu vertex'in tüm edge'lerini sil
            GraphEdge* edge = vertex->edges;
            while (edge != NULL) {
                GraphEdge* temp = edge;
                edge = edge->next;
                free(temp);  // Edge'i sil
            }
            free(vertex);  // Vertex'i sil
        }
    }
    
    free(graph);  // Graf yapısını sil
}
