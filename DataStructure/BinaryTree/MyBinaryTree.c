#include "MyBinaryTree.h"

/* ��� ���� */
BTNode* BT_CreateNode(ElementType val) {
    BTNode* newNode = (BTNode*) malloc(sizeof(BTNode));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
/* ��� �Ҹ� */
void BT_DestroyNode(BTNode* node) {
    free(node);
}
/* ���� Ʈ�� ���� �Ҹ� */
void BT_DestroyTree(BTNode* root) {
    if (root == NULL) return;
    BT_DestroyTree(root->left);
    BT_DestroyTree(root->right);
    BT_DestroyNode(root);
}

/* Ʈ���� ���� ��ȸ */
void BT_PreorderPrintTree(BTNode* node) {
    if (node == NULL) return;
    printf("%c ", node->data);
    BT_PreorderPrintTree(node->left);
    BT_PreorderPrintTree(node->right);
}
/* Ʈ���� ���� ��ȸ */
void BT_InorderPrintTree(BTNode* node) {
    if (node == NULL) return;
    BT_InorderPrintTree(node->left);
    printf("%c ", node->data);
    BT_InorderPrintTree(node->right);
}
/* Ʈ���� ���� ��ȸ */
void BT_PostorderPrintTree(BTNode* node) {
    if (node == NULL) return;
    BT_PostorderPrintTree(node->left);
    BT_PostorderPrintTree(node->right);
    printf("%c ", node->data);
}