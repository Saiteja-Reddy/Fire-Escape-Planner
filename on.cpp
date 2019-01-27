#include <bits/stdc++.h>
#include <curses.h>
#include <unistd.h>

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
			solution[i][j] = 1;
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
		// cout << "Done" << endl;
		return;
	}

	grid[x][y] = 0;

	if(solution[x+1][y])
	{
		if(grid[x+1][y] == 69)
		{
			// cout << "Done" << endl;
			return;
		}
		grid[x+1][y] = 83;
	} 
	else if(solution[x][y+1])
	{
		if(grid[x][y+1] == 69)
		{
			// cout << "Done" << endl;
			return;
		}

		grid[x][y+1] = 83;
	}
	else if(solution[x-1][y])
	{
		if(grid[x-1][y] == 69)
		{
			// cout << "Done" << endl;
			return;
		}

		grid[x-1][y] = 83;
	}
	else
	{
		if(grid[x][y-1] == 69)
		{
			// cout << "Done" << endl;
			return;
		}

		grid[x][y-1] = 83;
	}	
}

void print_to_screen(WINDOW * win, int mat[M][N])
{
	int off_x = 3;
	int off_y = 3;

	for (int i = 0; i < M; ++i)
	{
		off_y = 3 + i;
		for (int j = 0; j < N; ++j)
		{
			if(mat[i][j] == 0)
				mvwaddch(win, off_y, off_x + j, '0' | COLOR_PAIR(4));
			if(mat[i][j] == 1)
				mvwaddch(win, off_y, off_x + j, '1' | COLOR_PAIR(2));
			if(mat[i][j] == 83)
				mvwaddch(win, off_y, off_x + j, 'S' | COLOR_PAIR(5));
			if(mat[i][j] == 69)
				mvwaddch(win, off_y, off_x + j, 'E' | COLOR_PAIR(3));			
		}
	}
	wrefresh(win);
	sleep(1);
}

void move(WINDOW * win, int mat[M][N])
{
	vector <pair<int, int> > starts = find_start(mat);
	if(starts.size() == 0)
	{
		// cout << "No one to Escape!" << endl;
		return;
	}
	int min_dist = INT_MAX;
	
	int visited[M][N];
	memset(visited, 0, sizeof visited);	

	findShortestPath_Util(mat, visited, starts[0].first, starts[0].second, min_dist, 0);
	// cout << "solution: " << endl;
	// print_grid(solution);

	if(min_dist != INT_MAX)
	{
		get_next_step(mat, solution, starts[0].first, starts[0].second);
		// cout << "Done" << endl;
		// print_grid(mat);
		print_to_screen(win, mat);
	}
	else
	{
		// cout << "Can't Move!!" << endl;
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

	initscr();
	start_color();	
	use_default_colors();
	int h, w;
   	getmaxyx(stdscr, h, w);
	WINDOW * win = newwin(h/2, w/4, 5, 5);
	noecho();
	curs_set(0);
	wclear(win);
	wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);

	init_pair(1, COLOR_RED, -1);	
	init_pair(2, COLOR_BLACK, -1);	
	init_pair(3, COLOR_BLUE, -1);	
	init_pair(4, COLOR_WHITE, -1);	
	init_pair(5, COLOR_GREEN, -1);	



	wrefresh(win);

	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);
	move(win, mat);

	
	endwin();
	return 0;
}