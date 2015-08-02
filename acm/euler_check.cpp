// Finds Eulerian cycles and paths in an undirected graph
//
//		- Vladimir Novakovski, 11/26/2003


#include <assert.h>
#include <iostream.h>
#include <string>

using namespace std;

typedef basic_string<int> Array;

const int MAXN = 1000;

bool graph[MAXN][MAXN];
bool visited[MAXN][MAXN];
int degree[MAXN];
int N;
int start, finish;

bool check(Array p)
{

	int i, j;
	bool works = true;
	
	for (i = 0;  i < N; i++)
		for (j = 0; j < N; j++)
			visited[i][j] = false;

	for (i = 0 ; i < p.size()-1; i++)
	{
		int  a = p[i];
		int  b = p[i+1];

		if (!graph[a][b])
		{
			cout << "The edge " << a+1 << " " << b+1 << " is invalid." << endl;
			works = false;
		}

		visited[a][b] = true;
		visited[b][a] = true;

	}

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			if (!visited[i][j] && graph[i][j])
			{
				cout << "The edge " << i+1 << " " << j+1 << " is not visited." << endl;
				works =false;
			}

	return works;
}


bool explore(int v, int w, Array &p)
{
//  This algorithm is not fully optimal---O(V^3) instead of O(E).
//  because it only uses an adjacency-matrix representation.
//  Revise if efficiency is required.  -VN

	int i;
	
	
	bool nowhere_to_go = true;
	bool not_end_in_finish = true;
	p.resize(0);
	
	p += v;
	Array q, r;
	r.resize(0);

	for (i = 0; i < N; i++)
		if (graph[v][i] && !visited[v][i])
		{
			nowhere_to_go = false;
			visited[v][i] = true;
			visited[i][v] = true;

			if (explore(i,w,q))
			{
				r += q;				// Found a path that ends at the Finish
			
				not_end_in_finish = false;
			}
			else {
				p += q;				// Found a cycle that ends here at v
			}

		}

	p += r;

	if (nowhere_to_go)
		return (v==w);
	 else 
		return  !not_end_in_finish;

}



main()
{
	int i, j;
	Array answer;

	cin >> N;

	assert(N<=MAXN);

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			int p;
			cin >> p;
			graph[i][j] = p ? true : false;
			visited[i][j] = false;

		}


	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			assert(graph[i][j] == graph[j][i]);

	// Compute degrees of the vertices
	for (i = 0; i < N; i++)
	{
		degree[i] = 0;
		for (j = 0; j < N; j++)
			degree[i] += graph[i][j];
	}

	int odd_count = 0;
	start = -1;
	finish = -1;

	for (i = 0; i < N; i++)
	{
		if (degree[i] % 2 == 1 && start == -1)
			start = i;
		else if (degree[i] % 2 == 1 && finish == -1)
			finish = i;
					
		odd_count += degree[i] % 2;

	}

	assert(odd_count % 2 == 0);  // The handshake lemma

	if (start == -1)
		start = 0;
	if (finish == -1)
		finish = 0;
	
	if (odd_count > 2)
		cout << "There are no Eulerian circuits in this graph" << endl;
	else 
	{

		explore(start, finish, answer);

		cout << "There is an Eulerian circuit starting at "<< start+1 <<
				" and ending at " << finish+1 << ":" <<  endl;
		for (i = 0; i < answer.size(); i++)
			cout << answer[i] + 1 << endl;

			if (check(answer))
		cout << "Check passed" << endl;
			else
		cout << "Check failed" << endl;

	}



	return 0;
}