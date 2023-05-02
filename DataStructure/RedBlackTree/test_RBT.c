#include "my_RBT.h"

RBTNode* NIL;
int main(void) {
    NIL = RBT_CreateNode(0);
    NIL->color = BLACK;   

    RBTNode* Tree = NULL;
    RBTNode* Node = NULL;
    
    while ( true ) {
        int  cmd   = 0;
        int  param = 0;
        char buffer[10];

        printf("Enter command number :\n");
        printf("(1) Create a node, (2) Remove a node, (3) Search a Node\n");
        printf("(4) Display Tree (5) quit\n");
        printf("command number:");

        fgets(buffer, sizeof(buffer)-1, stdin);
        sscanf(buffer, "%d", &cmd );

        if ( cmd < 1 || cmd > 5 ) {
            printf("Invalid command number.\n");
            continue;
        }
        else if ( cmd == 4 ) {
            RBT_PrintTree(Tree, 0, 0);
            printf("\n");
            continue;
        }
        else if ( cmd == 5 ) break;

        printf("Enter parameter (1~200) : ");

        fgets(buffer, sizeof(buffer)-1, stdin);
        sscanf(buffer, "%d", &param );

        if ( param < 1 || param > 200 ) {
            printf("Invalid parameter.%d\n", param);
            continue;
        }

        switch ( cmd ) {
        case 1:
            RBT_InsertNode( &Tree, RBT_CreateNode(param) );            
            break;
        case 2:
            Node = RBT_RemoveNode( &Tree, param);
                
            if ( Node == NULL ) 
                printf("Not found node to delete:%d\n", param);
            else
                RBT_DestroyNode( Node );
            break;

        case 3:
            Node = RBT_SearchNode(Tree, param);
                
            if ( Node == NULL ) 
                printf("Not found node:%d\n", param);            
            else
                printf("Found Node: %d(Color:%s)\n", 
                        Node->data, (Node->color == RED) ? "RED" : "BLACK");            
            break;
        }
        printf("\n");
    }

    RBT_DestroyTree( Tree );
    return 0;
}