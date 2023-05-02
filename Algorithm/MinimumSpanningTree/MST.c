#include "MST.h"
/** Prim`s Algorithm�� �̿��Ͽ� MST ���ϱ�
 *  @param G MST�� ���� �׷���
 *  @param StartVertex  MST�� �������� �Ǵ� ����
 *  @param MST ������� MST�� ��� �׷���
*/
void Prim(Graph* G, Vertex* StartVertex, Graph* MST, int MaxWeight ) {
    // �켱���� ť ���� (priority = �ش� ���� ������ ����ġ)
    PQNode StartNode = { 0, StartVertex };
    PriorityQueue* PQ = PQ_Create(10);

    Vertex* CurrentVertex = NULL;
    Edge* CurrentEdge = NULL; 

    // MST���� �ش� �������� ������ ������ ����ġ�� ����ϴ� �迭
    int* Weights = (int*) malloc( sizeof(int) * G->VertexCount );
    // �ش� ������ MST�� ���ԵǾ����� ���θ� �����ϴ� bool �迭
    bool* Visit = (bool*) malloc(sizeof(bool) * G->VertexCount);
    // MST�� ���� �ּҸ� ��� �迭
    Vertex** MSTVertices = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    // MST���� �ش� �������� ������ ������ From ������ ������ �����ϴ� �迭
    Vertex** Precedences = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );

    // MST �׷��� ���� �߰� & �����Ҵ� ���� �迭 �ʱ�ȭ
    CurrentVertex = G->Vertices;
    for (int i = 0; i < G->VertexCount; i++) {
        // G �׷����� ������ MST �׷����� �߰�
        Vertex* NewVertex = CreateVertex( CurrentVertex->Data );
        AddVertex( MST, NewVertex );

        Weights[i]     = MaxWeight;        
        Visit[i]       = false;
        MSTVertices[i] = NewVertex;        
        Precedences[i] = NULL;

        CurrentVertex  = CurrentVertex->Next;
    }

    // ���� ������ �켱���� ť�� �ְ� Ž�� ����
    PQ_Enqueue ( PQ, StartNode );
    Weights[StartVertex->Index] = 0;

    while( !PQ_IsEmpty( PQ ) ) {
        // �켱���� ť���� Root ��带 �������� dequeue
        PQNode Popped;
        PQ_Dequeue(PQ, &Popped);
        
        // ���� ������ MST�� ���ԵǾ����� ǥ��
        CurrentVertex = (Vertex*)Popped.Data;
            // �̹� �ش� ������ MST�� ���ԵǾ��ٸ� continue
        if (Visit[CurrentVertex->Index]) continue;
        Visit[CurrentVertex->Index] = true;

        // ���� ���õ� ������ ����� ���� Ž��
        CurrentEdge = CurrentVertex->AdjacencyList;
        while ( CurrentEdge != NULL ) {            
            Vertex* TargetVertex = CurrentEdge->Target;

            // Ÿ�������� MST�� ���Ե��� �ʰ�, �� �������� ���� ����� ������� �ּ��� �� ����
            if ( !Visit[TargetVertex->Index] && CurrentEdge->Weight < Weights[TargetVertex->Index] ) {
                PQNode NewNode =  { CurrentEdge->Weight, TargetVertex };
                PQ_Enqueue ( PQ, NewNode );

                Precedences[TargetVertex->Index] = CurrentEdge->From;
                Weights[TargetVertex->Index] = CurrentEdge->Weight;                
            }
            CurrentEdge = CurrentEdge->Next;
        }
    }

    // ���� ������ ���� ���� ������ �������� MST ����
    for (int i = 0; i < G->VertexCount; i++ ) {
        // ��� ������ ������ ���� �� (���� ������ ��)
        if ( Precedences[i] == NULL ) continue;

        // ������ �������� ������ ����
        int FromIndex = Precedences[i]->Index;
        int ToIndex = i;
        Vertex* fromVertex = MSTVertices[FromIndex];
        Vertex* toVertex = MSTVertices[ToIndex];

        // ����� ���� �߰�
        AddEdge( fromVertex, CreateEdge( fromVertex, toVertex, Weights[i] ) );
        AddEdge( toVertex, CreateEdge( toVertex, fromVertex, Weights[i] ) );
    }

    // �����Ҵ� ���� ������ �Ҹ�
    free( Visit );
    free( Precedences );
    free( MSTVertices );
    free( Weights );

    PQ_Destroy( PQ );
}

/** Kruskal`s Algorithm�� �̿��Ͽ� MST ���ϱ�
 *  @param G MST�� ���� �׷���
 *  @param MST ������� MST�� ��� �׷���
*/
void Kruskal(Graph* G, Graph* MST ) {
    // MST�� ���� �ּҸ� ��� �迭
    Vertex** MSTVertices = (Vertex**) malloc( sizeof(Vertex*) * G->VertexCount );
    // �и������� �̿��ϱ� ���ؼ� �� ������ �ش��ϴ� �и����� ����ü �迭
    DisjointSet** VertexSet = (DisjointSet**)malloc( sizeof(DisjointSet*) * G->VertexCount );
    
    // ��� ������ ���鼭 ������ ������ �켱���� ť�� �־ ����(��������)
    PriorityQueue* PQ = PQ_Create(10);
    Vertex* CurrentVertex = G->Vertices;

    for (int i = 0; i < G->VertexCount; i++) {
        // �����Ҵ� ���� �迭�� �ʱ�ȭ & MST ���� ����
        VertexSet[i] = DS_MakeSet( CurrentVertex );
        MSTVertices[i] = CreateVertex( CurrentVertex->Data );
        AddVertex( MST, MSTVertices[i] );

        // �ش� ������ ����� ���� Ž��
        Edge* CurrentEdge = CurrentVertex->AdjacencyList;
        while ( CurrentEdge != NULL ) {
            PQNode NewNode = { CurrentEdge->Weight, CurrentEdge };
            PQ_Enqueue( PQ, NewNode );

            CurrentEdge = CurrentEdge->Next;
        }

        CurrentVertex  = CurrentVertex->Next;
    }

    // ����� ������ ���� ����
    int edge_cnt = 0;

    // ���� ���� ����ġ�� �������� �����鼭 MST �����
    while ( !PQ_IsEmpty( PQ ) && edge_cnt < (G->VertexCount - 1) ) {
        // �켱���� ť���� Root ��带 �������� dequeue
        PQNode Popped;
        PQ_Dequeue( PQ, &Popped );
        Edge* CurrentEdge = (Edge*)Popped.Data;

        int FromIndex = CurrentEdge->From->Index;
        int ToIndex   = CurrentEdge->Target->Index;
        
        // �� ������ ���� �ٸ� �����̶��
        if ( DS_isDiffrentSet(VertexSet[FromIndex], VertexSet[ToIndex]) ) {
            // ������ �������� ������ ����
            Vertex* fromVertex = MSTVertices[FromIndex];
            Vertex* toVertex = MSTVertices[ToIndex];

            // ����� ���� �߰�
            AddEdge( fromVertex, CreateEdge( fromVertex, toVertex, CurrentEdge->Weight ) );
            AddEdge( toVertex, CreateEdge( toVertex, fromVertex, CurrentEdge->Weight ) );

            // �� �и����� ��ġ��
            DS_UnionSet( VertexSet[FromIndex], VertexSet[ToIndex] );

            edge_cnt++;
        }
    }

    // �����Ҵ� ���� ������ �Ҹ�
    for (int i=0; i < G->VertexCount; i++)
        DS_DestroySet( VertexSet[i] );
    free( VertexSet );
    free( MSTVertices );
}