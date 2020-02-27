//Given an oriented connected acyclic graph and two vertices find the number of paths between them

#include <iostream>
#include <vector>

using namespace std;
#define MaxNumberOfVertices 100
#define NotFoundValue -1

struct Graph
{
	int numberOfVertices;
	vector<int> parents[MaxNumberOfVertices];
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
		graph.parents[b].push_back(a);
	}

	return graph;
}

void FillNumberOfPaths(int lastVertex, Graph& graph, int numberOfPaths[])
{
	if (numberOfPaths[lastVertex] != NotFoundValue)
	{
		return;
	}
	numberOfPaths[lastVertex] = 0;

	for (int i = 0; i < graph.parents[lastVertex].size(); i++)
	{
		int parent = graph.parents[lastVertex][i];
		FillNumberOfPaths(parent, graph, numberOfPaths);
		numberOfPaths[lastVertex] += numberOfPaths[parent];
	}
}

int GetNumberOfPaths(Graph& graph, int firstVertex, int lastVertex)
{
	//numberOfPaths[i] will be the number of paths from firstVertex to i
	int numberOfPaths[MaxNumberOfVertices];
	for (int i = 0; i < graph.numberOfVertices; i++)
	{
		numberOfPaths[i] = NotFoundValue;
	}
	numberOfPaths[firstVertex] = 1;

	FillNumberOfPaths(lastVertex, graph, numberOfPaths);

	return numberOfPaths[lastVertex];
}

int main()
{
	Graph graph = ReadGraph();
	int firstVertex, lastVertex;
	cin >> firstVertex >> lastVertex;

	int numberOfPaths = GetNumberOfPaths(graph, firstVertex, lastVertex);
	cout << "There are ";
	cout << numberOfPaths;
	cout << " paths between ";
	cout << firstVertex;
	cout << " and ";
	cout << lastVertex;
	cout << "." << endl;

	return 0;
}
