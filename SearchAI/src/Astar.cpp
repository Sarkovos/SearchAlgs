#include "Astar.h"

/* 
g(n): cost from start node to node n
h(n): heuristic cost from node n to the goal
f(n): estimated total cost of the cheapest solution through node n
f(n) = g(n) + h(n)

*/

std::vector<int> aStarSearch(const Graph& graph, int start, int goal) 
{
    // gScore is our g(n), set to infinity except for the start node
    std::vector<double> gScore(graph.numCities(), std::numeric_limits<double>::infinity());

    // stores the parent of each node, used for making the path
    std::vector<int> parent(graph.numCities(), -1);

    // keepts track of where we have been
    std::vector<bool> visited(graph.numCities(), false);

    // much like best first search, this gets our heuristic, h(n)
    auto heuristic = [&](int cityIndex) 
    {
        return graph.calculateDistance(cityIndex, goal);
    };

    // start node to itself is 0
    gScore[start] = 0.0;

    // our big bad priority queue, initialized with the start node
    std::priority_queue<AStarNode, std::vector<AStarNode>, std::greater<AStarNode>> openList;
    openList.push({start, heuristic(start)});

    // while we arent done...
    while (!openList.empty()) 
    {
        // take the front of the queue, remove it from the openList, and get its index
        AStarNode currentNode = openList.top();
        openList.pop();
        int current = currentNode.cityIndex;

        // if we already have evaluated the node, skip it
        if (visited[current]) 
        {
            continue;
        }
        // mark it as visited
        visited[current] = true;

        // if the node is the goal, we are done
        if (current == goal) 
        {
            break;
        } 

        // now we iterate over the neighbors
        for (int neighbor : graph.getNeighbors(current)) 
        {
            // calculates the bost to reach the neighbor from the current node
            double tentativeGScore = gScore[current] + graph.calculateDistance(current, neighbor);

            // if the new path to the neighbor is better than the other one...
            if (tentativeGScore < gScore[neighbor]) 
            {
                // updates cost to reach the neighbor
                gScore[neighbor] = tentativeGScore;

                // set the current node as the parent of the neighbor
                parent[neighbor] = current;

                // calculate f(n) for neighbor
                double fScore = tentativeGScore + heuristic(neighbor);

                // add the neighbor to the list
                openList.push({neighbor, fScore});
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