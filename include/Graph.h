#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <utility>
#include <unordered_map>
#include <vector>

struct RouteResult
{
    std::vector<std::string> path;
    int distance;
};


class Graph{
    private:
        std::unordered_map<std::string,
            std::vector<std::pair<std::string, int>>> adjacencyList;
    public:
        void addLocation(const std::string& city);
        void addRoad(const std::string& city, const std::string& destination, int distance);
        void displayGraph() const;
        RouteResult  findShortestRoute(const std::string& start, const std::string& destination);
        void saveToFile(const std::string& filename) const;
        void loadFromFile(const std::string& filename);
};

#endif