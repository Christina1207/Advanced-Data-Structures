
#include <iostream>
#include <cmath>
#include <queue>
#include <stack>
using namespace std;

// node data structure
struct Node
{
	int data;	   // contains the key
	int degree;	   // number of children
	Node *p;	   // pointer to parent
	Node *child;   // pointer to the leftmost child
	Node *sibling; // pointer to the right sibling
};

typedef Node *NodePtr;

// Class that represents Binomial heap data structure
class BinomialHeap
{
private:
	// head points to the root of the leftmost binomial tree
	NodePtr head;

	// initializes  the node with default values
	// all pointers are initialized to nullptr
	void initializeNode(NodePtr node, int data, int degree)
	{
		node->data = data;
		node->degree = degree;
		node->p = nullptr;
		node->child = nullptr;
		node->sibling = nullptr;
	}

	// merge two binomial trees of same degree
	static void linkBinomialTrees(NodePtr x, NodePtr y)
	{
		// x must be parent of y
		y->p = x;
		y->sibling = x->child;
		x->child = y;

		// increase the degree of x
		x->degree += 1;
	}

public:
	BinomialHeap()
	{
		head = nullptr;
	}

	// find the node with mininum data

	NodePtr findMinimum()
	{
		// traverse all the roots and find compare
		int min = 999999;
		NodePtr currPtr = head;
		NodePtr minPtr = nullptr;

		while (currPtr != nullptr)
		{
			if (currPtr->data < min)
			{
				min = currPtr->data;
				minPtr = currPtr;
			}
			currPtr = currPtr->sibling;
		}

		return minPtr;
	}

	// create sample heap (given in figure 5) with three trees for testing
	void createSampleHeap1()
	{
		// B0
		NodePtr node1 = new Node;
		initializeNode(node1, 5, 0);
		head = node1;

		// B1
		NodePtr node2 = new Node;
		initializeNode(node2, 17, 1);
		NodePtr node3 = new Node;
		initializeNode(node3, 27, 0);
		node2->child = node3;
		node3->p = node2;

		// link B0 and B1
		node1->sibling = node2;

		// B3
		NodePtr node4 = new Node;
		initializeNode(node4, 12, 3);
		NodePtr node5 = new Node;
		initializeNode(node5, 18, 2);
		NodePtr node6 = new Node;
		initializeNode(node6, 16, 1);
		NodePtr node7 = new Node;
		initializeNode(node7, 15, 0);
		NodePtr node8 = new Node;
		initializeNode(node8, 23, 1);
		NodePtr node9 = new Node;
		initializeNode(node9, 30, 0);
		NodePtr node10 = new Node;
		initializeNode(node10, 22, 0);
		NodePtr node11 = new Node;
		initializeNode(node11, 25, 0);
		node4->child = node5;
		node5->p = node4;
		node6->p = node4;
		node7->p = node4;
		node5->child = node8;
		node5->sibling = node6;
		node6->child = node10;
		node6->sibling = node7;
		node8->p = node5;
		node9->p = node5;
		node10->p = node6;
		node8->child = node11;
		node8->sibling = node9;
		node11->p = node8;

		// link B1 and B3
		node2->sibling = node4;
	}

	// create sample heap (given in figure Fig 10 (a))
	void createSampleHeap2()
	{
		// B0
		NodePtr node1 = new Node;
		initializeNode(node1, 5, 0);
		head = node1;

		// B2
		NodePtr node2 = new Node;
		initializeNode(node2, 6, 2);
		NodePtr node3 = new Node;
		initializeNode(node3, 12, 1);
		NodePtr node4 = new Node;
		initializeNode(node4, 34, 0);
		NodePtr node5 = new Node;
		initializeNode(node5, 33, 0);
		node2->child = node3;
		node3->p = node2;
		node4->p = node2;
		node3->child = node5;
		node3->sibling = node4;
		node5->p = node3;

		// link B0 and B1
		node1->sibling = node2;

		// B3
		
		NodePtr node6 = new Node;
		initializeNode(node6, 1, 3);
		NodePtr node7 = new Node;
		initializeNode(node7, 2, 2);
		NodePtr node8 = new Node;
		initializeNode(node8, 12, 1);
		NodePtr node9 = new Node;
		initializeNode(node9, 6, 0);
		NodePtr node10 = new Node;
		initializeNode(node10, 4, 1);
		NodePtr node11 = new Node;
		initializeNode(node11, 13, 0);
		NodePtr node12 = new Node;
		initializeNode(node12, 18, 0);
		NodePtr node13 = new Node;
		initializeNode(node13, 7, 0);
		node6->child = node7;
		node7->p = node6;
		node8->p = node6;
		node7->p = node6;
		node7->child = node10;
		node7->sibling = node8;
		node8->child = node12;
		node8->sibling = node9;
		node10->p = node7;
		node11->p = node7;
		node12->p = node8;
		node10->child = node13;
		node10->sibling = node11;
		node13->p = node10;

		// link B1 and B3
		node2->sibling = node6;
	}

	// crete sample heap (given in figure 10 (b))
	void createSampleHeap3()
	{
		// B1
		NodePtr node1 = new Node;
		initializeNode(node1, 29, 1);
		NodePtr node2 = new Node;
		initializeNode(node2, 33, 0);
		node1->child = node2;
		node2->p = node1;
		head = node1;

		// B2
		NodePtr node3 = new Node;
		initializeNode(node3, 21, 2);
		NodePtr node4 = new Node;
		initializeNode(node4, 23, 1);
		NodePtr node5 = new Node;
		initializeNode(node5, 78, 0);
		NodePtr node6 = new Node;
		initializeNode(node6, 50, 0);
		node3->child = node4;
		node4->p = node3;
		node5->p = node3;
		node4->child = node6;
		node4->sibling = node5;
		node6->p = node4;

		// link B1 and B2
		node1->sibling = node3;
	}

	// insert a node to the heap
	void insert(int data)
	{
		BinomialHeap h;
		NodePtr node = new Node;
		initializeNode(node, data, 0);
		h.setHead(node);
		merge(h);
	}

	// print the binomial heap with all the trees
	void printHeap()
	{
		NodePtr currPtr = head;
		while (currPtr != nullptr)
		{
			cout << "B" << currPtr->degree << endl;
			cout << "There are " << pow(2, currPtr->degree) << " nodes in this tree" << endl;
			cout << "The level order traversal is" << endl;
			queue<NodePtr> q;
			q.push(currPtr);
			while (!q.empty())
			{
				NodePtr p = q.front();
				q.pop();
				cout << p->data << " ";

				if (p->child != nullptr)
				{
					NodePtr tempPtr = p->child;
					while (tempPtr != nullptr)
					{
						q.push(tempPtr);
						tempPtr = tempPtr->sibling;
					}
				}
			}
			currPtr = currPtr->sibling;
			cout << endl
				 << endl;
		}
	}

	// returns the head pointer
	NodePtr getHead()
	{
		return head;
	}

	// setter for head
	void setHead(NodePtr head)
	{
		this->head = head;
	}

	// merge two binomial heaps H and H'
	// resulting heap will be H
	void merge(BinomialHeap h1)
	{
		NodePtr curr1 = getHead();
		NodePtr curr2 = h1.getHead();
		NodePtr curr3 = nullptr;
		NodePtr temp = nullptr;

		if (curr1->degree <= curr2->degree)
		{
			curr3 = curr1;
			curr1 = curr1->sibling;
		}
		else
		{
			curr3 = curr2;
			curr2 = curr2->sibling;
		}
		temp = curr3;
		while (curr1 != nullptr && curr2 != nullptr)
		{
			if (curr1->degree <= curr2->degree)
			{
				curr3->sibling = curr1;
				curr1 = curr1->sibling;
			}
			else
			{
				curr3->sibling = curr2;
				curr2 = curr2->sibling;
			}

			curr3 = curr3->sibling;
		}

		if (curr1 != nullptr)
		{
			// copy all the remaining trees of heap1
			while (curr1 != nullptr)
			{
				curr3->sibling = curr1;
				curr1 = curr1->sibling;
				curr3 = curr3->sibling;
			}
		}

		if (curr2 != nullptr)
		{
			// copy all the remaining trees of heap2
			while (curr2 != nullptr)
			{
				curr3->sibling = curr2;
				curr2 = curr2->sibling;
				curr3 = curr3->sibling;
			}
		}

		// scan the merged list and repeatidly merge binomial trees with same degree
		curr3 = temp;
		NodePtr prev = nullptr;
		NodePtr next = curr3->sibling;

		while (next != nullptr)
		{
			// if two adjacent tree roots have different degree or 3 consecutive roots have same degree
			// move to the next tree
			if ((curr3->degree != next->degree) || (next->sibling != nullptr && curr3->degree == next->sibling->degree))
			{
				prev = curr3;
				curr3 = next;
			}
			else
			{
				// otherwise repeatdly merge binomial trees with same degree
				if (curr3->data <= next->data)
				{
					curr3->sibling = next->sibling;
					BinomialHeap::linkBinomialTrees(curr3, next);
				}
				else
				{
					if (prev == nullptr)
					{
						temp = next;
					}
					else
					{
						prev->sibling = next;
					}

					BinomialHeap::linkBinomialTrees(next, curr3);
					curr3 = next;
				}
			}

			next = curr3->sibling;
		}

		setHead(temp);
	}

	// deletes the smallest node from the heap
	NodePtr deleteMin()
	{
		NodePtr min = findMinimum();
		NodePtr prev = nullptr;
		NodePtr curr = head;
		while (curr->data != min->data)
		{
			prev = curr;
			curr = curr->sibling;
		}

		if (prev && min->sibling)
		{
			prev->sibling = min->sibling;
		}
		else if (prev && !min->sibling)
		{
			prev->sibling = nullptr;
		}
		else if (!prev && min->sibling)
		{
			head = min->sibling;
		}
		else if (!prev && !min->sibling)
		{
			head = nullptr;
		}

		NodePtr childPtr = min->child;
		while (childPtr != nullptr)
		{
			childPtr->p = nullptr;
			childPtr = childPtr->sibling;
		}

		// during the session i implemented the reversal using pointers
		// and without using any external data structures
		// but i kept getting segmentation faults
		stack<NodePtr> st;
		childPtr = min->child;
		while (childPtr)
		{
			st.push(childPtr);
			childPtr = childPtr->sibling;
		}

		curr = st.top();
		NodePtr newHead = curr;
		st.pop();
		while (!st.empty())
		{
			curr->sibling = st.top();
			st.pop();
			curr = curr->sibling;
		}

		curr->sibling = nullptr;

		BinomialHeap h;
		h.setHead(newHead);
		merge(h);
		return min;
	}

	// in order to implement the decrease function we need to write
	// a function to find the key

	NodePtr findNode(NodePtr node, int key)
	{
		if (node == nullptr)
			return nullptr;

		if (node->data == key)
			return node;

		NodePtr check = findNode(node->child, key);
		if (check != nullptr)
			return check;

		return findNode(node->sibling, key);
	}

	// helper function
	void swapVal(NodePtr node1, NodePtr node2)
	{
		int temp = node1->data;
		node1->data = node2->data;
		node2->data = temp;
	}

	//implementaion of the decrease function
	void decrease(int val1, int val2)
	{
		NodePtr node = findNode(this->head, val1);
		if (node == nullptr)
			return;


		node->data = val2;
		NodePtr temp = node;
		while (temp->p && (temp->data < temp->p->data) )
		{
			swapVal(temp, temp->p);

			temp = temp->p;
			if(temp==nullptr)break;
		}
	}
};

int main()
{
	BinomialHeap heap1;
	BinomialHeap heap2;
	BinomialHeap heap3;
	heap1.createSampleHeap2();
	heap2.createSampleHeap3();
	heap1.merge(heap2);
	heap1.printHeap();
	heap1.deleteMin();
	heap1.printHeap();

	//testing decrease function
	heap1.decrease(33,1);
	heap1.printHeap();

	return 0;
}