#include "my_tree.h"

int main() {
    LCRSNode* nodes[9];
    for (int i = 0; i < 9; i++)
        nodes[i] = LCRS_CreateNode('A'+i);
        
    int edges[8][2] = {{0,1},{0,2},{0,3},{0,4},{1,5},{3,6},{3,7},{5,8}};

    for (int i = 0; i < 8; i++)
        LCRS_AddChildNode(nodes[edges[i][0]], nodes[edges[i][1]]);
    
    LCRSNode* root = nodes[0];
    LCRS_PrintTree(root, 0);
    LCRS_DestroyTree(root);
    printf("test is done.");
}