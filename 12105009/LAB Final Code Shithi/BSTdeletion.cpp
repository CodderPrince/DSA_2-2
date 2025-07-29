/*
    BST Deletion
    Without Graphical Interface
*/

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

Node *findMin(Node *root)
{
    while (root && root->left)
        root = root->left;
    return root;
}

bool foundToDelete = false;

Node *deleteNode(Node *root, int key)
{
    if (!root)
        return nullptr;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else
    {
        foundToDelete = true;
        if (!root->left)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        Node *temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
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
    string input;

    while (true)
    {
        cout << ">> ";
        getline(cin, input);
        if (input == "-1")
            break;
        if (input.empty())
            continue;

        stringstream ss(input);
        string token;
        ss >> token;

        if (token == "D" || token == "d")
        {
            int val;
            if (ss >> val)
            {
                foundToDelete = false;
                root = deleteNode(root, val);
                if (foundToDelete)
                    cout << "Deleted " << val << " successfully\n";
                else
                    cout << "Value " << val << " not found\n";
            }
            else
            {
                cout << "Invalid delete format. Use D <number>\n";
            }
        }
        else
        {
            try
            {
                int val = stoi(token);
                root = insert(root, val);
                cout << "Inserted " << val << "\n";
            }
            catch (...)
            {
                cout << "Invalid input. Use integer or D <number>\n";
            }
        }
    }

    cout << "\nFinal BST (Inorder Traversal): ";
    inorder(root);
    cout << "\n";

    return 0;
}

/*
Input:
15 11 13 8 9 17 16 18 -1
*/