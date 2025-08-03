#include <bits\stdc++.h>
using namespace std;

struct Node
{
    char data;
    Node *left;
    Node *right;
    Node(char val = '\0') : data(val), left(nullptr), right(nullptr) {}
};

Node *insert(char arr[], int index, int size)
{
    if (index >= size || arr[index] == '\0')
        return nullptr;

    Node *root = new Node(arr[index]);
    root->left = insert(arr, 2 * index + 1, size);
    root->right = insert(arr, 2 * index + 2, size);
    return root;
}

void preorder(Node *root)
{
    if (!root)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node *root)
{
    if (!root)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(Node *root)
{
    if (!root)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int main()
{
    int n;
    cin >> n;

    char arr[1000];
    for (int i = 0; i < n; i++)
    {
        char ch;
        cin >> ch;
        arr[i] = (ch == '0') ? '\0' : ch;
    }

    Node *tree = insert(arr, 0, n);

    cout << "\nPre-order traversal: ";
    preorder(tree);

    cout << "\nIn-order traversal: ";
    inorder(tree);

    cout << "\nPost-order traversal: ";
    postorder(tree);

    cout << "\n";
    return 0;
}