#include <iostream>
#include <vector>
using namespace std;

void greedyColoring(const vector<vector<int>>& graph, int n) {
    vector<int> result(n, -1);  // Color assigned to each node
    result[0] = 0;              // Assign first color to first node

    vector<bool> available(n, false); // Track used colors

    for (int u = 1; u < n; u++) {
        // Mark colors of adjacent vertices as unavailable
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && result[v] != -1) {
                available[result[v]] = true;
            }
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < n; cr++) {
            if (!available[cr]) {
                break;
            }
        }

        result[u] = cr; // Assign the found color

        // Reset the values back to false for the next iteration
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && result[v] != -1) {
                available[result[v]] = false;
            }
        }
    }

    // Print the result
    cout << "Vertex   Color" << endl;
    for (int i = 0; i < n; i++) {
        cout << "  " << i << "       " << result[i] << endl;
    }
}

int main() {
    int n;
    cin >> n; // Number of vertices (regions)

    vector<vector<int>> graph(n, vector<int>(n));

    // Input adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    greedyColoring(graph, n);

    return 0;
}

/*
5
0 1 1 1 0
1 0 1 0 0
1 1 0 1 1
1 0 1 0 1
0 0 1 1 0

*/