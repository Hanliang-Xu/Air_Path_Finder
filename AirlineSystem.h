#include "Graph.h"
#include <string>
#include <vector>
#include <unordered_map>

class AirlineSystem {
private:
    Graph flightNetwork;
    std::vector<std::string> airportNames;
    std::unordered_map<int, std::string> airportMapping;

    void generateRandomFlights();

public:
    AirlineSystem();
    void findShortestRoute(const std::string& start, const std::string& end);
    void displayAvailableAirlines();
    void displayAllRoutes(const std::string& start, const std::string& end);

};
