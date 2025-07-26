/*
Problem:    DFS
Approach:   Using adjList
Benefit:    Dynamic

Criteria:   Undirected & Unweighted Graph

Time Complexity:    O(N + E)
Space Complexity:   O(N + E)
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl endl

// max node size
const int mx = 1e5 + 123;

/// adjacency list array
vector<int> adjList[mx];

// visited array list
bool vis[mx];

// dfs output store array
vector<int> dfsOutput;

/* DFS Function*/
void dfs(int u)
{
    // mark as visited
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

/* Edges Input Section*/
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

/* Print DFS section*/
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

    // called edges input
    edgesInput(edges);

    // dfs section
    for (int i = 1; i <= node; i++)
    {
        if (vis[i] == 0)
        {
            dfs(i);
        }
    }

    // print section
    dfsPrint();

    return 0;
}

/*t-1
8 7
1 2
1 5
1 7
2 3
2 4
5 6
7 8
*/

/*t-2
4 3
1 2
2 3
3 4
*/