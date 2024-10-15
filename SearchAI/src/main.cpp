#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <chrono> // Include this if not already included
#include "BFS.h"
#include "graph.h"
#include "DFS.h"
#include "IDDFS.h"
#include "BestFS.h"
#include "Astar.h"

int main() {
    Graph graph("coordinates.csv", "Adjacencies.txt");

    while (true) {
        std::string startCityName, goalCityName;
        std::cout << "Enter start city (or 'exit' to quit): ";
        std::cin >> startCityName;
        if (startCityName == "exit" || startCityName == "Exit") 
        {
            break;
        }
        std::cout << "Enter goal city (or 'exit' to quit): ";
        std::cin >> goalCityName;
        if (goalCityName == "exit" || goalCityName == "Exit") 
        {
            break;
        }

        int startCity = graph.getCityIndex(startCityName);
        int goalCity = graph.getCityIndex(goalCityName);

        if (startCity == -1 || goalCity == -1) 
        {
            std::cout << "Invalid city names provided.\n";
            continue; 
        }

        std::cout << "Select search method:\n";
        std::cout << "1. Breadth-First Search\n";
        std::cout << "2. Depth-First Search\n";
        std::cout << "3. Iterative Deepening DFS\n";
        std::cout << "4. Best-First Search\n";
        std::cout << "5. A* Search\n";
        int choice;
        std::cin >> choice;

        std::vector<int> path;
        auto startTime = std::chrono::high_resolution_clock::now();

        switch (choice) 
        {
            case 1:
                path = bfs(graph, startCity, goalCity);
                break;
            case 2:
                path = dfs(graph, startCity, goalCity);
                break;
            case 3:
                path = iterativeDeepeningDFS(graph, startCity, goalCity);
                break;
            case 4:
                path = bestFirstSearch(graph, startCity, goalCity);
                break;
            case 5:
                path = aStarSearch(graph, startCity, goalCity);
                break;
            default:
                std::cout << "Invalid choice.\n";
                continue; // Prompt the user again
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = endTime - startTime;

        if (path.empty()) 
        {
            std::cout << "No path found between " << startCityName 
                      << " and " << goalCityName << ".\n";
        } else {
            std::cout << "Path found:\n";
            double totalDistance = 0.0;
            for (size_t i = 0; i < path.size(); ++i) 
            {
                std::cout << graph.getCity(path[i]).name;
                if (i != path.size() - 1) 
                {
                    std::cout << " -> ";
                    totalDistance += graph.calculateDistance(path[i], path[i + 1]);
                }
            }
            std::cout << "\nTotal distance: " << totalDistance << " km\n";
            std::cout << "Search time: " << elapsed.count() << " seconds\n";
        }

        // Ask if the user wants to perform another search
        std::cout << "Do you want to perform another search? (y/n): ";
        char again;
        std::cin >> again;
        if (again == 'n' || again == 'N') 
        {
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
