/*
Given a set of coin values {c1, c2, ..., cn} and a target value k,
find the number of different ways to reach the value k
using coins with the given coin values (order matters)

This is solved easily by dynamic programming.
Let's say dp[x] is the number of ways to reach x.
Then dp[x] = dp[x - c1] + dp[x - c2] + ... + dp[x - cn],
of course each dp[x - ci] is added only if x - ci >= 0.
The base case is dp[0] = 1 because we can reach 0 in 1 way:
by doing nothing

Time Complexity: O(k * n)
Space Complexity: O(k)
*/

#include <iostream>

using namespace std;
#define MaxNumberOfCoinValues 1000
#define MaxTargetSum 1000

int coinValues[MaxNumberOfCoinValues];
int numberOfCoinValues;

int targetSum;

int numberOfWays[MaxTargetSum + 1];

void Input()
{
	cin >> numberOfCoinValues;

	for (int i = 0; i < numberOfCoinValues; i++)
	{
		cin >> coinValues[i];
	}

	cin >> targetSum;
}

int GetNumberOfWays()
{
	numberOfWays[0] = 1;

	for (int i = 1; i <= targetSum; i++)
	{
		numberOfWays[i] = 0;
		for (int j = 0; j < numberOfCoinValues; j++)
		{
			if (i - coinValues[j] >= 0)
			{
				numberOfWays[i] += numberOfWays[i - coinValues[j]];
			}
		}
	}

	return numberOfWays[targetSum];
}

int main()
{
	Input();

	cout << GetNumberOfWays() << endl;

	return 0;
}