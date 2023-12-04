#include "dheap.h"

DHeap::DHeap(int n_, int d_, int s_) : n(n_), d(d_), s(s_), startDistance(INF), key(n, INF), name(n), index(n)
{
    for (int i = 0; i < n; i++)
    {
        name[i] = i;
        index[name[i]] = i;
    }
    if (s < n)
        key[s] = 0;
    else
        key[n - 1] = 0;
    FormQueue();
}

int DHeap::FirstChild(int i)
{
    int k = i * d + 1;
    if (k >= n)
        return -1;
    return k;
}

int DHeap::LastChild(int i)
{
    int k = FirstChild(i);
    if (k == -1)
        return -1;
    return std::min(k + d - 1, n - 1);
}

int DHeap::Father(int i) { return (i - 1) / d; }

int DHeap::MinChild(int i)
{
    int kf = FirstChild(i);
    if (kf == -1)
        return i;
    int kl = LastChild(i);
    long double min_key = key[kf];
    int minChild = kf;
    for (int j = kf + 1; j <= kl; j++)
    {
        if (key[j] < min_key)
        {
            min_key = key[j];
            minChild = j;
        }
    }
    return minChild;
}

void DHeap::HeapifyUp(int i)
{
    long double key0 = key[i];
    int name0 = name[i];
    int p = Father(i);

    while (i != 0 && key[p] > key0)
    {
        key[i] = key[p];
        name[i] = name[p];
        index[name[i]] = i;
        i = p;
        p = Father(i);
    }

    key[i] = key0;
    name[i] = name0;
    index[name[i]] = i;
}

void DHeap::HeapifyDown(int i)
{
    long double key0 = key[i];
    int name0 = name[i];
    int c = MinChild(i);

    while (c != i && key0 > key[c])
    {
        key[i] = key[c];
        name[i] = name[c];
        index[name[i]] = i;
        i = c;
        c = MinChild(i);
    }

    key[i] = key0;
    name[i] = name0;
    index[name[i]] = i;
}

void DHeap::RemoveMin(int& name1, long double& key1)
{
    name1 = name[0];
    key1 = key[0];
    name[0] = name[n - 1];
    key[0] = key[n - 1];
    name[n - 1] = name1;
    key[n - 1] = key1;
    index[name1] = n - 1;
    n--;
    if (n > 0) HeapifyDown(0);
}

void DHeap::FormQueue() { for (int i = n - 1; i > -1; i--) HeapifyDown(i); }
int DHeap::GetNumVertices() const { return n; }
int DHeap::GetIndex(int name) const { return index[name]; }
long double DHeap::GetKey(int index) const { return key[index]; }
void DHeap::SetKey(int index, long double value) { key[index] = value; }