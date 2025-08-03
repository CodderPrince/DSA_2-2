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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node *root = nullptr;
    int val, step = 0;

    cout << "Enter values to insert into BST (-1 to stop):\n";

    while (cin >> val && val != -1)
    {
        root = insert(root, val);
        step++;
        cout << "Inserted: " << val << " (Step " << step << ")\n";
    }

    cout << "All values inserted. Tree construction complete.\n";
    return 0;
}
