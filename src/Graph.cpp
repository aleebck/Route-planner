#include "Graph.h"

void Graph::adLocation(const std::string& city)
{
    adjacencyList[city];
}

void Graph::addRoad(const std::string& city, const std::string& destination, int distance)
{
    adjacencyList[city].push_back({destination, distance});
    adjacencyList[destination].push_back({city, distance});
}

void Graph::displayGraph() const 
{
    for(const auto& entry: adjacencyList)
    {
        std::cout << entry.first<< ": ";
        for(const auto& dests: entry.second)
        {
            std::cout<<"(" <<dests.first << ", " << dests.second << "miles) ";
        }

        std::cout<<'\n';
    }
}