#include "Graph.h"
#include <fstream>
#include <sstream>

void Graph::addLocation(const std::string& city)
{
    adjacencyList[city];
}

void Graph::addRoad(const std::string& city, const std::string& destination, int distance)
{
    if (distance < 0)
    {
        std::cout << "Distance cannot be negative!\n";
        return;
    }
    if (city == destination)
    {
        std::cout << "A location cannot have a road to itself!\n";
        return;
    }
    for (const auto& road : adjacencyList[city])
    {
        if (road.first == destination)
        {
            std::cout << "Road already exists!\n";
            return;
        }
    }

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
            std::cout<<"(" <<dests.first << ", " << dests.second << " miles) ";
        }

        std::cout<<'\n';
    }
}

void Graph::findShortestRoute(const std::string& start, const std::string& destination)
{
    if (adjacencyList.find(start) == adjacencyList.end())
    {
        std::cout << "Starting location not found!\n";
        return;
    }
    if(adjacencyList.find(destination) == adjacencyList.end())
    {
        std::cout << "Destination not found!\n";
        return;
    }

    std::unordered_map<std::string, int> distances;
    std::unordered_map<std::string, std::string> previous;

    for(const auto& entry: adjacencyList)
    {
        distances[entry.first] = std::numeric_limits<int>::max();
    }
    distances[start] = 0;

    std::priority_queue<
        std::pair<int, std::string>,
        std::vector<std::pair<int, std::string>>,
        std::greater<std::pair<int, std::string>> 
        >pq;

    pq.push({distances[start], start});

    while(!pq.empty())
    {
        int currentDistance = pq.top().first;
        std::string currentCity = pq.top().second;

        pq.pop();

        if(currentDistance > distances[currentCity])
        {
            continue;
        }

        for(const auto& road: adjacencyList[currentCity])
        {
            std::string nextCity = road.first;
            int roadDistance = road.second;

            int newDistance = currentDistance + roadDistance;

            if(newDistance < distances[nextCity])
            {
                distances[nextCity] = newDistance;
                previous[nextCity] = currentCity;
                pq.push({newDistance, nextCity});
            }
        }
    }

    if(distances[destination] == std::numeric_limits<int>::max())
    {
        std::cout << "No route found!\n";
        return;
    }

    std::vector<std::string> path;
    std::string current = destination;

    while(current != start)
    {
        path.push_back(current);
        current = previous[current];
    }
    path.push_back(current);

    std::reverse(path.begin(), path.end());

    std::cout << "Shortest route: ";
    for (int i = 0; i < path.size(); i++)
    {
        std::cout << path[i];

        if (i < path.size() - 1)
        {
            std::cout << " -> ";
        }
    }
    std::cout << "\nTotal distance: " << distances[destination] << " miles"<<'\n';
}

void Graph::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);

    if(!file)
    {
        std::cout << "Error opening file!\n";
        return;
    }

    for(const auto& entry: adjacencyList)
    {
        for(const auto& road: entry.second)
        {
            if(entry.first < road.first)
                file << entry.first << "|" << road.first << "|" << road.second << "\n";
        }
    }

    file.close();
}

void Graph::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if(!file)
    {
        std::cout << "Error opening file!\n";
        return;
    }

    std::string city, destination, distanceText;
    int distance;
    std::string line;
    while(std::getline(file, line))
    {
        std::stringstream ss(line);

        std::getline(ss, city, '|');
        std::getline(ss, destination, '|');
        std::getline(ss, distanceText);
        distance = std::stoi(distanceText);

        addRoad(city, destination, distance);
    }
}