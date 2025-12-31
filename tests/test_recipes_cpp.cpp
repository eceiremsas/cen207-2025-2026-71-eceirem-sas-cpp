/**
 * @file test_recipes_cpp.cpp
 * @brief Comprehensive unit tests for C++ API using GoogleTest
 * @details Tests all C++ classes: Recipe, LinkedList, Stack, Queue, 
 *          Heap, Graph, HashTable, SparseMatrix, AppContext, Menu
 *          All tests run automatically without user interaction
 */

#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <string>

#include "recipe.hpp"
#include "linked_list.hpp"
#include "stack.hpp"
#include "queue.hpp"
#include "heap.hpp"
#include "graph.hpp"
#include "hash_table.hpp"
#include "sparse_matrix.hpp"
#include "menu.hpp"

// ============================================================================
// RECIPE CLASS TESTS
// ============================================================================

TEST(RecipeCppTest, CreateRecipe) {
    auto recipe = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    ASSERT_NE(recipe, nullptr);
    EXPECT_EQ(recipe->getId(), 1);
    EXPECT_EQ(recipe->getName(), "Pizza");
    EXPECT_EQ(recipe->getCategory(), "Lunch");
    EXPECT_EQ(recipe->getCalories(), 800);
    EXPECT_EQ(recipe->getPreparationTime(), 45);
}

TEST(RecipeCppTest, AddIngredient) {
    auto recipe = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    recipe->addIngredient("Flour");
    recipe->addIngredient("Cheese");
    
    const auto& ingredients = recipe->getIngredients();
    EXPECT_EQ(ingredients.size(), 2);
    EXPECT_EQ(ingredients[0], "Flour");
    EXPECT_EQ(ingredients[1], "Cheese");
}

TEST(RecipeCppTest, SetAndGetMethods) {
    auto recipe = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    
    recipe->setName("Margherita Pizza");
    recipe->setCategory("Dinner");
    recipe->setCalories(900);
    recipe->setPreparationTime(50);
    recipe->setInstructions("Mix and bake");
    
    EXPECT_EQ(recipe->getName(), "Margherita Pizza");
    EXPECT_EQ(recipe->getCategory(), "Dinner");
    EXPECT_EQ(recipe->getCalories(), 900);
    EXPECT_EQ(recipe->getPreparationTime(), 50);
    EXPECT_EQ(recipe->getInstructions(), "Mix and bake");
}

TEST(RecipeCppTest, ComparisonOperators) {
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Salad", "Lunch", 200, 10);
    auto r3 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    
    EXPECT_TRUE(*r1 < *r2);  // 800 < 200 is false, wait...
    EXPECT_FALSE(*r1 < *r2); // Actually 800 > 200, so r1 > r2
    EXPECT_TRUE(*r2 < *r1);  // 200 < 800 is true
    EXPECT_TRUE(*r1 > *r2);  // 800 > 200 is true
    EXPECT_TRUE(*r1 == *r3); // Same ID
    EXPECT_FALSE(*r1 == *r2); // Different ID
}

TEST(RecipeCppTest, Clone) {
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    r1->addIngredient("Flour");
    r1->setInstructions("Bake for 20 minutes");
    
    auto r2 = r1->clone();
    ASSERT_NE(r2, nullptr);
    EXPECT_EQ(r2->getId(), r1->getId());
    EXPECT_EQ(r2->getName(), r1->getName());
    EXPECT_EQ(r2->getIngredients().size(), r1->getIngredients().size());
    EXPECT_NE(r1.get(), r2.get()); // Different objects
}

TEST(RecipeCppTest, Display) {
    auto recipe = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    recipe->addIngredient("Flour");
    recipe->setInstructions("Bake for 20 minutes");
    
    // Display should not crash
    recipe->display();
}

// ============================================================================
// LINKED LIST TESTS
// ============================================================================

TEST(LinkedListCppTest, CreateList) {
    LinkedList list;
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListCppTest, InsertHead) {
    LinkedList list;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    
    EXPECT_TRUE(list.insertHead(r1));
    EXPECT_TRUE(list.insertHead(r2));
    EXPECT_EQ(list.size(), 2);
    EXPECT_FALSE(list.isEmpty());
    
    auto found = list.find(2);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getId(), 2);
}

TEST(LinkedListCppTest, InsertTail) {
    LinkedList list;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    
    EXPECT_TRUE(list.insertTail(r1));
    EXPECT_TRUE(list.insertTail(r2));
    EXPECT_EQ(list.size(), 2);
    
    auto found = list.find(1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getId(), 1);
}

TEST(LinkedListCppTest, Remove) {
    LinkedList list;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    
    list.insertHead(r1);
    list.insertHead(r2);
    
    auto removed = list.remove(1);
    ASSERT_NE(removed, nullptr);
    EXPECT_EQ(removed->getId(), 1);
    EXPECT_EQ(list.size(), 1);
    
    auto found = list.find(1);
    EXPECT_EQ(found, nullptr);
}

TEST(LinkedListCppTest, Clear) {
    LinkedList list;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    list.insertHead(r1);
    
    list.clear();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListCppTest, Display) {
    LinkedList list;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    
    list.insertTail(r1);
    list.insertTail(r2);
    
    // Display should not crash
    list.display();
}

// ============================================================================
// STACK TESTS
// ============================================================================

TEST(StackCppTest, CreateStack) {
    Stack stack;
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackCppTest, PushPop) {
    Stack stack;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    
    EXPECT_TRUE(stack.push(OperationType::Add, r1));
    EXPECT_TRUE(stack.push(OperationType::Edit, r2));
    EXPECT_EQ(stack.size(), 2);
    EXPECT_FALSE(stack.isEmpty());
    
    auto op = stack.pop();
    ASSERT_NE(op, nullptr);
    EXPECT_EQ(op->type, OperationType::Edit);
    EXPECT_EQ(op->recipe->getId(), 2);
    
    op = stack.pop();
    ASSERT_NE(op, nullptr);
    EXPECT_EQ(op->type, OperationType::Add);
    EXPECT_EQ(op->recipe->getId(), 1);
    
    EXPECT_TRUE(stack.isEmpty());
}

TEST(StackCppTest, Peek) {
    Stack stack;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    
    stack.push(OperationType::Add, r1);
    
    auto op = stack.peek();
    ASSERT_NE(op, nullptr);
    EXPECT_EQ(op->type, OperationType::Add);
    EXPECT_EQ(stack.size(), 1); // Size should not change
}

TEST(StackCppTest, Clear) {
    Stack stack;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    stack.push(OperationType::Add, r1);
    
    stack.clear();
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 0);
}

// ============================================================================
// QUEUE TESTS
// ============================================================================

TEST(QueueCppTest, CreateQueue) {
    Queue queue;
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueCppTest, EnqueueDequeue) {
    Queue queue;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    
    EXPECT_TRUE(queue.enqueue(r1));
    EXPECT_TRUE(queue.enqueue(r2));
    EXPECT_EQ(queue.size(), 2);
    EXPECT_FALSE(queue.isEmpty());
    
    auto dequeued = queue.dequeue();
    ASSERT_NE(dequeued, nullptr);
    EXPECT_EQ(dequeued->getId(), 1); // FIFO
    EXPECT_EQ(queue.size(), 1);
    
    dequeued = queue.dequeue();
    ASSERT_NE(dequeued, nullptr);
    EXPECT_EQ(dequeued->getId(), 2);
    EXPECT_TRUE(queue.isEmpty());
}

TEST(QueueCppTest, Peek) {
    Queue queue;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    
    queue.enqueue(r1);
    
    auto peeked = queue.peek();
    ASSERT_NE(peeked, nullptr);
    EXPECT_EQ(peeked->getId(), 1);
    EXPECT_EQ(queue.size(), 1); // Size should not change
}

TEST(QueueCppTest, FullQueue) {
    Queue queue;
    auto r = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    
    // Fill queue to capacity
    for (int i = 0; i < WEEKLY_PLAN_SIZE; i++) {
        EXPECT_TRUE(queue.enqueue(r));
    }
    
    EXPECT_TRUE(queue.isFull());
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_EQ(queue.size(), WEEKLY_PLAN_SIZE);
    
    // Try to add one more - should fail
    EXPECT_FALSE(queue.enqueue(r));
}

TEST(QueueCppTest, Clear) {
    Queue queue;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    queue.enqueue(r1);
    
    queue.clear();
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(QueueCppTest, Display) {
    Queue queue;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    
    queue.enqueue(r1);
    queue.enqueue(r2);
    
    // Display should not crash
    queue.display();
}

// ============================================================================
// HEAP TESTS
// ============================================================================

TEST(HeapCppTest, CreateHeap) {
    Heap heap(10);
    EXPECT_TRUE(heap.isEmpty());
    EXPECT_FALSE(heap.isFull());
}

TEST(HeapCppTest, InsertExtractMin) {
    Heap heap(10);
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Salad", "Lunch", 200, 10);
    auto r3 = std::make_shared<Recipe>(3, "Burger", "Lunch", 600, 30);
    
    EXPECT_TRUE(heap.insert(r1));
    EXPECT_TRUE(heap.insert(r2));
    EXPECT_TRUE(heap.insert(r3));
    
    auto min = heap.extractMin();
    ASSERT_NE(min, nullptr);
    EXPECT_EQ(min->getId(), 2); // Salad has lowest calories (200)
    EXPECT_EQ(min->getCalories(), 200);
    
    min = heap.extractMin();
    ASSERT_NE(min, nullptr);
    EXPECT_EQ(min->getId(), 3); // Burger has next lowest (600)
    
    min = heap.extractMin();
    ASSERT_NE(min, nullptr);
    EXPECT_EQ(min->getId(), 1); // Pizza has highest (800)
    
    EXPECT_TRUE(heap.isEmpty());
}

TEST(HeapCppTest, Peek) {
    Heap heap(10);
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Salad", "Lunch", 200, 10);
    
    heap.insert(r1);
    heap.insert(r2);
    
    auto peeked = heap.peek();
    ASSERT_NE(peeked, nullptr);
    EXPECT_EQ(peeked->getId(), 2); // Salad has lowest calories
    EXPECT_EQ(heap.size(), 2); // Size should not change
}

TEST(HeapCppTest, SortRecipes) {
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Salad", "Lunch", 200, 10);
    auto r3 = std::make_shared<Recipe>(3, "Burger", "Lunch", 600, 30);
    
    std::vector<std::shared_ptr<Recipe>> recipes = {r1, r2, r3};
    Heap::sortRecipes(recipes);
    
    // After sorting, recipes should be ordered by calories (ascending)
    EXPECT_EQ(recipes[0]->getId(), 2); // Salad (200)
    EXPECT_EQ(recipes[1]->getId(), 3); // Burger (600)
    EXPECT_EQ(recipes[2]->getId(), 1); // Pizza (800)
}

TEST(HeapCppTest, FullHeap) {
    Heap heap(3);
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Salad", "Lunch", 200, 10);
    auto r3 = std::make_shared<Recipe>(3, "Burger", "Lunch", 600, 30);
    
    heap.insert(r1);
    heap.insert(r2);
    heap.insert(r3);
    
    EXPECT_TRUE(heap.isFull());
    EXPECT_FALSE(heap.isEmpty());
}

// ============================================================================
// GRAPH TESTS
// ============================================================================

TEST(GraphCppTest, CreateGraph) {
    Graph graph;
    EXPECT_EQ(graph.getVertexCount(), 0);
}

TEST(GraphCppTest, AddVertex) {
    Graph graph;
    
    EXPECT_TRUE(graph.addVertex(1));
    EXPECT_TRUE(graph.addVertex(2));
    EXPECT_TRUE(graph.addVertex(3));
    EXPECT_EQ(graph.getVertexCount(), 3);
    
    // Adding same vertex again should return true (already exists)
    EXPECT_TRUE(graph.addVertex(1));
    EXPECT_EQ(graph.getVertexCount(), 3);
}

TEST(GraphCppTest, FindVertex) {
    Graph graph;
    graph.addVertex(1);
    graph.addVertex(2);
    
    auto v1 = graph.findVertex(1);
    ASSERT_NE(v1, nullptr);
    EXPECT_EQ(v1->recipe_id, 1);
    
    auto v2 = graph.findVertex(2);
    ASSERT_NE(v2, nullptr);
    EXPECT_EQ(v2->recipe_id, 2);
    
    auto v3 = graph.findVertex(999);
    EXPECT_EQ(v3, nullptr); // Not found
}

TEST(GraphCppTest, AddEdge) {
    Graph graph;
    
    graph.addVertex(1);
    graph.addVertex(2);
    
    EXPECT_TRUE(graph.addEdge(1, 2, "dough"));
    
    auto v1 = graph.findVertex(1);
    ASSERT_NE(v1, nullptr);
    EXPECT_NE(v1->edges, nullptr);
    EXPECT_EQ(v1->edges->vertex_id, 2);
    EXPECT_EQ(v1->edges->edge_label, "dough");
}

TEST(GraphCppTest, HasCycle) {
    Graph graph;
    
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    
    graph.addEdge(1, 2, "edge1");
    graph.addEdge(2, 3, "edge2");
    // No cycle - should return false
    EXPECT_FALSE(graph.hasCycle());
    
    // Add cycle
    graph.addEdge(3, 1, "edge3");
    EXPECT_TRUE(graph.hasCycle());
}

TEST(GraphCppTest, ResetVisited) {
    Graph graph;
    graph.addVertex(1);
    graph.addVertex(2);
    
    auto v1 = graph.findVertex(1);
    auto v2 = graph.findVertex(2);
    
    v1->visited = true;
    v2->visited = true;
    
    graph.resetVisited();
    
    EXPECT_FALSE(v1->visited);
    EXPECT_FALSE(v2->visited);
}

TEST(GraphCppTest, DisplayDependencies) {
    Graph graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2, "dough");
    graph.addEdge(2, 3, "sauce");
    
    // Display should not crash
    graph.displayDependencies(1, 0);
}

TEST(GraphCppTest, Clear) {
    Graph graph;
    graph.addVertex(1);
    graph.addVertex(2);
    
    graph.clear();
    EXPECT_EQ(graph.getVertexCount(), 0);
}

// ============================================================================
// HASH TABLE TESTS
// ============================================================================

TEST(HashTableCppTest, CreateHashTable) {
    HashTable ht(10);
    EXPECT_EQ(ht.size(), 0);
    EXPECT_TRUE(ht.isEmpty());
}

TEST(HashTableCppTest, InsertSearch) {
    HashTable ht(10);
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    
    EXPECT_TRUE(ht.insert(r1));
    EXPECT_TRUE(ht.insert(r2));
    EXPECT_EQ(ht.size(), 2);
    
    auto found = ht.search(1);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getId(), 1);
    EXPECT_EQ(found->getName(), "Pizza");
    
    found = ht.search(2);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getId(), 2);
    
    found = ht.search(999);
    EXPECT_EQ(found, nullptr); // Not found
}

TEST(HashTableCppTest, Remove) {
    HashTable ht(10);
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    
    ht.insert(r1);
    ht.insert(r2);
    
    EXPECT_TRUE(ht.remove(1));
    EXPECT_EQ(ht.size(), 1);
    
    auto found = ht.search(1);
    EXPECT_EQ(found, nullptr); // Should be deleted
    
    found = ht.search(2);
    ASSERT_NE(found, nullptr); // Should still exist
    EXPECT_EQ(found->getId(), 2);
}

TEST(HashTableCppTest, CollisionHandling) {
    HashTable ht(5); // Small size to force collisions
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    auto r3 = std::make_shared<Recipe>(3, "Salad", "Lunch", 200, 10);
    
    // All should insert successfully even with collisions
    EXPECT_TRUE(ht.insert(r1));
    EXPECT_TRUE(ht.insert(r2));
    EXPECT_TRUE(ht.insert(r3));
    
    // All should be searchable
    EXPECT_NE(ht.search(1), nullptr);
    EXPECT_NE(ht.search(2), nullptr);
    EXPECT_NE(ht.search(3), nullptr);
}

TEST(HashTableCppTest, Clear) {
    HashTable ht(10);
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    ht.insert(r1);
    
    ht.clear();
    EXPECT_EQ(ht.size(), 0);
    EXPECT_TRUE(ht.isEmpty());
}

TEST(HashTableCppTest, Display) {
    HashTable ht(10);
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    
    ht.insert(r1);
    ht.insert(r2);
    
    // Display should not crash
    ht.display();
}

// ============================================================================
// SPARSE MATRIX TESTS
// ============================================================================

TEST(SparseMatrixCppTest, CreateMatrix) {
    SparseMatrix matrix;
    EXPECT_EQ(matrix.getEntryCount(), 0);
}

TEST(SparseMatrixCppTest, AddEntry) {
    SparseMatrix matrix;
    
    matrix.addEntry(0, 0, 5, "Flour");
    matrix.addEntry(0, 1, 3, "Cheese");
    matrix.addEntry(1, 0, 2, "Flour");
    
    EXPECT_EQ(matrix.getValue(0, 0), 5);
    EXPECT_EQ(matrix.getValue(0, 1), 3);
    EXPECT_EQ(matrix.getValue(1, 0), 2);
    EXPECT_EQ(matrix.getValue(1, 1), 0); // Non-existent entry
    EXPECT_EQ(matrix.getEntryCount(), 3);
}

TEST(SparseMatrixCppTest, FindRecipesByIngredient) {
    SparseMatrix matrix;
    
    matrix.addEntry(0, 0, 5, "Flour");
    matrix.addEntry(1, 0, 2, "Flour");
    matrix.addEntry(2, 1, 3, "Cheese");
    
    auto recipeIds = matrix.findRecipesByIngredient("Flour");
    EXPECT_EQ(recipeIds.size(), 2);
    EXPECT_EQ(recipeIds[0], 0);
    EXPECT_EQ(recipeIds[1], 1);
}

TEST(SparseMatrixCppTest, FindIngredientsByRecipe) {
    SparseMatrix matrix;
    
    matrix.addEntry(0, 0, 5, "Flour");
    matrix.addEntry(0, 1, 3, "Cheese");
    matrix.addEntry(1, 0, 2, "Flour");
    
    auto ingredients = matrix.findIngredientsByRecipe(0);
    EXPECT_EQ(ingredients.size(), 2);
    EXPECT_EQ(ingredients[0], "Cheese"); // Last added first (LIFO)
    EXPECT_EQ(ingredients[1], "Flour");
}

TEST(SparseMatrixCppTest, Display) {
    SparseMatrix matrix;
    matrix.addEntry(0, 0, 5, "Flour");
    matrix.addEntry(0, 1, 3, "Cheese");
    
    // Display should not crash
    matrix.display();
}

TEST(SparseMatrixCppTest, Clear) {
    SparseMatrix matrix;
    matrix.addEntry(0, 0, 5, "Flour");
    
    matrix.clear();
    EXPECT_EQ(matrix.getEntryCount(), 0);
}

// ============================================================================
// APP CONTEXT TESTS
// ============================================================================

TEST(AppContextCppTest, CreateContext) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    EXPECT_NE(ctx->hashTable, nullptr);
    EXPECT_NE(ctx->list, nullptr);
    EXPECT_NE(ctx->stack, nullptr);
    EXPECT_NE(ctx->queue, nullptr);
    EXPECT_NE(ctx->graph, nullptr);
    EXPECT_NE(ctx->sparseMatrix, nullptr);
    EXPECT_EQ(ctx->nextRecipeId, 1);
}

TEST(AppContextCppTest, ContextOperations) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    ctx->hashTable->insert(r1);
    ctx->list->insertTail(r1);
    
    EXPECT_EQ(ctx->hashTable->size(), 1);
    EXPECT_EQ(ctx->list->size(), 1);
}

// ============================================================================
// MENU TESTS
// ============================================================================

TEST(MenuCppTest, LoadSampleData) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    Menu::loadSampleData(*ctx);
    
    // Sample data should be loaded
    EXPECT_GT(ctx->list->size(), 0);
    EXPECT_GT(ctx->hashTable->size(), 0);
}

TEST(MenuCppTest, ViewAllRecipes) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    ctx->list->insertTail(r1);
    
    // Should not crash
    Menu::viewAllRecipes(*ctx);
}

TEST(MenuCppTest, HandleChoice) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // Test various menu choices
    Menu::handleChoice(*ctx, 5); // View all recipes
    Menu::handleChoice(*ctx, 6); // Sort by calories
    Menu::handleChoice(*ctx, 7); // Create weekly plan
    Menu::handleChoice(*ctx, 8); // View dependencies
    Menu::handleChoice(*ctx, 9); // Find by ingredient
    Menu::handleChoice(*ctx, 99); // Invalid choice
}

TEST(MenuCppTest, SortByCalories) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Salad", "Lunch", 200, 10);
    ctx->hashTable->insert(r1);
    ctx->hashTable->insert(r2);
    ctx->list->insertTail(r1);
    ctx->list->insertTail(r2);
    
    // Should not crash
    Menu::sortByCalories(*ctx);
}

TEST(MenuCppTest, CreateWeeklyPlan) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // Should not crash
    Menu::createWeeklyPlan(*ctx);
}

TEST(MenuCppTest, ViewDependencies) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    ctx->graph->addVertex(1);
    ctx->graph->addVertex(2);
    ctx->graph->addEdge(1, 2, "dough");
    
    // Should not crash
    Menu::viewDependencies(*ctx);
}

TEST(MenuCppTest, FindByIngredient) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    ctx->sparseMatrix->addEntry(0, 0, 5, "Flour");
    
    // Should not crash
    Menu::findByIngredient(*ctx);
}

TEST(MenuCppTest, UndoLastOperation) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    ctx->stack->push(OperationType::Add, r1);
    
    // Should not crash
    Menu::undoLastOperation(*ctx);
}

TEST(MenuCppTest, AddRecipe) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // Should not crash
    Menu::addRecipe(*ctx);
}

TEST(MenuCppTest, EditRecipe) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // Should not crash
    Menu::editRecipe(*ctx);
}

TEST(MenuCppTest, DeleteRecipe) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // Should not crash
    Menu::deleteRecipe(*ctx);
}

TEST(MenuCppTest, SearchRecipes) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // Should not crash
    Menu::searchRecipes(*ctx);
}

TEST(MenuCppTest, SearchByName) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // Should not crash
    Menu::searchByName(*ctx);
}

TEST(MenuCppTest, SearchByCategory) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // Should not crash
    Menu::searchByCategory(*ctx);
}

TEST(MenuCppTest, SearchByCalorieRange) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // Should not crash
    Menu::searchByCalorieRange(*ctx);
}

TEST(MenuCppTest, SortByCaloriesEmptyList) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // Should handle empty list gracefully
    Menu::sortByCalories(*ctx);
}

TEST(MenuCppTest, DisplayMain) {
    // Should not crash
    Menu::displayMain();
}

TEST(MenuCppTest, ClearConsole) {
    // Should not crash
    Menu::clearConsole();
}

// ============================================================================
// EDGE CASE TESTS
// ============================================================================

TEST(EdgeCaseTest, HashTableNullRecipe) {
    HashTable ht(10);
    EXPECT_FALSE(ht.insert(nullptr));
    EXPECT_EQ(ht.size(), 0);
}

TEST(EdgeCaseTest, LinkedListNullRecipe) {
    LinkedList list;
    EXPECT_FALSE(list.insertHead(nullptr));
    EXPECT_FALSE(list.insertTail(nullptr));
    EXPECT_EQ(list.size(), 0);
}

TEST(EdgeCaseTest, StackNullRecipe) {
    Stack stack;
    EXPECT_FALSE(stack.push(OperationType::Add, nullptr));
    EXPECT_TRUE(stack.isEmpty());
}

TEST(EdgeCaseTest, QueueNullRecipe) {
    Queue queue;
    EXPECT_FALSE(queue.enqueue(nullptr));
    EXPECT_TRUE(queue.isEmpty());
}

TEST(EdgeCaseTest, HeapNullRecipe) {
    Heap heap(10);
    EXPECT_FALSE(heap.insert(nullptr));
    EXPECT_TRUE(heap.isEmpty());
}

TEST(EdgeCaseTest, GraphDuplicateVertex) {
    Graph graph;
    EXPECT_TRUE(graph.addVertex(1));
    EXPECT_TRUE(graph.addVertex(1)); // Should return true (already exists)
    EXPECT_EQ(graph.getVertexCount(), 1);
}

TEST(EdgeCaseTest, GraphEdgeToNonExistentVertex) {
    Graph graph;
    graph.addVertex(1);
    // Adding edge to non-existent vertex should create it
    EXPECT_TRUE(graph.addEdge(1, 2, "edge"));
    EXPECT_EQ(graph.getVertexCount(), 2);
}

TEST(EdgeCaseTest, SparseMatrixEmptySearch) {
    SparseMatrix matrix;
    auto recipes = matrix.findRecipesByIngredient("NonExistent");
    EXPECT_TRUE(recipes.empty());
    
    auto ingredients = matrix.findIngredientsByRecipe(999);
    EXPECT_TRUE(ingredients.empty());
}

TEST(EdgeCaseTest, RecipeMaxIngredients) {
    auto recipe = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    
    // Add maximum ingredients (20)
    for (int i = 0; i < 20; i++) {
        recipe->addIngredient("Ingredient" + std::to_string(i));
    }
    
    EXPECT_EQ(recipe->getIngredients().size(), 20);
    
    // Try to add one more - should be ignored
    recipe->addIngredient("Extra");
    EXPECT_EQ(recipe->getIngredients().size(), 20);
}

TEST(EdgeCaseTest, StackFull) {
    Stack stack;
    auto r = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    
    // Fill stack to capacity
    for (int i = 0; i < UNDO_STACK_SIZE; i++) {
        stack.push(OperationType::Add, r);
    }
    
    EXPECT_TRUE(stack.isFull());
    EXPECT_EQ(stack.size(), UNDO_STACK_SIZE);
    
    // Push one more - should remove oldest
    stack.push(OperationType::Edit, r);
    EXPECT_EQ(stack.size(), UNDO_STACK_SIZE);
}

TEST(EdgeCaseTest, QueueCircular) {
    Queue queue;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Burger", "Lunch", 600, 30);
    
    // Fill queue
    for (int i = 0; i < WEEKLY_PLAN_SIZE; i++) {
        queue.enqueue(r1);
    }
    
    EXPECT_TRUE(queue.isFull());
    
    // Dequeue and enqueue to test circular behavior
    auto d = queue.dequeue();
    EXPECT_NE(d, nullptr);
    EXPECT_TRUE(queue.enqueue(r2));
    EXPECT_EQ(queue.size(), WEEKLY_PLAN_SIZE);
}

TEST(EdgeCaseTest, HeapExtractFromEmpty) {
    Heap heap(10);
    auto min = heap.extractMin();
    EXPECT_EQ(min, nullptr);
    
    auto peeked = heap.peek();
    EXPECT_EQ(peeked, nullptr);
}

TEST(EdgeCaseTest, LinkedListRemoveNonExistent) {
    LinkedList list;
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    list.insertHead(r1);
    
    auto removed = list.remove(999);
    EXPECT_EQ(removed, nullptr);
    EXPECT_EQ(list.size(), 1);
}

TEST(EdgeCaseTest, HashTableRemoveNonExistent) {
    HashTable ht(10);
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    ht.insert(r1);
    
    EXPECT_FALSE(ht.remove(999));
    EXPECT_EQ(ht.size(), 1);
}

TEST(EdgeCaseTest, GraphCycleDetectionNoCycle) {
    Graph graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2, "e1");
    graph.addEdge(2, 3, "e2");
    
    EXPECT_FALSE(graph.hasCycle());
}

TEST(EdgeCaseTest, GraphCycleDetectionSelfLoop) {
    Graph graph;
    graph.addVertex(1);
    graph.addEdge(1, 1, "self");
    
    EXPECT_TRUE(graph.hasCycle());
}

TEST(EdgeCaseTest, AppContextCreateFailure) {
    // This test verifies that create() returns valid context
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // All members should be initialized
    EXPECT_NE(ctx->hashTable, nullptr);
    EXPECT_NE(ctx->list, nullptr);
    EXPECT_NE(ctx->stack, nullptr);
    EXPECT_NE(ctx->queue, nullptr);
    EXPECT_NE(ctx->graph, nullptr);
    EXPECT_NE(ctx->sparseMatrix, nullptr);
}

// ============================================================================
// INTEGRATION TESTS
// ============================================================================

TEST(IntegrationTest, FullWorkflow) {
    auto ctx = AppContext::create();
    ASSERT_NE(ctx, nullptr);
    
    // Create recipes
    auto r1 = std::make_shared<Recipe>(1, "Pizza", "Lunch", 800, 45);
    auto r2 = std::make_shared<Recipe>(2, "Salad", "Lunch", 200, 10);
    
    // Add to hash table
    ctx->hashTable->insert(r1);
    ctx->hashTable->insert(r2);
    
    // Add to linked list
    ctx->list->insertTail(r1);
    ctx->list->insertTail(r2);
    
    // Add to stack (undo)
    ctx->stack->push(OperationType::Add, r1);
    
    // Add to queue (weekly plan)
    ctx->queue->enqueue(r1);
    ctx->queue->enqueue(r2);
    
    // Add to graph
    ctx->graph->addVertex(1);
    ctx->graph->addVertex(2);
    ctx->graph->addEdge(1, 2, "dough");
    
    // Add to sparse matrix
    ctx->sparseMatrix->addEntry(1, 0, 1, "Flour");
    ctx->sparseMatrix->addEntry(2, 0, 1, "Lettuce");
    
    // Verify all structures
    EXPECT_EQ(ctx->hashTable->size(), 2);
    EXPECT_EQ(ctx->list->size(), 2);
    EXPECT_EQ(ctx->stack->size(), 1);
    EXPECT_EQ(ctx->queue->size(), 2);
    EXPECT_EQ(ctx->graph->getVertexCount(), 2);
    EXPECT_EQ(ctx->sparseMatrix->getEntryCount(), 2);
}

