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

def isValid(x, y):
	if(x >= 0 and y >=0 and x<10 and y<10):
		return True
	return False

def isSafe(grid, sol, x, y):
	if(grid[x][y] == '1' or sol[x][y] == 'S'):
		return False
	return True

solution = None
min_dis = 10000

def solveMazeUtil(grid, x, y, sol, dis):
	global solution, min_dis
	if(grid[x][y] == 'E'):
		if dis < min_dis:
			solution = deepcopy(sol)
			min_dis = dis
		return

	sol[x][y] = 'S'

	if(isValid(x, y+1) and isSafe(grid, sol, x, y+1)):
		solveMazeUtil(grid, x, y+1, sol, dis+1)

	if(isValid(x+1, y) and isSafe(grid, sol, x+1, y)):
		solveMazeUtil(grid, x+1, y, sol, dis+1)

	if(isValid(x-1, y) and isSafe(grid, sol, x-1, y)):
		solveMazeUtil(grid, x-1, y, sol, dis+1)

	if(isValid(x, y-1) and isSafe(grid, sol, x, y-1)):
		solveMazeUtil(grid, x, y-1, sol, dis+1)
	
	sol[x][y] = '0'


def find_path(grid):
	 global solution
	 sol = [['0' for x in range(10)] for y in range(10)]
	 solveMazeUtil(grid, 1, 1, sol, 0)
	 if solution:
	 	print_grid(solution)
	 	# print_grid(solution[0])
	 else:
	 	print("No Path Exists!!")

find_path(grid)



# print(np.asarray(grid).shape)
