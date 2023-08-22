cmake_minimum_required(VERSION 3.24)
project(Airline_System)

set(CMAKE_CXX_STANDARD 17)

add_executable(Airline_System main.cpp Graph.cpp Graph.h AirlineSystem.cpp AirlineSystem.h)
