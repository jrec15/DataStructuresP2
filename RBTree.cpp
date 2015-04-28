// CSCI2720
// Project 2
// Author: Justin Rector
// RBTree.cpp
// This class implements a red black tree with all apropriate methods

#include "RBNode.h"
#include "RBTree.h"
#include <string>
#include <queue>

using namespace std;

//An empty constructor. Creates tNIL and assigns the root to it for now.
RBTree::RBTree() {
    RBNode * newTNIL = new RBNode(NULL, nullptr);
    newTNIL->setColor(false);
    tNIL = newTNIL;
    root = tNIL;
}

//Creates a tree based on a RBNode. This is intended as making a subtree of an already established RBTree.
//tNIL is passed so the address doesn't get reassigned.
RBTree::RBTree(RBNode * newRoot, RBNode * newTNIL) {
    root = newRoot;
    tNIL = newTNIL;
}

//Returns the in order successor of a node
RBNode * RBTree::getSuccessor(RBNode * currentNode) {
    currentNode = currentNode->getRightChild();
    while (currentNode->getLeftChild() != tNIL) {
        currentNode = currentNode->getLeftChild();
    }
    return currentNode;
}

//Inserts a RBNode into a RBTree
void RBTree::RBinsert(RBTree * tree, int zKey) {
    RBNode * yPtr = tNIL;
    RBNode * xPtr = root;
    //traverse to find proper spot
    while (xPtr != tNIL) {
        yPtr = xPtr;
        if (zKey < xPtr->getKey())
            xPtr = xPtr->getLeftChild();
        else
            xPtr = xPtr->getRightChild();
    }
    //make new node and set parent
    RBNode * zPtr = new RBNode(zKey, yPtr);
    //special case, empty tree
    if (yPtr == tNIL)
        root = zPtr;
    else if (zKey < yPtr->getKey())
        yPtr->setLeftChild(zPtr);
    else
        yPtr->setRightChild(zPtr);
    zPtr->setLeftChild(tNIL);
    zPtr->setRightChild(tNIL);
    zPtr->setColor(true);
    RBinsertFixup(zPtr);
    
}

//Deletes a RBNode from a RBTree
bool RBTree::RBdelete(RBTree * tree, int zKey) {
    RBNode * zPtr = root;
    RBNode * xPtr;
    bool result = true;
    //traverse to match node with key
    while (zPtr->getKey() != zKey) {
        if (zKey < zPtr->getKey())
            zPtr = zPtr->getLeftChild();
        else
            zPtr = zPtr->getRightChild();
        if (zPtr == tNIL) {
            result = false;
            break;
        }
    }
    RBNode * yPtr = zPtr;
    bool yOrigColor = yPtr->getColor();
    if (zPtr->getLeftChild() == tNIL) {
        xPtr = zPtr->getRightChild();
        RBtransplant(zPtr, zPtr->getRightChild());
    }
    else if (zPtr->getRightChild() == tNIL) {
        xPtr = zPtr->getLeftChild();
        RBtransplant(zPtr, zPtr->getLeftChild());
    }
    else {
        yPtr = getSuccessor(zPtr);
        yOrigColor = yPtr->getColor();
        xPtr = yPtr->getRightChild();
        if (yPtr->getParent() == zPtr)
            xPtr->setParent(yPtr);
        else {
            RBtransplant(yPtr, yPtr->getRightChild());
            yPtr->setRightChild(zPtr->getRightChild());
            yPtr->getRightChild()->setParent(yPtr);
        }
        RBtransplant(zPtr, yPtr);
        yPtr->setLeftChild(zPtr->getLeftChild());
        yPtr->getLeftChild()->setParent(yPtr);
        yPtr->setColor(zPtr->getColor());
    }
    if (yOrigColor == false)
        RBdeleteFixup(xPtr);
    return result;
}

//Prints the nodes of a RBTree through an inorder traversal
void RBTree::RBinorder(RBTree * tree) {
    if (root != tNIL) {
        if (root->getLeftChild() != tNIL) {
            RBTree * newTree = new RBTree(root->getLeftChild(), tNIL);
            newTree->RBinorder(newTree);
        }
        cout << root->getKey() << "(";
        if (root->getColor() == true)
            cout << "R";
        else
            cout << "B";
        cout << ")" << endl;
        if (root->getRightChild() != tNIL) {
            RBTree * newTree = new RBTree(root->getRightChild(), tNIL);
            newTree->RBinorder(newTree);
        }
    }
    
}

//Prints the nodes of a RBTree through a level order traversal
void RBTree::RBlevelorder(RBTree * tree) {
    queue<RBNode *> nodeQueue;
    RBNode * currentNode = root;
    nodeQueue.push(currentNode);
    while (currentNode != tNIL) {
        if (currentNode->getLeftChild() != tNIL) {
            RBNode * tempNode = currentNode->getLeftChild();
            nodeQueue.push(tempNode);
        }
        if (currentNode->getRightChild() != tNIL) {
            RBNode * tempNode = currentNode->getRightChild();
            nodeQueue.push(tempNode);
        }
        cout << currentNode->getKey() << "(";
        if (currentNode->getColor() == true)
            cout << "R";
        else
            cout << "B";
        cout << ")" << endl;
        nodeQueue.pop();
        if (nodeQueue.empty() != true)
            currentNode = nodeQueue.front();
        else
            currentNode = tNIL;
    }

}

//Rotates a subtree to the left. Node passed is the root of the subtree
void RBTree::leftRotate(RBNode * xPtr) {
    RBNode * yPtr = xPtr->getRightChild();
    //Make x's right subtree y's left subtree
    xPtr->setRightChild(yPtr->getLeftChild());
    //fix parent of changed subtree if it exists
    if (yPtr->getLeftChild() != tNIL)
        yPtr->getLeftChild()->setParent(xPtr);
    //update parent of Y
    yPtr->setParent(xPtr->getParent());
    //special case of parent being tNIL
    if (xPtr->getParent() == tNIL)
        root = yPtr;
    //update for if X was left child
    else if (xPtr == xPtr->getParent()->getLeftChild())
        xPtr->getParent()->setLeftChild(yPtr);
    //update for if X was right child
    else
        xPtr->getParent()->setRightChild(yPtr);
    yPtr->setLeftChild(xPtr);
    xPtr->setParent(yPtr);
    
}

//Rotates a subtree to the right. Node passed is the root of the subtree
void RBTree::rightRotate(RBNode * yPtr) {
    RBNode * xPtr = yPtr->getLeftChild();
    //Make y's left subtree x's right subtree
    yPtr->setLeftChild(xPtr->getRightChild());
    //fix parent of changed subtree if it exists
    if (xPtr->getRightChild() != tNIL)
        xPtr->getRightChild()->setParent(yPtr);
    //update parent of X
    xPtr->setParent(yPtr->getParent());
    //special case of parent being tNIL
    if (yPtr->getParent() == tNIL)
        root = xPtr;
    //update for if Y was right child
    else if (yPtr == yPtr->getParent()->getRightChild())
        yPtr->getParent()->setRightChild(xPtr);
    //update for if Y was left child
    else
        yPtr->getParent()->setLeftChild(xPtr);
    xPtr->setRightChild(yPtr);
    yPtr->setParent(xPtr);
}

//Fixes a RBTree after an insert has been performed. This is necessary when there are two RB nodes adjacent to each other
void RBTree::RBinsertFixup(RBNode * zPtr) {
    while (zPtr->getParent()->getColor() == true) {
        if (zPtr->getParent() == zPtr->getParent()->getParent()->getLeftChild()) {
            RBNode * yPtr = zPtr->getParent()->getParent()->getRightChild();
            //Case 1
            if (yPtr->getColor() == true) {
                zPtr->getParent()->setColor(false);
                yPtr->setColor(false);
                zPtr->getParent()->getParent()->setColor(true);
                zPtr = zPtr->getParent()->getParent();
            }
            else {
                //Case 2
                if (zPtr == zPtr->getParent()->getRightChild()) {
                    zPtr = zPtr->getParent();
                    leftRotate(zPtr);
                }
                //Case 3
                zPtr->getParent()->setColor(false);
                zPtr->getParent()->getParent()->setColor(true);
                rightRotate(zPtr->getParent()->getParent());
            }
        }
        else {
            RBNode * yPtr = zPtr->getParent()->getParent()->getLeftChild();
            //Case 1
            if (yPtr->getColor() == true) {
                zPtr->getParent()->setColor(false);
                yPtr->setColor(false);
                zPtr->getParent()->getParent()->setColor(true);
                zPtr = zPtr->getParent()->getParent();
            }
            else {
                //Case 2
                if (zPtr == zPtr->getParent()->getLeftChild()) {
                    zPtr = zPtr->getParent();
                    rightRotate(zPtr);
                }
                //Case 3
                zPtr->getParent()->setColor(false);
                zPtr->getParent()->getParent()->setColor(true);
                leftRotate(zPtr->getParent()->getParent());
            }
        }
    }
    root->setColor(false);
}

//Transplants a leaf to a position in the RBTree.
void RBTree::RBtransplant(RBNode * uPtr, RBNode * vPtr) {
    //special case of parent being tNIL
    if (uPtr->getParent() == tNIL)
        root = vPtr;
    //u is a left child
    else if (uPtr == uPtr->getParent()->getLeftChild())
        uPtr->getParent()->setLeftChild(vPtr);
    //u is a right child
    else {
        uPtr->getParent()->setRightChild(vPtr);
    }
    //fixing parent
    vPtr->setParent(uPtr->getParent());
}

//Fixes up a RBTree after a delete has been performed. This accounts for any "doubly black" or "red-black" nodes in the three
void RBTree::RBdeleteFixup(RBNode * xPtr) {
    while ((xPtr != root)&&(xPtr->getColor() == false)) {
        if (xPtr == xPtr->getParent()->getLeftChild()) {
            //set sibling
            RBNode * wPtr = xPtr->getParent()->getRightChild();
            //Case 1
            if (wPtr->getColor() == true) {
                wPtr->setColor(false);
                xPtr->getParent()->setColor(true);
                leftRotate(xPtr->getParent());
                wPtr = xPtr->getParent()->getRightChild();
            }
            //Case 2
            if ((wPtr->getLeftChild()->getColor() == false)&&(wPtr->getRightChild()->getColor() == false)) {
                wPtr->setColor(true);
                xPtr = xPtr->getParent();
            }
            else {
                //Case 3
                if (wPtr->getRightChild()->getColor() == false) {
                    wPtr->getLeftChild()->setColor(false);
                    wPtr->setColor(true);
                    rightRotate(wPtr);
                    wPtr = xPtr->getParent()->getRightChild();
                }
                //Case 4
                wPtr->setColor(xPtr->getParent()->getColor());
                xPtr->getParent()->setColor(false);
                wPtr->getRightChild()->setColor(false);
                leftRotate(xPtr->getParent());
                xPtr = root;
            }
        }
        else {
            //set sibling
            RBNode * wPtr = xPtr->getParent()->getLeftChild();
            //Case 1
            if (wPtr->getColor() == true) {
                wPtr->setColor(false);
                xPtr->getParent()->setColor(true);
                rightRotate(xPtr->getParent());
                wPtr = xPtr->getParent()->getLeftChild();
            }
            //Case 2
            if ((wPtr->getRightChild()->getColor() == false)&&(wPtr->getLeftChild()->getColor() == false)) {
                wPtr->setColor(true);
                xPtr = xPtr->getParent();
            }
            else {
                //Case 3
                if (wPtr->getLeftChild()->getColor() == false) {
                    wPtr->getRightChild()->setColor(false);
                    wPtr->setColor(true);
                    leftRotate(wPtr);
                    wPtr = xPtr->getParent()->getLeftChild();
                }
                //Case 4
                wPtr->setColor(xPtr->getParent()->getColor());
                xPtr->getParent()->setColor(false);
                wPtr->getLeftChild()->setColor(false);
                rightRotate(xPtr->getParent());
                xPtr = root;
            }
        }
    }
}