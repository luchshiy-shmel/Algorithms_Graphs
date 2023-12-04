#pragma once
#include <vector>

const long double INF = 1000000000000000;

class DHeap {
private:
    int s, n, d;
    std::vector<long double> key;
    std::vector<int> name;
    std::vector<int> index;
    const long double startDistance;

public:
    DHeap(int n_, int d_, int s_);

    int FirstChild(int i);
    int LastChild(int i);
    int Father(int i);
    int MinChild(int i);
    void HeapifyUp(int i);
    void HeapifyDown(int i);
    void RemoveMin(int& name1, long double& key1);
    void FormQueue();
    int GetNumVertices() const;
    int GetIndex(int name) const;
    long double GetKey(int index) const;
    void SetKey(int index, long double value);
};