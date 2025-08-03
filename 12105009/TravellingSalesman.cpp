#include <bits\stdc++.h>
using namespace std;

int tspGreedy(const vector<vector<int>> &graph, int start)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    int cost = 0;
    int current = start;

    visited[current] = true;

    cout << "Path: " << current;

    for (int count = 1; count < n; count++)
    {
        int nearest = -1;
        int minDist = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && graph[current][i] && graph[current][i] < minDist)
            {
                minDist = graph[current][i];
                nearest = i;
            }
        }

        if (nearest == -1)
            break;

        visited[nearest] = true;
        cost += minDist;
        current = nearest;
        cout << " -> " << current;
    }

    cost += graph[current][start];
    cout << " -> " << start << endl;

    return cost;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];

    int start = 0;
    int totalCost = tspGreedy(graph, start);

    cout << "Total cost: " << totalCost << endl;
    return 0;
}