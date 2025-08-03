#include <iostream>
using namespace std;

class Node
{
    int *keys;     // Array of keys
    int t;         // Minimum degree (defines the range for number of keys)
    Node **C;      // Array of child pointers
    int n;         // Current number of keys
    bool leaf;     // Is true when node is leaf

public:
    Node(int _t, bool _leaf);

    void traverse();

    void insertNonFull(int k);
    void splitChild(int i, Node *y);

    void remove(int k);
    int findKey(int k);

    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);

    int getPred(int idx);
    int getSucc(int idx);

    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BTree;
};

class BTree
{
    Node *root;
    int t;

public:
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    void insert(int k);

    void remove(int k);
};

// Node constructor
Node::Node(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;

    keys = new int[2 * t - 1];
    C = new Node *[2 * t];
    n = 0;
}

// Traverse all nodes in a subtree rooted with this node
void Node::traverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    if (leaf == false)
        C[i]->traverse();
}

// Insert a new key in subtree rooted with this node.
// The node must be non-full when this is called
void Node::insertNonFull(int k)
{
    int i = n - 1;

    if (leaf == true)
    {
        // Find location of new key to be inserted and move all greater keys one space ahead
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    }
    else
    {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

// Split the child y of this node.
// i is index of y in child array C[]
void Node::splitChild(int i, Node *y)
{
    Node *z = new Node(y->t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    // Copy the last t children of y to z
    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;

    // Create space for new child
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    // Move keys of current node to create space for middle key of y
    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    // Copy middle key of y to this node
    keys[i] = y->keys[t - 1];

    n = n + 1;
}

// Insert key k in the BTree
void BTree::insert(int k)
{
    if (root == NULL)
    {
        root = new Node(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            Node *s = new Node(t, false);
            s->C[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        }
        else
        {
            root->insertNonFull(k);
        }
    }
}

// Find the index of the first key that is >= k
int Node::findKey(int k)
{
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

// Remove key k from subtree rooted with this node
void Node::remove(int k)
{
    int idx = findKey(k);

    if (idx < n && keys[idx] == k)
    {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {
        if (leaf)
        {
            cout << "The key " << k << " is not present in the tree\n";
            return;
        }

        bool flag = ((idx == n) ? true : false);

        if (C[idx]->n < t)
            fill(idx);

        if (flag && idx > n)
            C[idx - 1]->remove(k);
        else
            C[idx]->remove(k);
    }
}

// Remove key present in idx-th position in this leaf node
void Node::removeFromLeaf(int idx)
{
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    n--;
}

// Remove key present in idx-th position in this internal node
void Node::removeFromNonLeaf(int idx)
{
    int k = keys[idx];

    if (C[idx]->n >= t)
    {
        int pred = getPred(idx);
        keys[idx] = pred;
        C[idx]->remove(pred);
    }
    else if (C[idx + 1]->n >= t)
    {
        int succ = getSucc(idx);
        keys[idx] = succ;
        C[idx + 1]->remove(succ);
    }
    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
}

// Get predecessor of keys[idx]
int Node::getPred(int idx)
{
    Node *cur = C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];
    return cur->keys[cur->n - 1];
}

// Get successor of keys[idx]
int Node::getSucc(int idx)
{
    Node *cur = C[idx + 1];
    while (!cur->leaf)
        cur = cur->C[0];
    return cur->keys[0];
}

// Fill child C[idx] which has less than t-1 keys
void Node::fill(int idx)
{
    if (idx != 0 && C[idx - 1]->n >= t)
        borrowFromPrev(idx);
    else if (idx != n && C[idx + 1]->n >= t)
        borrowFromNext(idx);
    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
}

// Borrow a key from C[idx-1] and insert it into C[idx]
void Node::borrowFromPrev(int idx)
{
    Node *child = C[idx];
    Node *sibling = C[idx - 1];

    // Shift all keys in child one step ahead
    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    // If child is not leaf, shift its child pointers
    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; --i)
            child->C[i + 1] = child->C[i];
    }

    // Set child's first key equal to keys[idx-1] from current node
    child->keys[0] = keys[idx - 1];

    // Move sibling's last child as child's first child
    if (!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    // Move the key from sibling to current node
    keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

// Borrow a key from C[idx+1] and insert it into C[idx]
void Node::borrowFromNext(int idx)
{
    Node *child = C[idx];
    Node *sibling = C[idx + 1];

    // keys[idx] is inserted as the last key in child
    child->keys[child->n] = keys[idx];

    // Sibling's first child is inserted as last child of child
    if (!(child->leaf))
        child->C[child->n + 1] = sibling->C[0];

    // First key from sibling is inserted into keys[idx]
    keys[idx] = sibling->keys[0];

    // Shift all keys in sibling one step behind
    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    // Shift child pointers if sibling is not leaf
    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->C[i - 1] = sibling->C[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

// Merge C[idx] and C[idx+1] after moving keys[idx] down
void Node::merge(int idx)
{
    Node *child = C[idx];
    Node *sibling = C[idx + 1];

    // Pull a key from the current node and insert it into (t-1)th position of child
    child->keys[t - 1] = keys[idx];

    // Copy keys from sibling to child
    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];

    // Copy child pointers from sibling to child
    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->n; ++i)
            child->C[i + t] = sibling->C[i];
    }

    // Move keys and child pointers in current node to fill gap
    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= n; ++i)
        C[i - 1] = C[i];

    child->n += sibling->n + 1;
    n--;

    delete (sibling);
}

// Remove key k from BTree
void BTree::remove(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }

    root->remove(k);

    if (root->n == 0)
    {
        Node *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];

        delete tmp;
    }
}

// Main function to test the B-tree
int main()
{
    int t_order, n_keys;
    cin >> t_order >> n_keys;

    BTree tree(t_order);

    for (int i = 0; i < n_keys; i++)
    {
        int key;
        cin >> key;
        tree.insert(key);
    }

    cout << "The B-tree is:";
    tree.traverse();
    cout << "\n";

    int n_delete;
    cin >> n_delete;

    for (int i = 0; i < n_delete; i++)
    {
        int key;
        cin >> key;
        cout << "Deleting " << key << ": ";
        tree.remove(key);
        cout << "After deletion, B-tree is:";
        tree.traverse();
        cout << "\n";
    }

    return 0;
}

/*
3 8
10 20 5 6 12 30 7 17
1
20

*/