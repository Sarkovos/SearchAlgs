#include "IDDFS.h"

/*IDDFS: Uses less memory compared to BFS, basically performs a series of DFS searches but with a limited depth, and we increase the depth until the goal is found
We start with a depth of 0, and we use DFS to the current limit, increasing and repeating until its done*/
bool iddfsUtil(const Graph& graph, int current, int goal, int depth, std::vector<int>& path) 
{
    /*Base case*/
    if (depth == 0 && current == goal) 
    {
        path.push_back(current);
        return true;
    }

    /*The current node is added to the path, and for each neighbor, we check for successes*/
    if (depth > 0) {
        path.push_back(current);
        for (int neighbor : graph.getNeighbors(current)) 
        {
            if (iddfsUtil(graph, neighbor, goal, depth - 1, path)) 
            {
                return true;
            }
        }
        path.pop_back();
    }
    return false;
}

 
 /*This function handles the deepening. We start at 0, and keep going up until we find a goal where the iddfsUtil function returns true*/
std::vector<int> iterativeDeepeningDFS(const Graph& graph, int start, int goal) 
{
    /*Because the loop below could go on for a very long time, we add a 10-second timeout*/
    auto startTime = std::chrono::steady_clock::now();
    const std::chrono::seconds TIMEOUT(10); // 10-second timeout


    /*std::numeric_limits stores the highest value the selected type can do, basically making this loop infinite*/
    for (int depth = 0; depth < std::numeric_limits<int>::max(); ++depth) 
    {
        auto currentTime = std::chrono::steady_clock::now();
        if (currentTime - startTime > TIMEOUT) 
        {
            std::cout << "Timeout!\n";
            return {};
        }

        /*For each depth, we call the util function to perform a search at the depth. If it does not find the path, we increase the depth and go again*/
        std::vector<int> path;
        if (iddfsUtil(graph, start, goal, depth, path)) 
        {
            return path;
        }
    }
    return {};
}

