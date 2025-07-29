/*
    Red Black Tree
    Without Graphical Interface
*/

#include <bits\stdc++.h>
using namespace std;

struct Node
{
    int data;
    string color;
    Node *left;
    Node *right;
    Node *parent;

    Node(int data) : data(data), color("RED"), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree
{
private:
    Node *root;
    Node *NIL;

    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != NIL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != NIL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void fixInsert(Node *k)
    {
        Node *u;
        while (k != root && k->parent->color == "RED")
        {
            if (k->parent == k->parent->parent->left)
            {
                u = k->parent->parent->right;
                if (u != NIL && u->color == "RED")
                {
                    k->parent->color = "BLACK";
                    u->color = "BLACK";
                    k->parent->parent->color = "RED";
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = "BLACK";
                    k->parent->parent->color = "RED";
                    rightRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->left;
                if (u != NIL && u->color == "RED")
                {
                    k->parent->color = "BLACK";
                    u->color = "BLACK";
                    k->parent->parent->color = "RED";
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = "BLACK";
                    k->parent->parent->color = "RED";
                    leftRotate(k->parent->parent);
                }
            }
            if (k == root)
            {
                break;
            }
        }
        root->color = "BLACK";
    }

    void inorderHelper(Node *node)
    {
        if (node != NIL)
        {
            inorderHelper(node->left);
            cout << node->data << (node->color == "RED" ? "R " : "B ");
            inorderHelper(node->right);
        }
    }

public:
    RedBlackTree()
    {
        NIL = new Node(0);
        NIL->color = "BLACK";
        NIL->left = NIL;
        NIL->right = NIL;
        NIL->parent = nullptr;
        root = NIL;
    }

    void insert(int data)
    {
        Node *node = new Node(data);
        node->left = NIL;
        node->right = NIL;
        node->parent = nullptr;

        Node *parent = nullptr;
        Node *current = root;

        while (current != NIL)
        {
            parent = current;
            if (node->data < current->data)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        node->parent = parent;

        if (parent == nullptr)
        {
            root = node;
        }
        else if (node->data < parent->data)
        {
            parent->left = node;
        }
        else
        {
            parent->right = node;
        }

        node->color = "RED";
        fixInsert(node);
        root->color = "BLACK";
    }

    void inorder()
    {
        inorderHelper(root);
        cout << "\n";
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    RedBlackTree rbt;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        rbt.insert(x);
    }

    cout << "Inorder traversal with colors:\n";
    rbt.inorder();

    return 0;
}

/*
intput:
9
1 2 3 4 5 6 7 8 9

Expected Output:
Inorder traversal with colors:
1B 2R 3B 4B 5B 6R 7R 8B 9R

*/