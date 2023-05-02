#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char* KeyType;
typedef char* ValueType;

typedef struct tagRBTNode {
    struct tagRBTNode* parent;
    struct tagRBTNode* left;
    struct tagRBTNode* right;
    KeyType key;
    ValueType value;
    enum{RED, BLACK} color;
} RBTNode;

RBTNode* RBT_CreateNode(KeyType key, ValueType value);
void     RBT_DestroyNode(RBTNode* mode);
void     RBT_DestroyTree(RBTNode* tree);

RBTNode* RBT_SearchNode(RBTNode* tree, KeyType target);
RBTNode* RBT_SearchMaxNode(RBTNode* tree);

void RBT_RotateCW(RBTNode** root, RBTNode* pNode);
void RBT_RotateCCW(RBTNode** root, RBTNode* pNode);

bool RBT_InsertNode(RBTNode** tree, RBTNode* new_node);
bool _RBT_FindAndInsert(RBTNode** tree, RBTNode* new_node);
void _RBT_RebuildAfterInsert(RBTNode** root, RBTNode* cur);

RBTNode* RBT_RemoveNode(RBTNode** root, KeyType target_data);
void _RBT_RebuildAfterRemove(RBTNode** root, RBTNode* cur);

void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount);

#endif