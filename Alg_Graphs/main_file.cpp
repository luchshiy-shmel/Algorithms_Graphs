#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include "graph.h"
#include <chrono>

void WriteResultsToNewFile(const std::vector<long double>& dist, const std::vector<int>& up, int vertex, long long operationTime, const std::string& filename) {
    std::ofstream outputFile(filename);

    if (outputFile.is_open()) {
        outputFile << "Время работы алгоритма: " << operationTime << " нс" << std::endl;
        for (int i = 0; i < dist.size(); i++) {
            outputFile << "Кратчайшее расстояние от вершины " << vertex << " до вершины " << i << ": " << dist[i] << "   Предпоследняя вершина в построенном кратчайшем пути из вершины s в вершину " << i << " : " << up[i] << std::endl;
        }
    }

    outputFile.close();
};

int main()
{
    Graph graph;
    graph.ReadGraphFromFile("graph.txt");

    int vertexForAlgorithms = 3;
    std::vector<long double> dist;
    std::vector<int> up;

    auto start_time = std::chrono::high_resolution_clock::now();
    graph.LDG_DIJKSTRA_DHEAP(dist, up, 3, vertexForAlgorithms);
    auto end_time = std::chrono::high_resolution_clock::now();

    WriteResultsToNewFile(dist, up, vertexForAlgorithms, std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count(), "LDG_DIJKSTRA_DHEAP.txt");

    start_time = std::chrono::high_resolution_clock::now();
    graph.LDG_DIJKSTRA_MARK(dist, up, vertexForAlgorithms);
    end_time = std::chrono::high_resolution_clock::now();

    WriteResultsToNewFile(dist, up, vertexForAlgorithms, std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count(), "LDG_DIJKSTRA_MARK.txt");
}