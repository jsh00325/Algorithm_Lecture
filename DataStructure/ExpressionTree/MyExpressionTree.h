#ifndef MY_EXPRESSION_TREE_H
#define MY_EXPRESSION_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char ElementType;

typedef struct tagETNode {
    ElementType data;
    struct tagETNode* left;
    struct tagETNode* right;
} ETNode;

ETNode* ET_CreateNode(ElementType val);
void ET_DestroyNode(ETNode* node);
void ET_DestroyTree(ETNode* root);

void ET_PreorderPrintTree(ETNode* node);
void ET_InorderPrintTree(ETNode* node);
void ET_PostorderPrintTree(ETNode* node);

void ET_BuildExpressionTree(char* postfix, ETNode** node);
double ET_Evaluate(ETNode* tree);

#endif