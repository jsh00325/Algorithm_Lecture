#ifndef MYBINARYTREE_H
#define MYBINARYTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct tagBTNode {
    ElementType data;
    struct tagBTNode* left;
    struct tagBTNode* right;
} BTNode;

BTNode* BT_CreateNode(ElementType val);
void BT_DestroyNode(BTNode* node);
void BT_DestroyTree(BTNode* root);

void BT_PreorderPrintTree(BTNode* node);
void BT_InorderPrintTree(BTNode* node);
void BT_PostorderPrintTree(BTNode* node);

#endif