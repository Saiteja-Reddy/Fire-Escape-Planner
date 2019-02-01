#include <bits/stdc++.h>
#include <curses.h>
#include <unistd.h>

using namespace std;
 
#define M 10
#define N 10

bool isSafe(int mat[M][N], int visited[M][N], int x, int y)
{
	if (mat[x][y] == 1 || mat[x][y] == 12 || visited[x][y])
		return false;
 
	return true;
}
 
bool isValid(int x, int y)
{
	if (x < M && y < N && x >= 0 && y >= 0)
		return true;
	 
	return false;
}

bool isValidFire(int mat[M][N],int x, int y)
{
	if (x < M && y < N && x >= 0 && y >= 0 && mat[x][y] == 0)
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
int final_x, final_y;

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
			final_x = i;
			final_y = j;
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
			if(mat[i][j] >= 'S')
			{
				if(mat[i][j] == 'S')
					a.push_back(make_pair(i, j));
				else
				{
					int r = mat[i][j] - 'S' + 1; 
					while(r--)
					{
						a.push_back(make_pair(i, j));
					}
				}
			}

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

vector <pair<int, int> > find_fire(int mat[M][N]) 
{
	vector <pair<int, int> > a;
	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if(mat[i][j] == 12)
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

	if(grid[x][y] == 83)
		grid[x][y] = 0;
	else
		grid[x][y]--;

	if(solution[x+1][y])
	{
		if(grid[x+1][y] == 69)
		{
			// cout << "Done" << endl;
			return;
		}
		if(grid[x+1][y] == 0)
			grid[x+1][y] = 83;
		else
			grid[x+1][y]++;
	} 
	else if(solution[x][y+1])
	{
		if(grid[x][y+1] == 69)
		{
			// cout << "Done" << endl;
			return;
		}
		if(grid[x][y+1] == 0)
			grid[x][y+1] = 83;
		else
			grid[x][y+1]++;
	}
	else if(solution[x-1][y])
	{
		if(grid[x-1][y] == 69)
		{
			// cout << "Done" << endl;
			return;
		}
		if(grid[x-1][y] == 0)
			grid[x-1][y] = 83;
		else
			grid[x-1][y]++;
	}
	else
	{
		if(grid[x][y-1] == 69)
		{
			// cout << "Done" << endl;
			return;
		}
		if(grid[x][y-1] == 0)
			grid[x][y-1] = 83;
		else
			grid[x][y-1]++;
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
			if(mat[i][j] >= 83)
				mvwaddch(win, off_y, off_x + j, mat[i][j] - 83 + '1' | COLOR_PAIR(5));
			if(mat[i][j] == 69)
				mvwaddch(win, off_y, off_x + j, 'E' | COLOR_PAIR(3));			
			if(mat[i][j] == 12)
				mvwaddch(win, off_y, off_x + j, 'F' | COLOR_PAIR(6) | A_BOLD);			

		}
	}
	wrefresh(win);
	sleep(1);
}



int FC = 0;

void move_fire(int mat[M][N])
{
	FC++;
	if(FC%2 == 0)
	{
		int x, y;
		vector <pair<int, int> > fires = find_fire(mat);
		for(auto& fire: fires)
		{
			x = fire.first;
			y = fire.second;
			if(isValidFire(mat, x+1, y))	
				mat[x+1][y] = 12;
			if(isValidFire(mat, x-1, y))	
				mat[x-1][y] = 12;			
			if(isValidFire(mat, x, y-1))	
				mat[x][y-1] = 12;			
			if(isValidFire(mat, x, y+1))	
				mat[x][y+1] = 12;			
		}
	}
	return;
}

void move(WINDOW * win, int mat[M][N])
// void move(int mat[M][N])
{
	vector <pair<int, int> > starts = find_start(mat);
	if(starts.size() == 0)
	{
		// cout << "No one to Escape!" << endl;
		return;
	}


	int exits_map[M][N];
	memset(exits_map, 0, sizeof exits_map);	

	vector <pair<int, int> > mark_exit;	

	for(auto& start: starts)
	{

		for(;;)
		{
			int min_dist = INT_MAX;
	
			int visited[M][N];
			memset(visited, 0, sizeof visited);				

			findShortestPath_Util(mat, visited, start.first, start.second, min_dist, 0);
			// cout << "solution: " << endl;
			// print_grid(solution);
				if(min_dist != INT_MAX)
				{
					if(exits_map[final_x][final_y] < 2)
					{
						// cout << final_x << " " << final_y << endl;
						exits_map[final_x][final_y]++;
						get_next_step(mat, solution, start.first, start.second);
						break;
					}
					else
					{
						mark_exit.push_back(make_pair(final_x, final_y));
						mat[final_x][final_y] = 1;
						// cout << final_x << " " << final_y << endl;
					}
					// cout << "Done" << endl;
					// print_grid(mat);
				}
				else
				{
					// cout << "Can't Move!!" << endl;
					break;
				}
		}
		
		// print_to_screen(win, mat);

	}

	for(auto& exit_n: mark_exit)
	{
		mat[exit_n.first][exit_n.second] = 69;
	}

	move_fire(mat);

	print_to_screen(win, mat);

}


int read_grid(int grid[M][N])
{
	char num;
	ifstream fp("grid.txt");
	if (! fp) {
	    cout << "Error, file couldn't be opened" << endl; 
	    return 0; 
	}    
	for(int row = 0; row < M; row++) {  // stop loops if nothing to read
	   for(int column = 0; column < N; column++){
	   		fp >> num;
	   		if(num == '1' || num == '0')
	   			grid[row][column] = num - '0';
	   		else if(num == 'S')
	   			grid[row][column] = 83;
	   		else if(num == 'E')
	   			grid[row][column] = 69;
	   		else if(num == 'F')
	   			grid[row][column] = 12;	   				   		
	        if ( !fp ) {
	           cout << "Error reading file for element " << row << "," << column << endl; 
	           return 0; 
	        }
	    }
	}
	return 1;	
}

int write_grid(int grid[M][N])
{
	char num;
	ofstream fp("test.txt");
	if (! fp) {
	    cout << "Error, file couldn't be opened" << endl; 
	    return 0; 
	}    
	for(int row = 0; row < M; row++) {  // stop loops if nothing to read
	   for(int column = 0; column < N; column++){
	   		if(grid[row][column] == 1 || grid[row][column] == 0)
	   			num = grid[row][column] + '0';
	   		else if(grid[row][column] == 63)
	   			num = 'S';
	   		else if(grid[row][column] == 69)
	   			num = 'E';
	   		else if(grid[row][column] == 12)
	   			num = 'F';

	   		fp << num << ' ';
	    }
	    if(row != M-1)
	    	fp << "\n";
	}
	return 1;	
}

int main()
{
	int mat[M][N];

	read_grid(mat);

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
	init_pair(6, COLOR_YELLOW, -1);	

	print_to_screen(win, mat);


	wrefresh(win);

	for (int i = 0; i < 20; ++i)
	{
		move(win, mat);
		write_grid(mat);
	}

	// move(mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);
	// move(win, mat);

	
	endwin();
	return 0;
}