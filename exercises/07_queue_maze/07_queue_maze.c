#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
    0, 1, 0, 0, 0,
    0, 1, 0, 1, 0,
    0, 0, 0, 0, 0,
    0, 1, 1, 1, 0,
    0, 0, 0, 1, 0,
};

// 定义队列中的节点结构
typedef struct {
    int x;
    int y;
    int parent_idx; // 关键：记录当前节点在队列数组中的父节点索引，用于回溯路径
} Node;

// BFS 专用的顺序队列
Node queue[MAX_ROW * MAX_COL];
int head = 0;
int tail = 0;

int visited[MAX_ROW][MAX_COL] = {0};

// 标准的四个搜索方向
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void bfs(int start_x, int start_y) {
    // 1. 起点入队
    queue[tail].x = start_x;
    queue[tail].y = start_y;
    queue[tail].parent_idx = -1; // 起点没有父节点
    tail++;
    visited[start_x][start_y] = 1;

    int found = 0;
    int target_idx = -1;

    // 2. 队列不为空时循环
    while (head < tail) {
        // 出队当前节点
        Node curr = queue[head];

        // 检查是否到达终点 (4, 4)
        if (curr.x == MAX_ROW - 1 && curr.y == MAX_COL - 1) {
            found = 1;
            target_idx = head; // 记住终点在队列里的索引
            break;
        }

        // 拓展四个方向
        for (int i = 0; i < 4; i++) {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            // 合法性与边界检查
            if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL &&
                maze[nx][ny] == 0 && !visited[nx][ny]) {
                
                visited[nx][ny] = 1;
                // 新节点入队
                queue[tail].x = nx;
                queue[tail].y = ny;
                queue[tail].parent_idx = head; // 父节点指向当前出队的 head 索引
                tail++;
            }
        }
        head++; // 真正弹出队首
    }

    // 3. 路径打印还原
    if (found) {
        printf("Path found:\n");
        int curr_idx = target_idx;
        // 顺着 parent_idx 链条从终点一路往回找，打印出来的顺序刚好是 (4,4) -> ... -> (0,0)
        while (curr_idx != -1) {
            printf("(%d, %d)\n", queue[curr_idx].x, queue[curr_idx].y);
            curr_idx = queue[curr_idx].parent_idx; // 移向父节点
        }
    } else {
        printf("No path!\n");
    }
}

int main(void) {
    bfs(0, 0);
    return 0;
}