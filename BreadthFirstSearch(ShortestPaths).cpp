/*
Breadth First Search (BFS) can be used to find the lengths of the shortest paths
from a root vertex to all other vertices in a non-weighted graph.

The idea is that if vertex b enters the queue via a vertex a,
then the shortest path to b is the same as the shortest path to a plus the edge (a, b)
Or dist[b] = dist[a] + 1, where dist[x] is the length of the shortest path
from the root to x

Time Complexity: O(n + m)
Space Complexity: O(n)
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define Read cin
#define Write cout
#define MaxNumberOfVertices 1000
#define Infinity 2147483647

vector<int> adj[MaxNumberOfVertices];
int numberOfVertices;

int dist[MaxNumberOfVertices];
int root;

void AddEdgeToGraph(int a, int b)
{
    adj[a].push_back(b);
    adj[b].push_back(a);
}

void ReadGraph()
{
    int numberOfEdges;
    Read >> numberOfVertices >> numberOfEdges;

    int a, b;
    for (int i = 0; i < numberOfEdges; i++)
    {
        Read >> a >> b;
        AddEdgeToGraph(a, b);
    }
}

void FillDistBFS()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        dist[i] = Infinity;
    }
    dist[root] = 0;

    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int a = q.front();
        q.pop();

        for (int i = 0; i < adj[a].size(); i++)
        {
            int b = adj[a][i];
            if (dist[b] == Infinity)
            {
                dist[b] = dist[a] + 1;
                q.push(b);
            }
        }
    }
}

void PrintDists()
{
    Write << "Shortest paths from " << root << " to all vertices:" << endl;

    for (int i = 0; i < numberOfVertices; i++)
    {
        Write << "Shortest path to " << i << ": " << dist[i] << endl;
    }
}

int main()
{
    ReadGraph();
    Read >> root;

    FillDistBFS();
    PrintDists();

    return 0;
}
