/*
    BST Implementation
    Recursive Approach
    Static Array
    Graphical Representation
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

// Struct for storing subtree print info
struct Display
{
    vector<string> lines;
    int width;
    int rootPos;
};

// Build display for subtree
Display buildDisplay(Node *root)
{
    if (!root)
        return {{}, 0, 0};
    string sval = to_string(root->data);
    int sw = (int)sval.size();

    if (!root->left && !root->right)
    {
        return {{sval}, sw, sw / 2};
    }

    Display left = buildDisplay(root->left);
    Display right = buildDisplay(root->right);

    int gap = 3;
    int widthLeft = left.width;
    int widthRight = right.width;

    // Calculate combined width
    int totalWidth = widthLeft + gap + widthRight;
    if (totalWidth < sw)
    {
        int diff = sw - totalWidth;
        totalWidth = sw;
        // pad left and right widths proportionally
        widthLeft += diff / 2;
        widthRight += diff - diff / 2;
    }

    // First line: place root string centered
    string line1(totalWidth, ' ');
    int rootPos = widthLeft + gap / 2;
    for (int i = 0; i < sw; i++)
    {
        line1[rootPos - sw / 2 + i] = sval[i];
    }

    // Second line: branches
    string line2(totalWidth, ' ');
    if (root->left)
    {
        int leftRootPos = left.rootPos;
        line2[leftRootPos] = '/';
        for (int i = leftRootPos + 1; i < rootPos; i++)
            line2[i] = ' ';
    }
    if (root->right)
    {
        int rightRootPos = widthLeft + gap + right.rootPos;
        line2[rightRootPos] = '\\';
        for (int i = rootPos + sw / 2 + 1; i < rightRootPos; i++)
            line2[i] = ' ';
    }

    // Merge child lines
    vector<string> merged;
    merged.push_back(line1);
    merged.push_back(line2);

    int maxChildLines = max((int)left.lines.size(), (int)right.lines.size());
    for (int i = 0; i < maxChildLines; i++)
    {
        string lstr = i < (int)left.lines.size() ? left.lines[i] : string(widthLeft, ' ');
        string rstr = i < (int)right.lines.size() ? right.lines[i] : string(widthRight, ' ');
        merged.push_back(lstr + string(gap, ' ') + rstr);
    }

    return {merged, totalWidth, rootPos};
}

void printTreeStructure(Node *root, int step)
{
    Display D = buildDisplay(root);

    // Print to console
    cout << "Step " << step << ":\n";
    for (auto &line : D.lines)
    {
        cout << line << "\n";
    }
    cout << "\n";

    // Append to file
    ofstream out("tree.txt", ios::app);
    if (out.is_open())
    {
        out << "Step " << step << ":\n";
        for (auto &line : D.lines)
        {
            out << line << "\n";
        }
        out << "\n\n";
        out.close();
    }
    else
    {
        cerr << "Failed to open tree.txt for writing.\n";
    }
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
        cin >> elements[i];

    // Clear previous file contents at start
    ofstream out("tree.txt");
    out.close();

    for (int i = 0; i < numNodes; i++)
    {
        cout << "Inserting: " << elements[i] << "\n";
        root = insert(root, elements[i]);
        cout << "BST (Top-Down View):\n";
        printTreeStructure(root, i + 1);
    }

    cout << "All tree steps saved to tree.txt\n";
    return 0;
}

/*
t-1

8
15 11 13 8 9 17 16 18

*/