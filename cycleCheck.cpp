//Given an undirected graph find out whether the graph contains a cycle or not

#include <iostream>
#include <vector>

using namespace std;

#define MaxNumberOfVertices 100

struct Graph
{
    int numberOfVertices;
    vector<int> neighbours[MaxNumberOfVertices];
};

Graph ReadGraph()
{
    Graph graph;

    cin >> graph.numberOfVertices;
    int numberOfEdges;
    cin >> numberOfEdges;

    int a, b;
    for (int i = 0; i < numberOfEdges; i++)
    {
        cin >> a >> b;

        graph.neighbours[a].push_back(b);
        graph.neighbours[b].push_back(a);
    }

    return graph;
}

bool FindCycle(int root, Graph& graph, bool visited[], int prevVertex)
{
    visited[root] = true;

    for (int i = 0; i < graph.neighbours[root].size(); i++)
    {
        if (visited[graph.neighbours[root][i]])
        {
            if (graph.neighbours[root][i] != prevVertex)
            {
                return true;
            }
        }
        else if (FindCycle(graph.neighbours[root][i], graph, visited, root))
        {
            return true;
        }
    }

    return false;
}

bool ContainsCycle(Graph& graph)
{
    bool visited[MaxNumberOfVertices];
    for (int i = 0; i < graph.numberOfVertices; i++)
    {
        visited[i] = false;
    }

    for (int i = 0; i < graph.numberOfVertices; i++)
    {
        if (!visited[i])
        {
            if (FindCycle(i, graph, visited, -1))
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    Graph graph = ReadGraph();

    if (ContainsCycle(graph))
    {
        cout << "The graph contains a cycle." << endl;
    }
    else
    {
        cout << "The graph does not contain a cycle" << endl;
    }

    return 0;
}