cmake_minimum_required(VERSION 3.10)
project(KaloriHesabi LANGUAGES C)

# C standardı
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Header yolu
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES
    "src/recipe.c"
    "src/main.c"
    "src/menu.c"
    "src/heap.c"
    "src/stack.c"
    "src/queue.c"
    "src/hash_table.c"
    "src/graph.c"
    "src/sparse_matrix.c"
    "src/linked_list.c"
)

# Ana uygulama
add_executable(kalori_hesabi ${SOURCES})

# Test
enable_testing()
add_executable(test_recipes
    tests/test_recipes.c
    src/hash_table.c
    src/linked_list.c
    src/recipe.c
)
add_test(NAME test_recipes COMMAND test_recipes)

# ---- MSVC'yi C moduna ZORLA ----
if (MSVC)
    # Tüm .c dosyalarını C olarak derle
    target_compile_options(kalori_hesabi PRIVATE /TC)
    target_compile_options(test_recipes  PRIVATE /TC)

    # Emniyet için kaynaklara da C dili özelliği ver
    set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE C)
    set_source_files_properties(${CMAKE_SOURCE_DIR}/tests/test_recipes.c PROPERTIES LANGUAGE C)
    set_source_files_properties(${CMAKE_SOURCE_DIR}/src/recipe.c PROPERTIES LANGUAGE C)
endif()

# Çıktı klasörü
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
