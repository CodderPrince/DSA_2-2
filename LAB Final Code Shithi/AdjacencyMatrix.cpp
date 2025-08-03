#include <bits/stdc++.h>
using namespace std;

int main()
{
    int nodes, edges;
    cin >> nodes >> edges;

    vector<vector<int>> mat(nodes + 1, vector<int>(nodes + 1, 0));

    for (int i = 1; i <= edges; i++)
    {
        int node1, node2;
        cin >> node1 >> node2;
        mat[node1][node2] = 1;
        mat[node2][node1] = 1;
    }

    cout << "Adjacency Matrix Representation:\n\n";
    cout << "\t";
    for (int i = 1; i <= nodes; i++)
    {
        cout << i << "\t";
    }
    cout << endl
         << endl;

    for (int i = 1; i <= nodes; i++)
    {
        cout << i << "\t";
        for (int j = 1; j <= nodes; j++)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl
             << endl;
    }

    return 0;
}
