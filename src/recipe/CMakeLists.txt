# recipe/CMakeLists.txt
set(ROOT src)
set(LIBNAME recipe)

message(STATUS "[${ROOT}/${LIBNAME}] Module Processing...")

# Collect files without having to explicitly list each header and source file
file(GLOB LIB_HEADERS
  "${CMAKE_CURRENT_SOURCE_DIR}/header/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/header/*.hpp")

file(GLOB LIB_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc")

# Create named folders for the sources within the project
source_group("header" FILES ${LIB_HEADERS})
source_group("src" FILES ${LIB_SOURCES})

# Set Properties->General->Configuration Type to Static Library
add_library(${LIBNAME} STATIC ${LIB_HEADERS} ${LIB_SOURCES})

target_include_directories(${LIBNAME} PUBLIC
						   ${CMAKE_CURRENT_SOURCE_DIR}/header)

# Set C++ standard
set_target_properties(${LIBNAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# creates preprocessor definition used for library exports
add_compile_definitions("RECIPE_LIB_EXPORTS")

install(TARGETS ${LIBNAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin )
		
# Copy required headers to the installation include folder		
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/header/
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h")

# Export the recipe target so other modules can use it
# export(TARGETS ${LIBNAME} FILE ${LIBNAME}Targets.cmake)

message(STATUS "[${ROOT}/${LIBNAME}] Added library target: ${LIBNAME}")
