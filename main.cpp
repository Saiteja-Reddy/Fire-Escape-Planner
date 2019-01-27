#include <bits/stdc++.h>
#include <curses.h>
using namespace std;
 
#define M 10
#define N 10

bool isSafe(int mat[M][N], int visited[M][N], int x, int y)
{
	if (mat[x][y] == 1 || visited[x][y])
		return false;
 
	return true;
}
 
bool isValid(int x, int y)
{
	if (x < M && y < N && x >= 0 && y >= 0)
		return true;
	 
	return false;
}

void print_grid(int visited[M][N])
{
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cout << visited[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int solution[M][N];

void copy_sol(int visited[M][N])
{
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
			solution[i][j] = visited[i][j];
}

void findShortestPath(int mat[M][N], int visited[M][N], int i, int j,
				int& min_dist, int dist)
{
	if (mat[i][j]  == 'E') 
	{
		if(dist < min_dist)
		{
			min_dist = dist;
			copy_sol(visited);
		}


		return;
	}

	visited[i][j] = 1;
	 
	if (isValid(i + 1, j) && isSafe(mat, visited, i + 1, j))
		findShortestPath(mat, visited, i + 1, j, min_dist, dist + 1);
 
	if (isValid(i, j + 1) && isSafe(mat, visited, i, j + 1))
		findShortestPath(mat, visited, i, j + 1, min_dist, dist + 1);
	 
	if (isValid(i - 1, j) && isSafe(mat, visited, i - 1, j))
		findShortestPath(mat, visited, i - 1, j, min_dist, dist + 1);
	 
	if (isValid(i, j - 1) && isSafe(mat, visited, i, j - 1))
		findShortestPath(mat, visited, i, j - 1, min_dist, dist + 1);
	 
	visited[i][j] = 0;
}

void findShortestPath_Util(int mat[M][N], int visited[M][N], int i, int j,
				int& min_dist, int dist)
{
	memset(solution, 0, sizeof solution);
	findShortestPath(mat, visited, i, j, min_dist, 0);
}

vector <pair<int, int> > find_start(int mat[M][N]) 
{
	vector <pair<int, int> > a;
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if(mat[i][j] == 'S')
				a.push_back(make_pair(i, j));
		}
	}
	return a;
}

vector <pair<int, int> > find_exit(int mat[M][N]) 
{
	vector <pair<int, int> > a;
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if(mat[i][j] == 'E')
				a.push_back(make_pair(i, j));
		}
	}
	return a;
}

void get_trajectory(int grid[M][N], int sol[M][N], int mat[M][N], int x, int y)
{
	mat[x][y] = 1;
	print_grid(mat);
	cout << endl;

	if(grid[x][y] == 69)
	{
		cout << "Done";
		return;
	}

	mat[x][y] = 0;
	sol[x][y] = 0;

	if(sol[x+1][y])
	{
		get_trajectory(grid, sol, mat, x+1, y);
	} 
	else if(sol[x][y+1])
	{
		get_trajectory(grid,sol, mat, x, y+1);
	}
	else if(sol[x-1][y])
	{
		get_trajectory(grid, sol, mat, x-1, y);
	}
	else
	{
		get_trajectory(grid,sol, mat, x, y-1);
	}

	return;
}

void get_trajectory_util(int grid[M][N], int solution[M][N], int x, int y)
{
	int sol[M][N];
	int mat[M][N];
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
		{
			sol[i][j] = solution[i][j];
			mat[i][j] = 0;
		}
	get_trajectory(grid, sol, mat, x,  y);

}




int main()
{
	int mat[M][N] = 
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1,83, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
		{69, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};
 
	int visited[M][N];

	memset(visited, 0, sizeof visited);
	
	int min_dist = INT_MAX;

	vector <pair<int, int> > starts = find_start(mat);
	
	findShortestPath_Util(mat, visited, starts[0].first, starts[0].second, min_dist, 0);

	get_trajectory_util(mat, solution, starts[0].first, starts[0].second);

	if(min_dist != INT_MAX)
	{
		cout << "The shortest path from source to destination "
				"has length " << min_dist << endl;
		print_grid(solution);
	}
	else 
		cout << "Destination can't be reached from given source";
	
	return 0;
}