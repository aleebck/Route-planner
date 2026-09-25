#include "Graph.h"

int main()
{
    Graph graph;

    graph.adLocation("Austin");
    graph.addRoad("Austin", "San Marcos", 32);
    graph.adLocation("Houston");
    graph.addRoad("Houston", "Austin", 150);

    graph.displayGraph();


    return 0;
}