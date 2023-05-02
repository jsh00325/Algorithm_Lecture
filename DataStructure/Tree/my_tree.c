#include "my_tree.h"

/** ��� ����
 *  @param val �����ϰ��� �ϴ� ����� data
 *  @return �����Ҵ� ���� ���ο� ��� */
LCRSNode* LCRS_CreateNode(ElementType val) {
    LCRSNode* newNode = (LCRSNode*)malloc(sizeof(LCRSNode));
    newNode->child = NULL;
    newNode->sibling = NULL;
    newNode->data = val;
    return newNode;
}

/** ��� �Ҹ�
 *  @param node �Ҹ��ϰ��� �ϴ� ��� */
void LCRS_DestroyNode(LCRSNode* node) {
    free(node);
}

/** ��͸� �̿��Ͽ� Ʈ���� �Ҹ���
 *  @param root �Ҹ��ϰ��� �ϴ� ����Ʈ���� ��Ʈ */
void LCRS_DestroyTree(LCRSNode* root) {
    if (root->child != NULL)
        LCRS_DestroyTree(root->child);
    if (root->sibling != NULL)
        LCRS_DestroyTree(root->sibling);
    free(root);
}

/** �θ� ��忡 ���ο� �ڽ��� �߰��ϴ� �Լ�
 *  @param parent ���ο� �ڽ��� �߰��� �θ� ���
 *  @param child ���Ӱ� �߰��� �ڽ� ��� */
void LCRS_AddChildNode(LCRSNode* parent, LCRSNode* child) {
    if (parent->child == NULL)
        parent->child = child;
    else {
        LCRSNode* cur = parent->child;
        while(cur->sibling != NULL) cur = cur->sibling;
        cur->sibling = child;
    }
}

/** Ʈ�� ������ �鿩���� ������� ��� 
 *  @param node ���� ���� ����� ���
 *  @param depth ���� ����� ���� (=�鿩���� �ؾ� �ϴ� ��) */
void LCRS_PrintTree(LCRSNode* node, int depth) {
    for (int i = 0; i < depth; i++) printf("-");
    printf("%c\n", node->data);
    if (node->child != NULL)
        LCRS_PrintTree(node->child, depth + 1);
    if (node->sibling != NULL)
        LCRS_PrintTree(node->sibling, depth);
}