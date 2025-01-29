#ifndef GRAPH_H
#define GRAPH_H

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
#include <string>

class Graph {
private:
    int numVertices;
    std::vector<std::vector<int>> adjacencyList;

    // Private helper methods
    bool hasEdge(int from, int to) const;
    void addEdge(int from, int to);
    void clear();

public:
    // Constructors and destructor
    Graph();
    explicit Graph(int vertices);
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    ~Graph() = default;

    // Getters
    int getNumVertices() const { return numVertices; }
    std::set<int> getNeighbors(int vertex) const;

    // File operations
    bool readGraphFromFile(const std::string& filename);
    bool writeGraphToFile(const std::string& filename) const;
    bool writeGraphToDotFile(const std::string& filename) const;
    bool visualizeGraph(const std::string& dotFilename, const std::string& outputImage) const;

    // Graph properties
    std::set<int> successors(int vertex) const;
    bool isAdjointGraph() const;
    bool isLinearGraph() const;
    bool isOneGraph() const;
    
    // Structure detection
    bool hasFirstStructure() const;
    bool hasSecondStructure() const;
    bool hasThirdStructure() const;
    
    // Graph transformations
    Graph transformToOriginalGraph() const;
    
    // Display
    void displayGraph() const;
};

#endif // GRAPH_H 