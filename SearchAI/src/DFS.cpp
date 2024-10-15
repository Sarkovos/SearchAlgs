#include "DFS.h"

bool dfsUtil(const Graph& graph, int current, int goal, std::vector<bool>& visited, std::vector<int>& path) 
{
    // We start by labeling the node as visited
    visited[current] = true;

    // Then we add it to our path
    path.push_back(current);

    // if the node we are on is the goal, then the path is done and we exit
    if (current == goal) 
    {
        return true;
    }

    // we loop through the neighbors from our current node
    for (int neighbor : graph.getNeighbors(current)) 
    {
        // if we have not visited a node...
        if (!visited[neighbor]) 
        {
            // we call the function on that node, and find its neighbors, and continue
            if (dfsUtil(graph, neighbor, goal, visited, path)) 
            {
                return true;
            }
        }
    }

    // if we have visited all of the nodes and havent reached our goal
    // we start backing up until we can start again, still looking for our goal
    path.pop_back();
    return false;
}

std::vector<int> dfs(const Graph& graph, int start, int goal) 
{
    // Initialize a vector of booleans to false with its size reflecting
    // the number of cities we have
    std::vector<bool> visited(graph.numCities(), false);

    // Create a vector for the path
    std::vector<int> path;

    // Send the args to the dfs function
    dfsUtil(graph, start, goal, visited, path);
    return path;
}
