#include <bits/stdc++.h>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int data) {
        this->data = data;
        left = right = parent = nullptr;
        color = RED;
    }
};

class RBTree {
private:
    Node* root;
    Node* TNULL; // Sentinel NIL node

    void initializeNULLNode(Node* node, Node* parent) {
        node->data = 0;
        node->color = BLACK;
        node->left = nullptr;
        node->right = nullptr;
        node->parent = parent;
    }

    // ========== Graphical Display ==========
    struct Display {
        vector<string> lines;
        int width;
        int rootPos;
    };

    // Build tree lines recursively
    Display buildDisplay(Node* root) {
        if (root == TNULL) return {{}, 0, 0};
        string sval = to_string(root->data);
        sval += (root->color == RED ? "R" : "B"); // Show color: R or B
        int sw = (int)sval.size();

        if (root->left == TNULL && root->right == TNULL)
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
        if (root->left != TNULL) {
            int leftRootPos = left.rootPos;
            line2[leftRootPos] = '/';
        }
        if (root->right != TNULL) {
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

    void printTreeStructure(const string& header) {
        Display D = buildDisplay(root);
        cout << header << "\n";
        for (auto &line : D.lines)
            cout << line << "\n";
        cout << "\n";

        ofstream out("rbtree.txt", ios::app);
        if (out.is_open()) {
            out << header << "\n";
            for (auto &line : D.lines)
                out << line << "\n";
            out << "\n";
            out.close();
        } else {
            cerr << "Failed to open rbtree.txt\n";
        }
    }

    // ========== Original RB Tree Helpers ==========

    void preOrderHelper(Node* node) {
        if (node != TNULL) {
            cout << node->data << (node->color == RED ? "R " : "B ");
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(Node* node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            cout << node->data << (node->color == RED ? "R " : "B ");
            inOrderHelper(node->right);
        }
    }

    void postOrderHelper(Node* node) {
        if (node != TNULL) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data << (node->color == RED ? "R " : "B ");
        }
    }

    Node* searchTreeHelper(Node* node, int key) {
        if (node == TNULL || key == node->data) {
            return node;
        }
        if (key < node->data) {
            return searchTreeHelper(node->left, key);
        }
        return searchTreeHelper(node->right, key);
    }

    void fixDelete(Node* x) {
        Node* s;
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == BLACK && s->left->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void rbTransplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(Node* node, int key) {
        Node* z = TNULL;
        Node* x, * y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }
            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            cout << "Cannot find key " << key << " in the tree\n";
            return;
        }

        y = z;
        Color y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK) {
            fixDelete(x);
        }
    }

    void fixInsert(Node* k) {
        Node* u;
        while (k->parent != nullptr && k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;
                if (u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = BLACK;
    }

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    Node* minimum(Node* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

public:
    RBTree() {
        TNULL = new Node(0);
        TNULL->color = BLACK;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
        // Clear output file at start
        ofstream clear("rbtree.txt");
        clear.close();
    }

    void preorder() {
        preOrderHelper(this->root);
        cout << "\n";
    }

    void inorder() {
        inOrderHelper(this->root);
        cout << "\n";
    }

    void postorder() {
        postOrderHelper(this->root);
        cout << "\n";
    }

    Node* searchTree(int k) {
        Node* node = searchTreeHelper(root, k);
        if (node == TNULL) return nullptr;
        return node;
    }

    void insert(int key) {
        Node* node = new Node(key);
        node->parent = nullptr;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        Node* y = nullptr;
        Node* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);

        printTreeStructure("Red-Black Tree after insertion of " + to_string(key) + ":");
    }

    void deleteNode(int data) {
        deleteNodeHelper(root, data);
        printTreeStructure("Red-Black Tree after deletion of " + to_string(data) + ":");
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    RBTree tree;

    int n_insert, n_delete;

    cin >> n_insert;
    for (int i = 0; i < n_insert; i++) {
        int key; cin >> key;
        tree.insert(key);
    }

    cout << "Inorder traversal after insertion: ";
    tree.inorder();

    cin >> n_delete;
    for (int i = 0; i < n_delete; i++) {
        int key; cin >> key;
        cout << "Deleting " << key << "\n";
        tree.deleteNode(key);
        cout << "Inorder traversal after deletion: ";
        tree.inorder();
    }

    return 0;
}

/*
5
10 20 30 15 25
2
20 10

*/