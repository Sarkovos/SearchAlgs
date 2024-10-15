#ifndef DFS_H
#define DFS_H

#include <vector>
#include "graph.h"

bool dfsUtil(const Graph& graph, int current, int goal, 
std::vector<bool>& visited, std::vector<int>& path);
std::vector<int> dfs(const Graph& graph, int start, int goal);


#endif
