#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

// Constructors
Graph::Graph() : numVertices(0) {}

Graph::Graph(int vertices) : numVertices(vertices) {
    if (vertices < 0) {
        throw std::invalid_argument("Number of vertices cannot be negative");
    }
    adjacencyList.resize(vertices + 1);
}

Graph::Graph(const Graph& other) : numVertices(other.numVertices), 
                                 adjacencyList(other.adjacencyList) {}

Graph& Graph::operator=(const Graph& other) {
    if (this != &other) {
        numVertices = other.numVertices;
        adjacencyList = other.adjacencyList;
    }
    return *this;
}

// Private helper methods
bool Graph::hasEdge(int from, int to) const {
    if (from < 1 || from > numVertices || to < 1 || to > numVertices) {
        return false;
    }
    return std::find(adjacencyList[from].begin(), 
                    adjacencyList[from].end(), to) != adjacencyList[from].end();
}

void Graph::addEdge(int from, int to) {
    if (from < 1 || from > numVertices || to < 1 || to > numVertices) {
        throw std::out_of_range("Vertex index out of range");
    }
    adjacencyList[from].push_back(to);
}

void Graph::clear() {
    numVertices = 0;
    adjacencyList.clear();
}

// File operations
bool Graph::readGraphFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    clear();
    infile >> numVertices;
    if (numVertices <= 0) {
        std::cerr << "Error: Invalid number of vertices" << std::endl;
        return false;
    }

    adjacencyList.resize(numVertices + 1);
    std::string line;
    std::getline(infile, line); // Skip the rest of the first line

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int vertex;
        char colon;
        iss >> vertex >> colon;
        
        if (vertex < 1 || vertex > numVertices) {
            std::cerr << "Error: Invalid vertex " << vertex << std::endl;
            clear();
            return false;
        }

        int neighbor;
        while (iss >> neighbor) {
            if (neighbor < 1 || neighbor > numVertices) {
                std::cerr << "Error: Invalid neighbor " << neighbor << std::endl;
                clear();
                return false;
            }
            addEdge(vertex, neighbor);
        }
    }

    return true;
}

std::set<int> Graph::successors(int vertex) const
{
    std::set<int> succ;
    if (vertex >= 1 && vertex <= numVertices)
    {
        for (int neighbor : adjacencyList[vertex])
        {
            succ.insert(neighbor);
        }
    }   
    return succ;
}

bool Graph::isOneGraph() const
{
    for (int u = 1; u <= numVertices; ++u)
    {
        std::set<int> neighborSet(adjacencyList[u].begin(), adjacencyList[u].end());
        if (neighborSet.size() != adjacencyList[u].size())
        {
            return false;
        }
    }
    return true;
}

bool Graph::writeGraphToFile(const std::string& filename) const {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Blad podczas otwierania pliku do zapisu" << std::endl;
        return false;
    }

    outfile << numVertices << std::endl;
    for (int i = 1; i <= numVertices; ++i) {
        outfile << i << ":";
        for (int neighbor : adjacencyList[i]) {
            outfile << " " << neighbor;
        }
        outfile << std::endl;
    }
    return true;
}

bool Graph::writeGraphToDotFile(const std::string& filename) const {
    std::ofstream outfile(filename);
    if (!outfile) {
        std::cerr << "Blad podczas otwierania pliku do zapisu" << std::endl;
        return false;
    }

    outfile << "graph G {" << std::endl;
    for (int i = 1; i <= numVertices; ++i) {
        for (int neighbor : adjacencyList[i]) {
            if (i < neighbor) { // Unikamy duplikacji krawędzi
                outfile << "    " << i << " -- " << neighbor << ";" << std::endl;
            }
        }
    }
    outfile << "}" << std::endl;
    return true;
}

bool Graph::visualizeGraph(const std::string& dotFilename, const std::string& outputImage) const {
    std::string command = "dot -Tpng " + dotFilename + " -o " + outputImage;
    int result = std::system(command.c_str());
    return result == 0;
}

void Graph::displayGraph() const
{
    for (int i = 1; i <= numVertices; i++)
    {
        std::cout << i << ": ";
        for (auto j : adjacencyList[i])
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

bool Graph::isAdjointGraph() const {
    // Sprawdź czy każdy wierzchołek ma tych samych sąsiadów co jego sąsiedzi
    for (int v = 1; v <= numVertices; ++v) {
        std::set<int> vNeighbors(adjacencyList[v].begin(), adjacencyList[v].end());
        
        for (int u : adjacencyList[v]) {
            std::set<int> uNeighbors(adjacencyList[u].begin(), adjacencyList[u].end());
            if (vNeighbors != uNeighbors) {
                return false;
            }
        }
    }
    return true;
}

bool Graph::isLinearGraph() const {
    return !hasFirstStructure() && !hasSecondStructure() && !hasThirdStructure();
}

Graph Graph::transformToOriginalGraph() const {
    Graph H;
    H.numVertices = numVertices;
    H.adjacencyList.resize(numVertices + 1);
    
    // Implementacja transformacji grafu sprzężonego do oryginalnego
    for (int v = 1; v <= numVertices; ++v) {
        for (int u : adjacencyList[v]) {
            // Dodaj krawędź w obu kierunkach
            H.adjacencyList[v].push_back(u);
            H.adjacencyList[u].push_back(v);
        }
    }
    
    return H;
}

bool Graph::hasFirstStructure() const {
    // Check if graph contains the first forbidden structure
    for (int v = 1; v <= numVertices; ++v) {
        for (int u : adjacencyList[v]) {
            std::set<int> vNeighbors(adjacencyList[v].begin(), adjacencyList[v].end());
            std::set<int> uNeighbors(adjacencyList[u].begin(), adjacencyList[u].end());
            
            if (vNeighbors.size() >= 2 && uNeighbors.size() >= 2) {
                std::vector<int> intersection;
                std::set_intersection(vNeighbors.begin(), vNeighbors.end(),
                                   uNeighbors.begin(), uNeighbors.end(),
                                   std::back_inserter(intersection));
                if (intersection.size() >= 2) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Graph::hasSecondStructure() const {
    // Sprawdź czy graf zawiera drugą strukturę zabronioną
    for (int v = 1; v <= numVertices; ++v) {
        std::set<int> vNeighbors(adjacencyList[v].begin(), adjacencyList[v].end());
        if (vNeighbors.size() >= 2) {
            for (int u : vNeighbors) {
                for (int w : vNeighbors) {
                    if (u != w) {
                        // Sprawdź czy u i w są połączone
                        std::set<int> uNeighbors(adjacencyList[u].begin(), adjacencyList[u].end());
                        if (uNeighbors.find(w) != uNeighbors.end()) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Graph::hasThirdStructure() const {
    // Sprawdź czy graf zawiera trzecią strukturę zabronioną (pętlę)
    for (int v = 1; v <= numVertices; ++v) {
        std::set<int> vNeighbors(adjacencyList[v].begin(), adjacencyList[v].end());
        if (vNeighbors.find(v) != vNeighbors.end()) {
            return true;
        }
    }
    return false;
} 