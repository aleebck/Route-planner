# C++ Route Planner

A command-line route planning application written in C++ that models locations and roads as a weighted graph and uses Dijkstra's algorithm to find the shortest route between two locations.

## Features

- Add locations to the map
- Add weighted, bidirectional roads between locations
- Find the shortest route using Dijkstra's algorithm
- Display the complete route and total distance
- Save map data to a file
- Automatically load saved map data when the program starts
- Preserve locations that have no connected roads
- Prevent duplicate roads and self-connections
- Validate user input and road distances
- Handle invalid file data without crashing

## Technologies & Concepts

- C++17
- Object-Oriented Programming
- Graphs and adjacency lists
- Dijkstra's shortest-path algorithm
- `std::unordered_map`
- `std::vector`
- `std::priority_queue`
- File I/O
- Exception handling

## Project Structure

```text
cpp-route-planner/
├── data/
│   └── roads.txt
├── include/
│   └── Graph.h
├── src/
│   ├── Graph.cpp
│   └── main.cpp
├── Makefile
└── README.md
```

## Build and Run

Compile the project:

```bash
make
```

Run the application:

```bash
./routeplanner
```

## Example

```text
===== ROUTE PLANNER =====
1. Display map
2. Find shortest route
3. Add location
4. Add road
5. Exit
Enter choice: 2

Enter starting location: San Marcos
Enter destination: Fort Worth

Shortest route: San Marcos -> Austin -> Fort Worth
Total distance: 222 miles
```

## How It Works

The map is represented as a weighted, undirected graph. Each location is a vertex, and each road is an edge containing a distance.

The program stores the graph using an adjacency list:

```cpp
std::unordered_map<
    std::string,
    std::vector<std::pair<std::string, int>>
> adjacencyList;
```

To find the shortest route, the program uses Dijkstra's algorithm with a min-priority queue.

It tracks the shortest known distance to each location and stores each location's previous vertex so the final route can be reconstructed.

Map data is stored in `data/roads.txt`, allowing locations and roads to persist between program runs.
