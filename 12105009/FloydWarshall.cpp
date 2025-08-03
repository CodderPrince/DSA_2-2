#include <bits/stdc++.h>
using namespace std;

const int INF = 1e8;
int node;

void floydWarshall(vector<vector<int>> &Q)
{

    for (int k = 0; k < node; k++)
    {
        for (int i = 0; i < node; i++)
        {
            for (int j = 0; j < node; j++)
            {
                if (Q[i][k] != 1e8 && Q[k][j] != 1e8)
                {

                    Q[i][j] = min(Q[i][j], Q[i][k] + Q[k][j]);
                }
            }
        }
    }
}

void printOutput(vector<vector<int>> &Q)
{
    cout << "All pairs shortest path:\n";
    for (int i = 0; i < node; i++)
    {
        for (int j = 0; j < node; j++)
        {
            if (Q[i][j] == INF)
            {
                cout << setw(5) << "INF";
            }
            else
            {
                cout << setw(5) << Q[i][j];
            }
        }
        cout << endl;
    }
}

int main()
{

    cin >> node;

    vector<vector<int>> Q(node, vector<int>(node));
    for (int i = 0; i < node; i++)
    {
        for (int j = 0; j < node; j++)
        {
            string str;
            cin >> str;
            if (str == "INF")
            {
                Q[i][j] = INF;
            }
            else
            {
                Q[i][j] = stoi(str);
            }
        }
    }

    floydWarshall(Q);
    printOutput(Q);

    return 0;
}