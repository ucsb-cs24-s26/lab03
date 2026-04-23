// intbst.cpp
// Implements class IntBST
// YOUR NAME(S), DATE

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = NULL;

}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n) {
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (root == NULL) {
        root = new Node(value);
        return true;
    }
    if(value == root->info)
        return false;
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (value < n->info) {
        if (n->left)
            return insert(value, n->left);
        else {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
    }
    else if (value > n->info) {
        if (n->right)
            return insert(value, n->right);
        else {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
    }
    else
        return false; // duplicate value 
        }

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(!n)
        return;
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(!n)
        return;
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if(!n)
        return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);

}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if(!n)
        return 0;
    return n->info + sum(n->left) + sum(n->right);

}

// return count of values
int IntBST::count() const {
    return count(root);
     
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if(!n)
        return 0;
    return 1 + count(n->left) + count(n->right);
     
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (!n)
        return NULL;
    if (value == n->info)
        return n;
    if (value > n->info)
        return getNodeFor(value, n->right);
    return getNodeFor(value, n->left);
      
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if (getNodeFor(value, root) != NULL)
        return true; 
    return false;
     
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* n = getNodeFor(value, root);
    if (!n)
        return NULL;
    if (n->left != NULL){
        Node* p = n->left;
        while (p->right != NULL)
            p = p->right;
        return p;
    }
    Node* pred = NULL;
    Node* curr = root;

    while (curr != n){
        if (value > curr->info){
            pred = curr;
            curr = curr->right;
        }else{
            curr = curr->left;
        }
    }

    return pred;
     
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* n = getPredecessorNode(value);
    if (!n)
        return 0;

    return n->info; 
     
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* n = getNodeFor(value, root);
    if (!n)
        return NULL; 
    if (n->right != NULL){
        Node* s = n->right;
        while (s->left != NULL)
            s = s->left;
            return s;
    }
    Node* succ = NULL;
    Node* curr = root;

    while (curr != n){
        if (value < curr->info){
            succ = curr;
            curr = curr->left;
        }else{
            curr = curr ->right;
        }
    }
    return succ;
     
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* n = getSuccessorNode(value);
    if (!n)
        return 0;
    return n->info; 
     
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* n = getNodeFor(value, root);
    Node* parent = NULL;
    Node* curr = root;
    Node* s = getSuccessorNode(value);

    if (!n)
        return false; 

    // Delete recursion case (two children)
    if(n->left && n->right){
        n->info = s->info;
        return remove(s->info);  
    }

    // Get child
    Node* child = NULL;
    if (n->left)
        child = n->left;
    else if (n->right)
        child = n->right;

    // Find curr
    while(curr && curr != n){
        parent = curr;
        if (n->info < curr->info)
            curr = curr->left;
        else
            curr = curr->right;
    }

    // Reorganize bst
    if(!parent)
        root = child;
    else if (parent->left == n)
        parent->left = child;
    else
        parent->right = child;

    // Update child's parent pointer
    if (child)
        child->parent = parent;

    delete n;
    return true;
}
