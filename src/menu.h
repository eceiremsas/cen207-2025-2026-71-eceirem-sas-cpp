#ifndef MENU_H
#define MENU_H

#include "stack.h"
#include "linked_list.h"
#include "queue.h"
#include "graph.h"
#include "sparse_matrix.h"
#include "hash_table.h"

#include <stdio.h>
#include <ctype.h>
#include "recipe.h"   // sadece tek yönlü: menu -> recipe

#define MAX_RECIPES 100


// Uygulama genelinde kullanılan veri yapısı
typedef struct {
    HashTable* hash_table;
    List* recipe_list;
    Stack* undo_stack;
    Queue* weekly_plan;
    Graph* dependency_graph;
    SparseMatrix* ingredient_matrix;
    int next_recipe_id;
} AppContext;


// Konsolu temizle
void clear_console(void);

// Enter bekle
void wait_for_enter(void) ;
   

// Güvenli string input
void safe_string_input(char* buffer, int size);

// Güvenli int input
int safe_int_input(void) ;
// Context oluştur
AppContext* app_context_create(void);

// Context temizle
void app_context_destroy(AppContext* ctx) ;

// Menü göster
void menu_display(void) ;

// Örnek veri yükle
void menu_load_sample_data(AppContext* ctx) ;
// 1. Tarif ekle
void menu_add_recipe(AppContext* ctx);

// 2. Tarif düzenle
void menu_edit_recipe(AppContext* ctx);

// 3. Tarif sil
void menu_delete_recipe(AppContext* ctx) ;


// 4. Arama alt menü
void menu_search_recipes(AppContext* ctx);
void menu_search_by_name(AppContext* ctx) ;
void menu_search_by_category(AppContext* ctx) ;

void menu_search_by_calorie_range(AppContext* ctx) ;

// 5. Tümünü listele
void menu_view_all_recipes(AppContext* ctx) ;
// 6. Sırala
void menu_sort_by_calories(AppContext* ctx) ;

// 7. Haftalık plan
void menu_create_weekly_plan(AppContext* ctx) ;

// 8. Bağımlılıklar
void menu_view_dependencies(AppContext* ctx) ;

// 9. Malzemeye göre
void menu_find_by_ingredient(AppContext* ctx);

// 10. Undo
void menu_undo(AppContext* ctx) ;

// Handler
void menu_handle_choice(AppContext* ctx, int choice);
#endif
