//Given a connected graph find an Eulerian circuit,
//that is a path that starts and ends on the same vertex
//and uses each edge exactly once

#include <iostream>
#include <vector>
#include <stack>

using namespace std;
#define MaxNumberOfVertices 100

int numberOfVertices;
vector<int> adj[MaxNumberOfVertices];

bool vertexUsed[MaxNumberOfVertices];
bool edgeUsed[MaxNumberOfVertices][MaxNumberOfVertices];

vector<int> cycle;

void ReadGraph()
{
    cin >> numberOfVertices;
    int numberOfEdges;
    cin >> numberOfEdges;

    int a, b;
    for (int i = 0; i < numberOfEdges; i++)
    {
        cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
}

bool FindCycle(int a, int b)
{
    vertexUsed[a] = true;
    cycle.push_back(a);

    for (int i = 0; i < adj[a].size(); i++)
    {
        int child = adj[a][i];

        if (edgeUsed[a][child])
        {
            continue;
        }
        if (child == b)
        {
            cycle.push_back(child);
            return true;
        }
        if (vertexUsed[child])
        {
            continue;
        }

        edgeUsed[a][child] = true;
        edgeUsed[child][a] = true;
        if (FindCycle(child, b))
        {
            return true;
        }
        edgeUsed[a][child] = false;
        edgeUsed[child][a] = false;
    }

    cycle.pop_back();
    vertexUsed[a] = false;

    return false;
}

vector<int> GetEulerianCircuit()
{
    stack<int> ancestors[MaxNumberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
    {
        vertexUsed[i] = false;
        for (int j = 0; j < numberOfVertices; j++)
        {
            edgeUsed[i][j] = false;
        }
    }

    vector<int> eulerianCircuit;

    int x = 0;
    while (true)
    {
        eulerianCircuit.push_back(x);
        while (FindCycle(x, x))
        {
            for (int i = 0; i < cycle.size() - 1; i++)
            {
                ancestors[cycle[i]].push(cycle[i + 1]);
                vertexUsed[i] = false;
            }
            cycle.clear();
        }

        if (ancestors[x].empty())
        {
            break;
        }

        int prevX = x;
        x = ancestors[x].top();
        ancestors[prevX].pop();
    }

    return eulerianCircuit;
}

int main()
{
    ReadGraph();

    vector<int> eulerianCircuit = GetEulerianCircuit();
    for (int i = 0; i < eulerianCircuit.size(); i++)
    {
        cout << eulerianCircuit[i] + 1 << " ";
    }
    cout << endl;

    return 0;
}
