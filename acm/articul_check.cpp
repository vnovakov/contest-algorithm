//  Finds articulation points in an undirected graph
//
//		-Vladimir Novakovski
//			11/23/2003

#include <assert.h>
#include <iostream.h>

const int MAXN=100;
int N;
bool graph[MAXN][MAXN];
bool art[MAXN];
int low[MAXN];
int number[MAXN];
bool visited[MAXN];
int count;

bool check(void)
{
	// Checks that points are articulation points

	bool FW[MAXN][MAXN];
	int i, j, k, l;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			for (k = 0; k < N; k++)
				if (j != i && k != i)
					FW[j][k] = graph[j][k];
				else
					FW[j][k] = false;

		for (j = 0; j < N; j++)
			for (k = 0; k < N; k++)
				for (l = 0; l < N; l++)
					FW[k][l] |= FW[k][j] && FW[j][l];

		bool isCon = true;
		for (j = 0; j < N; j++)
			for (k = 0; k < N; k++)
				if (j != i && k != i && !FW[j][k])
					isCon = false;

		
		if (isCon == art[i])
		{
			cout << i << " I think that isCon=" << isCon<< endl;
			return false;

		}

	}

	return true;

}

void explore(int v)
{

	int i;
	int degree= 0;   // This is the number of direct children of this node

	number[v] = count++; 
	visited[v] = true;
	low[v] = number[v];   // Low keeps track of the lowest-index direct
						  // ancestor that can be reached from v or its children.
	bool go_up = true;
	
	for (i = 0; i < N; i++)
		if (graph[v][i] && !visited[i])
		{
			

			degree++;

			explore(i);
			
			if (low[i] >= number[v])
			{
				// If the highest-up parent that this child is connected to
				// is just v, then v is essential for the child's connectedness
				go_up = false;
			}

			//  If a child is connected higher up than me, then update my low value
			if (low[i] < low[v])
				low[v] = low[i];

			
		}

	for (i = 0; i < N; i++)
		if (graph[v][i] && visited[i])
		{
			//  If there is backedge to somebody higher up than I've seen so far,
			//   make my low value the number of that ancestor
			if (number[i] < low[v])
				low[v] = number[i];

		}

	/**** This assumes that the explore starts with 0 ****/
		//  Should not be an issue but double-check with main() function. -VN
	if (v == 0 && degree==1)
		art[v] = false;   // Root is special---articulation iff two or more children
	else if (v == 0 && degree > 1)
		art[v] = true;
	// Otherwise just use the go_up (do all my children go up) criterion
	else if (go_up)
		art[v] = false;
	else
		art[v] = true;

	

}

main()
{
	int i, j;

	cin >> N;

	assert(N<=MAXN);

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			int p;
			cin >> p;
			graph[i][j] = p ? true : false;
		}


	count = 0;

	explore(0);

	int M = 0;

	for (i = 0 ; i < N; i++)
		M += visited[i];
	
	if (M < N - 1)
	{
		for (j = 0; j < N; j++)
			art[j] = true;
	} else if (M == N - 1)
	{
		for (j = 0; j < N; j++)
			art[j] = visited[j];

	}

	cout << "Removing these nodes will disconnect the city:" << endl;
	for (i = 0; i < N; i++)
		if (art[i]) 
			cout << i + 1 << endl;
	if (check())
		cout << "Check passed" << endl;
	else
		cout << "Check failed" << endl;

	return 0;
}
