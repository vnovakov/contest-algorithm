#include <iostream.h>
#include <string.h>


int nVars = 0;
int lenVar[100];
char vars[100][100];


void main()
{
	char S[100];
	int nLines;
	int i, j;
	
	
	cin >> nLines;

	cin.getline(S, 100);
	
	for (i = 0; i < nLines; i++)
	{
		cin.getline(S, 100);

		for (j = 0; j < strlen(S); j++)
			if (S[j] == '=')
				break;

		
		for (k = strlen(S)-1; k >= 0; k--)
			if (S[k] == ';')
				break;

		for (
	}

	return 0;


}