#include "test_graph.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

void TestGraph::createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not create test file: " + filename);
    }
    file << content;
}

void TestGraph::cleanup() {
    const std::vector<std::string> testFiles = {
        "test_input.txt", "test_invalid.txt", "test_successors.txt",
        "test_adjoint.txt", "test_non_adjoint.txt", "test_one_graph.txt",
        "test_multiple_edges.txt", "test_first.txt", "test_second.txt",
        "test_third.txt", "test_linear.txt"
    };
    
    for (const auto& file : testFiles) {
        if (std::filesystem::exists(file)) {
            std::filesystem::remove(file);
        }
    }
}

void TestGraph::assertGraphEquals(const Graph& expected, const Graph& actual) {
    // Capture output to compare graphs
    std::stringstream expectedOutput, actualOutput;
    
    // Redirect cout temporarily
    std::streambuf* oldCout = std::cout.rdbuf(expectedOutput.rdbuf());
    expected.displayGraph();
    std::cout.rdbuf(actualOutput.rdbuf());
    actual.displayGraph();
    std::cout.rdbuf(oldCout);

    assert(expectedOutput.str() == actualOutput.str());
}

void TestGraph::testFileIO() {
    std::cout << "Testing File I/O..." << std::endl;
    
    // Test valid input
    createTestFile("test_input.txt", "3\n1: 2 3\n2: 1 3\n3: 1 2");
    Graph g;
    g.readGraphFromFile("test_input.txt");
    
    // Verify graph structure
    std::set<int> succ1 = g.successors(1);
    assert(succ1.size() == 2);
    assert(succ1.find(2) != succ1.end());
    assert(succ1.find(3) != succ1.end());

    // Test invalid vertex number
    createTestFile("test_invalid.txt", "3\n4: 1 2\n2: 1\n3: 1");
    Graph g2;
    g2.readGraphFromFile("test_invalid.txt");
    assert(g2.successors(1).empty()); // Should be empty due to invalid input

    std::cout << "File I/O tests passed!" << std::endl;
}

void TestGraph::testSuccessors() {
    std::cout << "Testing successors()..." << std::endl;
    
    createTestFile("test_successors.txt", "3\n1: 2 3\n2: 3\n3: 1");
    Graph g;
    g.readGraphFromFile("test_successors.txt");

    // Test normal case
    std::set<int> succ1 = g.successors(1);
    assert(succ1.size() == 2);
    assert(succ1.find(2) != succ1.end());
    assert(succ1.find(3) != succ1.end());

    // Test vertex with one successor
    std::set<int> succ2 = g.successors(2);
    assert(succ2.size() == 1);
    assert(succ2.find(3) != succ2.end());

    // Test invalid vertex
    std::set<int> succ4 = g.successors(4);
    assert(succ4.empty());

    std::cout << "Successors tests passed!" << std::endl;
}

void TestGraph::testIsAdjointGraph() {
    std::cout << "Testing isAdjointGraph()..." << std::endl;

    // Test case 1: Adjoint graph
    // An adjoint graph should have the following properties:
    // 1. Each edge represents a common vertex in the original graph
    // 2. Connected vertices in the adjoint graph represent edges in the original graph
    createTestFile("test_adjoint.txt", 
        "4\n"
        "1: 2\n"     // Edge 1 connects to edge 2
        "2: 1 3\n"   // Edge 2 connects to edges 1 and 3
        "3: 2 4\n"   // Edge 3 connects to edges 2 and 4
        "4: 3\n");   // Edge 4 connects to edge 3
    Graph g1;
    g1.readGraphFromFile("test_adjoint.txt");
    assert(g1.isAdjointGraph());

    // Test case 2: Non-adjoint graph
    // This graph is not adjoint because it forms a cycle
    createTestFile("test_non_adjoint.txt", 
        "3\n"
        "1: 2 3\n"   // Each vertex is connected to others
        "2: 1 3\n"   // This structure cannot be an adjoint graph
        "3: 1 2\n"); // as it would represent invalid edge relationships
    Graph g2;
    g2.readGraphFromFile("test_non_adjoint.txt");
    assert(!g2.isAdjointGraph());

    std::cout << "isAdjointGraph tests passed!" << std::endl;
}

void TestGraph::testIsOneGraph() {
    std::cout << "Testing isOneGraph()..." << std::endl;

    // Test case 1: Graph with no multiple edges
    createTestFile("test_one_graph.txt", "3\n1: 2 3\n2: 1\n3: 1");
    Graph g1;
    g1.readGraphFromFile("test_one_graph.txt");
    assert(g1.isOneGraph());

    // Test case 2: Graph with multiple edges
    createTestFile("test_multiple_edges.txt", "3\n1: 2 2 3\n2: 1\n3: 1");
    Graph g2;
    g2.readGraphFromFile("test_multiple_edges.txt");
    assert(!g2.isOneGraph());

    std::cout << "isOneGraph tests passed!" << std::endl;
}

void TestGraph::testLinearStructures() {
    std::cout << "Testing linear structures..." << std::endl;

    // Test First Structure
    createTestFile("test_first.txt", "4\n1: 2 3\n2: 4\n3: 4\n4: 1");
    Graph g1;
    g1.readGraphFromFile("test_first.txt");
    assert(g1.hasFirstStructure());

    // Test Second Structure
    createTestFile("test_second.txt", "3\n1: 2 3\n2: 1\n3: 1");
    Graph g2;
    g2.readGraphFromFile("test_second.txt");
    assert(g2.hasSecondStructure());

    // Test Third Structure
    createTestFile("test_third.txt", "2\n1: 1 2\n2: 1 2");
    Graph g3;
    g3.readGraphFromFile("test_third.txt");
    assert(g3.hasThirdStructure());

    // Test Linear Graph (no structures)
    createTestFile("test_linear.txt", "3\n1: 2\n2: 3\n3: 1");
    Graph g4;
    g4.readGraphFromFile("test_linear.txt");
    assert(g4.isLinearGraph());

    std::cout << "Linear structures tests passed!" << std::endl;
}

void TestGraph::runAllTests() {
    try {
        testFileIO();
        testSuccessors();
        testIsAdjointGraph();
        testIsOneGraph();
        testLinearStructures();
        std::cout << "All tests passed successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        throw;
    }
    cleanup();
} 