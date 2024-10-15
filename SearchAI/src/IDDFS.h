#ifndef IDDS_H
#define IDDFS_H

#include <vector>
#include "graph.h"
#include <chrono>

bool iddfsUtil(const Graph& graph, int current, int goal, int depth, std::vector<int>& path);
std::vector<int> iterativeDeepeningDFS(const Graph& graph, int start, int goal);



#endif