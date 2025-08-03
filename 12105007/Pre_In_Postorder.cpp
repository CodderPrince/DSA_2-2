/*
    Pre order
    In order
    Post Order
    With Graphical Interface
*/

#include <bits/stdc++.h>
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

struct Display
{
    vector<string> lines;
    int width;
    int rootPos;
};

Display buildDisplay(Node *root)
{
    if (!root)
        return {{}, 0, 0};

    string sval(1, root->data);
    int sw = sval.size();

    if (!root->left && !root->right)
    {
        return {{sval}, sw, sw / 2};
    }

    Display left = buildDisplay(root->left);
    Display right = buildDisplay(root->right);

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
    {
        line1[rootPos - sw / 2 + i] = sval[i];
    }

    string line2(totalWidth, ' ');
    if (root->left)
    {
        int leftRootPos = left.rootPos;
        line2[leftRootPos] = '/';
    }
    if (root->right)
    {
        int rightRootPos = widthLeft + gap + right.rootPos;
        line2[rightRootPos] = '\\';
    }

    vector<string> merged;
    merged.push_back(line1);
    merged.push_back(line2);

    int maxChildLines = max(left.lines.size(), right.lines.size());
    for (int i = 0; i < maxChildLines; i++)
    {
        string lstr = i < left.lines.size() ? left.lines[i] : string(widthLeft, ' ');
        string rstr = i < right.lines.size() ? right.lines[i] : string(widthRight, ' ');
        merged.push_back(lstr + string(gap, ' ') + rstr);
    }

    return {merged, totalWidth, rootPos};
}

void printTreeStructure(Node *root)
{
    Display D = buildDisplay(root);

    cout << "\nGraphical Tree Representation (Top-Down):\n";
    for (auto &line : D.lines)
    {
        cout << line << "\n";
    }

    ofstream out("static_tree.txt", ios::app);
    if (out.is_open())
    {
        for (auto &line : D.lines)
        {
            out << line << "\n";
        }
        out << "\n";
        out.close();
    }
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

    ofstream clear("static_tree.txt");
    clear.close();

    Node *tree = insert(arr, 0, n);

    cout << "\nPre-order traversal: ";
    preorder(tree);

    cout << "\nIn-order traversal: ";
    inorder(tree);

    cout << "\nPost-order traversal: ";
    postorder(tree);

    printTreeStructure(tree);

    cout << "\nTree saved to static_tree.txt\n";
    return 0;
}

/*
intput:
7
B A C 0 D E F
*/