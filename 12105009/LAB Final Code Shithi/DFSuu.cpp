/*
Problem:    DFS
Criteria:   Undirected & Unweighted Graph
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl endl

const int mx = 1000;

vector<int> adjList[mx];

bool vis[mx];

vector<int> dfsOutput;

void dfs(int u)
{

    vis[u] = 1;
    dfsOutput.push_back(u);

    for (auto v : adjList[u])
    {
        if (vis[v] == 0)
        {
            dfs(v);
        }
    }
}

void edgesInput(int edges)
{
    for (int i = 1; i <= edges; i++)
    {
        int node1, node2;
        cin >> node1 >> node2;

        adjList[node1].push_back(node2);
        adjList[node2].push_back(node1);
    }
}

void dfsPrint()
{
    cout << "DFS output: ";
    for (int i = 0; i < dfsOutput.size(); i++)
    {
        cout << dfsOutput[i] << " ";
    }
    cout << nl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int node, edges;
    cin >> node >> edges;

    edgesInput(edges);

    for (int i = 1; i <= node; i++)
    {
        if (vis[i] == 0)
        {
            dfs(i);
        }
    }

    dfsPrint();

    return 0;
}

/*t-1
4 3
1 2
2 3
3 4
*/