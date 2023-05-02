#include "MyExpressionTree.h"

/* 노드 생성 */
ETNode* ET_CreateNode(ElementType val) {
    ETNode* newNode = (ETNode*) malloc(sizeof(ETNode));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
/* 노드 소멸 */
void ET_DestroyNode(ETNode* node) {
    free(node);
}
/* 이진 트리 구조 소멸 */
void ET_DestroyTree(ETNode* root) {
    if (root == NULL) return;
    ET_DestroyTree(root->left);
    ET_DestroyTree(root->right);
    ET_DestroyNode(root);
}

/* 트리의 전위 순회 */
void ET_PreorderPrintTree(ETNode* node) {
    if (node == NULL) return;
    printf("%c ", node->data);
    ET_PreorderPrintTree(node->left);
    ET_PreorderPrintTree(node->right);
}
/* 트리의 중위 순회 */
void ET_InorderPrintTree(ETNode* node) {
    if (node == NULL) return;
    if (node->left != NULL) printf("( ");
    ET_InorderPrintTree(node->left);
    printf("%c ", node->data);
    ET_InorderPrintTree(node->right);
    if (node->right != NULL) printf(") ");
}
/* 트리의 후위 순회 */
void ET_PostorderPrintTree(ETNode* node) {
    if (node == NULL) return;
    ET_PostorderPrintTree(node->left);
    ET_PostorderPrintTree(node->right);
    printf("%c ", node->data);
}

/* 후위 표기된 식을 기반으로 수식 트리 구성 */
void ET_BuildExpressionTree(char* postfix, ETNode** node) {
    int len = strlen(postfix);
    char curToken = postfix[len-1];
    postfix[len-1] = '\0';
    (*node) = ET_CreateNode(curToken);

    if ('0' <= curToken && curToken <= '9') return;
    ET_BuildExpressionTree(postfix, &((*node)->right));
    ET_BuildExpressionTree(postfix, &((*node)->left));
}

/* 수식트리의 값을 계산 */
double ET_Evaluate(ETNode* tree) {
    if ('0' <= tree->data && tree->data <= '9')
        return (double)(tree->data - '0');
    
    double l = ET_Evaluate(tree->left);
    double r = ET_Evaluate(tree->right);

    switch(tree->data) {
        case '+' : return l + r;
        case '-' : return l - r;
        case '*' : return l * r;
        case '/' : return l / r;
    }
}