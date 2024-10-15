#ifndef ASTAR_H
#define ASTAR_H

#include "graph.h"
#include <vector>

// stores our heuristic which is f(n)
// other than that, same is Best-first search
struct AStarNode {
    int cityIndex;
    double fScore;

    bool operator>(const AStarNode& other) const {
        return fScore > other.fScore;
    }
};

std::vector<int> aStarSearch(const Graph& graph, int start, int goal);

#endif