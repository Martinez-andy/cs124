#include <iostream>
#include <tuple>
#include <vector>
#include <stdexcept>
#include <cmath>
#include <random>
#include <algorithm>
#include <string>

#include <stdio.h>
double kruskals(std::vector<std::tuple<double, std::tuple<int, int>>> edgelist, int size);

// Finds the Euclidean distance between two coordinate points given (coords are given as vectors)
double distance(std::vector<double> c1, std::vector<double> c2) {
    // Handle improper inputs and throws an error if needed
    if (c1.empty() || c2.empty() || c1.size() != c2.size()) {
        throw std::invalid_argument("Coordinate's are of different size");
    }

    // accumulator
    long double acc = 0;
    // Temporary variable used for calculating the difference between indiviaul coords (aka x - x, y- y, ect.)
    double diff;

    // Iterate over all coordinates, find square difference and add to accumulator
    for (size_t i = 0; i < c1.size(); i++) {
        diff = (c1[i] - c2[i]);
        acc += diff * diff;
    }
    // Square root accumulator
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
       /*
       std::vector<std::vector<double>> adjacencyMatrix;
       */
        

    public:
        // Removed adjacency matrix
        Graph() : nodeNumber(0), numToNode(), edgeList() {} 


        // Adds nodes and maintains the complete graph invariant.
        void addNode(std::vector<double> coord, bool isCase1) {
            if (isCase1) {
                numToNode.push_back(coord);
                /*
                adjacencyMatrix.push_back(std::vector<double>());
                */
                

                // Iterate over all nodes and add edges (since graph is complete)
                for (size_t i = 0; i < numToNode.size(); i++) {
                    // Make sure no self loops exist
                    if (i == nodeNumber) continue;

                    // Generate a random number from a uniform distribution:
                    std::random_device rd;
                    std::mt19937 gen(rd());

                    std::uniform_real_distribution<double> dist(0.0, 1.0);
                    double random_number = dist(gen);

                    /*
                    // Add random number to adj matrix
                    adjacencyMatrix[nodeNumber].push_back(random_number);
                    */
                    

                    // Add to edgelist
                    edgeList.push_back(std::make_tuple(random_number, std::make_tuple(nodeNumber, i)));
                }
            }
            else {
                 // Assign coordinate to a node number
                numToNode.push_back(coord);
                // Initialize a new row for this new node
                /*
                adjacencyMatrix.push_back(std::vector<double>());
                */


                // Add edgeweights to adj matrix
                for (size_t i = 0; i < numToNode.size(); i++) {
                    // Make sure no self loops exist.
                    if (i == nodeNumber) continue;

                    // Calculate distance
                    double dist = distance(coord, numToNode[i]);

                    /*
                    // Distance becomes edgeweight
                    adjacencyMatrix[nodeNumber].push_back(dist);
                    */
                    

                    // Adds entry into edge list. Format: (edgeweight, edge-relation)
                    // AKA identifies the edge based on node numbers.
                    edgeList.push_back(std::make_tuple(dist, std::make_tuple(nodeNumber, i)));
                }
            }
            // Update nodeNumber
            nodeNumber++;
            return;
        }

        // Returns the adjacencyMatrix, aka the graph.
        /*
        std::vector<std::vector<double>> getMatrix() {
            return adjacencyMatrix;
        }
        */
        
        // Returns the edgelist (useful for Kruskal's alg)
        std::vector<std::tuple<double, std::tuple<int, int>>> getEdgeList() {
            return edgeList;
        }
};


// Implementation of UnionFind class
class UnionFind{
    public:
        // Constructor
        UnionFind(int size) {
            Set.resize(size);
            for (size_t i = 0; i < size; i++) {
                MakeSet(i);
            }
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
        // Initializes the set
        std::vector<std::tuple<int, int>> Set;

        // Makeset (Added to private because as soon as we initialize a UnionFind obj we add all verts)
        void MakeSet(int nodeNum) {
            Set[nodeNum] = std::make_tuple(nodeNum, 0);
            return;
        }

        // Link by rank method. Uses recursion on improperly ordered elements.
        // Link takes in nodeNum, rank tuples as input and returns nothing.
        void Link(std::tuple<int, int> num1, std::tuple<int, int> num2) {
            int rank1 = std::get<1>(num1);
            int rank2 = std::get<1>(num2);

            // If rank1 > rank2, swap
            if (rank1 > rank2) {
                // swap
                Link(num2, num1);
                return;
            }
            // Save node numbers into variables
            int nodeNum1 = std::get<0>(num1);
            int nodeNum2 = std::get<0>(num2);

            // If the two are of equal size, increment rank.
            if (rank1 == rank2) {
                Set[nodeNum2] = std::make_tuple(nodeNum2, rank2 + 1);
            }
            // Set nodeNum1 (root w smaller rank) to point to nodeNum2 (root w larger rank)
            Set[nodeNum1] = std::make_tuple(nodeNum2, rank1);
            return;
        }
};


int main(int argc, char* argv[]) {
    // ./randmst 0 numpoints numtrials dimension
    // Use mt19937 for random number generation?
    if (argc != 5) {
        printf("4 inputs needed: 0 numpoints numtrials dimension");
        return 1;
    }

    int n = std::stoi(argv[2]);

    int numtrials = std::stoi(argv[3]);

    int dimension = std::stoi(argv[4]);

    // Create variable to track total weight
    double totalMSTWeight = 0.0;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t i = 0; i < numtrials; i++) {
        // Restart graph object
        Graph graph;
        if (dimension == 0) {

            // Add all the nodes (vecotors don't matter since 0-dimensional.)
            // Number are randomly generated in the addNode method for 0-D graphs.
            for (size_t j = 0; j < n; j++) {
                graph.addNode({0.0}, true);
            }
        } 
        else {

            // Construct graphs for 2-D, 3-D, and 4-D cases
            for (size_t j = 0; j < n; j++) {
                // Generate coords randomly and add dimensions
                std::vector<double> coord;
                for (size_t k = 0; k < dimension; k++) {

                    std::uniform_real_distribution<double> dist(0.0, 1.0);
                    double random_number = dist(gen);

                    coord.push_back(random_number);
                }
                graph.addNode(coord, false);
            }

        }

        double treeWeight = kruskals(graph.getEdgeList(), n);
        totalMSTWeight += treeWeight;
        std::cout << treeWeight << std::endl;

    }
    double average = totalMSTWeight / numtrials;
    std::cout << average << std::endl;
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


// Implementation of Kruskal's algorithm. Takes in the edgelist from the graph class as input as well as the size
// of the graph (number of nodes) as input.
double kruskals(std::vector<std::tuple<double, std::tuple<int, int>>> edgelist, int size) {
    // Sort the edge lists by their edge weights
    std::sort(edgelist.begin(), edgelist.end(), 
              [](const auto& lhs, const auto& rhs) {
                  return std::get<0>(lhs) < std::get<0>(rhs);
              });
    // Instantiate UnionFind object
    UnionFind set(size);

    // Create list of edges for the MST and var to hold total sum.
    std::vector<std::tuple<int, int>> res;
    double tot = 0;
    for (size_t i = 0; i < edgelist.size(); i++) {
        std::tuple<double, std::tuple<int, int>> ele = edgelist[i];
        std::tuple<int, int> edge = std::get<1>(ele);
        int nodeNum1 = std::get<0>(edge);
        int nodeNum2 = std::get<1>(edge);

        if (set.Find(nodeNum1) != set.Find(nodeNum2)) {
            res.push_back(edge);
            tot += std::get<0>(ele);

            set.Union(nodeNum1, nodeNum2);
        }
    }
    return tot;
}