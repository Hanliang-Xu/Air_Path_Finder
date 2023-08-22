#include <vector>
#include <unordered_map>

class Edge {
public:
    int dest;
    int weight;
    Edge(int d, int w);
};

class Vertex {
public:
    int id;
    std::vector<Edge> adjList;
    Vertex(int id);
    void addEdge(int dest, int weight);
};

class Graph {
private:
    std::unordered_map<int, Vertex*> vertices;
    void findAllRoutesUtil(int u, int d, std::vector<bool> &visited, std::vector<int> &path, int &path_index, std::vector<std::vector<int>> &allPaths, int &current_distance, std::vector<int> &allDistances);


public:
    ~Graph();
    void addVertex(int id);
    void addEdge(int src, int dest, int weight);
    std::unordered_map<int, int> dijkstra(int start);
    Vertex* getVertex(int id);
    std::vector<std::vector<int>> findAllRoutes(int start, int end);
    std::vector<int> getAllRoutesDistances(int start, int end);
};
