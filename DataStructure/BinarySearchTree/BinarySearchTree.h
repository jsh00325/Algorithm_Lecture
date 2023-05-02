#ifndef MY_BINARY_SEARCH_TREE_H
#define MY_BINARY_SEARCH_TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagBSTNode {
    ElementType data;
    struct tagBSTNode* left;
    struct tagBSTNode* right;
} BSTNode;

BSTNode* BST_CreateNode(ElementType val);
BSTNode* BST_SearchNode(BSTNode* root, ElementType target);
void BST_InsertNode(BSTNode** tree, BSTNode* child);
BSTNode* BST_SearchMaxNode(BSTNode* root);
BSTNode* BST_RemoveNode(BSTNode* parent, BSTNode* tree, ElementType target);
void BST_PrintNode(BSTNode* root, int depth);

#endif