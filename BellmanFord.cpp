/*
The Bellman-Ford algorithm finds shortest paths from a root vertex
to all vertices of a weighted directed graph

The idea is to use edges to shorten paths that we already know.
Initially we know nothing but dist[root] = 0 and dist[x =/= root] = infinity
We go through all edges n-1 times and for every edge (a, b, w)
we try to reduce the path to b using this edge: dist[b] = min(dist[b], dist[a] + w)

(Assuming edge list representation of the graph)
Time Complexity: O(n * m)
Space Complexity: O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define Read cin
#define Write cout
#define MaxNumberOfVertices 1000
#define Infinity 2147483647

struct Edge
{
    int firstVertex, secondVertex;
    int weight;
};

vector<Edge> edges;
int numberOfVertices;

int root;
int dist[MaxNumberOfVertices];

void ReadGraph()
{
    int numberOfEdges;
    Read >> numberOfVertices >> numberOfEdges;

    int a, b, w;
    for (int i = 0; i < numberOfEdges; i++)
    {
        Read >> a >> b >> w;
        edges.push_back({a, b, w});
    }
}

void FillDist()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        dist[i] = Infinity;
    }
    dist[root] = 0;

    for (int i = 0; i < numberOfVertices - 1; i++)
    {
        for (int j = 0; j < edges.size(); j++)
        {
            int a = edges[j].firstVertex, b = edges[j].secondVertex, w = edges[j].weight;
            dist[b] = min(dist[b], dist[a] + w);
        }
    }
}

void PrintDists()
{
    Write << "Shortest paths from " << root << " to all vertices:" << endl;

    for (int i = 0; i < numberOfVertices; i++)
    {
        Write << "Shortest path to " << i << " is " << dist[i] << endl;
    }
}

int main()
{
    ReadGraph();

    FillDist();
    PrintDists();

    return 0;
}
