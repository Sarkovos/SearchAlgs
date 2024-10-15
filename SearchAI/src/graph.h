#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <cmath>
#include <limits>
#include <algorithm>
#include <chrono>

struct City 
{
    std::string name;
    double latitude;
    double longitude;
};

class Graph {
public:
    Graph(const std::string& coordinatesFile, const std::string& adjacencyFile) 
    {
        loadCities(coordinatesFile);
        loadAdjacency(adjacencyFile);
    }

    void addEdge(int u, int v) 
    {
        adjacencyList[u].push_back(v);
    }

    const std::vector<int>& getNeighbors(int cityIndex) const 
    {
        return adjacencyList.at(cityIndex);
    }

    int getCityIndex(const std::string& cityName) const 
    {
        auto it = cityToIndex.find(cityName);
        if (it != cityToIndex.end()) 
        {
            return it->second;
        }
        return -1;
    }

    const City& getCity(int index) const 
    {
        return cities.at(index);
    }

    int numCities() const 
    {
        return cities.size();
    }

    double calculateDistance(int u, int v) const 
    {
        const City& cityU = cities[u];
        const City& cityV = cities[v];
        // Haversine formula to calculate distance between two latitude-longitude points
        double lat1 = cityU.latitude * M_PI / 180.0;
        double lon1 = cityU.longitude * M_PI / 180.0;
        double lat2 = cityV.latitude * M_PI / 180.0;
        double lon2 = cityV.longitude * M_PI / 180.0;

        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;

        double a = pow(sin(dlat / 2), 2) +
                   cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double radius = 6371.0; // Earth's radius in kilometers
        return radius * c;
    }

private:
    std::vector<City> cities;
    std::unordered_map<std::string, int> cityToIndex;
    std::unordered_map<int, std::vector<int>> adjacencyList;

    /*Handles loading in coordinates.csv*/
    void loadCities(const std::string& filename) 
    {
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Error: Could not open coordinates file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line;
    int index = 0;
    while (std::getline(file, line)) 
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, latStr, lonStr;

        // Read the city name
        if (!std::getline(ss, name, ',')) 
        {
            std::cerr << "Error parsing city name in line: " << line << std::endl;
            continue;
        }

        // Read latitude
        if (!std::getline(ss, latStr, ',')) 
        {
            std::cerr << "Error parsing latitude in line: " << line << std::endl;
            continue;
        }

        // Read longitude
        if (!std::getline(ss, lonStr)) 
        {
            std::cerr << "Error parsing longitude in line: " << line << std::endl;
            continue;
        }

        //converts are strings into doubles
        double lat = std::stod(latStr);
        double lon = std::stod(lonStr);

        //adds the city to the city vector
        cityToIndex[name] = index++;
        cities.push_back({name, lat, lon});
    }
}


    /*Handles loading in adjaceny.txt*/
    void loadAdjacency(const std::string& filename) 
    {
        std::ifstream file(filename);
        if (!file.is_open()) 
        {
            std::cerr << "Error: Could not open adjacency file " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
        std::string line;
        bool isSymmetric = true; // Since adjacency is symmetric

        while (std::getline(file, line)) 
        {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string cityA, cityB;
            ss >> cityA >> cityB;

            int indexA = getCityIndex(cityA);
            int indexB = getCityIndex(cityB);

            // Since adjacency is symmetric, we add an edge from A to B, and then from B to A
            if (indexA != -1 && indexB != -1) 
            {
                addEdge(indexA, indexB);
                if (isSymmetric) 
                {
                    addEdge(indexB, indexA);
                }
            }
        }
    }
};


#endif