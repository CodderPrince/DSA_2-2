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
    string sval = to_string(root->data);
    int sw = sval.size();

    if (!root->left && !root->right)
        return {{sval}, sw, sw / 2};

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
        line1[rootPos - sw / 2 + i] = sval[i];

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

    int maxLines = max(left.lines.size(), right.lines.size());
    for (int i = 0; i < maxLines; i++)
    {
        string l = i < left.lines.size() ? left.lines[i] : string(widthLeft, ' ');
        string r = i < right.lines.size() ? right.lines[i] : string(widthRight, ' ');
        merged.push_back(l + string(gap, ' ') + r);
    }

    return {merged, totalWidth, rootPos};
}

void printTreeStructure(Node *root)
{
    Display D = buildDisplay(root);
    cout << "\nBST Graphical Representation:\n";
    for (auto &line : D.lines)
        cout << line << "\n";

    ofstream out("tree.txt");
    if (out.is_open())
    {
        for (auto &line : D.lines)
            out << line << "\n";
        out.close();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node *root = nullptr;
    int val;

    // Read insert values separated by spaces until -1
    while (cin >> val && val != -1)
    {
        root = insert(root, val);
        cout << "Inserted: " << val << "\n";
    }

    // Print tree once after all insertions
    printTreeStructure(root);

    // Search mode: one value per line, -1 to exit
    while (cin >> val && val != -1)
    {
        if (search(root, val))
            cout << val << " found in BST.\n";
        else
            cout << val << " NOT found in BST.\n";
    }

    cout << "Program ended. Final BST saved in tree.txt\n";
    return 0;
}

/*
intput:
10 53 1 3 7 2 18 9 -1
9
23
-1


*/