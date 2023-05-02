#include "my_tree.h"

/** 노드 생성
 *  @param val 만들하고자 하는 노드의 data
 *  @return 동적할당 받은 새로운 노드 */
LCRSNode* LCRS_CreateNode(ElementType val) {
    LCRSNode* newNode = (LCRSNode*)malloc(sizeof(LCRSNode));
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->data = val;
    return newNode;
}

/** 노드 소멸
 *  @param node 소멸하고자 하는 노드 */
void LCRS_DestroyNode(LCRSNode* node) {
    free(node);
}

/** 재귀를 이용하여 트리를 소멸함
 *  @param root 소멸하고자 하는 서브트리의 루트 */
void LCRS_DestroyTree(LCRSNode* root) {
    if (root->child != NULL)
        LCRS_DestroyTree(root->child);
    if (root->sibling != NULL)
        LCRS_DestroyTree(root->sibling);
    free(root);
}

/** 부모 노드에 새로운 자식을 추가하는 함수
 *  @param parent 새로운 자식을 추가할 부모 노드
 *  @param child 새롭게 추가될 자식 노드 */
void LCRS_AddChildNode(LCRSNode* parent, LCRSNode* child) {
    if (parent->child == NULL)
        parent->child = child;
    else {
        LCRSNode* cur = parent->child;
        while(cur->sibling != NULL) cur = cur->sibling;
        cur->sibling = child;
    }
}

/** 트리 구조를 들여쓰기 방식으로 출력 
 *  @param node 현재 값을 출력할 노드
 *  @param depth 현재 노드의 깊이 (=들여쓰기 해야 하는 값) */
void LCRS_PrintTree(LCRSNode* node, int depth) {
    for (int i = 0; i < depth; i++) printf("-");
    printf("%c\n", node->data);
    if (node->child != NULL)
        LCRS_PrintTree(node->child, depth + 1);
    if (node->sibling != NULL)
        LCRS_PrintTree(node->sibling, depth);
}