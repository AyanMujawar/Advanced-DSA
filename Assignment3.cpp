#include <iostream>
#include <queue>
using namespace std;

#define ROWS 4
#define COLS 4

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int maze[ROWS][COLS];
bool visited[ROWS][COLS] = {false};
int parentX[ROWS][COLS];
int parentY[ROWS][COLS];

bool isValid(int x, int y) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] == 0 && !visited[x][y]);
}

bool DFS(int x, int y, int goalX, int goalY) {
    if (x == goalX && y == goalY) {
        cout << "(" << x << "," << y << ") ";
        return true;
    }
    visited[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (isValid(newX, newY)) {
            if (DFS(newX, newY, goalX, goalY)) {
                cout << "(" << x << "," << y << ") ";
                return true;
            }
        }
    }
    return false;
}

bool BFS(int startX, int startY, int goalX, int goalY) {
    bool visitedBFS[ROWS][COLS] = {false};
    queue<int> qX, qY;
    qX.push(startX);
    qY.push(startY);
    visitedBFS[startX][startY] = true;
    parentX[startX][startY] = -1;
    parentY[startX][startY] = -1;
    
    while (!qX.empty()) {
        int x = qX.front();
        int y = qY.front();
        qX.pop();
        qY.pop();
        
        if (x == goalX && y == goalY) {
            int tempX = goalX;
            int tempY = goalY;
            while (tempX != -1) {
                cout << "(" << tempX << "," << tempY << ") ";
                int prevX = parentX[tempX][tempY];
                int prevY = parentY[tempX][tempY];
                tempX = prevX;
                tempY = prevY;
            }
            return true;
        }
        
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS && maze[newX][newY] == 0 && !visitedBFS[newX][newY]) {
                visitedBFS[newX][newY] = true;
                parentX[newX][newY] = x;
                parentY[newX][newY] = y;
                qX.push(newX);
                qY.push(newY);
            }
        }
    }
    return false;
}

int main() {
    int choice;
    int startX, startY, goalX, goalY;

    // Take maze input
    cout << "Enter the maze (0 for open path, 1 for blocked):\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cin >> maze[i][j];
        }
    }
    cin.ignore();

    // Take start and goal positions
    cout << "Enter start position (row column): ";
    cin >> startX >> startY;
    cout << "Enter goal position (row column): ";
    cin >> goalX >> goalY;

    cout << "Choose an option:\n";
    cout << "1. Solve using DFS\n";
    cout << "2. Solve using BFS\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "DFS Path: ";
            if (!DFS(startX, startY, goalX, goalY)) {
                cout << "No path found.";
            }
            break;
        case 2:
            cout << "BFS Path: ";
            if (!BFS(startX, startY, goalX, goalY)) {
                cout << "No path found.";
            }
            break;
        default:
            cout << "Invalid choice!";
    }
    cout << endl;
    return 0;
}
