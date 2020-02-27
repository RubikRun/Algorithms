//You are given a rooted tree of size n
//You have q queries to process
//Each query asks for the k-th ancestor of the node x
//Preprocessing: O(n * log n)
//Each query: O(log k)

#include <iostream>

using namespace std;
#define MaxNumberOfNodes 1024
#define NumberOfPowersOfTwo 11

//The structure of the tree is represented in this array
//parent[i] should be the parent of node i
int parent[MaxNumberOfNodes];
int numberOfNodes;
//The root of the tree. The only node with no parent
//parent[root] should be -1
int root;
//powerAncestor[i][j] should be the (2 ^ j)-th ancestor of node i
//powerAncestor[i][j] should be -1 if there is no such ancestor
int powerAncestor[MaxNumberOfNodes][NumberOfPowersOfTwo];

void ReadTree()
{
    cout << "Enter number of nodes: ";
    cin >> numberOfNodes;

    cout << "For each node enter its parent: ";
    for (int i = 0; i < numberOfNodes; i++)
    {
        cin >> parent[i];
    }
}

void FillPowerAncestor()
{
    int t = 1;
    while (t <= numberOfNodes)
    {
        for (int i = 0; i < numberOfNodes; i++)
        {
            if (t == 1)
            {
                powerAncestor[i][t] = parent[i];
                continue;
            }
            powerAncestor[i][t] = powerAncestor[i][t / 2];
            for (int j = 0; j < t / 2; j++)
            {
                powerAncestor[i][t] = parent[powerAncestor[i][t]];
                if (powerAncestor[i][t] == -1)
                {
                    break;
                }
            }
        }
        t *= 2;
    }
}

//Processing a query
int GetAncestor(int x, int k)
{
    int t = 1;
    while (t * 2 <= k)
    {
        t *= 2;
    }

    int ancestor = x;
    while (k > 0)
    {
        if (t <= k)
        {
            ancestor = powerAncestor[ancestor][t];
            k -= t;
            if (ancestor == -1)
            {
                break;
            }
        }
        t /= 2;
    }

    return ancestor;
}

int main()
{
    ReadTree();
    FillPowerAncestor();

    int numberOfQueries;
    cout << "Enter number of queries: ";
    cin >> numberOfQueries;

    for (int i = 0; i < numberOfQueries; i++)
    {
        cout << "Enter a node and an ancestor number: ";
        int x, k;
        cin >> x >> k;
        cout << "The " << k << "-th ancestor of node " << x << " is " << GetAncestor(x, k) << endl;
    }

    return 0;
}
