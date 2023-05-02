#include "Graph.h"

/* ���ο� �׷��� ���� ���� */
Graph* CreateGraph() {
    Graph* graph = (Graph*)malloc( sizeof( Graph ) );
    graph->Vertices = NULL;
    graph->VertexCount = 0;

    return graph;
}
/* �׷��� ���� �Ҹ� */
void DestroyGraph( Graph* G ) {
    while ( G->Vertices != NULL ) {
        // �׳� �ٷ� free(G)�� �ϸ� ���� �����̳� ������ ������ �� ����, 
        // ���� �� ���� ������, ���������� �����ϸ鼭 ������� ����
        Vertex* VertexHead = G->Vertices->Next;        
        DestroyVertex( G->Vertices );
        G->Vertices = VertexHead;        
    }
    free(G);
}

/* ���ο� ���� ���� ���� */
Vertex* CreateVertex( ElementType Data ) {
    Vertex* V = (Vertex*)malloc( sizeof(Vertex) );
    
    V->Data = Data;
    V->Next = NULL;
    V->AdjacencyList = NULL;
    V->Visited = NotVisited;
    V->Index = -1;  // ���߿� graph�� add�� �� index �ο�

    return V;
}
/* ���� ���� �Ҹ� */
void DestroyVertex( Vertex* V ) {
    while ( V->AdjacencyList != NULL ) {
        Edge* Edge = V->AdjacencyList->Next;
        DestroyEdge ( V->AdjacencyList );
        V->AdjacencyList = Edge;
    }
    free( V );
}

/* ���ο� ���� ���� ���� */
Edge* CreateEdge( Vertex* From, Vertex* Target, int Weight ) {
    Edge* E   = (Edge*)malloc( sizeof( Edge ) );
    E->From   = From;
    E->Target = Target;
    E->Next   = NULL;
    E->Weight = Weight;

    return E;
}
/* ���� ���� �Ҹ� */
void DestroyEdge( Edge* E ) {
    free( E );
}

/* graph�� ������ ����(���ܿ�) */
void AddVertex( Graph* G, Vertex* V ) {
    Vertex* VertexList = G->Vertices;

    // graph�� ������ �������� ���� ��
    if ( VertexList == NULL ) {
        G->Vertices = V;
    } 
    else {
        // G->Vertices�� ���� ���ܿ� V ���� ����
        while ( VertexList->Next != NULL )
            VertexList = VertexList->Next;
        VertexList->Next = V;
    }

    // graph�� ������ ������ ���� �ε��� �ο�
    V->Index = G->VertexCount++;
}
/* graph�� ������ ����(���ܿ�) */
void AddEdge( Vertex* V, Edge* E ) {
    // V ������ ������ �������� ���� ��
    if ( V->AdjacencyList == NULL ) {
        V->AdjacencyList = E;
    } 
    else {
        // V->AdjacencyList�� ���ܿ� E ���� ����
        Edge* AdjacencyList = V->AdjacencyList;
        while ( AdjacencyList->Next != NULL )
            AdjacencyList = AdjacencyList->Next;
        AdjacencyList->Next = E;
    }
}

/* �׷��� ���(��������Ʈ ���� ���) */
void PrintGraph ( Graph* G ) {
    Vertex* V = G->Vertices;
    Edge* E = NULL;

    // ������ ������ ��ȸ�ϸ鼭 ���
    while ( V != NULL ) {
        printf("%c : ", V->Data);

        // ������ ������ ��ȸ�ϸ鼭 ���
        E = V->AdjacencyList;
        while (E != NULL) {
            printf("%c[%d] ", E->Target->Data, E->Weight);
            E = E->Next;
        }
        printf("\n");

        // ���� �������� �Ѿ
        V = V->Next;   
    }
    printf("\n");
}