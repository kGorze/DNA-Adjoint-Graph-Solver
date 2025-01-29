cmake_minimum_required(VERSION 3.29)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

# Dodaj bibliotekę dla wspólnego kodu
add_library(graph_lib STATIC
    graph.cpp
    test_graph.cpp
)

# Główny program (zawiera też testy)
add_executable(untitled main.cpp)
target_link_libraries(untitled PRIVATE graph_lib)
