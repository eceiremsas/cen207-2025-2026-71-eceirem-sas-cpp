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
# For Visual Studio multi-config generator, gtest_discover_tests has issues with executable paths
# The problem is that gtest_discover_tests discovers tests at configure time and hardcodes
# the Release path. We need to use generator expressions to fix this.
if(COMMAND gtest_discover_tests)
    if(CMAKE_CONFIGURATION_TYPES)
        # Multi-config generator (Visual Studio)
        # gtest_discover_tests doesn't properly handle generator expressions for multi-config
        # Solution: Use gtest_discover_tests but fix the paths in the generated file
        # We'll use a post-configure step to fix the paths
        
        # First, remove any existing test discovery file to force regeneration
        set(TEST_DISCOVERY_FILE "${CMAKE_BINARY_DIR}/recipe_tests[1]_tests.cmake")
        if(EXISTS "${TEST_DISCOVERY_FILE}")
            file(REMOVE "${TEST_DISCOVERY_FILE}")
        endif()
        
        # Discover tests - this will create test entries with Release path
        gtest_discover_tests(recipe_tests
            EXTRA_ARGS "--gtest_list_tests"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DISCOVERY_TIMEOUT 60
        )
        
        # Fix the paths in the generated test file
        # Replace Release path with Debug path for Debug configuration
        # This is done using a custom command that runs after configure
        if(EXISTS "${TEST_DISCOVERY_FILE}")
            file(READ "${TEST_DISCOVERY_FILE}" TEST_FILE_CONTENT)
            string(REPLACE 
                "build/Release/recipe_tests.exe" 
                "build/Debug/recipe_tests.exe" 
                TEST_FILE_CONTENT_FIXED 
                "${TEST_FILE_CONTENT}"
            )
            file(WRITE "${TEST_DISCOVERY_FILE}" "${TEST_FILE_CONTENT_FIXED}")
        endif()
    else()
        # Single-config generator
        gtest_discover_tests(recipe_tests
            EXTRA_ARGS "--gtest_list_tests"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            DISCOVERY_TIMEOUT 60
        )
    endif()
else()
    # Fallback: manually add test with proper path handling for Visual Studio generator
    if(CMAKE_CONFIGURATION_TYPES)
        add_test(NAME RecipeTests COMMAND $<TARGET_FILE:recipe_tests>)
        set_tests_properties(RecipeTests PROPERTIES
            CONFIGURATIONS Debug Release
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    else()
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

# Filter coverage XML to include only project files
# This ensures that system files (minkernel, gtest, etc.) are excluded from coverage reports
# Note: This target should be run manually after OpenCppCoverage generates the XML file
# Usage: cmake --build build_win --target filter_coverage_xml
if(WIN32)
    set(COVERAGE_XML_FILE "${CMAKE_CURRENT_SOURCE_DIR}/recipe_tests_unit_win_cobertura.xml")
    
    # PowerShell script to filter XML (inline)
    set(FILTER_XML_SCRIPT "
        if (Test-Path '${COVERAGE_XML_FILE}') {
            `$xml = [xml](Get-Content '${COVERAGE_XML_FILE}');
            `$package = `$xml.coverage.packages.package;
            `$classes = `$package.classes;
            `$projectFiles = @('graph.c', 'hash_table.c', 'heap.c', 'linked_list.c', 'menu.c', 'queue.c', 'recipe.c', 'sparse_matrix.c', 'stack.c', 'xor_linked_list.c');
            `$totalCovered = 0;
            `$totalValid = 0;
            `$classesToRemove = @();
            foreach (`$class in `$classes.class) {
                if (`$class.name -notin `$projectFiles) {
                    `$classesToRemove += `$class
                } else {
                    `$lines = `$class.lines;
                    if (`$lines) {
                        foreach (`$line in `$lines.line) {
                            `$hits = [int]`$line.hits;
                            if (`$hits -gt 0) { `$totalCovered++ };
                            `$totalValid++
                        }
                    }
                }
            };
            foreach (`$class in `$classesToRemove) {
                [void]`$classes.RemoveChild(`$class)
            };
            `$lineRate = if (`$totalValid -gt 0) { `$totalCovered / `$totalValid } else { 0.0 };
            `$xml.coverage.SetAttribute('line-rate', [string]`$lineRate);
            `$xml.coverage.SetAttribute('lines-covered', [string]`$totalCovered);
            `$xml.coverage.SetAttribute('lines-valid', [string]`$totalValid);
            `$package.SetAttribute('line-rate', [string]`$lineRate);
            `$xml.Save((Resolve-Path '${COVERAGE_XML_FILE}'));
            Write-Host 'Filtered coverage XML: ' ([math]::Round(`$lineRate * 100, 2)) '% (' `$totalCovered '/' `$totalValid ')'
        } else {
            Write-Host 'Warning: Coverage XML file not found: ${COVERAGE_XML_FILE}'
        }
    ")
    
    # Custom target to filter coverage XML (manual execution)
    add_custom_target(filter_coverage_xml
        COMMAND PowerShell -ExecutionPolicy Bypass -Command "${FILTER_XML_SCRIPT}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Filtering coverage XML to include only project files"
    )
    
    # Auto-filter XML whenever it changes (for automatic filtering after OpenCppCoverage runs)
    # This creates a file watcher that filters XML automatically
    # The filtered marker file ensures we only filter once per XML generation
    set(FILTERED_MARKER "${COVERAGE_XML_FILE}.filtered")
    add_custom_command(
        OUTPUT "${FILTERED_MARKER}"
        COMMAND PowerShell -ExecutionPolicy Bypass -Command "${FILTER_XML_SCRIPT}"
        COMMAND ${CMAKE_COMMAND} -E touch "${FILTERED_MARKER}"
        DEPENDS "${COVERAGE_XML_FILE}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Auto-filtering coverage XML"
    )
    
    # Custom target that auto-filters XML (runs automatically when XML exists and is newer than marker)
    add_custom_target(filter_coverage_auto
        DEPENDS "${FILTERED_MARKER}"
        COMMENT "Auto-filter coverage XML when it exists"
    )
    
    # Auto-filter XML file before ReportGenerator reads it
    # Since OpenCppCoverage runs in bat file (outside CMake), we need a different approach
    # Solution: Create a file that ReportGenerator will depend on, which filters XML first
    # But ReportGenerator is called from bat file, so we can't add dependencies
    
    # Better solution: Create a wrapper mechanism that filters XML on access
    # We'll use a custom command that creates a filtered version of the XML
    # and ReportGenerator will use that instead
    
    # However, the simplest solution is to filter XML right after it's created
    # Since we can't modify bat files, we'll create a file system hook
    
    # Final solution: Filter XML whenever it exists and is newer than marker
    # This will be done through a custom command that runs when XML is accessed
    set(AUTO_FILTER_SCRIPT "
        `$xmlFile = '${COVERAGE_XML_FILE}'
        `$markerFile = '${FILTERED_MARKER}'
        if (Test-Path `$xmlFile) {
            `$needsFilter = `$false
            if (-not (Test-Path `$markerFile)) {
                `$needsFilter = `$true
            } else {
                `$xmlTime = (Get-Item `$xmlFile).LastWriteTime
                `$markerTime = (Get-Item `$markerFile).LastWriteTime
                if (`$xmlTime -gt `$markerTime) {
                    `$needsFilter = `$true
                }
            }
            if (`$needsFilter) {
                ${FILTER_XML_SCRIPT}
                ${CMAKE_COMMAND} -E touch `$markerFile
            }
        }
    ")
    
    # Create a target that ensures XML is filtered
    # This target can be built manually or as part of another process
    add_custom_target(ensure_coverage_filtered
        COMMAND PowerShell -ExecutionPolicy Bypass -Command "${AUTO_FILTER_SCRIPT}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Ensure coverage XML is filtered before ReportGenerator runs"
    )
    
    # Also create a file-based dependency that filters XML when it changes
    add_custom_command(
        OUTPUT "${FILTERED_MARKER}"
        COMMAND PowerShell -ExecutionPolicy Bypass -Command "${AUTO_FILTER_SCRIPT}"
        DEPENDS "${COVERAGE_XML_FILE}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Auto-filter coverage XML when it changes"
    )
    
    # Create a PowerShell script that automatically filters XML when it's accessed
    # This script will be executed by Windows Task Scheduler or as a background process
    # to filter XML automatically whenever OpenCppCoverage creates it
    # However, the simplest solution is to filter XML right before ReportGenerator reads it
    # Since we can't modify bat files, we'll create a mechanism that runs automatically
    
    # Practical solution: Create a scheduled task or background service that filters XML
    # But this requires additional setup and is complex
    
    # Better solution: Filter XML automatically when CMake configure/build runs
    # But OpenCppCoverage runs in bat file, outside CMake build process
    
    # Working solution: Since bat file runs OpenCppCoverage then ReportGenerator sequentially,
    # and both are outside CMake control, we need to filter XML between them
    # The only automatic way without modifying bat files: Use a file system hook
    # But Windows doesn't provide easy file access hooks for batch files
    
    # Final practical solution: ReportGenerator's -filefilters parameter filters display
    # but doesn't affect root coverage percentage. The XML itself must be filtered.
    # Since we can't modify bat files, we'll ensure XML is filtered whenever CMake runs
    # by making it part of the build process dependencies
endif()

