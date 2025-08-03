#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

class BPlusTreeNode {
public:
    bool leaf;
    std::vector<int> keys;
    std::vector<BPlusTreeNode*> children;
    BPlusTreeNode* parent;
    int numKeys;
    int t;  
    BPlusTreeNode(bool _leaf, int _t) : leaf(_leaf), numKeys(0), parent(nullptr), t(_t) {}

    void insertNonFull(int key);
    void splitChild(int index, BPlusTreeNode* y);
    void remove(int key);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPred(int idx);
    int getSucc(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BPlusTree;
};

class BPlusTree {
    BPlusTreeNode* root;
    int t;  

public:
    BPlusTree(int _t) : t(_t) {
        root = new BPlusTreeNode(true, t);
    }

    void insert(int key);
    void remove(int key);
    void traverse() { traverse(root); }

private:
    void traverse(BPlusTreeNode* node);
};

void BPlusTreeNode::insertNonFull(int key) {
    int i = numKeys - 1;

    if (leaf) {
        keys.push_back(0);
        while (i >= 0 && key < keys[i]) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
        numKeys++;
    } else {
        while (i >= 0 && key < keys[i]) {
            i--;
        }
        i++;
        if (children[i]->numKeys == 2 * t - 1) {
            splitChild(i, children[i]);
            if (key > keys[i]) {
                i++;
            }
        }
        children[i]->insertNonFull(key);
    }
}

void BPlusTreeNode::splitChild(int index, BPlusTreeNode* y) {
    BPlusTreeNode* z = new BPlusTreeNode(y->leaf, y->t);
    z->numKeys = t - 1;

    for (int j = 0; j < t - 1; j++) {
        z->keys.push_back(y->keys[j + t]);
    }

    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->children.push_back(y->children[j + t]);
        }
    }

    y->numKeys = t - 1;
    y->keys.resize(t - 1);
    if (!y->leaf) y->children.resize(t);

    children.insert(children.begin() + index + 1, z);
    keys.insert(keys.begin() + index, y->keys[t - 1]);
    numKeys++;
}

void BPlusTreeNode::remove(int key) {
    int idx = std::lower_bound(keys.begin(), keys.end(), key) - keys.begin();

    if (idx < numKeys && keys[idx] == key) {
        if (leaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
    } else {
        if (leaf) {
            std::cout << "The key " << key << " is not present in the tree.\n";
            return;
        }

        if (children[idx]->numKeys < t) {
            borrowFromPrev(idx);
        }
        children[idx]->remove(key);
    }
}

void BPlusTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < numKeys; i++) {
        keys[i - 1] = keys[i];
    }
    keys.pop_back();
    numKeys--;
}

void BPlusTreeNode::removeFromNonLeaf(int idx) {
    int key = keys[idx];

    if (children[idx]->numKeys >= t) {
        int pred = getPred(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    } else if (children[idx + 1]->numKeys >= t) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    } else {
        merge(idx);
        children[idx]->remove(key);
    }
}

int BPlusTreeNode::getPred(int idx) {
    BPlusTreeNode* cur = children[idx];
    while (!cur->leaf) {
        cur = cur->children[cur->numKeys];
    }
    return cur->keys[cur->numKeys - 1];
}

int BPlusTreeNode::getSucc(int idx) {
    BPlusTreeNode* cur = children[idx + 1];
    while (!cur->leaf) {
        cur = cur->children[0];
    }
    return cur->keys[0];
}

void BPlusTreeNode::borrowFromPrev(int idx) {
    if (idx == 0) return;
    BPlusTreeNode* child = children[idx];
    BPlusTreeNode* sibling = children[idx - 1];

    child->keys.insert(child->keys.begin(), keys[idx - 1]);
    if (!child->leaf) {
        child->children.insert(child->children.begin(), sibling->children[sibling->numKeys]);
    }

    keys[idx - 1] = sibling->keys[sibling->numKeys - 1];
    sibling->keys.pop_back();
    if (!sibling->leaf) sibling->children.pop_back();

    child->numKeys++;
    sibling->numKeys--;
}

void BPlusTreeNode::borrowFromNext(int idx) {
    BPlusTreeNode* child = children[idx];
    BPlusTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    if (!child->leaf) {
        child->children.push_back(sibling->children[0]);
        sibling->children.erase(sibling->children.begin());
    }

    keys[idx] = sibling->keys[0];
    sibling->keys.erase(sibling->keys.begin());

    child->numKeys++;
    sibling->numKeys--;
}

void BPlusTreeNode::merge(int idx) {
    BPlusTreeNode* child = children[idx];
    BPlusTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    for (int i = 0; i < sibling->numKeys; i++) {
        child->keys.push_back(sibling->keys[i]);
    }

    if (!child->leaf) {
        for (int i = 0; i <= sibling->numKeys; i++) {
            child->children.push_back(sibling->children[i]);
        }
    }

    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);

    child->numKeys += sibling->numKeys + 1;
    numKeys--;

    delete sibling;
}

void BPlusTree::insert(int key) {
    if (root->numKeys == 2 * t - 1) {
        BPlusTreeNode* s = new BPlusTreeNode(false, t);
        s->children.push_back(root);
        s->splitChild(0, root);
        root = s;
    }
    root->insertNonFull(key);
}

void BPlusTree::remove(int key) {
    if (!root) return;
    root->remove(key);
    if (root->numKeys == 0) {
        BPlusTreeNode* oldRoot = root;
        if (root->leaf) {
            root = nullptr;
        } else {
            root = root->children[0];
        }
        delete oldRoot;
    }
}

void BPlusTree::traverse(BPlusTreeNode* node) {
    if (node) {
        int i;
        for (i = 0; i < node->numKeys; i++) {
            if (!node->leaf) {
                traverse(node->children[i]);
            }
            std::cout << node->keys[i] << " ";
        }
        if (!node->leaf) {
            traverse(node->children[i]);
        }
    }
}

int main() {
    int t_order, n_keys;
    std::cin >> t_order >> n_keys;

    BPlusTree tree(t_order);

    for (int i = 0; i < n_keys; i++) {
        int key;
        std::cin >> key;
        tree.insert(key);
    }

    std::cout << "The B+ tree is: ";
    tree.traverse();
    std::cout << "\n";

    int n_delete;
    std::cin >> n_delete;

    for (int i = 0; i < n_delete; i++) {
        int key;
        std::cin >> key;
        std::cout << "Deleting " << key << ": ";
        tree.remove(key);
        std::cout << "After deletion, B+ tree is: ";
        tree.traverse();
        std::cout << "\n";
    }

    return 0;
}