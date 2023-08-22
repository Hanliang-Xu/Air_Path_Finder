#include "AirlineSystem.h"
#include <iostream>

int main() {
    AirlineSystem system;

    std::cout << "\nWould you like to view all available airlines? (yes/no): ";
    std::string choice;
    std::cin >> choice;
    if (choice == "yes" || choice == "Yes") {
        system.displayAvailableAirlines();
    }

    std::string startAirport, endAirport;
    std::cout << "Enter start airport: ";
    std::cin >> startAirport;
    std::cout << "Enter destination airport: ";
    std::cin >> endAirport;

    system.displayAllRoutes(startAirport, endAirport);
    system.findShortestRoute(startAirport, endAirport);

    return 0;
}
