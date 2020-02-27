//You are given a list of n numbers
//You have q queries to process.
//Each query gives you two numbers a and b. You should calculate the sum of numbers in [a, b] in the list
//O(n + q)

#include <iostream>

using namespace std;
#define MaxArrLen 1000

int main()
{
    int arr[MaxArrLen];
    int arrLen;

    cout << "Enter length of your array: ";
    cin >> arrLen;

    cout << "Enter your array: ";
    for (int i = 0; i < arrLen; i++)
    {
        cin >> arr[i];
    }

    int sumArr[MaxArrLen] = {arr[0]};
    for (int i = 1; i < arrLen; i++)
    {
        sumArr[i] = sumArr[i - 1] + arr[i];
    }

    int numOfQueries;
    cout << "Enter number of queries: ";
    cin >> numOfQueries;

    for (int i = 0; i < numOfQueries; i++)
    {
        int a, b;
        cout << "Enter interval's ends: ";
        cin >> a >> b;

        int sum = sumArr[b];
        if (a > 0)
        {
            sum -= sumArr[a - 1];
        }

        cout << "Sum of numbers in [" << a << ", " << b << "] is " << sum << endl;
    }

    return 0;
}
