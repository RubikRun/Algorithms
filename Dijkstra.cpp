/*
Dijkstra's algorithm finds shortest paths from a root vertex
to all vertices of a weighted directed graph.

The idea is similar to finding shortest paths using Breadth-First Search.
Instead of using a queue it uses a priority queue, because we are not sure
which of the vertices in the queue are the closest.

The algorithm is fast, but it can be used only when the edges have non-negative weights

Time Complexity: O(n + m * logm)
Space Complexity: O(m)
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define Read cin
#define Write cout
#define MaxNumberOfVertices 1000
#define Infinity 9999999


int numberOfVertices;
vector< pair<int, int> > adj[MaxNumberOfVertices];

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
		adj[a].push_back({b, w});
	}
}

void Dijkstra()
{
	bool processed[MaxNumberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
	{
		dist[i] = Infinity;
		processed[i] = false;
	}
	dist[root] = 0;

	priority_queue< pair<int, int> > q;
	q.push({0, root});
	while(!q.empty())
	{
		int a = q.top().second;
		q.pop();
		if (processed[a]) continue;
		processed[a] = true;

		for (int i = 0; i < adj[a].size(); i++)
		{
			int b = adj[a][i].first, w = adj[a][i].second;
			if (dist[a] + w < dist[b])
			{
				dist[b] = dist[a] + w;
				q.push({-dist[b], b});
			}
		}
	}
}

void PrintDists()
{
	Write << "Shortest paths from " << root << " to all other vertices:" << endl;

	for (int i = 0; i < numberOfVertices; i++)
	{
		Write << "Shortest path to " << i << " is " << dist[i] << endl;
	}
}

int main()
{
	ReadGraph();
	Read >> root;

	Dijkstra();
	PrintDists();

	return 0;
}