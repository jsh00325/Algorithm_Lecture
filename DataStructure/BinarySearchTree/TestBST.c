#include "BinarySearchTree.h"

int main() {
    BSTNode* tree = NULL;
    BST_InsertNode(&tree, BST_CreateNode(4));
    BST_InsertNode(&tree, BST_CreateNode(2));
    BST_InsertNode(&tree, BST_CreateNode(6));
    BST_InsertNode(&tree, BST_CreateNode(1));
    BST_InsertNode(&tree, BST_CreateNode(3));
    BST_InsertNode(&tree, BST_CreateNode(5));
    BST_InsertNode(&tree, BST_CreateNode(7));
    BST_PrintNode(tree, 0);

    while (1) {
        ElementType target;
        printf("������ �� : ");
        scanf("%d", &target);

        BSTNode* delNode = BST_RemoveNode(NULL, tree, target);
        if (delNode == NULL) printf("%d�� �������� ���߽��ϴ�.\n\n", target);
        else {
            printf("%d�� �����߽��ϴ�.\n\n", target);
            BST_PrintNode(tree, 0); printf("\n\n");
        }
    }    
}