//  Solution to MIT Selection Contest problem--words
#include <iostream.h>
#include <string>

using namespace std;

string letters;
bool alpha[256];

int solve(string s)
{
	int n = s.size();
	int i, j=0, k;
	if (n == 0)
		return 0;
	
	for (i = 0; i < letters.size(); i++)
	{
		k = s.find_first_of(letters[i], 0);
		if (k >= s.size())
			return 0;
		if ( j < k )
			j = k;
	}

	if (j==s.size()-1)
		return 1;
	else
		return 1+solve(s.substr(j+1,s.size()-1-j));

}


main()
{
	string s;
	char S[100];
	int ncase = 0;
	int i;

	while (cin>>S)
	{
		s = S;

		ncase++;
		for (i = 0; i < 256; i++)
			alpha[i] = false;

		letters.resize(0);

		for (i = 0; i < s.size(); i++)
			if (!alpha[s[i]])
			{
				alpha[s[i]] = true;
				letters += s[i];
			}

		cout << "String " << ncase << ": " << solve(s) << endl;

	}

	return 0;

}