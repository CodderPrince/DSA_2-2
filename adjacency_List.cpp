/*
Problem:    Adjacency list
Approach:   Using Linked List
Benefit:    Dynamic

Criteria:   Directed & Unweighted Graph
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define nl endl

const int mx = 1e5 + 123;

struct Node
{
    int data;
    Node *next;
};

Node *adjacencyList[mx] = {nullptr};

void addEdge(int node1, int node2)
{
    // add node1 and node2
    Node *newNode1 = new Node{node2, adjacencyList[node1]};
    adjacencyList[node1] = newNode1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int nodes, edges;
    cin >> nodes >> edges;

    // edges input section
    for (int i = 1; i <= edges; i++)
    {
        int node1, node2;
        cin >> node1 >> node2;

        addEdge(node1, node2);
    }

    // print section
    for (int i = 1; i <= nodes; i++)
    {
        cout << "Adjacency list of " << i << ": ";
        Node *temp = adjacencyList[i];
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << nl;
    }

    return 0;
}

/*t-1
5 7
1 2
1 5
1 4
2 3
2 4
3 4
5 4
*/