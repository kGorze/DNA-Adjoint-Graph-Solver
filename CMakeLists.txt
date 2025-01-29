cmake_minimum_required(VERSION 3.29)
project(graph_project VERSION 1.0
        DESCRIPTION "Graph Analysis Project"
        LANGUAGES CXX)

# Set C++ standard for all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing
enable_testing()

# Create library target with source files
add_library(graph_lib STATIC
    graph.cpp
    graph.h
)

# Create test library
add_library(test_lib STATIC
    test_graph.cpp
    test_graph.h
)

# Link test library with main library
target_link_libraries(test_lib PRIVATE graph_lib)

# Create main executable
add_executable(graph_analyzer main.cpp)

# Link main executable with both libraries
target_link_libraries(graph_analyzer 
    PRIVATE 
        graph_lib
        test_lib
)

# Set include directories for targets
target_include_directories(graph_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(test_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add compiler warnings
if(MSVC)
    target_compile_options(graph_lib PRIVATE /W4)
    target_compile_options(test_lib PRIVATE /W4)
    target_compile_options(graph_analyzer PRIVATE /W4)
else()
    target_compile_options(graph_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(test_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(graph_analyzer PRIVATE -Wall -Wextra -Wpedantic)
endif()
