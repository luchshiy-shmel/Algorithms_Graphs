#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "dheap.h"
#include <sstream>

struct vtype {
    int name;
    int w;
    vtype* next;
};

class Graph {
private:
    int numVertices, numEdges;
    std::vector<vtype*> adjacencyList;
public:
    Graph();
    ~Graph();

    int GetNumVertices() const;
    int GetNumEdges() const;
    void ClearGraph();
    void AssignGraph(int numVert);
    void AddEdge(int src, int dest, int weight);
    void ReadGraphFromFile(const std::string& filename);
    void ChangeWeightEdges(int newMinValue, int newMaxValue);
    void GenerateGraph(int n, int m, int q, int r);
    void LDG_DIJKSTRA_DHEAP(std::vector<long double>& dist, std::vector<int>& up, int d, int s);
    void LDG_DIJKSTRA_MARK(std::vector<long double>& dist, std::vector<int>& up, int s);
};