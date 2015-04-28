// CSCI2720
// Project 2
// Author: Justin Rector
// RBNode.h
// This class sets up a RB tree node.

#ifndef RBNODE_H
#define RBNODE_H

#include <iostream>

class RBNode {
    
public:
    RBNode(int, RBNode *);
    void setParent(RBNode *);
    void setLeftChild(RBNode *);
    void setRightChild(RBNode *);
    void setColor(bool);
    int getKey() const;
    bool getColor() const;
    RBNode * getParent();
    RBNode * getLeftChild();
    RBNode * getRightChild();
    
private:
    int key; //The integer key attached to the node
    bool color; //The color of the node. True = Red. False = Black.
    RBNode * parent; //A pointer to the parent of the node
    RBNode * leftChild; //A pointer to the left child of the node
    RBNode * rightChild; //A pointer to the right child of the node
};

#endif
