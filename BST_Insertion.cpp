#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node *insert(Node *root, int val) {
    if (!root) return new Node(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// Struct for displaying tree
struct Display {
    vector<string> lines;
    int width;
    int rootPos;
};

Display buildDisplay(Node *root) {
    if (!root) return {{}, 0, 0};
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
    if (totalWidth < sw) {
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
    if (root->left) {
        int leftRootPos = left.rootPos;
        line2[leftRootPos] = '/';
    }
    if (root->right) {
        int rightRootPos = widthLeft + gap + right.rootPos;
        line2[rightRootPos] = '\\';
    }

    vector<string> merged;
    merged.push_back(line1);
    merged.push_back(line2);

    int maxLines = max(left.lines.size(), right.lines.size());
    for (int i = 0; i < maxLines; i++) {
        string l = i < left.lines.size() ? left.lines[i] : string(widthLeft, ' ');
        string r = i < right.lines.size() ? right.lines[i] : string(widthRight, ' ');
        merged.push_back(l + string(gap, ' ') + r);
    }

    return {merged, totalWidth, rootPos};
}

void printTreeStructure(Node *root, int step) {
    Display D = buildDisplay(root);
    cout << "Step " << step << ":\n";
    for (auto &line : D.lines)
        cout << line << "\n";
    cout << "\n";

    ofstream out("tree.txt", ios::app);
    if (out.is_open()) {
        out << "Step " << step << ":\n";
        for (auto &line : D.lines)
            out << line << "\n";
        out << "\n\n";
        out.close();
    } else {
        cerr << "Failed to open tree.txt\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node *root = nullptr;
    int val, step = 0;

    // Clear previous output
    ofstream clear("tree.txt");
    clear.close();

    cout << "Enter values to insert into BST (-1 to stop):\n";

    while (true) {
        cin >> val;
        if (val == -1) break;
        root = insert(root, val);
        step++;
        cout << "Inserted: " << val << "\n";
        printTreeStructure(root, step);
    }

    cout << "Final BST saved in tree.txt\n";
    return 0;
}

/*
15 11 13 8 9 17 16 18 -1

*/