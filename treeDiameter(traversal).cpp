//Given a tree find its diameter - the longest path between two vertices

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MaxNumberOfVertices 100

struct Graph
{
    int numberOfVertices;
    vector<int> adj[MaxNumberOfVertices];
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
        graph.adj[a].push_back(b);
        graph.adj[b].push_back(a);
    }

    return graph;
}

pair<int, int> GetFarthestVertex(Graph& graph, int root)
{
    int dist[MaxNumberOfVertices];
    for (int i = 0; i < graph.numberOfVertices; i++)
    {
        dist[i] = -1;
    }
    dist[root] = 0;

    pair<int, int> farthestVertex = {root, 0};

    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int a = q.front();
        q.pop();

        for (int i = 0; i < graph.adj[a].size(); i++)
        {
            int b = graph.adj[a][i];

            if (dist[b] == -1)
            {
                dist[b] = dist[a] + 1;
                q.push(b);

                if (dist[b] > farthestVertex.second)
                {
                    farthestVertex = {b, dist[b]};
                }
            }
        }
    }

    return farthestVertex;
}

int GetDiameter(Graph& graph)
{
    pair<int, int> a = GetFarthestVertex(graph, 0);
    pair<int, int> b = GetFarthestVertex(graph, a.first);

    return b.second;
}

int main()
{
    Graph graph = ReadGraph();

    int diameter = GetDiameter(graph);

    cout << "The diameter of the tree is " << diameter << endl;

    return 0;
}