// CSCI2720
// Project 2
// Author: Justin Rector
// RBTree.h
// This class sets up a RB tree.

#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include "RBNode.h"

class RBTree {
    
public:
    RBTree();
    RBTree(RBNode *, RBNode *);
    RBNode * getSuccessor(RBNode *);
    void RBinsert(RBTree *, int);
    bool RBdelete(RBTree *, int);
    void RBinorder(RBTree *);
    void RBlevelorder(RBTree *);
    void leftRotate(RBNode *);
    void rightRotate(RBNode *);
    void RBinsertFixup(RBNode *);
    void RBtransplant(RBNode *, RBNode *);
    void RBdeleteFixup(RBNode *);
    
    
private:
    RBNode * root; //The root of the RBTree
    RBNode * tNIL; //tNIL node that all nodes without a left or right child point to. It is also the root's parent. 
};

#endif