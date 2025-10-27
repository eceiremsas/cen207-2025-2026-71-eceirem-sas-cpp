cmake_minimum_required(VERSION 3.10)
project(kalori_hesabi C)

set(CMAKE_C_STANDARD 99)

# Kaynak dosyalar (src klasörü altındaki tüm .c dosyaları)
set(SOURCES
    src/main.c
    src/menu.c
    src/stack.c
    src/queue.c
    src/graph.c
    src/sparse_matrix.c
    src/hash_table.c
    src/linked_list.c
    src/heap.c
    src/recipe.c
)

# Ana program için derleme hedefi
add_executable(kalori_hesabi ${SOURCES})

# Test dosyası için ayrı executable
add_executable(test_recipes
    src/tests/test_recipes.c
    src/recipe.c
    src/hash_table.c
    src/linked_list.c
)
