//Given an undirected connected graph find a tree with the same vertex set and minimum weight sum

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 1000
#define SetRootPrev -1

struct Edge { int v1, v2, w; };
bool EdgeComp(Edge& e1, Edge& e2) { return e1.w < e2.w; }

int n;
vector<Edge> edges;

int prv[MAXN];
int setSize[MAXN];

void ReadGraph()
{
	cin >> n;
	int m; cin >> m;

	int a, b, w;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b >> w;
		edges.push_back( {a, b, w} );
	}
}

void InitSets()
{
	for (int i = 0; i < n; i++)
	{
		prv[i] = SetRootPrev;
		setSize[i] = 1;
	}
}

int FindSetRoot(int x)
{
	while (prv[x] != -1)
	{
		x = prv[x];
	}
	return x;
}

void JoinSets(int x, int y)
{
	int xRoot = FindSetRoot(x);
	int yRoot = FindSetRoot(y);

	if (setSize[xRoot] < setSize[yRoot])
	{
		prv[xRoot] = yRoot;
		setSize[yRoot] += setSize[xRoot];
	}
	else
	{
		prv[yRoot] = xRoot;
		setSize[xRoot] += setSize[yRoot];
	}
}

bool SameSet(int x, int y)
{
	return FindSetRoot(x) == FindSetRoot(y);
}

vector<Edge> GetMinSpanTree()
{
	sort(edges.begin(), edges.end(), EdgeComp);


	InitSets();
	vector<Edge> spanTree;
	for (int i = 0; i < edges.size(); i++)
	{
		if (!SameSet(edges[i].v1, edges[i].v2))
		{
			JoinSets(edges[i].v1, edges[i].v2);
			spanTree.push_back( edges[i] );
		}
	}

	return spanTree;
}

int main()
{
	ReadGraph();
	vector<Edge> minSpanTree = GetMinSpanTree();

	cout << "Minimum Span Tree consists of these edges:" << endl;
	for (int i = 0; i < minSpanTree.size(); i++)
	{
		cout << "(" << minSpanTree[i].v1 << ", " << minSpanTree[i].v2 << ")" << endl;
	}

	return 0;
}
