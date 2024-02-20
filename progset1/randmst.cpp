#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <tuple>
#include <stdexcept>
#include <cmath>

// Graph implementation (Adjacancy list):
/*
    Graph implementation (Adjacency list):

*/

double distance(std::vector<double> c1, std::vector<double> c2) {
    if (c1.empty() || c2.empty() || c1.size() != c2.size()) {
        throw std::invalid_argument("Coordinate's are of different size");
    }

    long double acc = 0;
    double diff;
    for (size_t i = 0; i < c1.size(); i++) {
        diff = (c1[i] - c2[i]);
        acc += diff * diff;
    }
    return (double) std::sqrt(acc);
}

class Graph{
    private:
        // A counter that will give each node a unique int ID number. Used for indexing in numToNode
        int nodeNumber;
        // Maps a nodeNumber to a node's coordinate value
        std::vector<std::vector<double>> numToNode;
        /*
            Edge list is a list of tuples. Each element in edgelist is a 
            tuple of length 2, 0th element contains edgeweight and 1st
            contains the node number
        */
        std::vector<std::tuple<double, int>> edgeList;
        
        /*
            Adjacency matrix, a vector of vectors. i-th
        element represents a list of edge weights. The j-th
        slot in the i-th element of the adjacency matrix
        represents the edgeweight between nodes i and j.
        */
        std::vector<std::vector<double>> adjacencyMatrix;

    public:
        Graph() : nodeNumber(0), numToNode(), adjacencyMatrix(), edgeList() {} 

        // HANDLE CASE 1 BROTHER

        // Adds nodes and maintains the complete graph invariant.
        void addNode(std::vector<double> coord) {
            // Assign coordinate to a node number
            numToNode.push_back(coord);
            std::vector<double> initial =  {0.};
            adjacencyMatrix.push_back(initial);

            // Add edgeweights to adj matrix
            for (size_t i = 0; i < numToNode.size(); i++) {
                // Calculate distance
                double dist = distance(coord, numToNode[i]);

                // Distance becomes edge weight
                std::vector<double> initial =  {dist};

                adjacencyMatrix[nodeNumber].push_back(dist);
                adjacencyMatrix[i].push_back(dist);
                // Add distance nodeNumber tuple onto the edgeList.
                edgeList.push_back(std::make_tuple(dist, nodeNumber));
            }
            nodeNumber++;
        }

        // Returns the adjacencyMatrix, aka the graph.
        std::vector<std::vector<double>> getMatrix() {
            return adjacencyMatrix;
        }

        // Returns the edgelist (useful for Kruskal's alg)
        std::vector<std::tuple<double, int>> getEdgeList() {
            return edgeList;
        }
}


int main(int argc, char* argv[]) {
    // ./randmst 0 numpoints numtrials dimension
    // Use mt19937 for random number generation?
    if (argc != 5) {
        printf("4 inputs needed: 0 numpoints numtrials dimension");
    }
    return 0;
}

    /*
    Constructing 3 graphs:
        1.) Graph with n vertices where edge weights are distributed uniformly [0, 1]
        2.) Graph with n vertices where nodes are placed randomly into a unit squaure
        and edge weights are equal to the euclidean distance between nodes
        3.) Graph with n vertices where nodes are placed randomly into a unit cube 
        and edge weights are equal to the euclidean distance between nodes
        4.) Graph with n vertices where nodes are placed randomly into a unit hypercube
        and edge weights are equal to the euclidean distance between nodes
    */