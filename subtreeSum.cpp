#include <iostream>
#include <vector>

using namespace std;
#define MaxNumberOfNodes 100

//The structure of the tree
vector<int> children[MaxNumberOfNodes]; //children[i] are the children of node i
int numberOfNodes;
int root;
int nodeValues[MaxNumberOfNodes];

int trIndex[MaxNumberOfNodes]; //trIndex[i] is the index that node i got with DFS
int trIndexInverse[MaxNumberOfNodes]; //trIndexInverse[i] is the node which got index i with DFS
int lastTrIndex;

int subtreeSize[MaxNumberOfNodes]; //subtreeSize[i] is the size of the subtree with root i

int segmentTree[MaxNumberOfNodes * 2];

void ReadTree()
{
    cout << "Enter the number of nodes: ";
    cin >> numberOfNodes;

    cout << "Enter the root: ";
    cin >> root;

    for (int i = 0; i < numberOfNodes; i++)
    {
        cout << "Enter children of node " << i << ". When done enter -1." << endl;
        int child;
        while (true)
        {
            cin >> child;
            if (child == -1)
            {
                break;
            }
            children[i].push_back(child);
        }
    }

    for (int i = 0; i < numberOfNodes; i++)
    {
        cout << "Enter the value of node " << i << ": ";
        cin >> nodeValues[i];
    }
}

//Traverses the tree with DFS and finds values of arrays trIndex, trIndexInverse, subtreeSize
void DFS(int start)
{
    trIndex[start] = lastTrIndex;
    trIndexInverse[lastTrIndex++] = start;

    subtreeSize[start] = 1;
    for (int i = 0; i < children[start].size(); i++)
    {
        int child = children[start][i];
        DFS(child);
        subtreeSize[start] += subtreeSize[child];
    }
}

void CreateSegmentTree()
{
    for (int i = 0; i < numberOfNodes; i++)
    {
        segmentTree[i + numberOfNodes] = nodeValues[trIndexInverse[i]];
    }

    for (int i = numberOfNodes - 1; i >= 0; i--)
    {
        segmentTree[i] = segmentTree[i * 2] + segmentTree[i * 2 + 1];
    }
}

//Calculates the sum of interval [a, b] in the segment tree
int GetIntervalSumFromSegmentTree(int a, int b)
{
    a += numberOfNodes;
    b += numberOfNodes;

    int intervalSum = 0;
    while (a <= b)
    {
        if (a % 2 == 1)
        {
            intervalSum += segmentTree[a];
            a++;
        }
        if (b % 2 == 0)
        {
            intervalSum += segmentTree[b];
            b--;
        }

        a /= 2;
        b /= 2;
    }

    return intervalSum;
}

//Updates value at x to k in the segment tree
void UpdateSegmentTreeValue(int x, int k)
{
    x += numberOfNodes;
    segmentTree[x] = k;

    x /= 2;
    while (x > 0)
    {
        segmentTree[x] = segmentTree[x * 2] + segmentTree[x * 2 + 1];
        x /= 2;
    }
}

//Calculates the sum of the nodes in the subtree with root x
int GetSubtreeSum(int x)
{
    return GetIntervalSumFromSegmentTree(trIndex[x], trIndex[x] + subtreeSize[x] - 1);
}

//Updates value at x to k in the tree
void UpdateTreeValue(int x, int k)
{
    nodeValues[x] = k;
    UpdateSegmentTreeValue(trIndex[x], k);
}

int main()
{
    ReadTree();
    DFS(root);
    CreateSegmentTree();

    int numberOfQueries;
    cout << "Enter number of queries: ";
    cin >> numberOfQueries;

    cout << "For each query enter 0 or 1 to choose the type of query - 0 for sum query, 1 for update query." << endl;
    cout << "If you choose sum query, enter a number x and you will get the sum of node values in the subtree with root x." << endl;
    cout << "If you choose update query, enter two numbers x and k and you will update the value of node x to k." << endl;
    for (int i = 0; i < numberOfQueries; i++)
    {
        int q;
        cin >> q;

        if (q == 0)
        {
            int x;
            cin >> x;
            cout << "The sum of the subtree with root " << x << " is " << GetSubtreeSum(x) << endl;
        }
        else
        {
            int x, k;
            cin >> x >> k;
            UpdateTreeValue(x, k);
            cout << "Value of node " << x << " updated to " << k << endl;
        }
    }

    return 0;
}
