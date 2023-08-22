#include "Graph.h"
#include <limits>
#include <set>

// Definitions for Edge
Edge::Edge(int d, int w): dest(d), weight(w) {}

// Definitions for Vertex
Vertex::Vertex(int id): id(id) {}

void Vertex::addEdge(int dest, int weight) {
    adjList.push_back(Edge(dest, weight));
}

// Definitions for Graph
Graph::~Graph() {
    for (auto& pair : vertices) {
        delete pair.second;
    }
}

void Graph::addVertex(int id) {
    if (vertices.find(id) == vertices.end()) {
        vertices[id] = new Vertex(id);
    }
}

void Graph::addEdge(int src, int dest, int weight) {
    if (vertices.find(src) == vertices.end()) {
        addVertex(src);
    }
    if (vertices.find(dest) == vertices.end()) {
        addVertex(dest);
    }
    vertices[src]->addEdge(dest, weight);
}

std::unordered_map<int, int> Graph::dijkstra(int start) {
    std::unordered_map<int, int> distances;
    for (const auto& pair : vertices) {
        distances[pair.first] = std::numeric_limits<int>::max();
    }
    distances[start] = 0;

    std::set<std::pair<int, int>> unvisited;  // pair of distance and vertex id
    unvisited.insert({0, start});

    while (!unvisited.empty()) {
        int current = unvisited.begin()->second;
        unvisited.erase(unvisited.begin());

        for (const Edge& edge : vertices[current]->adjList) {
            int newDist = distances[current] + edge.weight;
            if (newDist < distances[edge.dest]) {
                unvisited.erase({distances[edge.dest], edge.dest});
                distances[edge.dest] = newDist;
                unvisited.insert({newDist, edge.dest});
            }
        }
    }
    return distances;
}

Vertex* Graph::getVertex(int id) {
    if (vertices.find(id) != vertices.end()) {
        return vertices[id];
    }
    return nullptr;
}

void Graph::findAllRoutesUtil(int u, int d, std::vector<bool> &visited, std::vector<int> &path, int &path_index, std::vector<std::vector<int>> &allPaths, int &current_distance, std::vector<int> &allDistances) {
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    if (u == d) {
        std::vector<int> currentPath;
        for (int i = 0; i < path_index; i++) {
            currentPath.push_back(path[i]);
        }
        allPaths.push_back(currentPath);
        allDistances.push_back(current_distance);  // Storing the current path's distance
    } else {
        for (const Edge &edge : vertices[u]->adjList) {
            if (!visited[edge.dest]) {
                current_distance += edge.weight; // Add edge weight to current distance
                findAllRoutesUtil(edge.dest, d, visited, path, path_index, allPaths, current_distance, allDistances);
                current_distance -= edge.weight; // Revert the distance as you backtrack
            }
        }
    }
    path_index--;
    visited[u] = false;
}


std::vector<std::vector<int>> Graph::findAllRoutes(int start, int end) {
    std::vector<bool> visited(vertices.size(), false);
    std::vector<int> path(vertices.size());
    int path_index = 0;
    int current_distance = 0;
    std::vector<std::vector<int>> allPaths;
    std::vector<int> allDistances;

    findAllRoutesUtil(start, end, visited, path, path_index, allPaths, current_distance, allDistances);

    return allPaths;
}

std::vector<int> Graph::getAllRoutesDistances(int start, int end) {
    std::vector<bool> visited(vertices.size(), false);
    std::vector<int> path(vertices.size());
    int path_index = 0;
    std::vector<std::vector<int>> allPaths;
    int current_distance = 0;
    std::vector<int> allDistances;

    findAllRoutesUtil(start, end, visited, path, path_index, allPaths, current_distance, allDistances);
    return allDistances;
}