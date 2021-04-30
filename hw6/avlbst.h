#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO

protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft(AVLNode<Key,Value>* node);
    void rotateRight(AVLNode<Key,Value>* node);
    bool isLeftChild(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p);
    bool isRightChild(AVLNode<Key,Value>* n, AVLNode<Key,Value>*p);
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void removeFix(AVLNode<Key,Value>* n);
    void fixHeight(AVLNode<Key,Value>* n);
};


template<class Key, class Value>
bool AVLTree<Key, Value>::isRightChild(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p)
{
    return (p->getRight() == n);
}

template<class Key, class Value>
bool AVLTree<Key, Value>::isLeftChild(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p)
{
    return (p->getLeft() == n);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* node)
{
    AVLNode<Key,Value>* parent = node->getParent();
    AVLNode<Key,Value>* child = node->getRight();
    // current node is the root
    if (node == this->root_){
        AVLNode<Key,Value>* temp = child->getLeft();
        child->setLeft(node);
        child->setParent(NULL);
        node->setRight(temp);
        node->setParent(child);
        if (temp != NULL){
            temp->setParent(node);
        }
        this->root_ = child;
        return;
    }
    // current node is not the root
    if (isRightChild(node, parent)){ // node is the right child of its parent
        AVLNode<Key,Value>* temp = child->getLeft();
        parent->setRight(child);
        child->setLeft(node);
        child->setParent(parent);
        node->setRight(temp);
        node->setParent(child);
        if (temp != NULL){
            temp->setParent(node);
        }
    }
    else{ // node is the left child of its parent
        AVLNode<Key,Value>* temp = child->getLeft();
        parent->setLeft(child);
        child->setLeft(node);
        child->setParent(parent);
        node->setRight(temp);
        node->setParent(child);
        if (temp != NULL){
            temp->setParent(node);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* node)
{
    AVLNode<Key,Value>* parent = node->getParent(); 
    AVLNode<Key,Value>* child = node->getLeft();
    // current node is the root
    if (node == this->root_){
        AVLNode<Key,Value>* temp = child->getRight();
        child->setRight(node);
        child->setParent(NULL);
        node->setLeft(temp);
        node->setParent(child);
        if (temp != NULL){
            temp->setParent(node);
        }
        this->root_ = child;
        return;
    }
    // current node is not the root
    if (isLeftChild(node, parent)){ // node is the left child of its parent
        AVLNode<Key,Value>* temp = child->getRight();
        parent->setLeft(child);
        child->setRight(node);
        child->setParent(parent);
        node->setLeft(temp);
        node->setParent(child);
        if (temp != NULL){
            temp->setParent(node);
        }
    }
    else{ // node is the right child of its parent
        AVLNode<Key,Value>* temp = child->getRight();
        parent->setRight(child);
        child->setRight(node);
        child->setParent(parent);
        node->setLeft(temp);
        node->setParent(child);
        if (temp != NULL){
            temp->setParent(node);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::fixHeight(AVLNode<Key,Value>* n)
{
    if (!n){ // current node is NULL
        return;
    }
    int left = 0;
    int right = 0;
    if (n->getLeft() != NULL){
        left = (n->getLeft())->getHeight();
    }
    if (n->getRight() != NULL){
        right = (n->getRight())->getHeight();
    }
    int h = std::max(left, right) + 1;
    if (h == n->getHeight()){ // height does not change
        return;
    }
    n->setHeight(h);
}

// insert-fix
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n)
{
    if (!p || !(p->getParent())){ // check if the node is NULL and if parent exists
        return;
    }
    AVLNode<Key,Value>* g = p->getParent();
    int left = 0; 
    int right = 0;
    if (g->getLeft()!= NULL){
        left = (g->getLeft())->getHeight();
    }
    if (g->getRight()!= NULL){
        right = (g->getRight())->getHeight();
    }
    int new_gh = std::max(left, right) + 1;
    int diff = left - right;
    // g height doesn't change, done!
    if (g->getHeight()==new_gh){
        return;
    }
    // g is balanced, call next insertFix
    else if (diff <= 1 && diff >= -1){
        g->setHeight(new_gh);
        insertFix(g, p);
    }
    // g is unbalanced, do rotations
    else {
        g->setHeight(new_gh);
        if (diff > 1 && (n->getKey() < p->getKey())){ // zig-zig (rightRotate)
            rotateRight(g);
            fixHeight(p);
            fixHeight(g);
        }
        else if (diff > 1 && (n->getKey() > p->getKey())){ // zig-zag (leftRotate then rightRotate)
            rotateLeft(p);
            rotateRight(g);
            fixHeight(n);
            fixHeight(p);
            fixHeight(g);
        }
        else if (diff < -1 && (n->getKey() > p->getKey())){ // zig-zig (leftRotate)
            rotateLeft(g);
            fixHeight(p);
            fixHeight(g); 
        }
        else if (diff < -1 && (n->getKey() < p->getKey())){ // zig-zag (rightRotate then leftRotate)
            rotateRight(p);
            rotateLeft(g);
            fixHeight(n);
            fixHeight(p);
            fixHeight(g); 
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // BST Insert
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);
    if (!(this->root_)){ // root is NULL
        AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        this->root_ = newNode;
        return;
    }
    while (current != NULL)
    {
        if (new_item.first > current->getKey()){
            if (current->getRight() == NULL){
                AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
                current->setRight(newNode);
                current = current->getRight();
                break;
            }
            current = current->getRight();
        }
        else if (new_item.first < current->getKey()){
            if (current->getLeft() == NULL){
                AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
                current->setLeft(newNode);
                current = current->getLeft();
                break;
            }
            current = current->getLeft();
        }
        else{
            current->setValue(new_item.second);
            break;
        }
    }
    // Adjust height and balance of the tree
    AVLNode<Key, Value>* parent = current->getParent();
    if(!parent){
        return;
    }
    if (parent->getHeight() == 2){
        return;
    }
    parent->setHeight(2);
    insertFix(parent, current);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n)
{
    if(!n){ // check if n is NULL
        return;
    }
    int left = 0;
    int right = 0;
    if (n->getLeft()!= NULL){
        left = (n->getLeft())->getHeight();
    }
    if (n->getRight()!= NULL){
        right = (n->getRight())->getHeight();
    }
    int h = std::max(left, right) + 1;
    int diff = left - right;
    if (diff>1 || diff < -1) { // current node is not balanced
        AVLNode<Key,Value>* c = NULL;
        AVLNode<Key,Value>* g = NULL;
        // find the n's child with largest height, and name it c
        if (left > right){
            c = n->getLeft();
        }
        else{
            c = n->getRight();
        }
        // find the height of c's child
        int c_left = 0;
        int c_right = 0;
        if (c->getLeft()!=NULL){
            c_left = (c->getLeft())->getHeight();
        }
        if (c->getRight()!=NULL){
            c_right = (c->getRight())->getHeight();
        }
        // find c's child with the largest height, and name it g. (if there is a tie, use zig-zig)
        if (c_left > c_right){
            g = c->getLeft();
        }
        else if (c_left < c_right){
            g = c->getRight();
        }
        else{
            if (isLeftChild(c, n)){
                g = c->getLeft();
            }
            else{
                g = c->getRight();
            }
        }
        // perform rotation
        if (diff > 1 && (g->getKey() < c->getKey())){ // zig-zig (rightRotate)
            rotateRight(n);
            fixHeight(n);
            fixHeight(c);
        }
        else if (diff > 1 && (g->getKey() > c->getKey())){ // zig-zag (leftRotate then rightRotate)
            rotateLeft(c);
            rotateRight(n);
            fixHeight(n);
            fixHeight(c);
            fixHeight(g);
        }
        else if (diff < -1 && (g->getKey() > c->getKey())){ // zig-zig (leftRotate)
            rotateLeft(n);
            fixHeight(n);
            fixHeight(c);
        }
        else if (diff < -1 && (g->getKey() < c->getKey())){ // zig-zag (rightRotate then leftRotate)
            rotateRight(c);
            rotateLeft(n);
            fixHeight(n);
            fixHeight(c);
            fixHeight(g);
        }
        removeFix(n->getParent());
    }
    else if (h == n->getHeight()){ // current node height remains the same
        return;
    }
    else { // current node is balanced
        n->setHeight(h);
        removeFix(n->getParent());
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    // BST Remove
    if (!this->root_){
        return;
    }
    AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    AVLNode<Key, Value>* parent = NULL;
    if (current != NULL){
        // current node has no children
        if ((current->getLeft()==NULL) && (current->getRight()==NULL)){
            parent = current->getParent();
            if (parent!=NULL){
                if(isLeftChild(current, parent)){
                    parent->setLeft(NULL);
                }
                else{
                    parent->setRight(NULL);
                }
            }
            else{
                this->root_ = NULL;
            }
            delete current;
            current = NULL;
        }
        // current node has one rightChild
        else if (current->getLeft()==NULL){
            parent = current->getParent();
            AVLNode<Key, Value>* rightChild = current->getRight();
            if (!parent){
                this->root_ = rightChild;
            }
            else{
                if (isLeftChild(current, parent)){
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
        // current node has one leftChild
        else if (current->getRight()==NULL){
            parent = current->getParent();
            AVLNode<Key, Value>* leftChild = current->getLeft();
            if (!parent){
                this->root_ = leftChild;
            }
            else{
                if (isLeftChild(current, parent)){
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
        // current node has both left and right children
        else{
            AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(current));
            nodeSwap(current, pred); // swap current node with its predecessor
            // current node has no children
            if ((current->getLeft()==NULL) && (current->getRight()==NULL)){
                if (current->getParent()!=NULL){
                    parent = current->getParent();
                    if(isLeftChild(current, parent)){
                        parent->setLeft(NULL);
                    }
                    else{
                        parent->setRight(NULL);
                    }
                }
                else{
                    this->root_ = NULL;
                }
                delete current;
                current = NULL;
            }
            // current node has one rightChild
            else if (current->getLeft()==NULL){
                parent = current->getParent();
                AVLNode<Key, Value>* rightChild = current->getRight();
                if (!parent){
                    this->root_ = rightChild;
                }
                else{
                    if (isLeftChild(current, parent)){
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
            // current node has one leftChild
            else if (current->getRight()==NULL){
                parent = current->getParent();
                AVLNode<Key, Value>* leftChild = current->getLeft();
                if (!parent){
                    this->root_ = leftChild;
                }
                else{
                    if (isLeftChild(current, parent)){
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
    // Adjust height and balance of the tree
    removeFix(parent);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


#endif
