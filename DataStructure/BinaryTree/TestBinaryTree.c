#include "MyBinaryTree.h"

int main() {
    BTNode* A = BT_CreateNode('A');
    BTNode* B = BT_CreateNode('B');
    BTNode* C = BT_CreateNode('C');
    BTNode* D = BT_CreateNode('D');
    BTNode* E = BT_CreateNode('E');
    BTNode* F = BT_CreateNode('F');
    BTNode* G = BT_CreateNode('G');
    
    /*  Ʈ���� ��� �߰� */
    A->left  = B;
    B->left  = C;
    B->right = D;

    A->right = E;
    E->left  = F;
    E->right = G;
    
    /*  Ʈ�� ��� */
    printf("Preorder ...\n");
    BT_PreorderPrintTree( A );
    printf("\n\n");

    printf("Inorder ... \n");
    BT_InorderPrintTree( A );
    printf("\n\n");

    printf("Postorder ... \n");
    BT_PostorderPrintTree( A );
    printf("\n");

    /*  Ʈ�� �Ҹ��Ű�� */
    BT_DestroyTree( A );
}