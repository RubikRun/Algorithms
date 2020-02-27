#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MaxNumberOfVertices 1000
#define iPair pair<int, int>
#define Infinity 9999999

struct Graph
{
	int numberOfVertices;
	vector<iPair> adj[MaxNumberOfVertices];
};

struct Tree
{
	int numberOfVertices;
	vector<iPair> edges;
};

Graph ReadGraph()
{
	Graph graph;

	cin >> graph.numberOfVertices;
	int numberOfEdges;
	cin >> numberOfEdges;

	int a, b, w;
	for (int i = 0; i < numberOfEdges; i++)
	{
		cin >> a >> b >> w;
		graph.adj[a].push_back( {b, w} );
		graph.adj[b].push_back( {a, w} );
	}

	return graph;
}

Tree GetMinSpanTree(Graph& graph)
{
	Tree tree;
	tree.numberOfVertices = graph.numberOfVertices;

	int numberOfVerticesLeft = tree.numberOfVertices;

	bool inTree[MaxNumberOfVertices];
	for (int i = 0; i < tree.numberOfVertices; i++) inTree[i] = false;

	int root = 0;
	inTree[root] = true;
	numberOfVerticesLeft--;

	int parent[MaxNumberOfVertices];
	int connectWeight[MaxNumberOfVertices];
	for (int i = 0; i < tree.numberOfVertices; i++) connectWeight[i] = Infinity;

	priority_queue<iPair> pq;
	for (int i = 0; i < graph.adj[root].size(); i++)
	{
		int b = graph.adj[root][i].first;
		int w = graph.adj[root][i].second;
		pq.push( {-w, b} );
		parent[b] = root;
		connectWeight[b] = w;
	}

	while (numberOfVerticesLeft > 0)
	{
		int b = pq.top().second;
		pq.pop();
		int a = parent[b];

		if (!inTree[b])
		{
			tree.edges.push_back( {a, b} );
			inTree[b] = true;
			numberOfVerticesLeft--;

			for (int i = 0; i < graph.adj[b].size(); i++)
			{
				int c = graph.adj[b][i].first;
				int w = graph.adj[b][i].second;

				if (!inTree[c] && w < connectWeight[c])
				{
					pq.push( {-w, c} );
					parent[c] = b;
					connectWeight[c] = w;
				}
			}
		}
	}

	return tree;
}


int main()
{
	Graph graph = ReadGraph();
	Tree minSpanTree = GetMinSpanTree(graph);

	cout << "Minimum spanning tree contains these edges:" << endl;
	for (int i = 0; i < minSpanTree.edges.size(); i++)
	{
		cout << "(";
		cout << minSpanTree.edges[i].first;
		cout << ", ";
		cout << minSpanTree.edges[i].second;
		cout << ")";
		cout << endl;
	}

	return 0;
}
