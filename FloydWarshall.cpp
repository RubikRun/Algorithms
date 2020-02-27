/*
Floyd-Warshall algorithm finds shortest paths between all pair of vertices
in a directed weighted graph

It tries to use all vertices k to shorten the dist between i and j as follows:
dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

Time Complexity: O(n ^ 3)
Space Complexity: O(n ^ 2)
*/

#include <iostream>
#include <algorithm>

using namespace std;
#define Read cin
#define Write cout
#define MaxNumberOfVertices 1000
#define MissingEdge -191977
#define Infinity 2147483647

int numberOfVertices;
int weightMatrix[MaxNumberOfVertices][MaxNumberOfVertices];
int distMatrix[MaxNumberOfVertices][MaxNumberOfVertices];

void ReadGraph()
{
    int numberOfEdges;
    Read >> numberOfVertices >> numberOfEdges;

    for (int i = 0; i < numberOfVertices; i++)
    {
        for (int j = 0; j < numberOfVertices; j++)
        {
            weightMatrix[i][j] = MissingEdge;
        }
    }
    int a, b, w;
    for (int i = 0; i < numberOfEdges; i++)
    {
        Read >> a >> b >> w;
        weightMatrix[a][b] = w;
    }
}

void FillDistMatrix()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        for (int j = 0; j < numberOfVertices; j++)
        {
            if (i == j) distMatrix[i][j] = 0;
            else if (weightMatrix[i][j] != MissingEdge) distMatrix[i][j] = weightMatrix[i][j];
            else distMatrix[i][j] = Infinity;
        }
    }
    for (int k = 0; k < numberOfVertices; k++)
    {
        for (int i = 0; i < numberOfVertices; i++)
        {
            for (int j = 0; j < numberOfVertices; j++)
            {
                distMatrix[i][j] = min(distMatrix[i][j], distMatrix[i][k] + distMatrix[k][j]);
            }
        }
    }
}

void PrintDistMatrix()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        for (int j = 0; j < numberOfVertices; j++)
        {
            Write << distMatrix[i][j] << " ";
        }
        Write << endl;
    }
}

int main()
{
    ReadGraph();

    FillDistMatrix();
    PrintDistMatrix();

    return 0;
}
