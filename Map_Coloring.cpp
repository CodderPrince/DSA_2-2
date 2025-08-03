#include <bits\stdc++.h>
using namespace std;

void greedyColoring(const vector<vector<int>> &graph, int n)
{
    vector<int> result(n, -1);
    result[0] = 0;

    vector<bool> available(n, false);

    for (int u = 1; u < n; u++)
    {

        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] && result[v] != -1)
            {
                available[result[v]] = true;
            }
        }

        int cr;
        for (cr = 0; cr < n; cr++)
        {
            if (!available[cr])
            {
                break;
            }
        }

        result[u] = cr;

        for (int v = 0; v < n; v++)
        {
            if (graph[u][v] && result[v] != -1)
            {
                available[result[v]] = false;
            }
        }
    }

    cout << "Vertex   Color" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "  " << i << "       " << result[i] << endl;
    }
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    greedyColoring(graph, n);

    return 0;
}