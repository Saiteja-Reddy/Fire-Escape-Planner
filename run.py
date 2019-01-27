import numpy as np
from copy import deepcopy

def find_starts(grid):
	starts = []
	for i in range(0, 10):
		for j in range(0, 10):
			if grid[i][j] == 'S':
				starts.append((i,j))
	return starts

def print_grid(grid):
	print("Grid Now is: ")
	for i in range(0, 10):
		print(' '.join(grid[i]))


f = open('grid.txt', 'r')
grid = f.readlines()
grid = list(map(str.rstrip, grid))
dims = grid[0].split()
grid = grid[1:]
grid = list(map(str.split, grid))
print(dims)
print_grid(grid)

starts = find_starts(grid)
print(starts)

def isSafe(grid, sol, x, y):
	if(x>=0 and y>=0 and x<10 and y<10 and grid[x][y] is not '1' and sol[x][y] is not 'S'):
		return True
	return False

solution = None

def solveMazeUtil(grid, x, y, sol, dis):
	global solution
	if(grid[x][y] == 'E'):
		sol[x][y] = 'S'

		if solution is None:
			solution = (deepcopy(sol), dis)
			return

		if dis < solution[1]:
			solution = (deepcopy(sol), dis)
		return

	if(isSafe(grid, sol, x, y)):
		sol[x][y] = 'S'
		solveMazeUtil(grid, x, y+1, sol, dis+1)
		solveMazeUtil(grid, x+1, y, sol, dis+1)
		solveMazeUtil(grid, x-1, y, sol, dis+1)
		solveMazeUtil(grid, x, y-1, sol, dis+1)
		sol[x][y] = '0'


def find_path(grid):
	 global solution
	 sol = [['0' for x in range(10)] for y in range(10)]
	 solveMazeUtil(grid, 1, 1, sol, 0)
	 if solution:
	 	print_grid(solution[0])
	 else:
	 	print("No Path Exists!!")

find_path(grid)



# print(np.asarray(grid).shape)
