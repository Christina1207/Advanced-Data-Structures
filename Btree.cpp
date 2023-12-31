#include <iostream>
using namespace std;

class Node
{
    int *keys; // array of keys
    int t;     // degree of tree
    Node **C;  // array of children
    int n;     // number of keys in the node
    bool leaf; // is true if node is a leaf node

public:
    Node(int _t, bool _leaf);        // constructer
    void insertNonFull(int k);       // insert into an non-full node
    void splitChild(int i, Node *y); // split children in insertion
    void traverse();                 // traversal of the keys of a node
    void remove(int k);              // remove a key froma node
    friend class BTree;
};

class BTree
{

public:
    Node *root;                        // root of the tree
    int t;                             // degree of the tree
    BTree(int _t);                     // constructer
    void traverse();                   // inorder traversal of Btree
    void insert(int k);                // insert a key to btree
    void print(Node *node, int level); // print
};

// Node Constructer
Node::Node(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;

    keys = new int[2 * t - 1];
    C = new Node *[2 * t];

    n = 0;
}

// Insert key into a non full node
void Node::insertNonFull(int k)
{
    int i = n - 1;

    if (leaf == true)
    {
        // moving all keys until k's place is found
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }
        // putting k in its place
        keys[i + 1] = k;
        n = n + 1;
    }
    else
    {
        // finding the right child that could contain k
        while (i >= 0 && keys[i] > k)
            i--;

        // if child is full
        if (C[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }

        C[i + 1]->insertNonFull(k);
    }
}

// split the child
void Node::splitChild(int i, Node *y)
{
    Node *z = new Node(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n = n + 1;
}

// Here we're implementing a travesal similar to the inorder traversal of a binary tree
// the function recursivly traverses the keys in the node and its child nodes
// printing the keys in depth first manner
// starting from the leftmost child up to the root and down to the rightmost child
void Node::traverse()
{
    for (int i = 0; i < n; i++)
    {
        if (!leaf)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    if (!leaf && C[n])
        C[n]->traverse();
}

// Btree Constructer
BTree::BTree(int _t)
{
    root = NULL;
    t = _t;
}

// inorder traversal of Btree
void BTree::traverse()
{
    if (root != NULL)
        root->traverse();
}

// Insert the key k in the Btree
void BTree::insert(int k)
{
    // tree is empty
    if (root == NULL)
    {
        root = new Node(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
        // root is full
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
            root->insertNonFull(k);
    }
}

// printing the Btre
void BTree::print(Node *root, int level)
{
    if (root != NULL)
    {
        int i;
        for (i = root->n - 1; i >= 0; i--)
        {
            if (root->leaf == false)
                print(root->C[i + 1], level + 1);

            for (int k = 0; k < level; k++)
                cout << "    ";
            cout << root->keys[i] << "\n";
        }

        if (root->leaf == false)
            print(root->C[i + 1], level + 1);
    }
}

int main()
{
    BTree t(3);

    int keys[] = {18, 27, 8, 35, 12, 45, 22, 31, 7, 40, 15, 26, 36, 5, 48, 17, 30, 2, 38, 20, 42, 11, 33, 6, 25, 37, 13, 21, 10, 44};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < num_keys; i++)
    {
        t.insert(keys[i]);
        cout << "Tree after inserting " << keys[i] << ":\n";
        t.print(t.root, 0);
        cout << "----------------\n";
    }
    cout << "Traversing the B-tree is: ";
    t.traverse();
}
