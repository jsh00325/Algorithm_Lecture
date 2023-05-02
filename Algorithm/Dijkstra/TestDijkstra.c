#include "MyDijkstra.h"

int main() {
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
    Vertex* I = create_vertex( 'I' );

    /*  �׷����� ������ �߰� */
    add_vertex( graph, A );
    add_vertex( graph, B );
    add_vertex( graph, C );
    add_vertex( graph, D );
    add_vertex( graph, E );
    add_vertex( graph, F );
    add_vertex( graph, G );
    add_vertex( graph, H );
    add_vertex( graph, I );

    /*  ������ ������ �������� �ձ� */
    
    add_edge( A, create_edge(A, E, 247) );

    add_edge( B, create_edge(B, A, 35  ) );
    add_edge( B, create_edge(B, C, 126 ) );
    add_edge( B, create_edge(B, F, 150 ) );
    
    add_edge( C, create_edge(C, D, 117 ) );
    add_edge( C, create_edge(C, F, 162 ) );
    add_edge( C, create_edge(C, G, 220 ) );
    
    add_edge( E, create_edge(E, H, 98 ) );

    add_edge( F, create_edge(F, E, 82  ) );
    add_edge( F, create_edge(F, G, 154 ) );
    add_edge( F, create_edge(F, H, 120 ) );

    add_edge( G, create_edge(G, I, 106 ) );

    /*  ���� B�� ���� �������� �ϴ� ���� */
    
    Graph* Dijk = create_graph();
    int* dist = Dijkstra(graph, B, Dijk);

    Vertex* cur = Dijk->vertex_list;
    for (int i = 0; i < Dijk->vertex_cnt; i++) {
        printf("%c[%d]  ", cur->data, dist[i]);
        cur = cur->nxt_vertex;
    } printf("\n\n");

    print_graph( Dijk );
    
    /*  �׷��� �Ҹ� */
    destroy_graph( Dijk );
    destroy_graph( graph );
    printf("program is end!\n");
    return 0;
}