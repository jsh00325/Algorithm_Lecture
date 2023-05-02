#include "Graph.h"

/* 새로운 그래프 구조 생성 */
Graph* CreateGraph() {
    Graph* graph = (Graph*)malloc( sizeof( Graph ) );
    graph->Vertices = NULL;
    graph->VertexCount = 0;

    return graph;
}
/* 그래프 구조 소멸 */
void DestroyGraph( Graph* G ) {
    while ( G->Vertices != NULL ) {
        // 그냥 바로 free(G)를 하면 남은 정점이나 간선에 접근할 수 없고, 
        // 지울 수 없기 때문에, 순차적으로 추적하면서 남김없이 지움
        Vertex* VertexHead = G->Vertices->Next;        
        DestroyVertex( G->Vertices );
        G->Vertices = VertexHead;        
    }
    free(G);
}

/* 새로운 정점 구조 생성 */
Vertex* CreateVertex( ElementType Data ) {
    Vertex* V = (Vertex*)malloc( sizeof(Vertex) );
    
    V->Data = Data;
    V->Next = NULL;
    V->AdjacencyList = NULL;
    V->Visited = NotVisited;
    V->Index = -1;  // 나중에 graph에 add될 떄 index 부여

    return V;
}
/* 정점 구조 소멸 */
void DestroyVertex( Vertex* V ) {
    while ( V->AdjacencyList != NULL ) {
        Edge* Edge = V->AdjacencyList->Next;
        DestroyEdge ( V->AdjacencyList );
        V->AdjacencyList = Edge;
    }
    free( V );
}

/* 새로운 간선 구조 생성 */
Edge* CreateEdge( Vertex* From, Vertex* Target, int Weight ) {
    Edge* E   = (Edge*)malloc( sizeof( Edge ) );
    E->From   = From;
    E->Target = Target;
    E->Next   = NULL;
    E->Weight = Weight;

    return E;
}
/* 간선 구조 소멸 */
void DestroyEdge( Edge* E ) {
    free( E );
}

/* graph에 정점을 삽입(말단에) */
void AddVertex( Graph* G, Vertex* V ) {
    Vertex* VertexList = G->Vertices;

    // graph에 정점이 존재하지 않을 때
    if ( VertexList == NULL ) {
        G->Vertices = V;
    } 
    else {
        // G->Vertices의 가장 말단에 V 정점 삽입
        while ( VertexList->Next != NULL )
            VertexList = VertexList->Next;
        VertexList->Next = V;
    }

    // graph의 정점의 개수에 따라 인덱스 부여
    V->Index = G->VertexCount++;
}
/* graph에 간선을 삽입(말단에) */
void AddEdge( Vertex* V, Edge* E ) {
    // V 정점에 간선이 존재하지 않을 때
    if ( V->AdjacencyList == NULL ) {
        V->AdjacencyList = E;
    } 
    else {
        // V->AdjacencyList의 말단에 E 간선 삽입
        Edge* AdjacencyList = V->AdjacencyList;
        while ( AdjacencyList->Next != NULL )
            AdjacencyList = AdjacencyList->Next;
        AdjacencyList->Next = E;
    }
}

/* 그래프 출력(인접리스트 형태 출력) */
void PrintGraph ( Graph* G ) {
    Vertex* V = G->Vertices;
    Edge* E = NULL;

    // 정점을 끝까지 순회하면서 출력
    while ( V != NULL ) {
        printf("%c : ", V->Data);

        // 간선을 끝까지 순회하면서 출력
        E = V->AdjacencyList;
        while (E != NULL) {
            printf("%c[%d] ", E->Target->Data, E->Weight);
            E = E->Next;
        }
        printf("\n");

        // 다음 간선으로 넘어감
        V = V->Next;   
    }
    printf("\n");
}