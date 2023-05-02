#include "MyExpressionTree.h"

int main() {
    ETNode* tree = NULL;
    char postfix[100];

    printf("input postfix : ");
    scanf("%s", postfix);

    ET_BuildExpressionTree(postfix, &tree);
    
    printf("Inorder Print...\n");
    ET_InorderPrintTree(tree);
    printf("\n\n");

    printf("result : %.3f", ET_Evaluate(tree));
    ET_DestroyTree(tree);
}