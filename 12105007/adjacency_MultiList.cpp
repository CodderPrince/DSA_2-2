#include <bits/stdc++.h>
using namespace std;

#define nl endl

struct EdgeNode
{
    int u, v;
    int nextU = 0, nextV = 0; // will set after processing
};

const int mx = 100;
EdgeNode edgeList[mx];
int edgeCount = 0;

vector<int> adj[mx]; // adj[node] = list of edge indices connected to node

/* Edges input section*/
void addEdge(int node1, int node2)
{
    ++edgeCount;
    edgeList[edgeCount].u = node1;
    edgeList[edgeCount].v = node2;
    adj[node1].push_back(edgeCount);
    adj[node2].push_back(edgeCount);
}

void buildNextPointers()
{
    // For each node, edges are sorted by insertion (input order)
    // For each edge connected to node, set next pointer for that node in that edge

    for (int node = 1; node < 4; node++)
    {
        vector<int> &edges = adj[node];
        // For edges connected to this node, link them as a linked list via next pointers
        for (int i = 0; i + 1 < edges.size(); i++)
        {
            int curEdge = edges[i];
            int nextEdge = edges[i + 1];

            if (edgeList[curEdge].u == node)
            {
                edgeList[curEdge].nextU = nextEdge;
            }
            else
            {
                edgeList[curEdge].nextV = nextEdge;
            }
        }

        // Last edge in this adjacency list points to 0
        if (!edges.empty())
        {
            int lastEdge = edges.back();
            if (edgeList[lastEdge].u == node)
            {
                edgeList[lastEdge].nextU = 0;
            }
            else
            {
                edgeList[lastEdge].nextV = 0;
            }
        }
    }
}

void printEdgeList()
{
    // Print table header
    cout << left
         << setw(6) << "Edge"
         << setw(8) << "Visited"
         << setw(8) << "Node U"
         << setw(8) << "Node V"
         << setw(10) << "NextU"
         << setw(10) << "NextV" << nl;

    // Print a line under the header
    cout << string(45, '-') << nl;

    for (int i = 1; i <= edgeCount; ++i)
    {
        cout << left
             << setw(6) << ("N" + to_string(i))
             << setw(8) << "vis"
             << setw(8) << edgeList[i].u
             << setw(8) << edgeList[i].v;

        if (edgeList[i].nextU)
        {
            cout << setw(10) << ("N" + to_string(edgeList[i].nextU));
        }
        else
        {
            cout << setw(10) << "0";
        }

        if (edgeList[i].nextV)
        {
            cout << setw(10) << ("N" + to_string(edgeList[i].nextV));
        }
        else
        {
            cout << setw(10) << "0";
        }

        cout << nl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nodes, edges;
    cin >> nodes >> edges;

    // edges input section
    for (int i = 1; i <= edges; ++i)
    {
        int node1, node2;
        cin >> node1 >> node2;
        addEdge(node1, node2);
    }

    buildNextPointers();

    printEdgeList();

    return 0;
}

/*t-1
4 6
1 2
1 3
1 4
2 3
2 4
3 4
*/

/*t-2
3 3
1 2
2 3
1 3
*/