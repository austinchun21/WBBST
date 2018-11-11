// C++ Implementation of Weight-Balance BST
// Austin Chun


#include "weightBalancedBST.hpp"
#include <stack>
#include <queue>
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
    Node* tmp; // Used for rebalance new_root (just in case rebalnce returns NULL)
    bool DONE = false;
    bool REPEAT = false;
    while(!DONE){ // Loop until leaf
        // If duplicate, do nothing
        if(e == cur->value){
            std::cout << "Duplicate value, thus no insertion" << std::endl;
            REPEAT = true;
            return;
        }
        ++cur->size; // Increment sizes

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
                // Check if too unbalanced
                if( (cur->right->size + 1) >= ( cur->size * alpha_)){
                    cout << "Rebalancing Right" << endl;
                    cout << " Before: " <<endl<< *this << endl;
                    tmp = rebalance(cur,e);
                    cout << " After:  " <<endl<< *this << endl;
                    // If cur is NULL, e is a duplicate
                    if(cur == NULL){
                        undoSizing(cur);
                        REPEAT = true;
                    }
                    else{
                        cur = tmp;
                    }
                    DONE = true;
                }

                // ++cur->size; // Increment size
                cur = cur->right; // Continue down tree
                cout << "Update current to right" << endl;
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
                // Check if too unbalanced
                if( (cur->left->size + 1) >= (cur->size * alpha_)){
                    cout << "Rebalancing Left" << endl;
                    cout << " Before: " <<endl<< *this << endl;
                    tmp = rebalance(cur,e);
                    cout << " After:  " <<endl<< *this << endl;
                    // If cur is NULL, e is a duplicate
                    if(cur == NULL){
                        undoSizing(cur);
                        REPEAT = true;
                    }
                    else{
                        cur = tmp;
                    }
                    DONE = true;
                }

                // ++cur->size; // Increment size
                cur = cur->left;
            }
        }

    }

    if(!REPEAT){
        ++size_;
    }

}


///////////////////////
//// Node Subclass ////
///////////////////////
WBBST::Node::Node(int val)
    : value(val), size(1), depth(0), parent(NULL), left(NULL), right(NULL)
{   
    // Nothing else
}

WBBST::Node::Node(int val, Node* parent)
    : value(val), size(1), depth(parent->depth+1), parent(parent), left(NULL), right(NULL)
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

// void WBBST::rebalance()
// {
//     rebalance(root_,);
// }

/**
 * @brief      rebalances a tree, given a root to rebalnce around
 *
 * @param      n     initial subtree root node
 * @param[in]  e     int to be inserted
 *
 * @return     the new root node (or NULL if e is a duplicate)
 */
WBBST::Node* WBBST::rebalance(Node* n, int e)
{

    // Convert subtree to sorted vector
    vector<int> v = inorder(n, e);
    // If sizes aren't equal, means insert is a duplicate
    if(v.size() != n->size){
        return NULL;
    }

    cout << "InOrder v: ";
    for(int i : v){
        cout << i << ",";
    }
    cout << endl;

    // Store previous parent
    Node* prev_parent = n->parent; 
    // Delete current subtree
    delete n;
    cout << "  Deleted n" << endl;
    // Convert vector into balanced tree
    int parent_depth;
    if(prev_parent == NULL)
        parent_depth = -1;
    else
        parent_depth = prev_parent->depth;

    Node* new_root = vectorToBST(v, 0, v.size(), parent_depth+1);

    cout << "  Finished vectToBST()" << endl;

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

    cout << "End rebalance" << endl;

    return new_root;

}

WBBST::Node* WBBST::vectorToBST(const std::vector<int>& v, int start, int end, int depth){
    // Base case
    if(start >= end){
        return NULL;
    }

    int mid = (start+end)/2;

    cout << "   Mid: " << mid << ", d: " << depth << endl;

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


std::vector<int> WBBST::inorder(Node* n, int e)
{

    // Initialize vector to store sorted array
    std::vector<int> v (n->size); // 
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

        // Check if should insert e first
        if(e < cur->value){
            v[i++] = e;
        }

        // Insert cur-> val
        v[i++] = cur->value;

        // Now check the right tree
        cur = cur->right;
    }
    // Check if e wasn't inserted
    if(i < n->size){
        if(e > v[i-1])
            v[i] = e;
        // If e wasn't inserted, but not the largest, then it was a duplicate
        else{
            v.pop_back(); // Pop off last unused element
        }
    }

    return v;
}

void WBBST::undoSizing(Node* cur){
    while(cur != NULL){
        cur->size --;
        cur = cur->parent;
    }
}


/**
 * @brief      Print tree with layers
 */
std::ostream& WBBST::print(std::ostream& out) const
{
    if(empty())
        return out;

    Node* cur;
    // Node* cur = root_;
    queue<Node*> q;
    q.push(root_);
    int depth = 0;
    out << " " << depth << ": ";

    while(!q.empty()){
        cur = q.front();
        q.pop();
        if(cur == NULL){
            continue;
        }
        // If new depth
        if(cur->depth != depth){
            depth = cur->depth;
            out << endl << " " << depth << ": ";
        }
        out << cur->value << ", ";

        // Push children
        q.push(cur->left);
        q.push(cur->right);
    }
    out << endl;

    return out;
}



std::ostream& WBBST::printPreOrder(std::ostream& out) const
{
    return printPreOrder(out, root_);
}

std::ostream& WBBST::printInOrder(std::ostream& out) const
{
    return printInOrder(out, root_);
}

std::ostream& WBBST::printPreOrder(std::ostream& out, const Node* n) const
{
    if(n == NULL){
        return out;
    }
    out << n->value << ",";

    printPreOrder(out, n->left);
    printPreOrder(out, n->right);

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
