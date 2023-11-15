#include <iostream >

using namespace std;

class DisjointSet
{
private:
    int *parent; // parent of node
    int *rank;   // depth of subtree rooted at node
    int total;   // number of nodes

public:
    // Constructor to construct Disjoint set with n elements
    DisjointSet(int numberOfNodes)
    {
        // one indexing
        parent = new int[numberOfNodes + 1];
        rank = new int[numberOfNodes + 1];

        for (int i = 1; i <= numberOfNodes; i++)
        {
            // originally all nodes are seperate so each node is its own parent
            parent[i] = i;

            // rank=0 beacuse ever node is a set ,so it has no children
            rank[i] = 0;
        }
        total = numberOfNodes;
    }

    // Finding the representative of the set which has the node
    int find(int node)
    {
        int temp = node;

        // when we reach a node that is its own parent tha means we reached the representative
        while (parent[temp] != temp)
        {
            temp = parent[temp];
        }

        return temp;
    }

    // Finding the representative of the set which has the node
    // and also applying path compression
    int findPathComp(int node)
    {
        if (parent[node] != node)
        {
            parent[node] = find(parent[node]);
            rank[node] = 0;
            rank[parent[node]] = max(rank[parent[node]] - 1, 1);
        }
        return parent[node];
    }

    // Combining the two sets of node1 & node2
    void Union(int node1, int node2)
    {
        // finding the representatives of the sets
        int representative1 = find(node1);
        int representative2 = find(node2);

        // nodes are already in the same set
        if (representative1 == representative2)
            return;

        // making the set with the less rank(shorter subtree rooted at representative)
        //  a subtree in the other set

        if (rank[representative1] < rank[representative2])
        {
            parent[representative1] = representative2;
        }

        else if (rank[representative1] > rank[representative2])
        {
            parent[representative2] = representative1;
        }

        // ranks are equal
        else
        {
            parent[representative1] = representative2;
            rank[representative2]++;
        }
    }

    void Print()
    {
        for (int i = 1; i <= total; i++)
        {
            cout << i << " ";
        }
        cout << '\n';
        for (int i = 1; i <= total; i++)
        {
            cout << parent[i] << " ";
        }
        cout << '\n';
        for (int i = 1; i <= total; i++)
        {
            cout << rank[i] << " ";
        }
        cout << "\n-----------------------------\n";
    }

    // Destructor
    ~DisjointSet()
    {
        delete[] parent;
        delete[] rank;
    }
};

int main()
{
    int n = 8;

    DisjointSet ds(n);
    ds.Print();

    //  TEST CASE 1

    ds.Union(1, 2);
    ds.Print();
    ds.Union(3, 2);
    ds.Print();
    ds.Union(5, 4);
    ds.Print();
    ds.Union(6, 4);
    ds.Print();

    ds.Union(2, 5);
    ds.Print();

    // Path compression
    for (int i = 1; i <= 8; i++)
    {
        int x = ds.findPathComp(i);
    }
    ds.Print();

    //  TEST CASE2

    /*
        for (int i = 1; i < 8; i += 2)
        {
            ds.Union(i, i + 1);
        }
        ds.Print();

        for (int i = 2; i < 8; i += 2)
        {
            ds.Union(i, i + 1);
        }
        ds.Print();

        // Path compression
        for (int i = 1; i <= 8; i++)
        {
            int x = ds.findPathComp(i);
        }
        ds.Print();
    */
    return 0;
}
