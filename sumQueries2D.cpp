//You are given a 2D array of numbers with n rows and m columns
//You have q queries to process
//Each query gives you four numbers r1, c1, r2, c2
//You should calculate the sum of numbers on row r (r1 <= r <= r2) and col c (c1 <= c <= c2)
//O(n*m + q)

#include <iostream>

using namespace std;
#define MaxNumberOfRows 100
#define MaxNumberOfCols 100

int main()
{
    int arr[MaxNumberOfRows][MaxNumberOfCols];
    int numberOfRows, numberOfCols;
    cout << "Enter number of rows: ";
    cin >> numberOfRows;
    cout << "Enter number of columns: ";
    cin >> numberOfCols;

    for (int i = 0; i < numberOfRows; i++)
    {
        cout << "Enter row " << i << ": ";
        for (int j = 0; j < numberOfCols; j++)
        {
            cin >> arr[i][j];
        }
    }

    int sumArr[MaxNumberOfRows][MaxNumberOfCols];
    for (int i = 0; i < numberOfRows; i++)
    {
        int rowSum = 0;
        for (int j = 0; j < numberOfCols; j++)
        {
            rowSum += arr[i][j];
            sumArr[i][j] = rowSum;
            if (i > 0)
            {
                sumArr[i][j] += sumArr[i - 1][j];
            }
        }
    }

    int numberOfQueries;
    cout << "Enter number of queries: ";
    cin >> numberOfQueries;

    for (int q = 0; q < numberOfQueries; q++)
    {
        int r1, c1, r2, c2;
        cout << "Enter row and column for the top left corner and then for the bottom right one: ";
        cin >> r1 >> c1 >> r2 >> c2;

        int sum = sumArr[r2][c2];
        if (r1 > 0)
        {
            sum -= sumArr[r1 - 1][c2];
        }
        if (c1 > 0)
        {
            sum -= sumArr[r2][c1 - 1];
        }
        if (r1 > 0 && c1 > 0)
        {
            sum += sumArr[r1 - 1][c1 - 1];
        }

        cout << "Sum of that region is: " << sum << endl;
    }

    return 0;
}
