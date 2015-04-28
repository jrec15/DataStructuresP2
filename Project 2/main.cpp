// CSCI2720
// Project 2
// Author: Justin Rector
// main.cpp
// This class was made to test RBTree and RBNode classes

#include <iostream>
#include "RBNode.h"
#include "RBTree.h"

using namespace std;

int main(int argc, const char * argv[])
{
    RBTree * testTree = new RBTree();
    testTree->RBinsert(testTree, 100);
    testTree->RBinsert(testTree, 10);
    testTree->RBinsert(testTree, 150);
    testTree->RBinsert(testTree, 30);
    testTree->RBinsert(testTree, 50);
    testTree->RBinsert(testTree, 40);
    testTree->RBinsert(testTree, 170);
    testTree->RBinsert(testTree, 110);
    testTree->RBinsert(testTree, 160);
    testTree->RBinsert(testTree, 90);
    testTree->RBinsert(testTree, 20);
    testTree->RBinsert(testTree, 165);
    cout << "PRINTING LEVEL ORDER" << endl;
    testTree->RBlevelorder(testTree);
    cout << "\nPRINTING INORDER" << endl;
    testTree->RBinorder(testTree);
    return 0;
}

