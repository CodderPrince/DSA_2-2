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

bool search(Node *root, int key)
{
    if (!root)
        return false;
    if (root->data == key)
        return true;
    return key < root->data ? search(root->left, key) : search(root->right, key);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node *root = nullptr;
    int val;

    while (cin >> val && val != -1)
    {
        root = insert(root, val);
        cout << "Inserted: " << val << "\n";
    }

    while (cin >> val && val != -1)
    {
        if (search(root, val))
            cout << val << " found in BST.\n";
        else
            cout << val << " NOT found in BST.\n";
    }

    cout << "Program ended.\n";
    return 0;
}