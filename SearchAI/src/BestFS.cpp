#include "BestFS.h"

/*This search, using a heuristic, estimates how close a node is to a goal, and expanding on it*/
/*We use a priority queue to always search the node with the best heuristic value,
and we have a visited list so we don't search the same city twice which could cause loops*/

std::vector<int> bestFirstSearch(const Graph& graph, int start, int goal) 
{
    // initialize a visited vector of bools and a parent vectors of int indexes
    std::vector<bool> visited(graph.numCities(), false);
    std::vector<int> parent(graph.numCities(), -1);

    // the heuristic is determined by calculateDistance, which uses the coordinates to compute the distance to the goal city
    auto heuristic = [&](int cityIndex) 
    {
        return graph.calculateDistance(cityIndex, goal);
    };

    // establish a priority queue, sorting by heuristic value
    std::priority_queue<BestFirstNode, std::vector<BestFirstNode>, std::greater<BestFirstNode>> openList;
    openList.push({start, heuristic(start)});

    // while there is nodes to explore...
    while (!openList.empty()) 
    {
        // we get the node that is closest, and pop it from the list
        BestFirstNode currentNode = openList.top();
        openList.pop();

        // we then take the index from that city
        int current = currentNode.cityIndex;

        // we mark that city as visited
        if (visited[current]) 
        {
            continue;
        }
        
        visited[current] = true;

        // if we are on the goal, we exit the loop
        if (current == goal) 
        {
            break;
        }

        // we loop over the neighbors of the city
        for (int neighbor : graph.getNeighbors(current)) 
        {
            // this makes sure we only consider neighors that we have not visited
            if (!visited[neighbor]) 
            {
                // set the parent to the current node
                parent[neighbor] = current;

                // add the nieghbor to the list with its heuristic value
                openList.push({neighbor, heuristic(neighbor)});
            }
        }
    }

    // Reconstruct path
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
