#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <utility>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <limits>

class Graph{
    private:
        std::unordered_map<std::string,
            std::vector<std::pair<std::string, int>>> adjacencyList;
    public:
        void adLocation(const std::string& city);
        void addRoad(const std::string& city, const std::string& destination, int distance);
        void displayGraph() const;
};

#endif