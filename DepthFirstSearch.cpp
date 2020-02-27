/*
Depth First Search (DFS) is a general graph traversal algorithm.
It traverses the vertices recursively,
first going as deep as possible and then going back and taking different directions.

Time Complexity: O(n + m)
Space Complexity: O(n)
*/

#include <iostream>
#include <vector>

using namespace std;
#define Read cin
#define Write cout
#define MaxNumberOfVertices 1000

vector<int> adj[MaxNumberOfVertices];
int numberOfVertices;

bool traversed[MaxNumberOfVertices];

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

void DFS(int x)
{
    Write << x << endl;
    traversed[x] = true;

    for (int i = 0; i < adj[x].size(); i++)
    {
        int a = adj[x][i];
        if (!traversed[a])
        {
            DFS(a);
        }
    }
}

int main()
{
    ReadGraph();
    int x;
    Read >> x;

    for (int i = 0; i < numberOfVertices; i++)
    {
        traversed[i] = false;
    }
    Write << "Vertices traversed with DFS:" << endl;
    DFS(x);

    return 0;
}
