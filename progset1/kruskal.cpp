#include <algorithm>



double kruskals(std::vector<std::tuple<double, std::tuple<int, int>>> edgelist) {
    // Sort the edge lists by their edge weights
    std::sort(edgeList.begin(), edgeList.end(), 
              [](const auto& lhs, const auto& rhs) {
                  return std::get<0>(lhs) < std::get<0>(rhs);
              });

    
}