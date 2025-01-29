#ifndef TEST_GRAPH_H
#define TEST_GRAPH_H

#include <string>
#include "graph.h"

class TestGraph {
private:
    static void createTestFile(const std::string& filename, const std::string& content);
    static void assertGraphEquals(const Graph& expected, const Graph& actual);
    static void cleanup();

public:
    static void testFileIO();
    static void testSuccessors();
    static void testIsAdjointGraph();
    static void testIsOneGraph();
    static void testLinearStructures();
    static void runAllTests();
};

#endif // TEST_GRAPH_H 