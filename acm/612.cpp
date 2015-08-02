#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void run612()
{


	int m, n;
	cin >> m >> n;

	vector<string> A(n);
	vector<pair<int, string> > B(n);

	for (int i = 0; i < n; i++)
	{
		cin >> A[i];
		int count = 0;
		for (int j = 0; j < m; j++)
			for (int k = 0; k < j; k++)
				if (A[i][j] < A[i][k])
					count++;
		B[i] = pair<int, string>(-count, A[i]);
	}

	sort(B.begin(), B.end(), less<pair<int, string> >() );

	for (i = 0; i < n; i++)
		cout << B[i].second << endl;

}