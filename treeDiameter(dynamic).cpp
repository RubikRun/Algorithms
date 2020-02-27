//Given a tree find its diameter - the longest path between two nodes

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define MaxNumberOfVertices 100
#define MaxNumberOfNodes MaxNumberOfVertices

struct Graph
{
    int numberOfVertices;
    int numberOfEdges;
    vector<int> neighbours[MaxNumberOfNodes];
};

struct Tree
{
    int numberOfNodes;
    int root;
    int parent[MaxNumberOfNodes];
    vector<int> children[MaxNumberOfNodes];

    int toLeaf[MaxNumberOfNodes];
};

Graph ReadGraph()
{
    Graph graph;

    cin >> graph.numberOfVertices;
    cin >> graph.numberOfEdges;

    int a, b;
    for (int i = 0; i < graph.numberOfEdges; i++)
    {
        cin >> a >> b;
        graph.neighbours[a].push_back(b);
        graph.neighbours[b].push_back(a);
    }

    return graph;
}

Tree ReadTree()
{
    Graph graph = ReadGraph();

    Tree tree;
    tree.numberOfNodes = graph.numberOfVertices;

    tree.root = 0;
    tree.parent[tree.root] = -1;

    queue<int> q;
    q.push(tree.root);
    while (!q.empty())
    {
        int currNode = q.front();
        q.pop();

        for (int i = 0; i < graph.neighbours[currNode].size(); i++)
        {
            int nextNode = graph.neighbours[currNode][i];
            if (nextNode == tree.parent[currNode])
            {
                continue;
            }

            tree.parent[nextNode] = currNode;
            tree.children[currNode].push_back(nextNode);
            q.push(nextNode);
        }
    }

    return tree;
}

void DFS(Tree& tree, int currNode)
{
    tree.toLeaf[currNode] = 0;

    if (tree.children[currNode].size() == 0)
    {
        return;
    }

    for (int i = 0; i < tree.children[currNode].size(); i++)
    {
        int nextNode = tree.children[currNode][i];
        DFS(tree, nextNode);

        tree.toLeaf[currNode] = max(tree.toLeaf[currNode], tree.toLeaf[nextNode] + 1);
    }
}

int GetDiameter(Tree& tree)
{
    #define ToLeafFromChild(x) tree.toLeaf[tree.children[tree.root][x]]

    if (tree.children[tree.root].size() == 0)
    {
        return 0;
    }
    else if (tree.children[tree.root].size() == 1)
    {
        return ToLeafFromChild(0) + 1;
    }

    int p = 0;
    for (int i = 1; i < tree.children[tree.root].size(); i++)
    {
        if (ToLeafFromChild(i) > ToLeafFromChild(p))
        {
            p = i;
        }
    }

    int q = 0;
    if (p == 0)
    {
        q++;
    }
    for (int i = q + 1; i < tree.children[tree.root].size(); i++)
    {
        if (q == p)
        {
            continue;
        }
        if (ToLeafFromChild(i) > ToLeafFromChild(q))
        {
            q = i;
        }
    }

    return ToLeafFromChild(p) + ToLeafFromChild(q) + 2;
}

int main()
{
    Tree tree = ReadTree();

    DFS(tree, tree.root);
    int diameter = GetDiameter(tree);

    cout << "The diameter of the tree is " << diameter << endl;

    return 0;
}