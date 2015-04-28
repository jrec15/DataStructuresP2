// CSCI2720
// Project 2
// Author: Justin Rector
// RBNode.cpp

#include "RBNode.h"
#include <string>

//Sets up a node with both its key and parent, left child and right child
//remain unknown at this time
RBNode::RBNode(int newKey, RBNode * newParent) {
    key = newKey;
    parent = newParent;
    leftChild = nullptr;
    rightChild = nullptr;
}

//Assigns a node a parent
void RBNode::setParent(RBNode * newParent) {
    parent = newParent;
}

//Assigns a node a left child
void RBNode::setLeftChild(RBNode * newLeftChild) {
    leftChild = newLeftChild;
}

//Assigns a node a right child
void RBNode::setRightChild(RBNode * newRightChild) {
    rightChild = newRightChild;
}

//Sets the node's color as a boolean. True = Red. False = Black.
void RBNode::setColor(bool newColor) {
    color = newColor;
}

//Returns the node's key
int RBNode::getKey() const {
    return key;
}

//Returns the node's color
bool RBNode::getColor() const {
    return color;
}

//Returns a pointer to the node's parent
RBNode * RBNode::getParent() {
    return parent;
}

//Returns a pointer to the node's left child
RBNode * RBNode::getLeftChild() {
    return leftChild;
}

//Returns a pointer to the node's right child
RBNode * RBNode::getRightChild() {
    return rightChild;
}
