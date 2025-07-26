#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};

int height(Node* N) {
    return N ? N->height : 0;
}

int getBalance(Node* N) {
    if (!N) return 0;
    return height(N->left) - height(N->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
    if (!node)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (!root)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    if (!root)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// ========== Tree Graphical Display Code ==========

struct Display {
    vector<string> lines;
    int width;
    int rootPos;
};

Display buildDisplay(Node* root) {
    if (!root) return {{}, 0, 0};
    string sval = to_string(root->key);
    int sw = (int)sval.size();

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

    int maxLines = max((int)left.lines.size(), (int)right.lines.size());
    for (int i = 0; i < maxLines; i++) {
        string l = i < (int)left.lines.size() ? left.lines[i] : string(widthLeft, ' ');
        string r = i < (int)right.lines.size() ? right.lines[i] : string(widthRight, ' ');
        merged.push_back(l + string(gap, ' ') + r);
    }

    return {merged, totalWidth, rootPos};
}

void printTreeStructure(Node* root, const string& header) {
    Display D = buildDisplay(root);

    cout << header << "\n";
    for (auto& line : D.lines)
        cout << line << "\n";
    cout << "\n";

    ofstream out("avl_tree.txt", ios::app);
    if (out.is_open()) {
        out << header << "\n";
        for (auto& line : D.lines)
            out << line << "\n";
        out << "\n";
        out.close();
    } else {
        cerr << "Failed to open avl_tree.txt\n";
    }
}

// =======================

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node* root = nullptr;
    int n_insert, n_delete;

    // Clear output file before starting
    ofstream clear("avl_tree.txt");
    clear.close();

    cin >> n_insert;
    for (int i = 1; i <= n_insert; i++) {
        int key; cin >> key;
        root = insert(root, key);
        cout << "Inserted: " << key << "\n";
        printTreeStructure(root, "AVL Tree after insertion step " + to_string(i) + ":");
    }

    cout << "Inorder traversal after insertion: ";
    inorder(root);
    cout << "\n";

    cin >> n_delete;
    for (int i = 1; i <= n_delete; i++) {
        int key; cin >> key;
        root = deleteNode(root, key);
        cout << "Deleted: " << key << "\n";
        printTreeStructure(root, "AVL Tree after deletion step " + to_string(i) + ":");

        cout << "Inorder traversal after deleting " << key << ": ";
        inorder(root);
        cout << "\n";
    }

    return 0;
}

/*
5
10 20 30 40 50
2
20 30

*/