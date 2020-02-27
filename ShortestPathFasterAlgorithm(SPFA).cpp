/*
Shortest Path Faster Algorithm (SPFA) is a faster version of Bellman-Ford algorithm.

The algorithm maintains a queue of vertices that might be used for reducing
the shortest paths. First, the algorithm adds the root vertex to the queue. Then,
the algorithm always processes the first vertex in the queue, and when an edge
a → b reduces a shortest path, node b is added to the queue.

SPFA is usually faster than Bellman-Ford, but their time complexity in the worst case
is the same.

Time Complexity: O(n * m)
Space Complexity: O(m)
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define Read cin
#define Write cout
#define MaxNumberOfVertices 1000
#define Infinity 999999

vector< pair<int, int> > adj[MaxNumberOfVertices];
int numberOfVertices;

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
		adj[a].push_back( {b, w} );
	}
}

void SPFA()
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
			int b = adj[a][i].first, w = adj[a][i].second;

			if (dist[a] + w < dist[b])
			{
				dist[b] = dist[a] + w;
				q.push(b);
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

	SPFA();
	PrintDists();

	return 0;
}