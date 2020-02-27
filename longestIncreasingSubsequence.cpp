#include <iostream>
#include <algorithm>

using namespace std;
#define MaxNumberOfElements 1000

int GetLISsize(int arr[], int nummberOfElements)
{
    int bestEnd[MaxNumberOfElements];
    int length[MaxNumberOfElements];
    int maxLength;

    length[0] = 1;
    bestEnd[1] = arr[0];
    maxLength = 1;
    for (int i = 1; i < nummberOfElements; i++)
    {
        if (arr[i] < bestEnd[1])
        {
            bestEnd[1] = arr[i];
            length[i] = 1;
        }
        else if (arr[i] > bestEnd[maxLength])
        {
            length[i] = maxLength + 1;
            maxLength++;
            bestEnd[maxLength] = arr[i];
        }
        else
        {
            int k;
            int first = 1, last = maxLength - 1;
            while (first <= last)
            {
                k = (first + last) / 2;

                if (bestEnd[k] < arr[i] && bestEnd[k + 1] > arr[i])
                {
                    break;
                }
                else if (bestEnd[k] > arr[i])
                {
                    last = k - 1;
                }
                else
                {
                    first = k + 1;
                }
            }

            length[i] = k + 1;
            bestEnd[k + 1] = min(bestEnd[k + 1], arr[i]);
        }
    }

    return maxLength;
}

int main()
{
    int arr[MaxNumberOfElements];
    int numberOfElements;

    cin >> numberOfElements;
    for (int i = 0; i < numberOfElements; i++)
    {
        cin >> arr[i];
    }

    cout << GetLISsize(arr, numberOfElements) << endl;

    return 0;
}
