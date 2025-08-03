#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl endl

const int mx = 100;

vector<int> adjList[mx];

bool vis[mx];

vector<int> bfsOutput;

void bfs(int top)
{
    queue<int> q;

    vis[top] = 1;
    q.push(top);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        bfsOutput.push_back(u);

        for (auto v : adjList[u])
        {
            if (vis[v] == 0)
            {
                vis[v] = 1;
                q.push(v);
            }
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

void bfsPrint()
{
    cout << "BFS output: ";
    for (int i = 0; i < bfsOutput.size(); i++)
    {
        cout << bfsOutput[i] << " ";
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
            bfs(i);
        }
    }

    bfsPrint();

    return 0;
}