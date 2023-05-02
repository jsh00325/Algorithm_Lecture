#ifndef MY_TREE_H
#define MY_TREE_H

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct tagLCRSNode {
    ElementType data;
    struct tagLCRSNode* child;
    struct tagLCRSNode* sibling;
} LCRSNode;

LCRSNode* LCRS_CreateNode(ElementType val);
void LCRS_DestroyNode(LCRSNode* node);
void LCRS_DestroyTree(LCRSNode* root);

void LCRS_AddChildNode(LCRSNode* parent, LCRSNode* child);
void LCRS_PrintTree(LCRSNode* node, int depth);

#endif