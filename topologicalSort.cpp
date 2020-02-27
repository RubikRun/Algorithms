#include <iostream>
#include <vector>
#include <algorithm>

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
	}

	return graph;
}

bool DFS(int root, int processed[], Graph& graph, vector<int>& topSort)
{
	processed[root] = 1;

	for (int i = 0; i < graph.adj[root].size(); i++)
	{
		int child = graph.adj[root][i];
		if (processed[child] == 1)
		{
			return false;
		}
		if (processed[child] == 0)
		{
			if (!DFS(child, processed, graph, topSort))
			{
				return false;
			}
		}
	}

	processed[root] = 2;
	topSort.push_back(root);
	return true;
}

vector<int> GetTopSort(Graph& graph)
{
	int processed[MaxNumberOfVertices];
	for (int i = 0; i < graph.numberOfVertices; i++)
	{
		processed[i] = 0;
	}

	vector<int> topSort;
	for (int i = 0; i < graph.numberOfVertices; i++)
	{
		if (processed[i] == 0)
		{
			if (!DFS(i, processed, graph, topSort))
			{
				return {-1};
			}
		}
	}

	reverse(topSort.begin(), topSort.end());
	return topSort;
}

int main()
{
	Graph graph = ReadGraph();
	vector<int> topSort = GetTopSort(graph);

	if (topSort[0] == -1)
	{
		cout << "The graph has a cycle and a topological sort does not exist." << endl;
	}
	else
	{
		cout << "One topological sort of the graph is:" << endl;
		for (int i = 0; i < topSort.size() - 1; i++)
		{
			cout << topSort[i] << ", ";
		}
		cout << topSort.back() << endl;
	}

	return 0;
}
