// Inserting a key on a B-tree in C++

#include <iostream>
using namespace std;

class Node
{
  int *keys;
  int t;
  Node **C;
  int n;
  bool leaf;

public:
  Node(int _t, bool _leaf);

  void insertNonFull(int k);
  void splitChild(int i, Node *y);
  void traverse();
  void remove(int k);
  friend class BTree;
};

class BTree
{

public:
  Node *root;
  int t;
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
  void print(Node *node, int level);
};

Node::Node(int t1, bool leaf1)
{
  t = t1;
  leaf = leaf1;

  keys = new int[2 * t - 1];
  C = new Node *[2 * t];

  n = 0;
}

// TODO: Implement traverse function

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

// Insert the node
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
      root->insertNonFull(k);
  }
}
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

// Insert non full condition
void Node::insertNonFull(int k)
{
  int i = n - 1;

  if (leaf == true)
  {
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
