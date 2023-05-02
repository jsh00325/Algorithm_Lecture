#include "MST.h"
/** Prim`s Algorithm을 이용하여 MST 구하기
 *  @param G MST를 만들 그래프
 *  @param StartVertex  MST의 시작점이 되는 정점
 *  @param MST 만들어진 MST를 담는 그래프
*/
void Prim(Graph* G, Vertex* StartVertex, Graph* MST, int MaxWeight ) {
    // 우선순위 큐 생성 (priority = 해당 정점 까지의 가중치)
    PQNode StartNode = { 0, StartVertex };
    PriorityQueue* PQ = PQ_Create(10);

    Vertex* CurrentVertex = NULL;
    Edge* CurrentEdge = NULL; 

    // MST에서 해당 정점으로 들어오는 간선의 가중치를 기록하는 배열
    int* Weights = (int*) malloc( sizeof(int) * G->VertexCount );
    // 해당 정점이 MST에 포함되었는지 여부를 저장하는 bool 배열
    bool* Visit = (bool*) malloc(sizeof(bool) * G->VertexCount);
    // MST의 정점 주소를 담는 배열
    Vertex** MSTVertices = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    // MST에서 해당 정점으로 들어오는 간선의 From 정점의 정보를 저장하는 배열
    Vertex** Precedences = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );

    // MST 그래프 정점 추가 & 동적할당 받은 배열 초기화
    CurrentVertex = G->Vertices;
    for (int i = 0; i < G->VertexCount; i++) {
        // G 그래프의 정점을 MST 그래프에 추가
        Vertex* NewVertex = CreateVertex( CurrentVertex->Data );
        AddVertex( MST, NewVertex );

        Weights[i]     = MaxWeight;        
        Visit[i]       = false;
        MSTVertices[i] = NewVertex;        
        Precedences[i] = NULL;

        CurrentVertex  = CurrentVertex->Next;
    }

    // 시작 정점을 우선순위 큐에 넣고 탐색 시작
    PQ_Enqueue ( PQ, StartNode );
    Weights[StartVertex->Index] = 0;

    while( !PQ_IsEmpty( PQ ) ) {
        // 우선순위 큐에서 Root 노드를 가져오고 dequeue
        PQNode Popped;
        PQ_Dequeue(PQ, &Popped);
        
        // 현재 정점이 MST에 포함되었음을 표시
        CurrentVertex = (Vertex*)Popped.Data;
            // 이미 해당 정점이 MST에 포함되었다면 continue
        if (Visit[CurrentVertex->Index]) continue;
        Visit[CurrentVertex->Index] = true;

        // 현재 선택된 정점과 연결된 간선 탐색
        CurrentEdge = CurrentVertex->AdjacencyList;
        while ( CurrentEdge != NULL ) {            
            Vertex* TargetVertex = CurrentEdge->Target;

            // 타겟정점이 MST에 포함되지 않고, 그 정점으로 가는 비용이 현재까지 최선일 때 실행
            if ( !Visit[TargetVertex->Index] && CurrentEdge->Weight < Weights[TargetVertex->Index] ) {
                PQNode NewNode =  { CurrentEdge->Weight, TargetVertex };
                PQ_Enqueue ( PQ, NewNode );

                Precedences[TargetVertex->Index] = CurrentEdge->From;
                Weights[TargetVertex->Index] = CurrentEdge->Weight;                
            }
            CurrentEdge = CurrentEdge->Next;
        }
    }

    // 위의 과정을 통해 얻은 정보를 바탕으로 MST 구성
    for (int i = 0; i < G->VertexCount; i++ ) {
        // 출발 정점의 정보가 없을 때 (시작 정점일 때)
        if ( Precedences[i] == NULL ) continue;

        // 간선의 시작점과 도착점 정의
        int FromIndex = Precedences[i]->Index;
        int ToIndex = i;
        Vertex* fromVertex = MSTVertices[FromIndex];
        Vertex* toVertex = MSTVertices[ToIndex];

        // 양방향 간선 추가
        AddEdge( fromVertex, CreateEdge( fromVertex, toVertex, Weights[i] ) );
        AddEdge( toVertex, CreateEdge( toVertex, fromVertex, Weights[i] ) );
    }

    // 동적할당 받은 변수들 소멸
    free( Visit );
    free( Precedences );
    free( MSTVertices );
    free( Weights );

    PQ_Destroy( PQ );
}

/** Kruskal`s Algorithm을 이용하여 MST 구하기
 *  @param G MST를 만들 그래프
 *  @param MST 만들어진 MST를 담는 그래프
*/
void Kruskal(Graph* G, Graph* MST ) {
    // MST의 정점 주소를 담는 배열
    Vertex** MSTVertices = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    // 분리집합을 이용하기 위해서 각 정점에 해당하는 분리집합 구조체 배열
    DisjointSet** VertexSet = (DisjointSet**)malloc( sizeof(DisjointSet*) * G->VertexCount );
    
    // 모든 정점을 돌면서 간선의 정보를 우선순위 큐에 넣어서 정렬(오름차순)
    PriorityQueue* PQ = PQ_Create(10);
    Vertex* CurrentVertex = G->Vertices;

    for (int i = 0; i < G->VertexCount; i++) {
        // 동적할당 받은 배열들 초기화 & MST 정점 구성
        VertexSet[i] = DS_MakeSet( CurrentVertex );
        MSTVertices[i] = CreateVertex( CurrentVertex->Data );
        AddVertex( MST, MSTVertices[i] );

        // 해당 정점과 연결된 간선 탐색
        Edge* CurrentEdge = CurrentVertex->AdjacencyList;
        while ( CurrentEdge != NULL ) {
            PQNode NewNode = { CurrentEdge->Weight, CurrentEdge };
            PQ_Enqueue( PQ, NewNode );

            CurrentEdge = CurrentEdge->Next;
        }

        CurrentVertex  = CurrentVertex->Next;
    }

    // 연결된 간선의 수를 저장
    int edge_cnt = 0;

    // 가장 작은 가중치의 간선부터 꺼내면서 MST 만들기
    while ( !PQ_IsEmpty( PQ ) && edge_cnt < (G->VertexCount - 1) ) {
        // 우선순위 큐에서 Root 노드를 가져오고 dequeue
        PQNode Popped;
        PQ_Dequeue( PQ, &Popped );
        Edge* CurrentEdge = (Edge*)Popped.Data;

        int FromIndex = CurrentEdge->From->Index;
        int ToIndex   = CurrentEdge->Target->Index;
        
        // 두 집합이 서로 다른 집합이라면
        if ( DS_isDiffrentSet(VertexSet[FromIndex], VertexSet[ToIndex]) ) {
            // 간선의 시작점과 도착점 정의
            Vertex* fromVertex = MSTVertices[FromIndex];
            Vertex* toVertex = MSTVertices[ToIndex];

            // 양방향 간선 추가
            AddEdge( fromVertex, CreateEdge( fromVertex, toVertex, CurrentEdge->Weight ) );
            AddEdge( toVertex, CreateEdge( toVertex, fromVertex, CurrentEdge->Weight ) );

            // 두 분리집합 합치기
            DS_UnionSet( VertexSet[FromIndex], VertexSet[ToIndex] );

            edge_cnt++;
        }
    }

    // 동적할당 받은 변수들 소멸
    for (int i=0; i < G->VertexCount; i++)
        DS_DestroySet( VertexSet[i] );
    free( VertexSet );
    free( MSTVertices );
}