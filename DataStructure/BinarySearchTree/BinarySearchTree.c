#include "BinarySearchTree.h"

BSTNode* BST_CreateNode(ElementType val) {
    BSTNode* newNode = (BSTNode*) malloc(sizeof(BSTNode));
    newNode->data = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BSTNode* BST_SearchNode(BSTNode* root, ElementType target) {
    if (root == NULL) return NULL;
    if (root->data == target) return root;
    if (root->data > target) return BST_SearchNode(root->left, target);
    else return BST_SearchNode(root->right, target);
}

void BST_InsertNode(BSTNode** tree, BSTNode* child) {
    if ((*tree) == NULL) {
        (*tree) = child;
        return;
    }

    if ((*tree)->data > child->data) 
        return BST_InsertNode(&((*tree)->left), child);
    if ((*tree)->data < child->data)
        return BST_InsertNode(&((*tree)->right), child);
}

BSTNode* BST_SearchMaxNode(BSTNode* root) {
    if (root->right == NULL) return root;
    else return BST_SearchMaxNode(root->right);
}

BSTNode* BST_RemoveNode(BSTNode* parent, BSTNode* tree, ElementType target) {
    if (tree == NULL) return NULL;
    if (tree->data > target) return BST_RemoveNode(tree, tree->left, target);
    if (tree->data < target) return BST_RemoveNode(tree, tree->right, target);

    if (tree->left == NULL && tree->right == NULL) {
        if (parent == NULL) return tree;
        if (parent->left == tree) parent->left = NULL;
        else parent->right = NULL;
    }   
    else if (tree->left != NULL && tree->right != NULL) {
        BSTNode* maxNode = BST_SearchMaxNode(tree->left);
        maxNode = BST_RemoveNode(tree, tree->left, maxNode->data);
        tree->data = maxNode->data;
    } 
    else {
        BSTNode* nxtNode;
        if (tree->left != NULL) nxtNode = tree->left;
        else nxtNode = tree->right;

        if (parent == NULL) return tree;
        if (parent->left == tree) parent->left = nxtNode;
        else parent->right = nxtNode;
    }
    return tree;
}

void BST_PrintNode(BSTNode* root, int depth) {
    if (root == NULL) return;
    for (int i = 0; i < depth; i++) printf("--");
    printf("%d\n", root->data);
    BST_PrintNode(root->left, depth+1);
    BST_PrintNode(root->right, depth+1);
}