#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024
#define INIT_VALUE -1

#define START    'S'
#define GOAL     'G'
#define WAY      ' '
#define WALL     '#'
#define MARKED   '+'


enum DIRECTION {NORTH, SOUTH, EAST, WEST};
enum RESULT    {FAIL, SUCCEED}; 

typedef struct tagPosition
{
    int x;
    int y;
} Position;

typedef struct tagMazeInfo
{
    int columnSize;
    int rowSize;

    char** data;
} MazeInfo;

int solve(MazeInfo *maze);
int moveTo(MazeInfo *maze, Position *current, int direction);
int getNextStep(MazeInfo *maze, Position *current, int direction, Position *next);
int getMaze(char *filePath, MazeInfo *maze);

int solve(MazeInfo *maze) {
	int startFound = FAIL;
	int result = FAIL;

	Position start;

	for (int i = 0; i < maze->rowSize; i++) {
		for (int j = 0; j < maze->columnSize; j++) {
			if (maze->data[i][j] == START) {
				start.x = i;
				start.y = j;
				startFound = SUCCEED;
				break;
			}
		}
	}

	if (startFound == FAIL) {
		return FAIL;
	}

	if (moveTo(maze, &start, NORTH)) {
		result = SUCCEED;
	} else if (moveTo(maze, &start, SOUTH)) {
		result = SUCCEED;
	} else if (moveTo(maze, &start, EAST)) {
		result = SUCCEED;
	} else if (moveTo(maze, &start, WEST)) {
		result = SUCCEED;
	}

	maze->data[start.x][start.y] = START;

	return result;
}

int moveTo(MazeInfo *maze, Position *current, int direction) {
	int dirs[] = {NORTH, SOUTH, WEST, EAST};
	Position next;

	if (maze->data[current->x][current->y] == GOAL) {
		return SUCCEED;
	}

	maze->data[current->x][current->y] = MARKED;

	for (int i = 0; i < 4; i++) {
		if (getNextStep(maze, current, dirs[i], &next) == FAIL) {
			continue;
		}
		if (moveTo(maze, &next, NORTH) == SUCCEED) {
			return SUCCEED;
		}
	}

	maze->data[current->x][current->y] = WAY;

	return FAIL;
}

int getNextStep(MazeInfo *maze, Position *current, int direction, Position *next) {
	switch (direction) {
	case NORTH:
		next->x = current->x;
		next->y = current->y - 1;
		if (next->y == 1) {
			return FAIL;
		}
		break;
	case SOUTH:
		next->x = current->x;
		next->y = current->y + 1;
		if (next->y == maze->rowSize) {
			return FAIL;
		}	
		break;
	case WEST:
		next->x = current->x - 1;
		next->y = current->y;
		if (next->y == -1) {
			return FAIL;
		}	
		break;
	case EAST:
		next->x = current->x + 1;
		next->y = current->y;
		if (next->y == maze->columnSize) {
			return FAIL;
		}	
		break;	
	}

	if (maze->data[next->x][next->y] == WALL) {
		return FAIL;
	}
	if (maze->data[next->x][next->y] == MARKED) {
		return FAIL;
	}

	return SUCCEED;
}

int getMaze(char *filePath, MazeInfo *maze) {
	int rowSize = 0;
	int columnSize = INIT_VALUE;
	FILE *fp;
	char buffer[MAX_BUFFER];

	fp = fopen(filePath, "r");

	if (fp) {
		while (fgets(buffer, MAX_BUFFER, fp) != NULL) {
			rowSize++;
			if (columnSize == INIT_VALUE) {
				columnSize = strlen(buffer) - 1;
			} else if (columnSize != strlen(buffer) - 1) {
				printf("maze data in file :%s is not vaild.(%d)\n", filePath, strlen(buffer));
				fclose(fp);
				return fail;
			}
		}

		maze->rowSize = rowSize;
		maze->columnSize = columnSize;
		maze->data = (char **)malloc(sizeof(char *) * rowSize);

		for (int i = 0; i < rowSize; i++) {
			fgets(buffer, MAX_BUFFER, fp);
			for (int j = 0; j < columnSize; j++) {
				maze->data[i][j] = buffer[]
			}
		}
	}
}

int main(int argc, char *argv[]) {
	MazeInfo maze;

	if (argc < 2) {
		printf("usage: magesolver\n");
		return 0;
	}

	if (getMaze(argv[1], &maze) == FAIL) {
		return 0;
	}

	if (solve(&maze) == FAIL) {
		return 0;
	}

	for (int i = 0; i < maze.rowSize; i++) {
		for (int j = 0; j < maze.columnSize; j++) {
			printf("%c", maze.data[i][j]);
		}
		printf("\n");
	}

	return 0;
}