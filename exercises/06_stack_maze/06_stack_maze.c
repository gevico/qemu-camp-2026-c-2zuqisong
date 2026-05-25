#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

typedef struct {
	int x;
	int y;
} Node;

Node stack[MAX_ROW * MAX_COL];
int top = -1;

int visted[MAX_ROW][MAX_COL] = {0};

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int dfs(int x, int y) {
	if (x < 0 || x >= MAX_ROW || y < 0 || y >= MAX_COL ||
	    maze[x][y] == 1 || visted[x][y]) {
		return 0;
	}

	visted[x][y] = 1;

	stack[++top].x = x;
	stack[top].y = y;

	if (x == MAX_ROW - 1 && y == MAX_COL - 1) {
        return 1; 
    }

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (dfs(nx, ny)) {
			return 1;
		}
	}

	// 回溯
	visted[x][y] = 0;
	top--;

	return 0;
}

int main(void)
{
	if (dfs(0, 0)) {
		for (int i = top; i >= 0; i--) {
			printf("(%d, %d)\n", stack[i].x, stack[i].y);
		}
	} else {
		printf("No path found.\n");
	}

	return 0;
}