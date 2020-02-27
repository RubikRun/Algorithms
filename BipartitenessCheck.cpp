/*
A graph is called bipartite if all of its vertices can be colored with two colors,
such that no two adjacent vertices have the same color.

We can check if a graph is bipartite using Depth First Search (DFS).
Greedily we just start coloring its vertices different colors and if we cannot make it,
then the graph is not bipartite, otherwise it's bipartite.

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

int color[MaxNumberOfVertices];

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

bool Color(int x, int prevColor)
{
    color[x] = (prevColor + 1) % 2;

    for (int i = 0; i < adj[x].size(); i++)
    {
        int a = adj[x][i];
        if (color[a] == -1)
        {
            if (!Color(a, color[x]))
            {
                return false;
            }
        }
        else if (color[a] == color[x])
        {
            return false;
        }
    }

    return true;
}

bool IsBipartite()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        color[i] = -1;
    }

    for (int i = 0; i < numberOfVertices; i++)
    {
        if (color[i] == -1 && !Color(i, -1))
        {
            return false;
        }
    }

    return true;
}

int main()
{
    ReadGraph();

    if (IsBipartite())
    {
        Write << "The graph is bipartite" << endl;
    }
    else
    {
        Write << "The graph is not bipartite" << endl;
    }

    return 0;
}
