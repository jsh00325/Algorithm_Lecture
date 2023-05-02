#include "PriorityQueue.h"

/* 새로운 우선순위 큐 구조 생성 */
PriorityQueue* PQ_Create( int IntitialSize ) {
    PriorityQueue* NewPQ = (PriorityQueue*) malloc( sizeof( PriorityQueue ) );
    NewPQ->Capacity = IntitialSize;
    NewPQ->UsedSize = 0;
    // 용량만큼의 크기를 가지는 배열 동적할당
    NewPQ->Nodes = (PQNode*) malloc( sizeof ( PQNode ) * NewPQ->Capacity );

    return NewPQ;
}
/* 우선순위 큐 구조 소멸 */
void PQ_Destroy( PriorityQueue* PQ ) {
    free( PQ->Nodes );
    free( PQ );
}
/* 우선순위 큐 PQ에 NewNode 삽입 */
void PQ_Enqueue( PriorityQueue* PQ, PQNode NewNode ) {
    int CurrentPosition = PQ->UsedSize;
    int ParentPosition  = PQ_GetParent( CurrentPosition );

    // 우선순위 큐의 크기가 가득 찼을 때
    if ( PQ->UsedSize == PQ->Capacity ) {
        // 용량을 2배로 늘려서 다시 동적할당 받음
        if ( PQ->Capacity == 0 )
            PQ->Capacity = 1;
        PQ->Capacity *= 2;
        PQ->Nodes = (PQNode*) realloc( PQ->Nodes, sizeof( PQNode ) * PQ->Capacity );
    }
    // 먼저 배열의 가장 끝에 NewNode 삽입
    PQ->Nodes[CurrentPosition] = NewNode;

    // reheap up을 통해 힙 구조 유지하기
    while ( CurrentPosition > 0 && PQ->Nodes[CurrentPosition].Priority < PQ->Nodes[ParentPosition].Priority ) {
        // 부모의 우선순위가 더 높을 때 실행
        // 현재 노드와 부모노드를 교환하고, heap구조가 만들어 질 때까지 반복
        PQ_SwapNodes( PQ, CurrentPosition, ParentPosition );
        CurrentPosition = ParentPosition;
        ParentPosition  = PQ_GetParent( CurrentPosition );
    }
    PQ->UsedSize++;
}

/* 우선순위 큐 PQ에 Index1과 Index2 인덱스의 노드 교환 */
void PQ_SwapNodes( PriorityQueue* PQ, int Index1, int Index2 ) { 
    int CopySize = sizeof( PQNode );
    PQNode* Temp = (PQNode*)malloc(CopySize);
        
    memcpy( Temp, &PQ->Nodes[Index1], CopySize);
    memcpy( &PQ->Nodes[Index1] , &PQ->Nodes[Index2], CopySize);
    memcpy( &PQ->Nodes[Index2] , Temp, CopySize);

    free(Temp);
}

/*  우선순위 큐 PQ에서 우선순위가 가장 낮은 노드 삭제 (0번 인덱스 삭제)
    @param Root Dequeue된 루트 노드 정보를 담음 */
void PQ_Dequeue( PriorityQueue* PQ, PQNode* Root ) {
    int ParentPosition = 0;
    int LeftPosition   = 0;    
    int RightPosition  = 0;    
    
    // 0번(root)노드와 가장 끝의 노드를 바꾸기
    memcpy(Root, &PQ->Nodes[0], sizeof(PQNode));
    memset(&PQ->Nodes[0], 0, sizeof(PQNode));
    PQ_SwapNodes( PQ, 0, --(PQ->UsedSize) );

    LeftPosition  = PQ_GetLeftChild( 0 );
    RightPosition = LeftPosition + 1;

    // reheap down을 통해 heap구조 유지
    while ( 1 ) {
        // 현재 노드와 교체해야 할 노드의 인덱스
        int SelectedChild = 0;

        // 자식이 없는 경우
        if ( LeftPosition >= PQ->UsedSize )
            break;

        // 왼쪽 자식만 있는 경우
        if ( RightPosition >= PQ->UsedSize ) {
            SelectedChild = LeftPosition;
        }
        else {  // 자식이 모두 있는 경우
            // 우선순위가 더 작은 자식을 선택
            if ( PQ->Nodes[LeftPosition].Priority > PQ->Nodes[RightPosition].Priority)
                SelectedChild = RightPosition;
            else
                SelectedChild = LeftPosition;                
        }

        // 교체해야 할 노드인지 확인
        if ( PQ->Nodes[SelectedChild].Priority < PQ->Nodes[ParentPosition].Priority) {
            PQ_SwapNodes(PQ, ParentPosition, SelectedChild);
            ParentPosition = SelectedChild;
        }
        // 교체해야할 노드가 없는 경우 = 이미 heap구조를 이룬 경우
        else break;

        LeftPosition  = PQ_GetLeftChild(ParentPosition);
        RightPosition = LeftPosition + 1;
    }

    // 만약 현재 사용하는 용량이 전체 용량의 절반 미만이면 용량을 줄여서 공간 절약
    if ( PQ->UsedSize < ( PQ->Capacity / 2 ) ) {
        PQ->Capacity /= 2;
        PQ->Nodes =  (PQNode*) realloc( PQ->Nodes, sizeof( PQNode ) * PQ->Capacity );
    }
}
/* 부모의 인덱스 반환 */
int PQ_GetParent( int Index ) {
    return (int) ((Index - 1) / 2);
}
/* 왼쪽 자식의 인덱스 반환(오른쪽 자식은 왼쪽 자식 인덱스 + 1) */
int PQ_GetLeftChild( int Index ) {
    return (2 * Index) + 1;
}
/* 우선순위 큐가 비어있으면 1, 아니면 0 반환*/
int PQ_IsEmpty( PriorityQueue* PQ ) {
    return ( PQ->UsedSize == 0 );
}