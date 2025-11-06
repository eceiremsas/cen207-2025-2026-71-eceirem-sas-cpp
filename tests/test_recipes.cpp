/**
 * @file test_recipes.cpp
 * @brief Comprehensive unit tests for all data structures using GoogleTest
 * @details Tests all 7 midterm algorithms: Recipe, Linked List, XOR Linked List,
 *          Sparse Matrix, Stack, Queue, Heap, Graph (BFS/DFS), Hash Table
 *          All tests run automatically without user interaction
 */

#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
extern "C" {
#include "../include/recipe.h"
#include "../include/linked_list.h"
#include "../include/xor_linked_list.h"
#include "../include/sparse_matrix.h"
#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/heap.h"
#include "../include/graph.h"
#include "../include/hash_table.h"
#include "../include/menu.h"
}

// Helper variables for traversal tests
static int g_forward_count = 0;
static int g_backward_count = 0;
static std::vector<int> g_visited_order;

static void forward_visit_counter(Recipe* r) {
    if (r) g_forward_count++;
}

static void backward_visit_counter(Recipe* r) {
    if (r) g_backward_count++;
}

static void graph_visit_func(int vertex_id) {
    g_visited_order.push_back(vertex_id);
}

/**
 * @brief Test recipe creation
 */
TEST(RecipeTest, CreateRecipe) {
    Recipe* r = recipe_create(1, "Pizza", "Lunch", 800, 45);
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->id, 1);
    EXPECT_STREQ(r->name, "Pizza");
    EXPECT_STREQ(r->category, "Lunch");
    EXPECT_EQ(r->calories, 800);
    EXPECT_EQ(r->preparation_time, 45);
    recipe_destroy(r);
}

/**
 * @brief Test adding ingredients to recipe
 */
TEST(RecipeTest, AddIngredient) {
    Recipe* r = recipe_create(1, "Pizza", "Lunch", 800, 45);
    ASSERT_NE(r, nullptr);
    
    EXPECT_EQ(recipe_add_ingredient(r, "Flour"), 1);
    EXPECT_EQ(recipe_add_ingredient(r, "Cheese"), 1);
    EXPECT_EQ(r->ingredient_count, 2);
    
    recipe_destroy(r);
}

/**
 * @brief Test setting instructions
 */
TEST(RecipeTest, SetInstructions) {
    Recipe* r = recipe_create(1, "Pizza", "Lunch", 800, 45);
    ASSERT_NE(r, nullptr);
    
    recipe_set_instructions(r, "Mix ingredients and bake");
    EXPECT_STREQ(r->instructions, "Mix ingredients and bake");
    
    recipe_destroy(r);
}

/**
 * @brief Test recipe comparison by ID
 */
TEST(RecipeTest, CompareByID) {
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    ASSERT_NE(r1, nullptr);
    ASSERT_NE(r2, nullptr);
    
    EXPECT_LT(recipe_compare_by_id(r1, r2), 0);
    EXPECT_GT(recipe_compare_by_id(r2, r1), 0);
    EXPECT_EQ(recipe_compare_by_id(r1, r1), 0);
    
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test recipe comparison by calories
 */
TEST(RecipeTest, CompareByCalories) {
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Salad", "Lunch", 200, 10);
    ASSERT_NE(r1, nullptr);
    ASSERT_NE(r2, nullptr);
    
    EXPECT_GT(recipe_compare_by_calories(r1, r2), 0);
    EXPECT_LT(recipe_compare_by_calories(r2, r1), 0);
    
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test recipe copy
 */
TEST(RecipeTest, CopyRecipe) {
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    ASSERT_NE(r1, nullptr);
    recipe_add_ingredient(r1, "Flour");
    recipe_set_instructions(r1, "Bake for 20 minutes");
    
    Recipe* r2 = recipe_copy(r1);
    ASSERT_NE(r2, nullptr);
    
    EXPECT_EQ(r2->id, r1->id);
    EXPECT_STREQ(r2->name, r1->name);
    EXPECT_EQ(r2->ingredient_count, r1->ingredient_count);
    EXPECT_STREQ(r2->instructions, r1->instructions);
    
    // Verify they are different objects
    EXPECT_NE(r1, r2);
    
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test binary file save and load
 */
TEST(RecipeTest, BinaryFileOperations) {
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    ASSERT_NE(r1, nullptr);
    recipe_add_ingredient(r1, "Flour");
    recipe_add_ingredient(r1, "Cheese");
    recipe_set_instructions(r1, "Bake for 20 minutes");
    
    // Save to binary file
    const char* filename = "test_recipe.bin";
    EXPECT_EQ(recipe_save_binary(r1, filename), 1);
    
    // Load from binary file
    Recipe* r2 = recipe_load_binary(filename);
    ASSERT_NE(r2, nullptr);
    
    // Verify loaded data
    EXPECT_EQ(r2->id, r1->id);
    EXPECT_STREQ(r2->name, r1->name);
    EXPECT_STREQ(r2->category, r1->category);
    EXPECT_EQ(r2->calories, r1->calories);
    EXPECT_EQ(r2->preparation_time, r1->preparation_time);
    EXPECT_EQ(r2->ingredient_count, r1->ingredient_count);
    EXPECT_STREQ(r2->instructions, r1->instructions);
    
    // Cleanup
    remove(filename);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test recipe display function
 */
TEST(RecipeTest, DisplayRecipe) {
    Recipe* r = recipe_create(1, "Pizza", "Lunch", 800, 45);
    ASSERT_NE(r, nullptr);
    recipe_add_ingredient(r, "Flour");
    recipe_set_instructions(r, "Bake for 20 minutes");
    
    // Display should not crash
    recipe_display(r);
    
    recipe_destroy(r);
}

/**
 * @brief Test recipe array binary operations
 */
TEST(RecipeTest, ArrayBinaryFileOperations) {
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    Recipe* r3 = recipe_create(3, "Salad", "Lunch", 200, 10);
    
    Recipe recipes[] = {*r1, *r2, *r3};
    const char* filename = "test_recipes_array.bin";
    
    EXPECT_EQ(recipe_save_array_binary(recipes, 3, filename), 1);
    
    int count = 0;
    Recipe* loaded = recipe_load_array_binary(filename, &count);
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(count, 3);
    EXPECT_EQ(loaded[0].id, 1);
    EXPECT_EQ(loaded[1].id, 2);
    EXPECT_EQ(loaded[2].id, 3);
    
    remove(filename);
    free(loaded);
    recipe_destroy(r1);
    recipe_destroy(r2);
    recipe_destroy(r3);
}

// ============================================================================
// LINKED LIST TESTS
// ============================================================================

/**
 * @brief Test linked list creation
 */
TEST(LinkedListTest, CreateList) {
    List* list = list_create();
    ASSERT_NE(list, nullptr);
    EXPECT_EQ(list_size(list), 0);
    EXPECT_TRUE(list_is_empty(list));
    list_destroy(list);
}

/**
 * @brief Test inserting at head
 */
TEST(LinkedListTest, InsertHead) {
    List* list = list_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    EXPECT_EQ(list_insert_head(list, r1), 1);
    EXPECT_EQ(list_insert_head(list, r2), 1);
    EXPECT_EQ(list_size(list), 2);
    EXPECT_FALSE(list_is_empty(list));
    
    Recipe* found = list_find(list, 2);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->id, 2);
    
    list_destroy(list);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test inserting at tail
 */
TEST(LinkedListTest, InsertTail) {
    List* list = list_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    EXPECT_EQ(list_insert_tail(list, r1), 1);
    EXPECT_EQ(list_insert_tail(list, r2), 1);
    EXPECT_EQ(list_size(list), 2);
    
    Recipe* found = list_find(list, 1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->id, 1);
    
    list_destroy(list);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test removing from list
 */
TEST(LinkedListTest, RemoveFromList) {
    List* list = list_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    list_insert_head(list, r1);
    list_insert_head(list, r2);
    
    Recipe* removed = list_remove(list, 1);
    ASSERT_NE(removed, nullptr);
    EXPECT_EQ(removed->id, 1);
    EXPECT_EQ(list_size(list), 1);
    
    recipe_destroy(removed);
    list_destroy(list);
    recipe_destroy(r2);
}

/**
 * @brief Test binary file operations for linked list
 */
TEST(LinkedListTest, BinaryFileOperations) {
    List* list = list_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    list_insert_tail(list, r1);
    list_insert_tail(list, r2);
    
    const char* filename = "test_list.bin";
    EXPECT_EQ(list_save_binary(list, filename), 1);
    
    List* loaded = list_load_binary(filename);
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(list_size(loaded), 2);
    
    Recipe* found = list_find(loaded, 1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->id, 1);
    
    remove(filename);
    list_destroy(list);
    list_destroy(loaded);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test list display function
 */
TEST(LinkedListTest, DisplayList) {
    List* list = list_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    list_insert_tail(list, r1);
    list_insert_tail(list, r2);
    
    // Display should not crash
    list_display(list);
    
    list_destroy(list);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

// ============================================================================
// XOR LINKED LIST TESTS
// ============================================================================

/**
 * @brief Test XOR linked list creation
 */
TEST(XORLinkedListTest, CreateList) {
    XORList* list = xor_list_create();
    ASSERT_NE(list, nullptr);
    EXPECT_EQ(xor_list_size(list), 0);
    EXPECT_TRUE(xor_list_is_empty(list));
    xor_list_destroy(list);
}

/**
 * @brief Test inserting at head and tail
 */
TEST(XORLinkedListTest, InsertOperations) {
    XORList* list = xor_list_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    EXPECT_EQ(xor_list_insert_head(list, r1), 1);
    EXPECT_EQ(xor_list_insert_tail(list, r2), 1);
    EXPECT_EQ(xor_list_size(list), 2);
    
    Recipe* found = xor_list_find(list, 1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->id, 1);
    
    xor_list_destroy(list);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test bidirectional traversal
 */
TEST(XORLinkedListTest, BidirectionalTraversal) {
    XORList* list = xor_list_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    Recipe* r3 = recipe_create(3, "Salad", "Lunch", 200, 10);
    
    xor_list_insert_tail(list, r1);
    xor_list_insert_tail(list, r2);
    xor_list_insert_tail(list, r3);
    
    g_forward_count = 0;
    xor_list_traverse_forward(list, forward_visit_counter);
    EXPECT_EQ(g_forward_count, 3);
    
    g_backward_count = 0;
    xor_list_traverse_backward(list, backward_visit_counter);
    EXPECT_EQ(g_backward_count, 3);
    
    xor_list_destroy(list);
    recipe_destroy(r1);
    recipe_destroy(r2);
    recipe_destroy(r3);
}

/**
 * @brief Test binary file operations for XOR linked list
 */
TEST(XORLinkedListTest, BinaryFileOperations) {
    XORList* list = xor_list_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    xor_list_insert_tail(list, r1);
    xor_list_insert_tail(list, r2);
    
    const char* filename = "test_xor_list.bin";
    EXPECT_EQ(xor_list_save_binary(list, filename), 1);
    
    XORList* loaded = xor_list_load_binary(filename);
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(xor_list_size(loaded), 2);
    
    remove(filename);
    xor_list_destroy(list);
    xor_list_destroy(loaded);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

// ============================================================================
// SPARSE MATRIX TESTS
// ============================================================================

/**
 * @brief Test sparse matrix creation
 */
TEST(SparseMatrixTest, CreateMatrix) {
    SparseMatrix* matrix = sparse_matrix_create();
    ASSERT_NE(matrix, nullptr);
    EXPECT_EQ(matrix->entry_count, 0);
    sparse_matrix_destroy(matrix);
}

/**
 * @brief Test adding entries
 */
TEST(SparseMatrixTest, AddEntry) {
    SparseMatrix* matrix = sparse_matrix_create();
    
    sparse_matrix_add_entry(matrix, 0, 0, 5, "Flour");
    sparse_matrix_add_entry(matrix, 0, 1, 3, "Cheese");
    sparse_matrix_add_entry(matrix, 1, 0, 2, "Flour");
    
    EXPECT_EQ(sparse_matrix_get_value(matrix, 0, 0), 5);
    EXPECT_EQ(sparse_matrix_get_value(matrix, 0, 1), 3);
    EXPECT_EQ(sparse_matrix_get_value(matrix, 1, 0), 2);
    EXPECT_EQ(sparse_matrix_get_value(matrix, 1, 1), 0); // Non-existent entry
    
    sparse_matrix_destroy(matrix);
}

/**
 * @brief Test finding recipes by ingredient
 */
TEST(SparseMatrixTest, FindRecipesByIngredient) {
    SparseMatrix* matrix = sparse_matrix_create();
    
    sparse_matrix_add_entry(matrix, 0, 0, 5, "Flour");
    sparse_matrix_add_entry(matrix, 1, 0, 2, "Flour");
    sparse_matrix_add_entry(matrix, 2, 1, 3, "Cheese");
    
    int recipe_ids[10];
    int count = sparse_matrix_find_recipes_by_ingredient(matrix, "Flour", recipe_ids, 10);
    EXPECT_EQ(count, 2);
    
    sparse_matrix_destroy(matrix);
}

/**
 * @brief Test binary file operations for sparse matrix
 */
TEST(SparseMatrixTest, BinaryFileOperations) {
    SparseMatrix* matrix = sparse_matrix_create();
    sparse_matrix_add_entry(matrix, 0, 0, 5, "Flour");
    sparse_matrix_add_entry(matrix, 0, 1, 3, "Cheese");
    
    const char* filename = "test_matrix.bin";
    EXPECT_EQ(sparse_matrix_save_binary(matrix, filename), 1);
    
    SparseMatrix* loaded = sparse_matrix_load_binary(filename);
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(loaded->entry_count, 2);
    EXPECT_EQ(sparse_matrix_get_value(loaded, 0, 0), 5);
    
    remove(filename);
    sparse_matrix_destroy(matrix);
    sparse_matrix_destroy(loaded);
}

/**
 * @brief Test finding ingredients by recipe
 */
TEST(SparseMatrixTest, FindIngredientsByRecipe) {
    SparseMatrix* matrix = sparse_matrix_create();
    
    sparse_matrix_add_entry(matrix, 0, 0, 5, "Flour");
    sparse_matrix_add_entry(matrix, 0, 1, 3, "Cheese");
    sparse_matrix_add_entry(matrix, 1, 0, 2, "Flour");
    
    int count = sparse_matrix_find_ingredients_by_recipe(matrix, 0);
    EXPECT_EQ(count, 2); // Recipe 0 has 2 ingredients
    
    sparse_matrix_destroy(matrix);
}

/**
 * @brief Test sparse matrix display
 */
TEST(SparseMatrixTest, DisplayMatrix) {
    SparseMatrix* matrix = sparse_matrix_create();
    sparse_matrix_add_entry(matrix, 0, 0, 5, "Flour");
    sparse_matrix_add_entry(matrix, 0, 1, 3, "Cheese");
    
    // Display should not crash
    sparse_matrix_display(matrix);
    
    sparse_matrix_destroy(matrix);
}

// ============================================================================
// STACK TESTS
// ============================================================================

/**
 * @brief Test stack creation
 */
TEST(StackTest, CreateStack) {
    Stack* stack = stack_create();
    ASSERT_NE(stack, nullptr);
    EXPECT_TRUE(stack_is_empty(stack));
    EXPECT_FALSE(stack_is_full(stack));
    EXPECT_EQ(stack_size(stack), 0);
    stack_destroy(stack);
}

/**
 * @brief Test push and pop operations
 */
TEST(StackTest, PushPop) {
    Stack* stack = stack_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    EXPECT_EQ(stack_push(stack, OP_ADD, r1), 1);
    EXPECT_EQ(stack_push(stack, OP_EDIT, r2), 1);
    EXPECT_EQ(stack_size(stack), 2);
    EXPECT_FALSE(stack_is_empty(stack));
    
    StackOperation* op = stack_pop(stack);
    ASSERT_NE(op, nullptr);
    EXPECT_EQ(op->type, OP_EDIT);
    EXPECT_EQ(op->recipe->id, 2);
    
    op = stack_pop(stack);
    ASSERT_NE(op, nullptr);
    EXPECT_EQ(op->type, OP_ADD);
    EXPECT_EQ(op->recipe->id, 1);
    
    EXPECT_TRUE(stack_is_empty(stack));
    
    stack_destroy(stack);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test peek operation
 */
TEST(StackTest, Peek) {
    Stack* stack = stack_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    
    stack_push(stack, OP_ADD, r1);
    
    StackOperation* op = stack_peek(stack);
    ASSERT_NE(op, nullptr);
    EXPECT_EQ(op->type, OP_ADD);
    EXPECT_EQ(stack_size(stack), 1); // Size should not change
    
    stack_destroy(stack);
    recipe_destroy(r1);
}

/**
 * @brief Test binary file operations for stack
 */
TEST(StackTest, BinaryFileOperations) {
    Stack* stack = stack_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    stack_push(stack, OP_ADD, r1);
    stack_push(stack, OP_EDIT, r2);
    
    const char* filename = "test_stack.bin";
    EXPECT_EQ(stack_save_binary(stack, filename), 1);
    
    Stack* loaded = stack_load_binary(filename);
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(stack_size(loaded), 2);
    
    remove(filename);
    stack_destroy(stack);
    stack_destroy(loaded);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test stack full condition
 */
TEST(StackTest, StackFull) {
    Stack* stack = stack_create();
    Recipe* r = recipe_create(1, "Pizza", "Lunch", 800, 45);
    
    // Fill stack to capacity
    for (int i = 0; i < UNDO_STACK_SIZE; i++) {
        stack_push(stack, OP_ADD, r);
    }
    
    EXPECT_TRUE(stack_is_full(stack));
    EXPECT_FALSE(stack_is_empty(stack));
    EXPECT_EQ(stack_size(stack), UNDO_STACK_SIZE);
    
    stack_destroy(stack);
    recipe_destroy(r);
}

// ============================================================================
// QUEUE TESTS
// ============================================================================

/**
 * @brief Test queue creation
 */
TEST(QueueTest, CreateQueue) {
    Queue* queue = queue_create();
    ASSERT_NE(queue, nullptr);
    EXPECT_TRUE(queue_is_empty(queue));
    EXPECT_FALSE(queue_is_full(queue));
    EXPECT_EQ(queue_size(queue), 0);
    queue_destroy(queue);
}

/**
 * @brief Test enqueue and dequeue operations
 */
TEST(QueueTest, EnqueueDequeue) {
    Queue* queue = queue_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    EXPECT_EQ(queue_enqueue(queue, r1), 1);
    EXPECT_EQ(queue_enqueue(queue, r2), 1);
    EXPECT_EQ(queue_size(queue), 2);
    EXPECT_FALSE(queue_is_empty(queue));
    
    Recipe* dequeued = queue_dequeue(queue);
    ASSERT_NE(dequeued, nullptr);
    EXPECT_EQ(dequeued->id, 1); // FIFO - first in, first out
    EXPECT_EQ(queue_size(queue), 1);
    
    dequeued = queue_dequeue(queue);
    ASSERT_NE(dequeued, nullptr);
    EXPECT_EQ(dequeued->id, 2);
    EXPECT_TRUE(queue_is_empty(queue));
    
    queue_destroy(queue);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test peek operation
 */
TEST(QueueTest, Peek) {
    Queue* queue = queue_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    
    queue_enqueue(queue, r1);
    
    Recipe* peeked = queue_peek(queue);
    ASSERT_NE(peeked, nullptr);
    EXPECT_EQ(peeked->id, 1);
    EXPECT_EQ(queue_size(queue), 1); // Size should not change
    
    queue_destroy(queue);
    recipe_destroy(r1);
}

/**
 * @brief Test binary file operations for queue
 */
TEST(QueueTest, BinaryFileOperations) {
    Queue* queue = queue_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    queue_enqueue(queue, r1);
    queue_enqueue(queue, r2);
    
    const char* filename = "test_queue.bin";
    EXPECT_EQ(queue_save_binary(queue, filename), 1);
    
    Queue* loaded = queue_load_binary(filename);
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(queue_size(loaded), 2);
    
    remove(filename);
    queue_destroy(queue);
    queue_destroy(loaded);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test queue display function
 */
TEST(QueueTest, DisplayQueue) {
    Queue* queue = queue_create();
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    queue_enqueue(queue, r1);
    queue_enqueue(queue, r2);
    
    // Display should not crash
    queue_display(queue);
    
    queue_destroy(queue);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test queue full condition
 */
TEST(QueueTest, QueueFull) {
    Queue* queue = queue_create();
    Recipe* r = recipe_create(1, "Pizza", "Lunch", 800, 45);
    
    // Fill queue to capacity
    for (int i = 0; i < WEEKLY_PLAN_SIZE; i++) {
        queue_enqueue(queue, r);
    }
    
    EXPECT_TRUE(queue_is_full(queue));
    EXPECT_FALSE(queue_is_empty(queue));
    EXPECT_EQ(queue_size(queue), WEEKLY_PLAN_SIZE);
    
    queue_destroy(queue);
    recipe_destroy(r);
}

// ============================================================================
// HEAP TESTS
// ============================================================================

/**
 * @brief Test heap creation
 */
TEST(HeapTest, CreateHeap) {
    Heap* heap = heap_create(10);
    ASSERT_NE(heap, nullptr);
    EXPECT_TRUE(heap_is_empty(heap));
    EXPECT_FALSE(heap_is_full(heap));
    heap_destroy(heap);
}

/**
 * @brief Test heap insert and extract min
 */
TEST(HeapTest, InsertExtractMin) {
    Heap* heap = heap_create(10);
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Salad", "Lunch", 200, 10);
    Recipe* r3 = recipe_create(3, "Burger", "Lunch", 600, 30);
    
    EXPECT_EQ(heap_insert(heap, r1), 1);
    EXPECT_EQ(heap_insert(heap, r2), 1);
    EXPECT_EQ(heap_insert(heap, r3), 1);
    
    Recipe* min = heap_extract_min(heap);
    ASSERT_NE(min, nullptr);
    EXPECT_EQ(min->id, 2); // Salad has lowest calories (200)
    EXPECT_EQ(min->calories, 200);
    
    min = heap_extract_min(heap);
    ASSERT_NE(min, nullptr);
    EXPECT_EQ(min->id, 3); // Burger has next lowest (600)
    
    min = heap_extract_min(heap);
    ASSERT_NE(min, nullptr);
    EXPECT_EQ(min->id, 1); // Pizza has highest (800)
    
    EXPECT_TRUE(heap_is_empty(heap));
    
    heap_destroy(heap);
    recipe_destroy(r1);
    recipe_destroy(r2);
    recipe_destroy(r3);
}

/**
 * @brief Test heap sort
 */
TEST(HeapTest, HeapSort) {
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Salad", "Lunch", 200, 10);
    Recipe* r3 = recipe_create(3, "Burger", "Lunch", 600, 30);
    
    Recipe* recipes[] = {r1, r2, r3};
    heap_sort_recipes(recipes, 3);
    
    // After sorting, recipes should be ordered by calories (ascending)
    EXPECT_EQ(recipes[0]->id, 2); // Salad (200)
    EXPECT_EQ(recipes[1]->id, 3); // Burger (600)
    EXPECT_EQ(recipes[2]->id, 1); // Pizza (800)
    
    recipe_destroy(r1);
    recipe_destroy(r2);
    recipe_destroy(r3);
}

/**
 * @brief Test binary file operations for heap
 */
TEST(HeapTest, BinaryFileOperations) {
    Heap* heap = heap_create(10);
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Salad", "Lunch", 200, 10);
    
    heap_insert(heap, r1);
    heap_insert(heap, r2);
    
    const char* filename = "test_heap.bin";
    EXPECT_EQ(heap_save_binary(heap, filename), 1);
    
    Heap* loaded = heap_load_binary(filename);
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(loaded->size, 2);
    
    Recipe* min = heap_extract_min(loaded);
    ASSERT_NE(min, nullptr);
    EXPECT_EQ(min->id, 2); // Salad has lowest calories
    
    remove(filename);
    heap_destroy(heap);
    heap_destroy(loaded);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test heap peek operation
 */
TEST(HeapTest, Peek) {
    Heap* heap = heap_create(10);
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Salad", "Lunch", 200, 10);
    
    heap_insert(heap, r1);
    heap_insert(heap, r2);
    
    Recipe* peeked = heap_peek(heap);
    ASSERT_NE(peeked, nullptr);
    EXPECT_EQ(peeked->id, 2); // Salad has lowest calories
    EXPECT_EQ(heap->size, 2); // Size should not change
    
    heap_destroy(heap);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test heap full condition
 */
TEST(HeapTest, HeapFull) {
    Heap* heap = heap_create(3);
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Salad", "Lunch", 200, 10);
    Recipe* r3 = recipe_create(3, "Burger", "Lunch", 600, 30);
    
    heap_insert(heap, r1);
    heap_insert(heap, r2);
    heap_insert(heap, r3);
    
    EXPECT_TRUE(heap_is_full(heap));
    EXPECT_FALSE(heap_is_empty(heap));
    
    heap_destroy(heap);
    recipe_destroy(r1);
    recipe_destroy(r2);
    recipe_destroy(r3);
}

// ============================================================================
// GRAPH TESTS (BFS/DFS)
// ============================================================================

/**
 * @brief Test graph creation
 */
TEST(GraphTest, CreateGraph) {
    Graph* graph = graph_create();
    ASSERT_NE(graph, nullptr);
    EXPECT_EQ(graph->vertex_count, 0);
    graph_destroy(graph);
}

/**
 * @brief Test adding vertices and edges
 */
TEST(GraphTest, AddVertexEdge) {
    Graph* graph = graph_create();
    
    EXPECT_EQ(graph_add_vertex(graph, 1), 1);
    EXPECT_EQ(graph_add_vertex(graph, 2), 1);
    EXPECT_EQ(graph_add_vertex(graph, 3), 1);
    EXPECT_EQ(graph->vertex_count, 3);
    
    EXPECT_EQ(graph_add_edge(graph, 1, 2, "dough"), 1);
    EXPECT_EQ(graph_add_edge(graph, 2, 3, "sauce"), 1);
    
    GraphVertex* v = graph_find_vertex(graph, 1);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->recipe_id, 1);
    
    graph_destroy(graph);
}

/**
 * @brief Test BFS traversal
 */
TEST(GraphTest, BFSTraversal) {
    Graph* graph = graph_create();
    
    graph_add_vertex(graph, 1);
    graph_add_vertex(graph, 2);
    graph_add_vertex(graph, 3);
    graph_add_vertex(graph, 4);
    
    graph_add_edge(graph, 1, 2, "edge1");
    graph_add_edge(graph, 1, 3, "edge2");
    graph_add_edge(graph, 2, 4, "edge3");
    
    g_visited_order.clear();
    graph_bfs(graph, 1, graph_visit_func);
    
    // BFS should visit vertices level by level
    EXPECT_GE(g_visited_order.size(), 1);
    EXPECT_EQ(g_visited_order[0], 1); // Start vertex
    
    graph_destroy(graph);
}

/**
 * @brief Test DFS traversal
 */
TEST(GraphTest, DFSTraversal) {
    Graph* graph = graph_create();
    
    graph_add_vertex(graph, 1);
    graph_add_vertex(graph, 2);
    graph_add_vertex(graph, 3);
    
    graph_add_edge(graph, 1, 2, "edge1");
    graph_add_edge(graph, 2, 3, "edge2");
    
    g_visited_order.clear();
    graph_dfs(graph, 1, graph_visit_func);
    
    // DFS should visit vertices depth-first
    EXPECT_GE(g_visited_order.size(), 1);
    EXPECT_EQ(g_visited_order[0], 1); // Start vertex
    
    graph_destroy(graph);
}

/**
 * @brief Test cycle detection
 */
TEST(GraphTest, CycleDetection) {
    Graph* graph = graph_create();
    
    graph_add_vertex(graph, 1);
    graph_add_vertex(graph, 2);
    graph_add_vertex(graph, 3);
    
    graph_add_edge(graph, 1, 2, "edge1");
    graph_add_edge(graph, 2, 3, "edge2");
    // No cycle - should return 0
    EXPECT_EQ(graph_has_cycle(graph), 0);
    
    // Add cycle
    graph_add_edge(graph, 3, 1, "edge3");
    EXPECT_EQ(graph_has_cycle(graph), 1);
    
    graph_destroy(graph);
}

/**
 * @brief Test binary file operations for graph
 */
TEST(GraphTest, BinaryFileOperations) {
    Graph* graph = graph_create();
    
    graph_add_vertex(graph, 1);
    graph_add_vertex(graph, 2);
    graph_add_edge(graph, 1, 2, "dough");
    
    const char* filename = "test_graph.bin";
    EXPECT_EQ(graph_save_binary(graph, filename), 1);
    
    Graph* loaded = graph_load_binary(filename);
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(loaded->vertex_count, 2);
    
    GraphVertex* v = graph_find_vertex(loaded, 1);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->recipe_id, 1);
    
    remove(filename);
    graph_destroy(graph);
    graph_destroy(loaded);
}

/**
 * @brief Test graph reset visited
 */
TEST(GraphTest, ResetVisited) {
    Graph* graph = graph_create();
    
    graph_add_vertex(graph, 1);
    graph_add_vertex(graph, 2);
    graph_add_edge(graph, 1, 2, "edge1");
    
    GraphVertex* v1 = graph_find_vertex(graph, 1);
    GraphVertex* v2 = graph_find_vertex(graph, 2);
    
    v1->visited = 1;
    v2->visited = 1;
    
    graph_reset_visited(graph);
    
    EXPECT_EQ(v1->visited, 0);
    EXPECT_EQ(v2->visited, 0);
    
    graph_destroy(graph);
}

/**
 * @brief Test graph display dependencies
 */
TEST(GraphTest, DisplayDependencies) {
    Graph* graph = graph_create();
    
    graph_add_vertex(graph, 1);
    graph_add_vertex(graph, 2);
    graph_add_vertex(graph, 3);
    graph_add_edge(graph, 1, 2, "dough");
    graph_add_edge(graph, 2, 3, "sauce");
    
    // Display should not crash
    graph_display_dependencies(graph, 1, 0);
    
    graph_destroy(graph);
}

// ============================================================================
// HASH TABLE TESTS
// ============================================================================

/**
 * @brief Test hash table creation
 */
TEST(HashTableTest, CreateHashTable) {
    HashTable* ht = hash_table_create(10);
    ASSERT_NE(ht, nullptr);
    EXPECT_EQ(ht->size, 10);
    EXPECT_EQ(ht->count, 0);
    hash_table_destroy(ht);
}

/**
 * @brief Test insert and search operations
 */
TEST(HashTableTest, InsertSearch) {
    HashTable* ht = hash_table_create(10);
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    EXPECT_EQ(hash_table_insert(ht, r1), 1);
    EXPECT_EQ(hash_table_insert(ht, r2), 1);
    EXPECT_EQ(ht->count, 2);
    
    Recipe* found = hash_table_search(ht, 1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->id, 1);
    EXPECT_STREQ(found->name, "Pizza");
    
    found = hash_table_search(ht, 2);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->id, 2);
    
    found = hash_table_search(ht, 999);
    EXPECT_EQ(found, nullptr); // Not found
    
    hash_table_destroy(ht);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test delete operation
 */
TEST(HashTableTest, Delete) {
    HashTable* ht = hash_table_create(10);
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    hash_table_insert(ht, r1);
    hash_table_insert(ht, r2);
    
    EXPECT_EQ(hash_table_delete(ht, 1), 1);
    EXPECT_EQ(ht->count, 1);
    
    Recipe* found = hash_table_search(ht, 1);
    EXPECT_EQ(found, nullptr); // Should be deleted
    
    found = hash_table_search(ht, 2);
    ASSERT_NE(found, nullptr); // Should still exist
    EXPECT_EQ(found->id, 2);
    
    hash_table_destroy(ht);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test collision handling
 */
TEST(HashTableTest, CollisionHandling) {
    HashTable* ht = hash_table_create(5); // Small size to force collisions
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    Recipe* r3 = recipe_create(3, "Salad", "Lunch", 200, 10);
    
    // All should insert successfully even with collisions
    EXPECT_EQ(hash_table_insert(ht, r1), 1);
    EXPECT_EQ(hash_table_insert(ht, r2), 1);
    EXPECT_EQ(hash_table_insert(ht, r3), 1);
    
    // All should be searchable
    EXPECT_NE(hash_table_search(ht, 1), nullptr);
    EXPECT_NE(hash_table_search(ht, 2), nullptr);
    EXPECT_NE(hash_table_search(ht, 3), nullptr);
    
    hash_table_destroy(ht);
    recipe_destroy(r1);
    recipe_destroy(r2);
    recipe_destroy(r3);
}

/**
 * @brief Test binary file operations for hash table
 */
TEST(HashTableTest, BinaryFileOperations) {
    HashTable* ht = hash_table_create(10);
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    hash_table_insert(ht, r1);
    hash_table_insert(ht, r2);
    
    const char* filename = "test_hash_table.bin";
    EXPECT_EQ(hash_table_save_binary(ht, filename), 1);
    
    HashTable* loaded = hash_table_load_binary(filename);
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(loaded->count, 2);
    
    Recipe* found = hash_table_search(loaded, 1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->id, 1);
    
    remove(filename);
    hash_table_destroy(ht);
    hash_table_destroy(loaded);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

/**
 * @brief Test hash table display function
 */
TEST(HashTableTest, DisplayHashTable) {
    HashTable* ht = hash_table_create(10);
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    Recipe* r2 = recipe_create(2, "Burger", "Lunch", 600, 30);
    
    hash_table_insert(ht, r1);
    hash_table_insert(ht, r2);
    
    // Display should not crash
    hash_table_display(ht);
    
    hash_table_destroy(ht);
    recipe_destroy(r1);
    recipe_destroy(r2);
}

// ============================================================================
// MENU/CONTEXT TESTS
// ============================================================================

/**
 * @brief Test application context creation
 */
TEST(MenuTest, CreateContext) {
    AppContext* ctx = app_context_create();
    ASSERT_NE(ctx, nullptr);
    EXPECT_NE(ctx->hash_table, nullptr);
    EXPECT_NE(ctx->list, nullptr);
    EXPECT_NE(ctx->stack, nullptr);
    EXPECT_NE(ctx->queue, nullptr);
    EXPECT_NE(ctx->graph, nullptr);
    EXPECT_NE(ctx->sparse_matrix, nullptr);
    EXPECT_EQ(ctx->next_recipe_id, 1);
    
    app_context_destroy(ctx);
}

/**
 * @brief Test menu load sample data
 */
TEST(MenuTest, LoadSampleData) {
    AppContext* ctx = app_context_create();
    ASSERT_NE(ctx, nullptr);
    
    menu_load_sample_data(ctx);
    
    // Sample data should be loaded
    EXPECT_GT(list_size(ctx->list), 0);
    
    app_context_destroy(ctx);
}

/**
 * @brief Test menu context binary operations
 */
TEST(MenuTest, ContextBinaryFileOperations) {
    AppContext* ctx = app_context_create();
    ASSERT_NE(ctx, nullptr);
    
    Recipe* r1 = recipe_create(1, "Pizza", "Lunch", 800, 45);
    hash_table_insert(ctx->hash_table, r1);
    list_insert_tail(ctx->list, r1);
    
    const char* filename = "test_context.bin";
    EXPECT_EQ(menu_save_context_binary(ctx, filename), 1);
    
    AppContext* loaded = menu_load_context_binary(filename);
    ASSERT_NE(loaded, nullptr);
    EXPECT_EQ(loaded->next_recipe_id, ctx->next_recipe_id);
    
    remove(filename);
    app_context_destroy(ctx);
    app_context_destroy(loaded);
    recipe_destroy(r1);
}

