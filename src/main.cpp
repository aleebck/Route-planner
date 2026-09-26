#include "Graph.h"

#include <iostream>
#include <limits>

int main()
{
    Graph graph;

    graph.loadFromFile("data/roads.txt");

    int choice;

    do
    {
        std::cout << "\n===== ROUTE PLANNER =====\n";
        std::cout << "1. Display map\n";
        std::cout << "2. Find shortest route\n";
        std::cout << "3. Add location\n";
        std::cout << "4. Add road\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter choice: ";

        if (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Invalid input. Please enter a number from 1-5.\n";
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                graph.displayGraph();
                break;
            }
            
            case 2:
            {
                std::string start;
                std::string destination;

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Enter starting location: ";
                std::getline(std::cin, start);

                std::cout << "Enter destination: ";
                std::getline(std::cin, destination);

                graph.findShortestRoute(start, destination);

                break;
            }

            case 3:
            {
                std::string city;

                std::cout << "Enter the location: ";

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, city);

                graph.addLocation(city);
                
                break;
            }

            case 4:
            {
                std::string city, destination;
                int distance;

                std::cout<< "Enter starting location: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::getline(std::cin, city);

                std::cout<<"Enter destination: ";
                std::getline(std::cin, destination);

                std::cout << "Enter distance: ";
                if (!(std::cin >> distance))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

                    std::cout << "Invalid distance! Please enter a number.\n";
                    break;
                }

                graph.addRoad(city, destination, distance);

                break;
            }

            case 5:
            {
                graph.saveToFile("data/roads.txt");
                std::cout << "Map saved!\n";
                std::cout << "Goodbye!\n";
                break;
            }

            default:
                std::cout << "Invalid choice!\n";
        }

    } while (choice != 5);


    return 0;
}