// Strongly connected components
//
//	Vladimir Novakovski, 11/20/2003

#include <assert.h>
#include <iostream.h>

const int MAXN=2000;
int  M, N;
bool G[MAXN][MAXN];
bool T[MAXN][MAXN];
bool FW[MAXN][MAXN];
int comp[MAXN];
bool visited[MAXN];
int number[MAXN]; // The number according to depth-first order
int index[MAXN];  // Inverse of number
int first[MAXN];
int last[MAXN];
int count;

void explore(int v)
{
	int i;
	int mycount = count+1;

	// Explores the graph

	number[v] = ++count;
	index[number[v]] = v;
	visited[v] = true;
	
	for (i = 0; i < N; i++)
		if (!visited[i] && G[v][i])
			explore(i);
		
	last[mycount] = count; 
}

void exploreT(int v)
{
	int i;
	
	// Explores the transpose of the graph

	visited[v] = true;

	//   This is the key to the algorithm.
	//   * first[comp[v]] is the root of the component in the original graph
	//   * last[<root>] is the last node that was accessible from that root
	//       The nature of depth-first search ensures that all accessible nodes
	//       from root are between <root> and last[<root>] inclusive.
	//   * number[i] is the number of the node that can be explored, and it 
	//       needs to be in the tree starting at the current root.

	int root = number[first[comp[v]]];
	int last_node = last[root];


	for (i = 0; i < N; i++)


		if (!visited[i] && T[v][i] && number[i] >= root && number[i] <= last_node)
		{
			comp[i] = comp[v];
			exploreT(i);
		}
		
	
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
			G[i][j] = p ? true : false;
			T[j][i] = G[i][j];
		}

	for (i = 0; i < N; i++)
		visited[i] = false;

	count = -1;


	for (i = 0; i < N; i++)
		if (!visited[i])
			explore(i);

	for (i = 0; i < N; i++)
	{
		comp[i] = -1;
		visited[i] = false;
	}

	M = 0;


	for (i = 0; i < N; i++)
		if (!visited[index[i]])
		{
			// Found a new root, hence a new component.
			first[M] = index[i];
			// The first array stores the root of the component.
			comp[index[i]] = M++;
			exploreT(index[i]);
		}


	
	cout << M << endl;

	
return 0;
}




























