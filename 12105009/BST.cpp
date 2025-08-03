#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node *insert(Node *root, int val)
{
    if (!root)
        return new Node(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

void inorder(Node *root)
{
    if (!root)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node *root = nullptr;
    int numNodes;
    cin >> numNodes;

    vector<int> elements(numNodes);
    for (int i = 0; i < numNodes; i++)
    {
        cin >> elements[i];
        root = insert(root, elements[i]);
    }

    cout << "Inorder traversal:\n";
    inorder(root);
    cout << "\n";

    return 0;
}