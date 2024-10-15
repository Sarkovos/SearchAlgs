#include "BFS.h"



std::vector<int> bfs(const Graph& graph, int start, int goal) 
{
    // initialize a vectors of bools with all falses, and allocate the size of all cities
    std::vector<bool> visited(graph.numCities(), false);
    
    // initialize a vector of parents, also with the size of cities and all at -1
    std::vector<int> parent(graph.numCities(), -1);

    // initialize a queue
    std::queue<int> q;

    // label our starting node as visited, and push it on the queue
    visited[start] = true;
    q.push(start);

    // while the queue is not empty...
    while (!q.empty()) 
    {
        // we take the front of the queue and pop it out
        int current = q.front();
        q.pop();

        // if the front of the queue was our goal, we are done
        if (current == goal) 
        {
            break;
        }

        // if not, we go through all of the neighbors of our node
        for (int neighbor : graph.getNeighbors(current)) 
        {
            // if a neighbor has not been visited...
            if (!visited[neighbor]) 
            {
                // label that neighbor visited
                visited[neighbor] = true;

                // set that neighbor node as the current node
                parent[neighbor] = current;

                // push it onto the queue
                q.push(neighbor);
            }
        }
    }

    // Reconstruct path from end to start, then reverse it for final path
    std::vector<int> path;
    if (!visited[goal]) 
    {
        return path; // No path found
    }

    for (int at = goal; at != -1; at = parent[at]) 
    {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}
