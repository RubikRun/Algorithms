//You are given an array of n numbers
//You have q queries each of which is either updating an array value or asking for an interval sum
//Preprocessing: O(n)
//Update query: O(log n)
//Sum query: O(log n)

#include <iostream>

using namespace std;
#define MaxArrLen 32768

int arrLen;
int tree[MaxArrLen * 2];

void Input()
{
    int numberOfInputElements;
    cout << "Enter number of array elements: ";
    cin >> numberOfInputElements;

    //Finding next power of two
    arrLen = 1;
    while (arrLen <= numberOfInputElements)
    {
        arrLen *= 2;
    }

    cout << "Enter array elements: ";
    for (int i = arrLen; i < arrLen * 2; i++)
    {
        if (i < arrLen + numberOfInputElements)
        {
            cin >> tree[i];
        }
        else
        {
            tree[i] = 0;
        }
    }
}

void CreateTree()
{
    for (int i = arrLen - 1; i >= 1; i--)
    {
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }
}

//Updates the value of element k to x
void UpdateValue(int k, int x)
{
    k += arrLen;
    tree[k] = x;
    k /= 2;

    while (k >= 1)
    {
        tree[k] = tree[k * 2] + tree[k * 2 + 1];
        k /= 2;
    }
}

//Calculates the sum of elements in interval [a, b]
int GetIntervalSum(int a, int b)
{
    a += arrLen;
    b += arrLen;

    int sum = 0;
    while (a <= b)
    {
        if (a % 2 == 1)
        {
            sum += tree[a];
            a++;
        }
        if (b % 2 == 0)
        {
            sum += tree[b];
            b--;
        }
        a /= 2;
        b /= 2;
    }

    return sum;
}

int main()
{
    Input();
    CreateTree();

    int numberOfQueries;
    cout << "Enter the number of queries: ";
    cin >> numberOfQueries;

    cout << "For each query enter three numbers q, a, b" << endl;
    cout << "q = 0 if you want the sum of elements in interval [a, b]" << endl;
    cout << "q = 1 if you want to update the element at index a to value b" << endl;
    for (int i = 0; i < numberOfQueries; i++)
    {
        int q, a, b;
        cin >> q >> a >> b;

        if (q == 0)
        {
            cout << "Sum of elements in [" << a << ", " << b << "] is " << GetIntervalSum(a, b) << endl;
        }
        else
        {
            UpdateValue(a, b);
            cout << "Value at " << a << " updated to " << b << endl;
        }
    }

    return 0;
}
