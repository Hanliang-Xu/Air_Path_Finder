#include "AirlineSystem.h"
#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>  // for time()

AirlineSystem::AirlineSystem() {
    // Example airport names
    airportNames = {"JFK", "LAX", "ORD", "DFW", "DEN", "SFO", "SEA", "ATL", "MCO", "BOS"};

    for (int i = 0; i < airportNames.size(); i++) {
        airportMapping[i] = airportNames[i];
    }

    generateRandomFlights();
}

void AirlineSystem::generateRandomFlights() {
    srand(time(nullptr)); // seed random number generator
    for (int i = 0; i < airportNames.size(); i++) {
        int connections = rand() % 5 + 1;  // Random number of connections from 1 to 5
        for (int j = 0; j < connections; j++) {
            int target = rand() % airportNames.size();
            if (target != i) {
                int cost = rand() % 1000 + 50; // Random flight cost from 50 to 1050
                flightNetwork.addEdge(i, target, cost);
            }
        }
    }
}

void AirlineSystem::findShortestRoute(const std::string& start, const std::string& end) {
    int startIndex = -1, endIndex = -1;
    for (const auto& pair : airportMapping) {
        if (pair.second == start) startIndex = pair.first;
        if (pair.second == end) endIndex = pair.first;
    }

    if (startIndex == -1 || endIndex == -1) {
        std::cout << "Invalid airport names." << std::endl;
        return;
    }

    std::unordered_map<int, int> distances = flightNetwork.dijkstra(startIndex);

    if (distances[endIndex] == std::numeric_limits<int>::max()) {
        std::cout << "No route found." << std::endl;
    } else {
        std::cout << "Shortest flight cost from " << start << " to " << end << " is: " << distances[endIndex] << std::endl;
    }
}

void AirlineSystem::displayAvailableAirlines() {
    std::cout << "Available Airlines and Their Direct Connections:" << std::endl;
    for (const auto& source : airportMapping) {
        std::cout << source.second << " --> ";
        for (const Edge& edge : flightNetwork.getVertex(source.first)->adjList) {
            std::cout << airportMapping[edge.dest] << " (Cost: " << edge.weight << "), ";
        }
        std::cout << std::endl;
    }
}

void AirlineSystem::displayAllRoutes(const std::string& start, const std::string& end) {
    int startIndex = -1, endIndex = -1;
    for (const auto& pair : airportMapping) {
        if (pair.second == start) startIndex = pair.first;
        if (pair.second == end) endIndex = pair.first;
    }

    if (startIndex == -1 || endIndex == -1) {
        std::cout << "Invalid airport names." << std::endl;
        return;
    }

    std::vector<std::vector<int>> routes = flightNetwork.findAllRoutes(startIndex, endIndex);
    std::vector<int> distances = flightNetwork.getAllRoutesDistances(startIndex, endIndex);

    if (routes.empty()) {
        std::cout << "No routes found." << std::endl;
    } else {
        std::cout << "All routes from " << start << " to " << end << " are: " << std::endl;
        for (size_t i = 0; i < routes.size(); i++) {
            for (int j : routes[i]) {
                std::cout << airportMapping[j] << " -> ";
            }
            std::cout << "Distance: " << distances[i] << std::endl;
        }
    }
}