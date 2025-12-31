# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# Project name - Recipe and Nutrition Tracker
project(recipeapp C CXX)

# Set C and C++ standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Print useful information
message(STATUS "[ROOT] CMake version ${CMAKE_VERSION}")
message(STATUS "[ROOT] System ${CMAKE_SYSTEM_NAME}")
message(STATUS "[ROOT] Processor ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "[ROOT] C Standard: ${CMAKE_C_STANDARD}")

# Set the default installation directory
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install" CACHE PATH "Default installation directory" FORCE)
endif()

message(STATUS "[ROOT] Installation folder: ${CMAKE_INSTALL_PREFIX}")

# Enable testing
enable_testing()

# Set build configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Set the output directories for Debug and Release configurations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/build/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/build/Release)

# Custom definitions based on environment
if(MSVC)
  add_definitions(-DMSVC_ENV -D_CRT_SECURE_NO_WARNINGS)
endif()

if(CMAKE_COMPILER_IS_GNUCC)
  add_definitions(-DGCC_ENV)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  add_definitions(-DMAC_ENV)
endif()

# Set Debug and Release configuration flags
if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" MATCHES "Clang")
  message(STATUS "[ROOT] Setting Ubuntu/MacOS C Flags")

  set(COMP_WARNINGS "-Wall -Wextra -Wunused-function -Wno-unknown-pragmas")
  set(COMP_PROFILE "-fprofile-arcs -ftest-coverage")
  set(COMP_OPTIMIZATION "-O0") #for debugging
  set(COMP_SHARED "-shared -fPIC")

  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g ${COMP_OPTIMIZATION} ${COMP_WARNINGS} ${COMP_PROFILE}")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${COMP_WARNINGS} ${COMP_PROFILE}")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${COMP_WARNINGS} ${COMP_PROFILE}")

elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC")
  message(STATUS "[ROOT] Setting Windows C Flags")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
  # Set C++ flags to match C flags for runtime library consistency
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
else()
  message(WARNING "[ROOT] Not supported with the current compiler.")
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add C++ modules (recipe library and recipeapp)
add_subdirectory(src/recipe)
add_subdirectory(src/recipeapp)

# Source files for the C library
set(LIB_SOURCES
    src/recipe.c
    src/linked_list.c
    src/xor_linked_list.c
    src/stack.c
    src/queue.c
    src/hash_table.c
    src/graph.c
    src/heap.c
    src/sparse_matrix.c
    src/menu.c
)

# Source files for the C library (legacy C version)
set(APP_SOURCES
    src/main.c
    ${LIB_SOURCES}
)

# Create the C library (legacy)
add_library(recipe_lib STATIC ${LIB_SOURCES})
target_include_directories(recipe_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Note: C++ executable (recipeapp) is created in src/recipeapp/CMakeLists.txt
# The C version executable is commented out to avoid conflicts
# add_executable(recipeapp_c ${APP_SOURCES})
# target_link_libraries(recipeapp_c recipe_lib)

# Install targets (C++ targets are installed by their respective CMakeLists.txt)
install(TARGETS recipe_lib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# Copy headers to installation include folder
install(FILES ${PROJECT_SOURCE_DIR}/include/recipe.h
              ${PROJECT_SOURCE_DIR}/include/linked_list.h
              ${PROJECT_SOURCE_DIR}/include/xor_linked_list.h
              ${PROJECT_SOURCE_DIR}/include/stack.h
              ${PROJECT_SOURCE_DIR}/include/queue.h
              ${PROJECT_SOURCE_DIR}/include/hash_table.h
              ${PROJECT_SOURCE_DIR}/include/graph.h
              ${PROJECT_SOURCE_DIR}/include/heap.h
              ${PROJECT_SOURCE_DIR}/include/sparse_matrix.h
              ${PROJECT_SOURCE_DIR}/include/menu.h
        DESTINATION include)

# GoogleTest Integration
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Set GoogleTest to use the same runtime library as our code
if(MSVC)
    # Force GoogleTest to use static runtime library to match our C library
    if(TARGET gtest)
        target_compile_options(gtest PRIVATE
            $<$<CONFIG:Debug>:/MTd>
            $<$<CONFIG:Release>:/MT>
        )
    endif()
    if(TARGET gtest_main)
        target_compile_options(gtest_main PRIVATE
            $<$<CONFIG:Debug>:/MTd>
            $<$<CONFIG:Release>:/MT>
        )
    endif()
endif()

# Include GoogleTest CMake module for test discovery (if available)
# GoogleTest module is typically in the googletest source directory
if(EXISTS "${googletest_SOURCE_DIR}/googletest/cmake/GoogleTest.cmake")
    include("${googletest_SOURCE_DIR}/googletest/cmake/GoogleTest.cmake")
else()
    # Fallback: try to find GoogleTest module
    find_package(GTest QUIET)
    if(GTest_FOUND)
        include(GoogleTest)
    endif()
endif()

# Test sources (C++ for GoogleTest compatibility)
set(TEST_SOURCES
    tests/test_recipes.cpp
    tests/test_recipes_cpp.cpp
)

# Create test executable (C++ for GoogleTest)
add_executable(recipe_tests ${TEST_SOURCES})
target_link_libraries(recipe_tests recipe_lib gtest_main gtest)
target_include_directories(recipe_tests PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src/recipe/header
)
set_target_properties(recipe_tests PROPERTIES LINKER_LANGUAGE CXX)
# Set runtime library to match the C library (MTd for Debug, MT for Release)
if(MSVC)
    # Force static runtime library for test executable to match C library
    target_compile_options(recipe_tests PRIVATE
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
endif()

# Add tests to CTest
# Try to use GoogleTest's automatic test discovery if available
if(COMMAND gtest_discover_tests)
    # Use GoogleTest's automatic test discovery (CMake 3.10+ with GoogleTest module)
    # This automatically discovers all GoogleTest tests and registers them with CTest
    gtest_discover_tests(recipe_tests
        EXTRA_ARGS "--gtest_list_tests"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DISCOVERY_TIMEOUT 60
    )
else()
    # Fallback: manually add test with proper path handling for Visual Studio generator
    # For Visual Studio generator, executable paths can be tricky
    if(CMAKE_CONFIGURATION_TYPES)
        # Multi-config generator (Visual Studio)
        # Use generator expression with proper configuration handling
        add_test(NAME RecipeTests COMMAND $<TARGET_FILE:recipe_tests>)
        set_tests_properties(RecipeTests PROPERTIES
            CONFIGURATIONS Debug Release
        )
        # Also set the working directory to ensure tests can find resources
        set_tests_properties(RecipeTests PROPERTIES
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    else()
        # Single-config generator
        add_test(NAME RecipeTests COMMAND recipe_tests)
        set_tests_properties(RecipeTests PROPERTIES
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif()
endif()

# Doxygen Integration
find_package(Doxygen OPTIONAL_COMPONENTS dot)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_LATEX YES)
    set(DOXYGEN_PROJECT_NAME "Recipe and Nutrition Tracker")
    set(DOXYGEN_PROJECT_BRIEF "CEN207 Data Structures Project - Midterm Phase")
    
    doxygen_add_docs(
        doxygen_docs
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/include
        COMMENT "Generate Doxygen documentation"
    )
endif()

