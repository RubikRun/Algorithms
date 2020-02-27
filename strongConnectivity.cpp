#include <iostream>
#include <vector>

using namespace std;
#define MaxNumberOfVertices 100

struct Graph
{
	int numberOfVertices;
	vector<int> children[MaxNumberOfVertices];
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
		graph.children[a].push_back(b);
	}

	return graph;
}

Graph GetReverseGraph(Graph& graph)
{
	Graph reverseGraph;

	reverseGraph.numberOfVertices = graph.numberOfVertices;

	for (int i = 0; i < graph.numberOfVertices; i++)
	{
		for (int j = 0; j < graph.children[i].size(); j++)
		{
			int child = graph.children[i][j];
			reverseGraph.children[child].push_back(i);
		}
	}

	return reverseGraph;
}

void DFSforOrder(Graph& graph, int root, vector<int>& order, bool done[])
{
	done[root] = true;

	for (int i = 0; i < graph.children[root].size(); i++)
	{
		int child = graph.children[root][i];
		if (!done[child])
		{
			DFSforOrder(graph, child, order, done);
		}
	}

	order.push_back(root);
}

void DFSforComponent(Graph& graph, bool hasComponent[], vector<int>& component, int root)
{
	component.push_back(root);
	hasComponent[root] = true;

	for (int i = 0; i < graph.children[root].size(); i++)
	{
		int child = graph.children[root][i];

		if (!hasComponent[child])
		{
			DFSforComponent(graph, hasComponent, component, child);
		}
	}
}

vector< vector<int> > GetComponents(Graph& graph)
{
	vector<int> dfsOrderVertices;
	bool done[MaxNumberOfVertices];
	for (int i = 0; i < graph.numberOfVertices; i++)
	{
		done[i] = false;
	}

	for (int i = 0; i < graph.numberOfVertices; i++)
	{
		if (!done[i])
		{
			DFSforOrder(graph, i, dfsOrderVertices, done);
		}
	}

	Graph reverseGraph = GetReverseGraph(graph);

	bool hasComponent[MaxNumberOfVertices];
	for (int i = 0; i < graph.numberOfVertices; i++)
	{
		hasComponent[i] = false;
	}

	vector< vector<int> > components;
	for (int i = dfsOrderVertices.size() - 1; i >= 0; i--)
	{
		int currVertex = dfsOrderVertices[i];
		if (!hasComponent[currVertex])
		{
			components.push_back( {} );
			DFSforComponent(reverseGraph, hasComponent, components.back(), currVertex);
		}
	}

	return components;
}

int main()
{
	Graph graph = ReadGraph();

	vector< vector<int> > components = GetComponents(graph);

	cout << "Strongly connected components of the given graph are:" << endl;
	for (int i = 0; i < components.size(); i++)
	{
		cout << "{";
		for (int j = 0; j < components[i].size() - 1; j++)
		{
			cout << components[i][j] << ", ";
		}
		cout << components[i].back();
		cout << "}" << endl;
	}

	return 0;
}
