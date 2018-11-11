#ifndef WBBST_INCLUDED
#define WBBST_INCLUDED 1


#include <vector>
#include <cstddef>
#include <iostream>

class WBBST{

public:

    // Constructor
    WBBST();
    WBBST(float alpha);
    // WBBST(const WBBST& orig); // Copy constructor

    // Destructor
    ~WBBST();

    // Insert int 
    void insert(int e);
    void insert(std::vector<int> es);

    // Remove element
    void remove(int e); 

    // Check if element exists
    bool exists(int e);

    size_t size() const;
    bool empty() const;
    void setAlpha(float alpha);
    float getAlpha() const;
    int height() const;

    // std::vector<int> inorder(); // Return inorder traversal of tree as vector

    std::ostream& print(std::ostream& out) const; // Layer wise

    std::ostream& printPreOrder(std::ostream& out) const;
    std::ostream& printInOrder(std::ostream& out) const;
    // std::ostream& print(std::ostream& out) const; ///< Printing

    // bool operator==(const WBBST& rhs);
    // bool operator!=(const WBBST& rhs);

    // void rebalance();

private:

    struct Node{
        // Data members
        int value; 
        int size; // Size of subtree
        int depth;
        Node* parent;
        Node* left; // left child
        Node* right;  // right child

        // Constructor
        Node(int val); 
        Node(int val, Node* parent);
        Node(int val, int size, int depth, Node* parent, Node* left, Node* right);

        // Destructor
        ~Node();
    };

    std::ostream& printPreOrder(std::ostream& out, const Node* n) const;
    std::ostream& printInOrder(std::ostream& out, const Node* n) const;


    Node* root_; // Pointer to root
    size_t size_; // Number of elements in tree
    float alpha_;
    int height_; // Height of tree


    Node* rebalance(Node* n, int e); // Rebalances tree given the current root, and returns new root
    std::vector<int> inorder(Node* n, int e);
    Node* vectorToBST(const std::vector<int>& v, int start, int end, int depth);
    void undoSizing(Node* cur);
};

inline std::ostream& operator<<(std::ostream& out, const WBBST& w)
{
    return w.print(out);
}

#endif 