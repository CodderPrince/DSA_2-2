#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

Node* findMin(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

struct Display {
    vector<string> lines;
    int width;
    int rootPos;
};

Display buildDisplay(Node* root) {
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
    if (root->left)
        line2[left.rootPos] = '/';
    if (root->right)
        line2[widthLeft + gap + right.rootPos] = '\\';

    vector<string> merged = {line1, line2};
    int maxLines = max(left.lines.size(), right.lines.size());

    for (int i = 0; i < maxLines; i++) {
        string l = i < left.lines.size() ? left.lines[i] : string(widthLeft, ' ');
        string r = i < right.lines.size() ? right.lines[i] : string(widthRight, ' ');
        merged.push_back(l + string(gap, ' ') + r);
    }

    return {merged, totalWidth, rootPos};
}

void printTreeStructure(Node* root, int step, const string& op, int val) {
    Display D = buildDisplay(root);
    cout << "\nStep " << step << " - " << op << " " << val << ":\n";
    for (auto& line : D.lines)
        cout << line << "\n";
    cout << "\n";

    ofstream out("tree.txt", ios::app);
    if (out.is_open()) {
        out << "Step " << step << " - " << op << " " << val << ":\n";
        for (auto& line : D.lines)
            out << line << "\n";
        out << "\n";
        out.close();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node* root = nullptr;
    string input;
    int step = 0;

    // Clear old tree output
    ofstream clear("tree.txt");
    clear.close();

    cout << "Enter values to insert (e.g. 10),\n";
    cout << "To delete: type D <value> (e.g. D 25)\n";
    cout << "To exit: -1\n\n";

    while (true) {
        cout << ">> ";
        getline(cin, input);
        if (input == "-1") break;

        if (input.empty()) continue;

        stringstream ss(input);
        string token;
        ss >> token;

        if (token == "D" || token == "d") {
            int val;
            if (ss >> val) {
                root = deleteNode(root, val);
                step++;
                printTreeStructure(root, step, "Deleted", val);
            } else {
                cout << "⚠️  Invalid delete format. Use D <number>\n";
            }
        } else {
            try {
                int val = stoi(token);
                root = insert(root, val);
                step++;
                printTreeStructure(root, step, "Inserted", val);
            } catch (...) {
                cout << "⚠️  Invalid input. Use integer or D <number>\n";
            }
        }
    }

    cout << "\n✅ Final BST written to tree.txt\n";
    return 0;
}

/*
10
5
20
15
D 5
-1

*/