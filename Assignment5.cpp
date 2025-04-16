#include <iostream>
using namespace std;

#define INF 999999
#define MAX 10

// Function to find the location with the minimum distance
int findMinDistance(int dist[], bool visited[], int V) {
    int min = INF, index;
    for (int i = 0; i < V; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

int main() {
    int V;
    string locations[MAX];
    int graph[MAX][MAX];

    cout << "Enter number of supply chain locations: ";
    cin >> V;

    cout << "Enter location names:\n";
    for (int i = 0; i < V; i++) {
        cout << "Location " << i << ": ";
        cin >> locations[i];
    }

    cout << "Enter distance/cost between locations (0 if no direct path):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << "Distance from " << locations[i] << " to " << locations[j] << ": ";
            cin >> graph[i][j];
        }
    }

    int source;
    cout << "Enter source location index (e.g. 0 for " << locations[0] << "): ";
    cin >> source;

    int dist[MAX]; // Shortest distances from source
    bool visited[MAX]; // Mark visited locations

    // Initialize distances
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
    dist[source] = 0;

    // Dijkstra's algorithm
    for (int count = 0; count < V - 1; count++) {
        int u = findMinDistance(dist, visited, V);
        visited[u] = true;

        // Update the distance values of the adjacent locations
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Output result
    cout << "\nShortest paths from " << locations[source] << ":\n";
    for (int i = 0; i < V; i++) {
        cout << locations[source] << " -> " << locations[i] << " = " << dist[i] << endl;
    }

    return 0;
}
