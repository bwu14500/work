#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <algorithm>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();
        
    protected:
        Node<Key, Value> *current_;
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    static std::pair<int, bool> checkBalance(Node<Key,Value>* current);
    static Node<Key, Value>* successor(Node<Key, Value>* current); 
    static bool balanceHelper (Node<Key,Value>* n); 
    void deleteTree(Node<Key, Value>* root);

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (this->current_ == rhs.current_);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return (this->current_ != rhs.current_);
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    Node<Key, Value>* succ = successor(current_);
    current_ = succ;
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    Node<Key, Value>* current = root_;
    if (!root_){ // root is NULL
        Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        root_ =  newNode;
    }
    while (current != NULL)
    {
        if (keyValuePair.first > current->getKey()){ // the node we try to insert has a larger key than the current node
            if (current->getRight() == NULL){
                Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
                current->setRight(newNode);
                break;
            }
            current = current->getRight();
        }
        else if (keyValuePair.first < current->getKey()){ // the node we try to insert has a smaller key than the current node
            if (current->getLeft() == NULL){
                Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, current);
                current->setLeft(newNode);
                break;
            }
            current = current->getLeft();
        }
        else{ // the node we try to insert has the same key as the current node, so just update the value
            current->setValue(keyValuePair.second);
            break;
        }
    }
}

/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    if (!root_){
        return;
    }
    bool left = false;
    Node<Key,Value>* current = internalFind(key);
    if (current != NULL){
        Node<Key,Value>*parent = NULL;
        if ((current->getLeft()==NULL) && (current->getRight()==NULL)){ // no children, just delete
            parent = current->getParent();
            if (parent!=NULL){
                if (parent->getLeft() == current){
                    left = true;
                }
                if(left){
                    parent->setLeft(NULL);
                }
                else{
                    parent->setRight(NULL);
                }
            }
            else{
                root_ = NULL;
            }
            delete current;
            current = NULL;
        }
        else if (current->getLeft()==NULL){ // have a right child, promote it to the current location
            parent = current->getParent();
            Node<Key,Value>* rightChild = current->getRight();
            if (!parent){
                root_ = rightChild;
            }
            else{
                if (parent->getLeft() == current){
                    left = true;
                }
                if (left){
                    parent->setLeft(rightChild);
                }
                else{
                    parent->setRight(rightChild);
                }       
            }
            rightChild->setParent(parent);
            delete current;
            current = NULL;
        }
        else if (current->getRight()==NULL){ // have a left child, promote to current location
            parent = current->getParent();
            Node<Key,Value>* leftChild = current->getLeft();
            if (!parent){
                root_ = leftChild;
            }
            else{
                if (parent->getLeft() == current){
                    left = true;
                }
                if (left){
                    parent->setLeft(leftChild);
                }
                else{
                    parent->setRight(leftChild);
                } 
            }
            leftChild->setParent(parent);
            delete current;
            current = NULL;
        }
        else{ // have both child, swap the current node with its predecessor
            Node<Key, Value>* pred = predecessor(current);
            nodeSwap(current, pred);
            if ((current->getLeft()==NULL) && (current->getRight()==NULL)){ // no child
                if (current->getParent()!=NULL){
                    parent = current->getParent();
                    if (parent->getLeft() == current){
                        left = true;
                    }
                    if(left){
                        parent->setLeft(NULL);
                    }
                    else{
                        parent->setRight(NULL);
                    }
                }
                else{
                    root_ = NULL;
                }
                delete current;
                current = NULL;
            }
            else if (current->getLeft()==NULL){ // have a right child
                parent = current->getParent();
                Node<Key,Value>* rightChild = current->getRight();
                if (!parent){
                    root_ = rightChild;
                }
                else{
                    if (parent->getLeft() == current){
                        left = true;
                    }
                    if (left){
                        parent->setLeft(rightChild);
                    }
                    else{
                        parent->setRight(rightChild);
                    }
                }
                rightChild->setParent(parent);
                delete current;
                current = NULL;
            }
            else if (current->getRight()==NULL){ // have a left child
                parent = current->getParent();
                Node<Key,Value>* leftChild = current->getLeft();
                if (!parent){
                    root_ = leftChild;
                }
                else{
                    if (parent->getLeft() == current){
                        left = true;
                    }
                    if (left){
                        parent->setLeft(leftChild);
                    }
                    else{
                        parent->setRight(leftChild);
                    }
                }
                leftChild->setParent(parent);
                delete current;
                current = NULL;
            }
        }
    }
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
    if (!current){
        return NULL;
    }
    Node<Key, Value>* successor = current;
    if (current->getRight()!=NULL){ // there is a right child
        successor = current->getRight();
        while((successor!= NULL) && (successor->getLeft() != NULL))
        {
            successor = successor->getLeft();
        }
    }
    else{ // there is no right child, go up the ancestral chain
        while (successor!=NULL){
            if ((successor->getParent()!= NULL) && ((successor->getParent())->getLeft() == successor)){
                successor = successor->getParent();
                break;
            }
            successor = successor->getParent();
        }
    }
    return successor;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if (!current){
        return NULL;
    }
    Node<Key, Value>* predecessor = current;
    if (predecessor->getLeft()!=NULL){ // there is a left child
        predecessor = current->getLeft();
        while((predecessor!= NULL) && (predecessor->getRight()!=NULL))
        {
            predecessor = predecessor->getRight();
        }
    }
    else{ // no left child, go up the ancestral chain
        while (predecessor!=NULL){
            if ((predecessor->getParent()!= NULL) && ((predecessor->getParent())->getRight() == predecessor)){
                predecessor = predecessor->getParent();
                break;
            }
            predecessor = predecessor->getParent();
        }
    }
    return predecessor;
}

// helper function for clear()
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::deleteTree(Node<Key, Value>* root)
{
    if (!root){
        return;
    }
    deleteTree(root->getRight());
    deleteTree(root->getLeft());
    delete root;
    root = NULL;
}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    deleteTree(root_);
    root_ = NULL;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    Node<Key, Value>* current = root_;
    if(!root_){
        return root_;
    }
    while(current->getLeft() != NULL){
        current = current->getLeft();
    }
    return current;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    if (!root_){
        return root_;
    }
    Node<Key,Value>* current = root_;
    while ((current != NULL) && (key != current->getKey())){
        if(key > current->getKey()){ // the node we try to find has larger key
            current = current->getRight();
        }
        else if (key < current->getKey()){ // the node we try to find has smaller key
            current = current->getLeft();
        }
    }
    return current;
}
/**
 * Private helper function for isBalance().
 */
template<typename Key, typename Value>
std::pair<int, bool> 
BinarySearchTree<Key, Value>::checkBalance(Node<Key,Value>* current)
{
    if (!current){ // NULL pointer, balanced
        return std::pair<int, bool>(0,true);
    }
    if ((current->getRight()==NULL) && (current->getLeft()==NULL)){ // no child, height is 1, balanced
        return std::pair<int, bool>(1,true);
    }
    int h = std::max(checkBalance(current->getLeft()).first,checkBalance(current->getRight()).first) + 1;
    int diff = checkBalance(current->getLeft()).first - checkBalance(current->getRight()).first;
    bool foo = false;
    if (diff <=1 && diff >= -1){ // the height difference of two subtree is less than or equal to 1, balanced
        foo = true;
    } 
    return std::pair<int,bool>(h,foo);
}
/**
  * help iterating through the whole map
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balanceHelper(Node<Key,Value>* n) 
{
    if (!n){
        return true;
    }
    if (n->getLeft()==NULL && n->getRight()==NULL){
        return (checkBalance(n).second);
    }
    else if (n->getLeft()!= NULL && n->getRight()!= NULL){
        return (checkBalance(n).second) && (balanceHelper(n->getLeft())) && (balanceHelper(n->getRight())); 
    }
    else if (n->getRight() != NULL){
        return (checkBalance(n).second) && (balanceHelper(n->getRight()));
    }
    else{
        return (checkBalance(n).second) && (balanceHelper(n->getLeft()));
    }
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    Node<Key, Value>* current = this->root_;
    return balanceHelper(current);
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
