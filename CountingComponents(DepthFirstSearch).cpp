/*
Depth First Search (DFS) can be used to count connected components of a graph.
The idea is that all vertices traversed with a DFS (or a BFS) belong to the same component.
So we can go through all vertices and for each non-traversed vertex count one more component
and do a DFS from it.

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

int GetNumberOfComponents()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        traversed[i] = false;
    }

    int numberOfComponents = 0;

    for (int i = 0; i < numberOfVertices; i++)
    {
        if (!traversed[i])
        {
            DFS(i);
            numberOfComponents++;
        }
    }

    return numberOfComponents;
}

int main()
{
    ReadGraph();

    Write << "Number of components: " << GetNumberOfComponents() << endl;

    return 0;
}
