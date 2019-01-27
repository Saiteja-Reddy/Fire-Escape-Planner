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

void get_next_step(int grid[M][N], int solution[M][N], int x, int y)
{
	if(grid[x][y] == 69)
	{
		cout << "Done";
		return;
	}

	grid[x][y] = 0;

	if(solution[x+1][y])
	{
		grid[x+1][y] = 83;
	} 
	else if(solution[x][y+1])
	{
		grid[x][y+1] = 83;
	}
	else if(solution[x-1][y])
	{
		grid[x-1][y] = 83;
	}
	else
	{
		grid[x][y-1] = 83;
	}	
}


void move(int mat[M][N])
{
	vector <pair<int, int> > starts = find_start(mat);
	int min_dist = INT_MAX;
	
	int visited[M][N];
	memset(visited, 0, sizeof visited);	

	findShortestPath_Util(mat, visited, starts[0].first, starts[0].second, min_dist, 0);

	if(min_dist != INT_MAX)
	{
		get_next_step(mat, solution, starts[0].first, starts[0].second);
		print_grid(mat);
	}
	else
	{
		cout << "Can't Move!!" << endl;
	}



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
 
	// int visited[M][N];

	// memset(visited, 0, sizeof visited);
	
	// int min_dist = INT_MAX;

	// vector <pair<int, int> > starts = find_start(mat);
	
	// findShortestPath_Util(mat, visited, starts[0].first, starts[0].second, min_dist, 0);

	// get_trajectory_util(mat, solution, starts[0].first, starts[0].second);

	move(mat);
	move(mat);
	move(mat);
	move(mat);
	move(mat);
	move(mat);
	move(mat);
	move(mat);
	move(mat);
	move(mat);
	move(mat);
	move(mat);
	move(mat);
	move(mat);
	move(mat);

	// if(min_dist != INT_MAX)
	// {
	// 	cout << "The shortest path from source to destination "
	// 			"has length " << min_dist << endl;
	// 	print_grid(solution);
	// }
	// else 
	// 	cout << "Destination can't be reached from given source";
	
	return 0;
}