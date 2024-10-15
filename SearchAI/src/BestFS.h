#ifndef BESTFS_H
#define BESTFS_H

#include "graph.h"
#include <vector>

struct BestFirstNode {
    int cityIndex;     // index of city
    double heuristic;  // heuristic value

    // overload the greater than operator to compare nodes based on their heuristic value, used by the priority queue
    bool operator>(const BestFirstNode& other) const 
    {
        return heuristic > other.heuristic;
    }
};

std::vector<int> bestFirstSearch(const Graph& graph, int start, int goal);


#endif