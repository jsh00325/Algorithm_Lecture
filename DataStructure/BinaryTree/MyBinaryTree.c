#include "MyBinaryTree.h"

/* 노드 생성 */
BTNode* BT_CreateNode(ElementType val) {
    BTNode* newNode = (BTNode*) malloc(sizeof(BTNode));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
/* 노드 소멸 */
void BT_DestroyNode(BTNode* node) {
    free(node);
}
/* 이진 트리 구조 소멸 */
void BT_DestroyTree(BTNode* root) {
    if (root == NULL) return;
    BT_DestroyTree(root->left);
    BT_DestroyTree(root->right);
    BT_DestroyNode(root);
}

/* 트리의 전위 순회 */
void BT_PreorderPrintTree(BTNode* node) {
    if (node == NULL) return;
    printf("%c ", node->data);
    BT_PreorderPrintTree(node->left);
    BT_PreorderPrintTree(node->right);
}
/* 트리의 중위 순회 */
void BT_InorderPrintTree(BTNode* node) {
    if (node == NULL) return;
    BT_InorderPrintTree(node->left);
    printf("%c ", node->data);
    BT_InorderPrintTree(node->right);
}
/* 트리의 후위 순회 */
void BT_PostorderPrintTree(BTNode* node) {
    if (node == NULL) return;
    BT_PostorderPrintTree(node->left);
    BT_PostorderPrintTree(node->right);
    printf("%c ", node->data);
}