#include <iostream>
#include <tuple>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <random>
#include <algorithm>



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
        std::vector<std::vector<double> > numToNode;
        /*
            Edge list is a list of tuples. Each element in edgelist is a 
            tuple of length 2, 0th element contains edgeweight and 1st
            contains the node number
        */
        std::vector<std::tuple<double, std::tuple<int, int>>> edgeList;
        
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
        void addNode(std::vector<double> coord, bool isCase1) {
            if (isCase1) {
                numToNode.push_back(std::vector<double>((double) nodeNumber));
                adjacencyMatrix.push_back(std::vector<double>());

                for (size_t i = 0; i < numToNode.size(); i++) {
                    // Generate a random number from a uniform distribution:
                    std::random_device rd;
                    std::mt19937 gen(rd());

                    std::uniform_real_distribution<double> dist(0.0, 1.0);
                    double random_number = dist(gen);


                    // Add random number to adj matrix
                    adjacencyMatrix[nodeNumber].push_back(random_number);

                    // Add to edgelist
                    edgeList.push_back(std::make_tuple(random_number, std::make_tuple(nodeNumber, i)));
                }
            }
            else {
                 // Assign coordinate to a node number
                numToNode.push_back(coord);
                // Initialize a new row for this new node
                adjacencyMatrix.push_back(std::vector<double>());


                // Add edgeweights to adj matrix
                for (size_t i = 0; i < numToNode.size(); i++) {
                    if (i == nodeNumber) continue;

                    // Calculate distance
                    double dist = distance(coord, numToNode[i]);

                    // Distance becomes edgeweight
                    adjacencyMatrix[nodeNumber].push_back(dist);

                    // Adds entry into edge list. Format: (edgeweight, edge-relation)
                    // AKA identifies the edge based on node numbers.
                    edgeList.push_back(std::make_tuple(dist, std::make_tuple(nodeNumber, i)));
                }
            }
            nodeNumber++;
            return;
        }

        // Returns the adjacencyMatrix, aka the graph.
        std::vector<std::vector<double>> getMatrix() {
            return adjacencyMatrix;
        }

        // Returns the edgelist (useful for Kruskal's alg)
        std::vector<std::tuple<double, std::tuple<int, int>>> getEdgeList() {
            return edgeList;
        }
};

class UnionFind{
    public:
        // Constructor
        UnionFind(int size) {
            Set.resize(size);
        }

        // Implement Makeset
        void MakeSet(int nodeNum) {
            Set[nodeNum] = std::make_tuple(nodeNum, 0);
            return;
        }

        // Find returns a nodeNum, rank tuple of root of set. Uses recursion for the path compression.
        std::tuple<int, int> Find(int nodeNum) {
            // Base case
            if (std::get<0>(Set[nodeNum]) == nodeNum) return Set[nodeNum];

            // Recursive step (Compresses path of all elements in path.)
            Set[nodeNum] = Find(std::get<0>(Set[nodeNum]));

            return Set[nodeNum];
        }

        // Link is in the private poriton. This is because only Union uses the link method


        // Union method as provided in the lecture slides. Unions two sets and returns nothing.
        void Union(int num1, int num2) {
            Link(Find(num1), Find(num2));
            return;
        }

    private:
        std::vector<std::tuple<int, int>> Set;
        // Link by rank method. Uses recursion on improperly ordered elements.
        // Link takes in nodeNum, rank tuples as input and returns nothing.
        void Link(std::tuple<int, int> num1, std::tuple<int, int> num2) {
            int rank1 = std::get<1>(num1);
            int rank2 = std::get<1>(num2);

            if (rank1 > rank2) {
                // swap
                Link(num2, num1);
                return;
            }

            int nodeNum1 = std::get<0>(num1);
            int nodeNum2 = std::get<0>(num2);

            if (rank1 == rank2) {
                int nodeNum2 = std::get<0>(num2);
                Set[nodeNum2] = std::make_tuple(nodeNum2, rank2 + 1);
            }
            Set[nodeNum1] = std::make_tuple(nodeNum2, rank1);
            return;
        }
};






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

double kruskals(std::vector<std::tuple<double, std::tuple<int, int>>> edgelist) {
    // Sort the edge lists by their edge weights
    std::sort(edgelist.begin(), edgelist.end(), 
              [](const auto& lhs, const auto& rhs) {
                  return std::get<0>(lhs) < std::get<0>(rhs);
              });
    return 0.0;
    // Create array for union find thing
    

    // 
}