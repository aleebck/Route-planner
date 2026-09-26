#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <utility>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <limits>
#include <queue>
#include <functional>
#include <algorithm>

class Graph{
    private:
        std::unordered_map<std::string,
            std::vector<std::pair<std::string, int>>> adjacencyList;
    public:
        void addLocation(const std::string& city);
        void addRoad(const std::string& city, const std::string& destination, int distance);
        void displayGraph() const;
        void findShortestRoute(const std::string& start, const std::string& destination);
        void saveToFile(const std::string& filename) const;
        void loadFromFile(const std::string& filename);
};

#endif