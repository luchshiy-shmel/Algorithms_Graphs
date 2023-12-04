#include "graph.h"
#include <chrono>

int CalculateNumEdges(int numVertex, int& menuEdgesItem) {
    if (menuEdgesItem == 0) {
        std::cout << std::endl << "Выберете зависимость числа ребер от количества вершин" << std::endl
            << "1) m ~ n^2" << std::endl
            << "2) m ~ n^2 / 10" << std::endl
            << "3) m ~ 100 * n" << std::endl
            << "4) m ~ 1000 * n" << std::endl;
        std::cin >> menuEdgesItem;
    }
    while (true) {
        switch (menuEdgesItem) {
        case 1:
            return numVertex * numVertex - numVertex;
        case 2:
            return numVertex * numVertex / 10 - numVertex;
        case 3:
            return 100 * numVertex - numVertex;
        case 4:
            return 1000 * numVertex - numVertex;
        }
        std::cout << std::endl << "Выберете корректный пункт меню";
        std::cin >> menuEdgesItem;
    }
}

void EnteringParameters(int& numVert, int& minV, int& maxV) {
    std::cout << std::endl << "Введите начальное количество вершин: ";
    std::cin >> numVert;
    std::cout << "Введите начальную нижнюю границу для весов ребер графа: ";
    std::cin >> minV;
    std::cout << "Введите начальную верхнюю границу для весов ребер графа: ";
    std::cin >> maxV;
}

void PrintResult(std::vector<long double>& dist, std::vector<int>& up, Graph& graph, int vertex, int minValue, int maxValue) {
    std::cout << "  Количество вершин: " << graph.GetNumVertices()
        << "  Количество ребер: " << graph.GetNumEdges()
        << "  Нижняя граница для весов ребер графа: " << minValue
        << "  Верхняя граница для весов ребер графа: " << maxValue << std::endl;

    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    graph.LDG_DIJKSTRA_DHEAP(dist, up, 3, vertex);
    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();

    std::cout << "Время работы алгоритма LDG_DIJKSTRA_DHEAP : " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    graph.LDG_DIJKSTRA_MARK(dist, up, vertex);
    end_time = std::chrono::high_resolution_clock::now();

    std::cout << "Время работы алгоритма LDG_DIJKSTRA_MARK : " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << std::endl;
}

void Menu(std::vector<long double>& dist, std::vector<int>& up) {
    int menuItem, menuEdgeItem = 0, variableStep;
    int numVertices, numEdges = 0, minValue, maxValue;
    int vertexToSearch;

    std::cout << "Задайте начальные параметры графа";
    EnteringParameters(numVertices, minValue, maxValue);

    std::cout << std::endl << "Введите вершину для поиска кратчайших путей: ";
    std::cin >> vertexToSearch;
    if (vertexToSearch >= numVertices) vertexToSearch = numVertices - 1;

    do {
        std::cout << std::endl << "Выберете варьируемый параметр" << std::endl
            << "1) Количество вершин" << std::endl
            << "2) Количество ребер" << std::endl
            << "3) Верхняя граница для весов ребер графа" << std::endl;
        std::cin >> menuItem;

        std::cout << "Введите шаг варьируемого параметра: ";
        std::cin >> variableStep;

        switch (menuItem) {
        case 1:
            while (numVertices <= 10001) {
                Graph graph;
                graph.GenerateGraph(numVertices, CalculateNumEdges(numVertices, menuEdgeItem), minValue, maxValue);
                PrintResult(dist, up, graph, vertexToSearch, minValue, maxValue);
                numVertices += variableStep;
            }
            return;
        case 2:
            while (numEdges <= 10000000) {
                Graph graph;
                graph.GenerateGraph(numVertices, numEdges, minValue, maxValue);
                PrintResult(dist, up, graph, vertexToSearch, minValue, maxValue);
                numEdges += variableStep;
            }
            return;
        case 3:
            Graph graph;
            graph.GenerateGraph(numVertices, CalculateNumEdges(numVertices, menuEdgeItem), minValue, maxValue);
            while (maxValue < 200) {
                PrintResult(dist, up, graph, vertexToSearch, minValue, maxValue);
                maxValue += variableStep;
                graph.ChangeWeightEdges(minValue, maxValue);
            }
            return;
        }
        std::cout << std::endl << "Укажите корректный пункт меню: ";
        std::cin >> menuItem;
    } while (menuItem != 0);
}

int main()
{
    setlocale(LC_ALL, "rus");

    std::vector<long double> dist;
    std::vector<int> up;

    Menu(dist, up);
}