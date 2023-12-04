#include "graph.h"

Graph::Graph() : numVertices(0), numEdges(0), adjacencyList(0) {}
Graph::~Graph() { ClearGraph(); }
int Graph::GetNumVertices() const { return numVertices; }
int Graph::GetNumEdges() const { return numEdges; }

void Graph::ClearGraph()
{
    numVertices = numEdges = 0;
    for (vtype* vertex : adjacencyList)
    {
        while (vertex != nullptr)
        {
            vtype* temp = vertex;
            vertex = vertex->next;
            delete temp;
        }
    }
    adjacencyList.clear();
}

void Graph::AssignGraph(int numVert)
{
    ClearGraph();
    numVertices = numVert;
    adjacencyList.resize(numVertices);
}

void Graph::AddEdge(int src, int dest, int weight)
{
    vtype* newEdge = new vtype;
    newEdge->name = dest;
    newEdge->w = weight;
    newEdge->next = adjacencyList[src];
    adjacencyList[src] = newEdge;
    numEdges++;
}

void Graph::ReadGraphFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;

        if (std::getline(file, line))
        {
            std::stringstream ss(line);
            ss >> numVertices;
            AssignGraph(numVertices);
        }

        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            int vertex, adjacentVertex, weight;
            ss >> vertex >> adjacentVertex >> weight;
            AddEdge(vertex, adjacentVertex, weight);
        }
        file.close();
    }
}

void Graph::ChangeWeightEdges(int newMinValue, int newMaxValue)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    for (int i = 0; i < numVertices; i++)
    {
        vtype* edge = adjacencyList[i];
        while (edge != nullptr)
        {
            edge->w = std::uniform_int_distribution<>(newMinValue, newMaxValue)(generator);
            edge = edge->next;
        }
    }
}

void Graph::GenerateGraph(int n, int m, int q, int r)
{
    if (n <= 0) n = 1;
    AssignGraph(n);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> toConstruct(0, 1);

    int numCanConstructEdge = n * n - n;
    if (m < 0 || m > numCanConstructEdge) m = numCanConstructEdge;

    int v1 = 0, v2 = 1;
    while (numEdges != m)
    {
        if (v1 != v2)
        {
            if (numCanConstructEdge > m)
            {
                if (toConstruct(generator)) AddEdge(v1, v2, std::uniform_int_distribution<>(q, r)(generator));
            }
            else AddEdge(v1, v2, std::uniform_int_distribution<>(q, r)(generator));

            numCanConstructEdge--;
        }
        v2++;
        if (v2 == numVertices)
        {
            v2 = 0;
            v1++;
        }
    }
}

void Graph::LDG_DIJKSTRA_DHEAP(std::vector<long double>& dist, std::vector<int>& up, int d, int s) {
    int n = numVertices;
    DHeap heap(n, d, s);
    up.assign(n, 0);
    dist.assign(n, INF);
    int name1;
    long double key1;
    while (heap.GetNumVertices() > 0) {
        heap.RemoveMin(name1, key1);
        int i = name1;
        dist[i] = key1;
        vtype* p = adjacencyList[i];
        while (p != nullptr) {
            int j = p->name;
            int jq = heap.GetIndex(j);
            if (heap.GetKey(jq) > dist[i] + p->w) {
                heap.SetKey(jq, dist[i] + p->w);
                heap.HeapifyUp(jq);
                up[j] = i;
            }
            p = p->next;
        }
    }
}

void Graph::LDG_DIJKSTRA_MARK(std::vector<long double>& dist, std::vector<int>& up, int s) {
    int n = numVertices;
    std::vector<int> h(n, 0);
    up.assign(n, 0);
    dist.assign(n, INF);
    int nq = n;
    if (s < n) dist[s] = 0;
    else dist[n - 1] = 0;
    while (nq > 0) {
        int c = 0;
        while (h[c] != 0) c++;
        int i = c;
        for (int k = c + 1; k < n; k++)
            if (h[k] == 0)
                if (dist[i] > dist[k]) i = k;
        h[i] = 1;
        nq--;
        vtype* p = adjacencyList[i];
        while (p != nullptr) {
            int j = p->name;
            if (dist[j] > dist[i] + p->w) {
                dist[j] = dist[i] + p->w;
                up[j] = i;
            }
            p = p->next;
        }
    }
}