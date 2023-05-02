#ifndef MY_RBT_H
#define MY_RBT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElementType;

typedef struct tagRBTNode {
    struct tagRBTNode* parent;
    struct tagRBTNode* left;
    struct tagRBTNode* right;
    ElementType data;
    enum{RED, BLACK} color;
} RBTNode;

RBTNode* RBT_CreateNode(ElementType new_data);
void     RBT_DestroyNode(RBTNode* mode);
void     RBT_DestroyTree( RBTNode* tree );

RBTNode* RBT_SearchNode(RBTNode* tree, ElementType target);
RBTNode* RBT_SearchMaxNode(RBTNode* tree);

void RBT_RotateCW(RBTNode** root, RBTNode* pNode);
void RBT_RotateCCW(RBTNode** root, RBTNode* pNode);

bool RBT_InsertNode(RBTNode** tree, RBTNode* new_node);
bool _RBT_FindAndInsert(RBTNode** tree, RBTNode* new_node);
void _RBT_RebuildAfterInsert(RBTNode** root, RBTNode* cur);

RBTNode* RBT_RemoveNode(RBTNode** root, ElementType target_data);
void _RBT_RebuildAfterRemove(RBTNode** root, RBTNode* cur);

void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount);

#endif