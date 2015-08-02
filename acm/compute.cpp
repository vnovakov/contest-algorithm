#include <iostream.h>
#include <string>
#include <string.h>
#include <strstrea.h>

using namespace std;


/*
Variable            Value
=========================
area                 1143
b                       0
length                 10
total                  80
width                 123
x                    1214
y                       0
*/

string var_names[100];
int var_vals[100];
int Nvars;

	
int var_index(string s)
{
	int i, j;
	j = -1;
	for (i = 0; i < Nvars; i++)
		if (var_names[i] == s)
		{ 
			j = i;
			break;
		}

	if (j == -1)
	{
		j = Nvars;
		var_names[Nvars++] = s;
	}

	return j;
}

int eval(string s)
{
	int paren[100];
	int i;
	cout << "Trying to evaluate " << s.c_str() << endl;

	paren[0] = s.at(0)=='(' ? 1 : 0;
	for (i = 1; i < s.size(); i++)
	{
		paren[i] = paren[i-1];
		int level =  paren[i-1];
		if (s.at(i-1) == ')')
			level--;
		if (s.at(i) == '(')
			paren[i] = level+1;
		
	}	


	return 0;
}

void parse(string s)
{
	
	s = s.substr(0, s.find_first_of(";",0));
	string vname;
	vname = s.substr(0,	s.find_first_of("=",0));
	vname = vname.substr( vname.find_first_not_of(" ",0), 
				vname.find_last_not_of(" ",0)- vname.find_first_not_of(" ",0)+1);
	
	
	int j = var_index(vname);

	var_vals[j] = eval(s.substr(s.find_first_of("=",0)+1,s.size()-s.find_first_of("=",0)-1));
	
}

main()
{

	char S[100];
	int Nlines;

	cin >> Nlines;
	
	Nvars = 0;
	cin.getline(S, 100);
	while (Nlines--)
	{
		cin.getline(S, 100);
		string s(S);
		parse(s);
		cout << s.c_str() << endl;
	}

	

	
	return 0;
}