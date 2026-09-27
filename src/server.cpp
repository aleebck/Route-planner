#include "httplib.h"
#include "Graph.h"

#include <iostream>

int main()
{
    Graph graph;
    graph.loadFromFile("data/roads.txt");

    httplib::Server server;

    server.Get("/hello", [](const httplib::Request& request, httplib::Response& response)
    {
        response.set_content("Hello from C++!", "text/plain");
    });

    server.Get("/route", [&graph](const httplib::Request& request, httplib::Response& response)
    {
        std::string start = request.get_param_value("start");
        std::string destination = request.get_param_value("destination");

        RouteResult result = graph.findShortestRoute(start, destination);

        if (result.distance == -1)
        {
            response.set_content(
                "{\"error\":\"No route found\"}",
                "application/json"
            );
            return;
        }

        std::string json = "{\"path\":[";
        for(std::size_t i = 0; i< result.path.size(); i++)
        {
            json += "\"" +result.path[i] +"\"";
            if(i < result.path.size()-1)
            {
                json += ",";
            }
        }
        json += "], \"distance\":" + std::to_string(result.distance) + "}";

        response.set_header("Access-Control-Allow-Origin", "*");
        response.set_content(json, "application/json");
    });

    server.Get("/locations", [&graph](const httplib::Request& request, httplib::Response& response)
    {
        std::string json = "[";
        std::vector<std::string> locations = graph.getLocations();
        for(std::size_t i = 0; i< locations.size(); i++)
        {
            json += "\""+locations[i] + "\"";

            if(i < locations.size()-1)
            {
                json +=", ";
            }
        }
        json+="]";

        response.set_header("Access-Control-Allow-Origin", "*");
        response.set_content(json, "application/json");
    });

    std::cout <<"Server running at http://localhost:8080\n";
    server.listen("localhost", 8080);

    return 0;
}