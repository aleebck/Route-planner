#include "Graph.h"

int main()
{
    Graph graph;

    graph.addLocation("Austin");
    graph.addLocation("San Marcos");
    graph.addLocation("Houston");

    graph.addRoad("Austin", "San Marcos", 32);
    graph.addRoad("Houston", "Austin", 150);

    graph.displayGraph();

    graph.findShortestRoute("Houston", "San Marcos");


    return 0;
}