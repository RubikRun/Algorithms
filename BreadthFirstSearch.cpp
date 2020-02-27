/*
Breadth First Search (BFS) is a general graph traversal algorithm.
It traverses the vertices in the order of their distance from the root.
It maintains a queue of vertices.
First the root enters the queue and after that while there are vertices in the queue,
the front vertex f is extracted and being processed as follows:
All the vertices adjacent to f that haven't been processed yet are added to the queue.
The moment of traversal for each vertex is when it enters the queue.

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

void BFS(int x)
{
    queue<int> q;
    q.push(x);
    traversed[x] = true;
    cout << x << endl;
    while (!q.empty())
    {
        int a = q.front();
        q.pop();

        for (int i = 0; i < adj[a].size(); i++)
        {
            int b = adj[a][i];
            if (!traversed[b])
            {
                q.push(b);
                traversed[b] = true;
                cout << b << endl;
            }
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
    Write << "Vertices traversed with BFS:" << endl;
    BFS(x);

    return 0;
}
