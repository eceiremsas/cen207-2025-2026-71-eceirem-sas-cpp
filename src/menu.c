
#include "menu.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Konsolu temizle
void clear_console(void) {
    system("cls"); 
}

//void clear_console(void) { system("cls"); }

// Enter bekle
void wait_for_enter(void) {
    printf("\nDevam etmek icin Enter'a basin...");
    while (getchar() != '\n');
    getchar();
}

// Güvenli string input
void safe_string_input(char* buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') buffer[len-1] = '\0';
    }
}

// Güvenli int input
int safe_int_input(void) {
    int value;
    while (scanf("%d", &value) != 1) {
        printf("Gecersiz giris! Lutfen bir sayi girin: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return value;
}

// Context oluştur
AppContext* app_context_create(void) {
    AppContext* ctx = (AppContext*)malloc(sizeof(AppContext));
    if (ctx == NULL) return NULL;
    ctx->hash_table = hash_table_create(MAX_RECIPES);
    ctx->recipe_list = list_create();
    ctx->undo_stack = stack_create();
    ctx->weekly_plan = queue_create();
    ctx->dependency_graph = graph_create();
    ctx->ingredient_matrix = sparse_matrix_create();
    ctx->next_recipe_id = 1;
    if (!ctx->hash_table || !ctx->recipe_list || !ctx->undo_stack ||
        !ctx->weekly_plan || !ctx->dependency_graph || !ctx->ingredient_matrix) {
        app_context_destroy(ctx);
        return NULL;
    }
    return ctx;
}

// Context temizle
void app_context_destroy(AppContext* ctx) {
    if (ctx == NULL) return;
    if (ctx->hash_table) hash_table_destroy(ctx->hash_table);
    if (ctx->recipe_list) list_destroy(ctx->recipe_list);
    if (ctx->undo_stack) stack_destroy(ctx->undo_stack);
    if (ctx->weekly_plan) queue_destroy(ctx->weekly_plan);
    if (ctx->dependency_graph) graph_destroy(ctx->dependency_graph);
    if (ctx->ingredient_matrix) sparse_matrix_destroy(ctx->ingredient_matrix);
    free(ctx);
}

// Menü göster
void menu_display(void) {
    printf("\n=== TARIF VE BESLENME TAKIP SISTEMI ===\n\n");
    printf("  1.  Yeni Tarif Ekle\n  2.  Tarif Duzenle\n  3.  Tarif Sil\n");
    printf("  4.  Tarif Ara\n  5.  Tum Tarifleri Listele\n");
    printf("  6.  Tarifleri Kaloriye Gore Sirala\n  7.  Haftalik Beslenme Plani Olustur\n");
    printf("  8.  Tarif Bagimliliklarini Gor\n  9.  Malzemeye Gore Tarif Bul\n");
    printf("  10. Geri Al (Undo)\n  0.  Cikis\n\nSeciminiz: ");
}

// Örnek veri yükle
void menu_load_sample_data(AppContext* ctx) {
    printf("Ornek tarifler yukleniyor...\n");
    Recipe* pizza = recipe_create(ctx->next_recipe_id++, "Pizza", "Lunch", 800, 45);
    recipe_add_ingredient(pizza, "Un");
    recipe_add_ingredient(pizza, "Su");
    recipe_add_ingredient(pizza, "Maya");
    recipe_add_ingredient(pizza, "Domates sosu");
    recipe_add_ingredient(pizza, "Peynir");
    recipe_set_instructions(pizza, "Hamuru hazirla, sos sur, malzemeleri ekle, 200C'de 20 dk pisir.");
    hash_table_insert(ctx->hash_table, pizza);
    list_insert_tail(ctx->recipe_list, pizza);
    graph_add_vertex(ctx->dependency_graph, pizza->id);
    for (int i = 0; i < pizza->ingredient_count; i++)
        sparse_matrix_add_entry(ctx->ingredient_matrix, i, pizza->id, 1, pizza->ingredients[i]);
    
    Recipe* salad = recipe_create(ctx->next_recipe_id++, "Caesar Salata", "Dinner", 350, 20);
    recipe_add_ingredient(salad, "Marul");
    recipe_add_ingredient(salad, "Tavuk");
    recipe_add_ingredient(salad, "Kruton");
    recipe_add_ingredient(salad, "Parmesan");
    recipe_add_ingredient(salad, "Sos");
    recipe_set_instructions(salad, "Marullari yika, tavugu pisir, tum malzemeleri karistir.");
    hash_table_insert(ctx->hash_table, salad);
    list_insert_tail(ctx->recipe_list, salad);
    graph_add_vertex(ctx->dependency_graph, salad->id);
    for (int i = 0; i < salad->ingredient_count; i++)
        sparse_matrix_add_entry(ctx->ingredient_matrix, i+5, salad->id, 1, salad->ingredients[i]);
    
    Recipe* smoothie = recipe_create(ctx->next_recipe_id++, "Berry Smoothie", "Breakfast", 180, 5);
    recipe_add_ingredient(smoothie, "Cilek");
    recipe_add_ingredient(smoothie, "Muz");
    recipe_add_ingredient(smoothie, "Yogurt");
    recipe_add_ingredient(smoothie, "Bal");
    recipe_set_instructions(smoothie, "Tum malzemeleri blender'a koy ve karistir.");
    hash_table_insert(ctx->hash_table, smoothie);
    list_insert_tail(ctx->recipe_list, smoothie);
    graph_add_vertex(ctx->dependency_graph, smoothie->id);
    for (int i = 0; i < smoothie->ingredient_count; i++)
        sparse_matrix_add_entry(ctx->ingredient_matrix, i+10, smoothie->id, 1, smoothie->ingredients[i]);
    printf("3 ornek tarif yuklendi!\n");
}

// 1. Tarif ekle
void menu_add_recipe(AppContext* ctx) {
    clear_console();
    printf("\n=== YENI TARIF EKLE ===\n\n");
    char name[MAX_NAME_LENGTH], category[MAX_CATEGORY_LENGTH];
    int calories, prep_time;
    printf("Tarif adi: "); safe_string_input(name, MAX_NAME_LENGTH);
    printf("Kategori (Breakfast/Lunch/Dinner): "); safe_string_input(category, MAX_CATEGORY_LENGTH);
    printf("Kalori: "); calories = safe_int_input();
    printf("Hazirlik suresi (dk): "); prep_time = safe_int_input();
    Recipe* recipe = recipe_create(ctx->next_recipe_id++, name, category, calories, prep_time);
    if (recipe == NULL) { printf("HATA!\n"); return; }
    printf("\nKac malzeme? (Max %d): ", MAX_INGREDIENTS);
    int count = safe_int_input();
    if (count > MAX_INGREDIENTS) count = MAX_INGREDIENTS;
    for (int i = 0; i < count; i++) {
        char ing[MAX_INGREDIENT_LENGTH];
        printf("Malzeme %d: ", i+1); safe_string_input(ing, MAX_INGREDIENT_LENGTH);
        recipe_add_ingredient(recipe, ing);
        sparse_matrix_add_entry(ctx->ingredient_matrix, i, recipe->id, 1, ing);
    }
    char inst[MAX_INSTRUCTIONS];
    printf("\nTalimatlar: "); safe_string_input(inst, MAX_INSTRUCTIONS);
    recipe_set_instructions(recipe, inst);
    hash_table_insert(ctx->hash_table, recipe);
    list_insert_tail(ctx->recipe_list, recipe);
    graph_add_vertex(ctx->dependency_graph, recipe->id);
    stack_push(ctx->undo_stack, OP_ADD, recipe);
    printf("\nBasarili! ID: %d\n", recipe->id);
    wait_for_enter();
}

// 2. Tarif düzenle
void menu_edit_recipe(AppContext* ctx) {
    clear_console();
    printf("\n=== TARIF DUZENLE ===\n\n");
    printf("Tarif ID: "); int id = safe_int_input();
    Recipe* r = hash_table_search(ctx->hash_table, id);
    if (!r) { printf("\nBulunamadi!\n"); wait_for_enter(); return; }
    printf("\nMevcut:\n"); recipe_display(r);
    stack_push(ctx->undo_stack, OP_EDIT, r);
    printf("\nYeni isim (Enter=degistirme): ");
    char name[MAX_NAME_LENGTH]; safe_string_input(name, MAX_NAME_LENGTH);
    if (strlen(name) > 0) strncpy(r->name, name, MAX_NAME_LENGTH - 1);
    printf("Yeni kalori (0=degistirme): "); int cal = safe_int_input();
    if (cal > 0) r->calories = cal;
    printf("\nGuncellendi!\n"); wait_for_enter();
}

// 3. Tarif sil
void menu_delete_recipe(AppContext* ctx) {
    clear_console();
    printf("\n=== TARIF SIL ===\n\n");
    printf("Tarif ID: "); int id = safe_int_input();
    Recipe* r = hash_table_search(ctx->hash_table, id);
    if (!r) { printf("\nBulunamadi!\n"); wait_for_enter(); return; }
    printf("\nSilinecek:\n"); recipe_display(r);
    printf("\nEmin misiniz? (1=Evet): "); int c = safe_int_input();
    if (c != 1) { printf("\nIptal.\n"); wait_for_enter(); return; }
    stack_push(ctx->undo_stack, OP_DELETE, r);
    hash_table_delete(ctx->hash_table, id);
    list_remove(ctx->recipe_list, id);
    printf("\nSilindi!\n"); wait_for_enter();
}

// 4. Arama alt menü
void menu_search_recipes(AppContext* ctx) {
    clear_console();
    printf("\n=== TARIF ARA ===\n\n");
    printf("  1. Isme Gore\n  2. Kategoriye Gore\n  3. Kalori Araligina Gore\n  0. Geri\n\nSecim: ");
    int c = safe_int_input();
    if (c == 1) menu_search_by_name(ctx);
    else if (c == 2) menu_search_by_category(ctx);
    else if (c == 3) menu_search_by_calorie_range(ctx);
}

void menu_search_by_name(AppContext* ctx) {
    clear_console();
    printf("\n=== ISME GORE ARA ===\n\n");
    char name[MAX_NAME_LENGTH];
    printf("Isim: "); safe_string_input(name, MAX_NAME_LENGTH);
    int found = 0;
    ListNode* cur = ctx->recipe_list->head;
    while (cur) {
        char lower1[MAX_NAME_LENGTH], lower2[MAX_NAME_LENGTH];
        strcpy(lower1, cur->recipe->name); strcpy(lower2, name);
        for (int i = 0; lower1[i]; i++) lower1[i] = tolower(lower1[i]);
        for (int i = 0; lower2[i]; i++) lower2[i] = tolower(lower2[i]);
        if (strstr(lower1, lower2)) { recipe_display(cur->recipe); found++; }
        cur = cur->next;
    }
    if (!found) printf("\nBulunamadi.\n");
    else printf("\n%d tarif bulundu.\n", found);
    wait_for_enter();
}

void menu_search_by_category(AppContext* ctx) {
    clear_console();
    printf("\n=== KATEGORIYE GORE ARA ===\n\n");
    printf("  1. Breakfast\n  2. Lunch\n  3. Dinner\n\nSecim: ");
    int c = safe_int_input();
    char cat[MAX_CATEGORY_LENGTH];
    if (c == 1) strcpy(cat, "Breakfast");
    else if (c == 2) strcpy(cat, "Lunch");
    else if (c == 3) strcpy(cat, "Dinner");
    else { printf("\nGecersiz!\n"); wait_for_enter(); return; }
    int found = 0;
    ListNode* cur = ctx->recipe_list->head;
    while (cur) {
        if (strcmp(cur->recipe->category, cat) == 0) { recipe_display(cur->recipe); found++; }
        cur = cur->next;
    }
    if (!found) printf("\nBulunamadi.\n");
    else printf("\n%d tarif.\n", found);
    wait_for_enter();
}

void menu_search_by_calorie_range(AppContext* ctx) {
    clear_console();
    printf("\n=== KALORI ARALIGINA GORE ===\n\n");
    printf("Min: "); int min = safe_int_input();
    printf("Max: "); int max = safe_int_input();
    if (min > max) { printf("\nHata!\n"); wait_for_enter(); return; }
    int found = 0;
    ListNode* cur = ctx->recipe_list->head;
    while (cur) {
        if (cur->recipe->calories >= min && cur->recipe->calories <= max) {
            recipe_display(cur->recipe); found++;
        }
        cur = cur->next;
    }
    if (!found) printf("\nBulunamadi.\n");
    else printf("\n%d tarif.\n", found);
    wait_for_enter();
}

// 5. Tümünü listele
void menu_view_all_recipes(AppContext* ctx) {
    clear_console();
    list_display(ctx->recipe_list);
    wait_for_enter();
}

// 6. Sırala
void menu_sort_by_calories(AppContext* ctx) {
    clear_console();
    printf("\n=== SIRALAMA ===\n");
    if (list_is_empty(ctx->recipe_list)) { printf("\nBos!\n"); wait_for_enter(); return; }
    int count = list_size(ctx->recipe_list);
    Recipe** arr = (Recipe**)malloc(sizeof(Recipe*) * count);
    ListNode* cur = ctx->recipe_list->head;
    for (int i = 0; i < count; i++) { arr[i] = cur->recipe; cur = cur->next; }
    heap_sort_recipes(arr, count);
    printf("\nDusukten yuksege:\n");
    for (int i = 0; i < count; i++) printf("%d. %s - %d kcal\n", i+1, arr[i]->name, arr[i]->calories);
    free(arr);
    wait_for_enter();
}

// 7. Haftalık plan
void menu_create_weekly_plan(AppContext* ctx) {
    clear_console();
    printf("\n=== 7 GUNLUK PLAN ===\n");
    while (!queue_is_empty(ctx->weekly_plan)) queue_dequeue(ctx->weekly_plan);
    for (int d = 1; d <= 7; d++) {
        printf("\nGun %d ID: ", d); int id = safe_int_input();
        Recipe* r = hash_table_search(ctx->hash_table, id);
        if (r) queue_enqueue(ctx->weekly_plan, r);
        else { printf("Bulunamadi!\n"); d--; }
    }
    queue_display(ctx->weekly_plan);
    wait_for_enter();
}

// 8. Bağımlılıklar
void menu_view_dependencies(AppContext* ctx) {
    clear_console();
    printf("\n=== BAGIMLIL IKLAR ===\n");
    printf("ID: "); int id = safe_int_input();
    graph_reset_visited(ctx->dependency_graph);
    graph_display_dependencies(ctx->dependency_graph, id, 0);
    wait_for_enter();
}

// 9. Malzemeye göre
void menu_find_by_ingredient(AppContext* ctx) {
    clear_console();
    printf("\n=== MALZEMEYE GORE ===\n");
    char ing[MAX_INGREDIENT_LENGTH];
    printf("Malzeme: "); safe_string_input(ing, MAX_INGREDIENT_LENGTH);
    int ids[MAX_RECIPES];
    int f = sparse_matrix_find_recipes_by_ingredient(ctx->ingredient_matrix, ing, ids, MAX_RECIPES);
    if (f == 0) printf("\nBulunamadi.\n");
    else {
        printf("\n%d tarif:\n", f);
        for (int i = 0; i < f; i++) {
            Recipe* r = hash_table_search(ctx->hash_table, ids[i]);
            if (r) printf("  - %s (ID:%d)\n", r->name, r->id);
        }
    }
    wait_for_enter();
}

// 10. Undo
void menu_undo(AppContext* ctx) {
    clear_console();
    printf("\n=== GERI AL ===\n");
    if (stack_is_empty(ctx->undo_stack)) {
        printf("\nYok!\n"); wait_for_enter(); return;
    }
    StackOperation* op = stack_pop(ctx->undo_stack);
    if (!op) return;
    if (op->type == OP_ADD) {
        hash_table_delete(ctx->hash_table, op->recipe->id);
        list_remove(ctx->recipe_list, op->recipe->id);
        printf("Ekleme geri alindi.\n");
    }
    recipe_destroy(op->recipe);
    wait_for_enter();
}

// Handler
void menu_handle_choice(AppContext* ctx, int choice) {
    switch (choice) {
        case 1: menu_add_recipe(ctx); break;
        case 2: menu_edit_recipe(ctx); break;
        case 3: menu_delete_recipe(ctx); break;
        case 4: menu_search_recipes(ctx); break;
        case 5: menu_view_all_recipes(ctx); break;
        case 6: menu_sort_by_calories(ctx); break;
        case 7: menu_create_weekly_plan(ctx); break;
        case 8: menu_view_dependencies(ctx); break;
        case 9: menu_find_by_ingredient(ctx); break;
        case 10: menu_undo(ctx); break;
        case 0: printf("\nCikis...\n"); break;
        default: printf("\nGecersiz!\n"); wait_for_enter(); break;
    }
}
