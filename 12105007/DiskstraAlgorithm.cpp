/*
Dijkstra's Algorithm
Single Pair Shortest Path
T.C: O((V + E)logV)
S.C: O(V + E)
*/

#include <bits/stdc++.h>
using namespace std;

#define MX 105
#define INF 1e8

struct node
{
    int node;
    int cost;
};

vector<node> Graph[MX];
bool vis[MX];
int dist[MX];

void reset()
{
    for (int i = 0; i < MX; i++)
    {
        Graph[i].clear();
        vis[i] = 0;
        dist[i] = INF;
    }
}

class cmp
{
public:
    bool operator()(node &A, node &B)
    {
        if (A.cost > B.cost)
        {
            return true;
        }
        return false;
    }
};

void dijkstra(int source)
{

    priority_queue<node, vector<node>, cmp> PQ;

    PQ.push({source, 0});

    while (!PQ.empty())
    {
        node current = PQ.top();
        PQ.pop();

        int node = current.node;

        int cost = current.cost;

        if (vis[node] == 1)
        {
            continue;
        }

        dist[node] = cost;
        vis[node] = 1;

        for (int i = 0; i < Graph[node].size(); i++)
        {
            int nxtNode = Graph[node][i].node;

            int nxtCost = Graph[node][i].cost;

            if (vis[nxtNode] == 0)
            {
                PQ.push({nxtNode, cost + nxtCost});
            }
        }
    }
}

int main()
{

    reset();

    int nodes, edges;
    cin >> nodes >> edges;

    for (int i = 1; i <= edges; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        Graph[u].push_back({v, w});
    }

    int source;
    cin >> source;

    dijkstra(source);

    for (int i = 1; i <= nodes; i++)
    {
        cout << "Node: " << i << " Distance: ";
        if (dist[i] == INF)
        {
            cout << "INF" << "\n";
        }
        else
        {
            cout << dist[i] << "\n";
        }
    }

    return 0;
}

/*t-1
5 6
1 2 2
1 3 1
2 3 1
1 4 3
4 5 2
5 3 5
1
*/