#include "MyTopologicalSort.h"

int main( void )
{
    Node* SortedList  = NULL;
    Node* CurrentNode = NULL;

    /*  �׷��� ����     */
    Graph* graph = create_graph();
    
    /*  ���� ���� */
    
    Vertex* A = create_vertex( 'A' );
    Vertex* B = create_vertex( 'B' );
    Vertex* C = create_vertex( 'C' );
    Vertex* D = create_vertex( 'D' );
    Vertex* E = create_vertex( 'E' );
    Vertex* F = create_vertex( 'F' );
    Vertex* G = create_vertex( 'G' );
    Vertex* H = create_vertex( 'H' );
    
    /*  �׷����� ������ �߰� */
    add_vertex( graph, A );
    add_vertex( graph, B );
    add_vertex( graph, C );
    add_vertex( graph, D );
    add_vertex( graph, E );
    add_vertex( graph, F );
    add_vertex( graph, G );
    add_vertex( graph, H );

    /*  ������ ������ �������� �ձ� */
    add_edge( A, create_edge( A, C, 0 ) );
    add_edge( A, create_edge( A, D, 0 ) );

    add_edge( B, create_edge( B, C, 0 ) );
    add_edge( B, create_edge( B, E, 0 ) );

    add_edge( C, create_edge( C, F, 0 ) );
    
    add_edge( D, create_edge( D, F, 0 ) );
    add_edge( D, create_edge( D, G, 0 ) );

    add_edge( E, create_edge( E, G, 0 ) );

    add_edge( F, create_edge( F, H, 0 ) );
    
    add_edge( G, create_edge( G, H, 0 ) );

    /*  ���� ���� */
    TopologicalSort( graph, &SortedList );

 
    printf("Topological Sort Result : ");

    CurrentNode = SortedList;

    while ( CurrentNode != NULL )
    {
        printf("%C ", CurrentNode->Data );
        CurrentNode = CurrentNode->NextNode;
    }
    printf("\n");
    

    /*  �׷��� �Ҹ� */
    destroy_graph( graph );

    return 0;
}
