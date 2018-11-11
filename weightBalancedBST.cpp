// C++ Implementation of Weight-Balance BST
// Austin Chun


#include "weightBalancedBST.hpp"
#include <stack>
#include <iostream>

using namespace std;

// Constructors
WBBST::WBBST() 
    : root_(NULL), size_(0), alpha_(0.8), height_(-1)
{
    // Nothing
}

WBBST::WBBST(float alpha) 
    : root_(NULL), size_(0), alpha_(alpha), height_(-1)
{
    // Nothing
}

// WBBST::WBBST(const WBBST& orig)
// {
//     // TODO   
// }


WBBST::~WBBST()
{
    delete root_;
}

void WBBST::insert(int e)
{
    
    Node* ne = new Node(e);

    // If empty tree
    if(size_ == 0){
        ne->depth = 0;
        root_ = ne;
        ++size_;
        ++height_;
        return;
    }

    // Non-empty tree

    Node* cur = root_;
    bool DONE = false;
    while(!DONE){ // Loop until leaf
        // If duplicate
        if(e == cur->value){
            std::cout << "Duplicate value, thus no insertion" << std::endl;
            return;
        }
        ++cur->size; // Increment size

        // If greater, right tree
        if(e > cur->value){
            // If reached 'leaf'
            if(cur->right == NULL){
                cur->right = ne; // Set new node as child
                ne->parent = cur; // Set parent nore
                ne->depth = ne->parent->depth + 1;
                if(ne->depth > height_){
                    height_ = ne->depth;
                }
                DONE = true;
            }
            else{
                // // Check if too unbalanced
                // if( (cur_->right->size + 1) >= (cur_->size_ * alpha_)){
                //     cur = rebalance(cur);
                // }


                cur = cur->right; // Continue down tree
            }
        }
        // If less, left tree
        else if(e < cur->value){
            // If reached 'leaf'
            if(cur->left == NULL){
                cur->left = ne;
                ne->parent = cur;
                ne->depth = ne->parent->depth + 1;
                if(ne->depth > height_){
                    height_ = ne->depth;
                }
                DONE = true;
            }
            else{
                cur = cur->left;
            }
        }
    }

    ++size_;


}


size_t WBBST::size() const
{
    return size_;
}

bool WBBST::empty() const
{
    return size_==0;
}

void WBBST::setAlpha(float alpha)
{
    alpha_ = alpha;
}

float WBBST::getAlpha() const
{
    return alpha_;
}

int WBBST::height() const
{
    return height_;
}


///////////////////////
//// Node Subclass ////
///////////////////////
WBBST::Node::Node(int val)
    : value(val), size(1), parent(NULL), left(NULL), right(NULL)
{   
    // Nothing else
}

WBBST::Node::Node(int val, Node* parent)
    : value(val), size(1), parent(parent), left(NULL), right(NULL)
{
    ++parent->size;
    if(parent->value > value){
        parent->left = this;
    }
    else{
        parent->right = this;
    }
}

WBBST::Node::~Node()
{
    delete left;
    delete right;
}

void WBBST::rebalance()
{
    rebalance(root_);
}

WBBST::Node* WBBST::rebalance(Node* n)
{

    // Convert subtree to sorted vector
    vector<int> v = inorder(n);

    // Store previous parent
    Node* prev_parent = n->parent; 
    // Delete current subtree
    delete n;

    // Convert vector into balanced tree
    Node* new_root = vectorToBST(v, 0, v.size(), n->depth);


    // If not the tree root (ie, has a parent)
    if(prev_parent != NULL){
        new_root->parent = prev_parent; 
        if(prev_parent->value > new_root->value){
            prev_parent->left = new_root;
        }
        else{
            prev_parent->right = new_root;
        }
    }
    else{ // Set tree root_ to be new root
        root_ = new_root;
    }

    return new_root;

}

WBBST::Node* WBBST::vectorToBST(const std::vector<int>& v, int start, int end, int depth){
    // Base case
    if(start >= end){
        return NULL;
    }

    int mid = (start+end)/2;

    Node* root = new Node(v[mid]);
    root->depth = depth;
    Node* left  = vectorToBST(v, start, mid, depth+1);
    Node* right = vectorToBST(v, mid+1, end, depth+1);

    root->left = left;
    root->right = right;

    if(left != NULL){
        root->size += left->size;
        left->parent = root;
    }
    if(right != NULL){
        root->size += right->size;
        right->parent = root;
    }

    return root;
}


std::vector<int> WBBST::inorder(Node* n)
{

    // Initialize vector to store sorted array
    std::vector<int> v (n->size);
    int i = 0;

    std::stack<Node*> s; // initialize stack
    Node* cur = n; // set current

    while( cur!=NULL || s.empty()==false){
        // Go as far left as possible
        while (cur != NULL){
            s.push(cur);
            cur = cur->left;
        }

        // Current is NULL
        cur = s.top();
        s.pop();

        v[i++] = cur->value;

        // Now check the right tree
        cur = cur->right;
    }

    return v;
}

std::ostream& WBBST::print(std::ostream& out) const
{
    return print(out, root_);
}

std::ostream& WBBST::printInOrder(std::ostream& out) const
{
    return printInOrder(out, root_);
}

std::ostream& WBBST::print(std::ostream& out, const Node* n) const
{
    if(n == NULL){
        return out;
    }
    out << n->value << ",";

    print(out, n->left);
    print(out, n->right);

    return out;
}

std::ostream& WBBST::printInOrder(std::ostream& out, const Node* n) const
{
    if(n == NULL){
        return out;
    }

    printInOrder(out, n->left);
    out << n->value << ",";
    printInOrder(out, n->right);

    return out;
}