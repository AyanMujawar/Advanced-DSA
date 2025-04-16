#include <iostream>
#include <cstring>
using namespace std;

#define INF 9999999
#define MAX 10

int main() {
    int V;
    char departments[MAX][30];
    int G[MAX][MAX]; // Adjacency matrix

    cout << "Enter number of departments: ";
    cin >> V;

    cout << "Enter department names:\n";
    for (int i = 0; i < V; i++) {
        cout << "Department " << i << ": ";
        cin >> departments[i];
    }

    cout << "Enter distance between departments (0 if no direct path):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                G[i][j] = 0;
            } else {
                cout << "Distance between " << departments[i] << " and " << departments[j] << ": ";
                cin >> G[i][j];
            }
        }
    }

    // Prim's Algorithm
    int no_edge = 0;
    int selected[MAX];
    memset(selected, false, sizeof(selected));
    selected[0] = true; // Start from first department

    cout << "\nMinimum Spanning Tree using Prim's Algorithm:\n";
    cout << "Edge\t\tWeight\n";

    while (no_edge < V - 1) {
        int min = INF;
        int x = 0, y = 0;
        for (int i = 0; i < V; i++) {
            if (selected[i]) {
                for (int j = 0; j < V; j++) {
                    if (!selected[j] && G[i][j]) {
                        if (G[i][j] < min) {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }

        cout << departments[x] << " - " << departments[y] << "\t" << G[x][y] << endl;
        selected[y] = true;
        no_edge++;
    }

    return 0;
}
