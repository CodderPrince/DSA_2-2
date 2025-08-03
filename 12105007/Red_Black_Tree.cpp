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

Node *root;
Node *newNode;

void leftRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left != newNode)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(Node *x)
{
    Node *y = x->left;
    x->left = y->right;
    if (y->right != newNode)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

void fixInsert(Node *k)
{
    while (k != root && k->parent->color == "RED")
    {
        if (k->parent == k->parent->parent->left)
        {
            Node *u = k->parent->parent->right;
            if (u != newNode && u->color == "RED")
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
            Node *u = k->parent->parent->left;
            if (u != newNode && u->color == "RED")
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
    }
    root->color = "BLACK";
}

struct Display
{
    vector<string> lines;
    int width;
    int rootPos;
};

Display buildDisplay(Node *node)
{
    if (node == newNode)
        return {{}, 0, 0};

    string sval = to_string(node->data) + (node->color == "RED" ? "R" : "B");
    int sw = sval.size();

    if (node->left == newNode && node->right == newNode)
    {
        return {{sval}, sw, sw / 2};
    }

    Display left = buildDisplay(node->left);
    Display right = buildDisplay(node->right);

    int gap = 3;
    int widthLeft = left.width;
    int widthRight = right.width;
    int totalWidth = widthLeft + gap + widthRight;

    if (totalWidth < sw)
    {
        int diff = sw - totalWidth;
        totalWidth = sw;
        widthLeft += diff / 2;
        widthRight += diff - diff / 2;
    }

    string line1(totalWidth, ' ');
    int rootPos = widthLeft + gap / 2;
    for (int i = 0; i < sw; i++)
        line1[rootPos - sw / 2 + i] = sval[i];

    string line2(totalWidth, ' ');

    if (node->left != newNode)
    {
        int leftRootPos = left.rootPos;
        int slashPos = (leftRootPos + rootPos - gap / 2) / 2;
        line2[slashPos] = '/';
    }

    if (node->right != newNode)
    {
        int rightRootPos = widthLeft + gap + right.rootPos;
        int slashPos = (rootPos + gap / 2 + rightRootPos) / 2;
        line2[slashPos] = '\\';
    }

    vector<string> merged;
    merged.push_back(line1);
    merged.push_back(line2);

    int maxLines = max(left.lines.size(), right.lines.size());
    for (int i = 0; i < maxLines; i++)
    {
        string l = i < left.lines.size() ? left.lines[i] : string(widthLeft, ' ');
        string r = i < right.lines.size() ? right.lines[i] : string(widthRight, ' ');
        merged.push_back(l + string(gap, ' ') + r);
    }

    return {merged, totalWidth, rootPos};
}

void printTree(const string &header)
{
    Display D = buildDisplay(root);
    cout << header << "\n";
    for (auto &line : D.lines)
        cout << line << "\n";
    cout << "\n";
}

void inorder(Node *node)
{
    if (node != newNode)
    {
        inorder(node->left);
        cout << node->data << (node->color == "RED" ? "R " : "B ");
        inorder(node->right);
    }
}

void insert(int data)
{
    Node *node = new Node(data);
    node->left = newNode;
    node->right = newNode;
    node->parent = nullptr;

    Node *parent = nullptr;
    Node *current = root;

    while (current != newNode)
    {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    node->parent = parent;
    if (parent == nullptr)
        root = node;
    else if (data < parent->data)
        parent->left = node;
    else
        parent->right = node;

    node->color = "RED";
    fixInsert(node);
    printTree("Red-Black Tree after insertion of " + to_string(data) + ":");
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    newNode = new Node(0);
    newNode->color = "BLACK";
    newNode->left = newNode;
    newNode->right = newNode;
    newNode->parent = nullptr;
    root = newNode;

    int n;
    cin >> n;
    while (n--)
    {
        int x;
        cin >> x;
        insert(x);
    }

    cout << "Inorder traversal with colors:\n";
    inorder(root);
    cout << "\n";

    return 0;
}

/*
intput:

11
10 20 30 15 25 5 12 35 40 32 50

*/