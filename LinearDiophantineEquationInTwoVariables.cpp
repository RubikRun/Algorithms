/*
x, y - variables
a, b, c - constants

We are looking for a solution to the equation:
ax + by = c

Algorithm:
1.Let d = gcd(a, b). If d does not divide c, then the equation has no solutions and we stop here.
2.When finding the gcd, we use Eucliden algorithm with division and keep track of all steps.
  We then use them to find x' and y' such that ax' + by' = d (This approach is called Extended Euclidean Algorithm)
3.Let d' = c / d.
  Then multiplying the equation from step 2 by d' gets us ax'd' + by'd' = c
  A solution has been found: x = x'd', y = y'd'

Time Complexity: O(logn)
Space Complexity: O(logn)
*/

#include <iostream>
#include <vector>

using namespace std;

pair<int, int> GetSolution(int a, int b, int c)
{
	bool swapped = false;
	if (a < b)
	{
		int t = a;
		a = b;
		b = t;
		swapped = true;
	}

	vector<int> g = {a, b};
	while (g.back() != 0)
	{
		g.push_back(g[g.size() - 2] % g[g.size() - 1]);
	}
	g.pop_back();

	int d = g.back();

	if (c % d != 0)
	{
		return {0, 0};
	}

	vector<pair<int, int>> v = {{1, 0}, {0, 1}};
	for (int i = 2; i < g.size(); i++)
	{
		v.push_back({v[i - 2].first - (g[i - 2] / g[i - 1]) * v[i - 1].first, v[i - 2].second - (g[i - 2] / g[i - 1]) * v[i - 1].second});
	}

	int xx = v.back().first, yy = v.back().second;
	int dd = c / d;
	int x = dd * xx, y = dd * yy;

	if (swapped) return {y, x};
	else return {x, y};
}

int main()
{
	int a, b, c;
	cin >> a >> b >> c;

	pair<int, int> solution = GetSolution(a, b, c);
	if (solution.first == 0 && solution.second == 0)
	{
		cout << "No solutions" << endl;
	}
	else
	{
		cout << "Solution: " << solution.first << ", " << solution.second << endl;
	}

	return 0;
}