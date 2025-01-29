// main.cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>  
#include <algorithm>
#include <functional>
#include <queue>
#include <map>
#include <cstdlib>  
#include "graph.h"
#include "test_graph.h"  // Zmienione z test_graph.cpp na test_graph.h

int main()
{
    // Flag for running tests
    const bool run_tests = false;  // Set to true to run tests

    if (run_tests) {
        TestGraph::runAllTests();
        return 0;
    }

    // Main program
    Graph g;
    g.readGraphFromFile("input.txt");
    std::cout << "Input graph G:" << std::endl;
    g.displayGraph();

    g.writeGraphToDotFile("input_graph.dot");
    g.visualizeGraph("input_graph.dot", "input_graph.png");
    std::cout << "Input graph has been saved to 'input_graph.png'." << std::endl;

    if (g.isAdjointGraph())
    {
        std::cout << "The graph is an adjoint graph." << std::endl;

        if (g.isLinearGraph())
        {
            std::cout << "The graph is a line graph (verified through structures)." << std::endl;
        }
        else
        {
            std::cout << "The graph is not a line graph (verified through structures)." << std::endl;
        }

        Graph H = g.transformToOriginalGraph();
        std::cout << "Original graph H after transformation:" << std::endl;
        H.displayGraph();

        if (H.isOneGraph())
        {
            std::cout << "Graph H is a 1-graph (no multiple edges)." << std::endl;
            std::cout << "Graph G is a line graph (verified through graph H)." << std::endl;
        }
        else
        {
            std::cout << "Graph H is not a 1-graph (multiple edges exist)." << std::endl;
            std::cout << "Graph G is not a line graph (verified through graph H)." << std::endl;
        }

        H.writeGraphToFile("output.txt");
        std::cout << "Graph H has been saved to file 'output.txt'." << std::endl;

        H.writeGraphToDotFile("output_graph.dot");
        H.visualizeGraph("output_graph.dot", "output_graph.png");
        std::cout << "Graph H has been saved to 'output_graph.png'." << std::endl;
    }
    else
    {
        std::cout << "The graph is not an adjoint graph." << std::endl;
    }

    std::cout << "Specific linear structures (should be false for line graph):" << std::endl;
    std::cout << "hasFirstStructure: " << g.hasFirstStructure() << std::endl;
    std::cout << "hasSecondStructure: " << g.hasSecondStructure() << std::endl;
    std::cout << "hasThirdStructure: " << g.hasThirdStructure() << std::endl;

    return 0;
}
