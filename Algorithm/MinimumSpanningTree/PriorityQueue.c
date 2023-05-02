#include "PriorityQueue.h"

/* ���ο� �켱���� ť ���� ���� */
PriorityQueue* PQ_Create( int IntitialSize ) {
    PriorityQueue* NewPQ = (PriorityQueue*) malloc( sizeof( PriorityQueue ) );
    NewPQ->Capacity = IntitialSize;
    NewPQ->UsedSize = 0;
    // �뷮��ŭ�� ũ�⸦ ������ �迭 �����Ҵ�
    NewPQ->Nodes = (PQNode*) malloc( sizeof ( PQNode ) * NewPQ->Capacity );

    return NewPQ;
}
/* �켱���� ť ���� �Ҹ� */
void PQ_Destroy( PriorityQueue* PQ ) {
    free( PQ->Nodes );
    free( PQ );
}
/* �켱���� ť PQ�� NewNode ���� */
void PQ_Enqueue( PriorityQueue* PQ, PQNode NewNode ) {
    int CurrentPosition = PQ->UsedSize;
    int ParentPosition  = PQ_GetParent( CurrentPosition );

    // �켱���� ť�� ũ�Ⱑ ���� á�� ��
    if ( PQ->UsedSize == PQ->Capacity ) {
        // �뷮�� 2��� �÷��� �ٽ� �����Ҵ� ����
        if ( PQ->Capacity == 0 )
            PQ->Capacity = 1;
        PQ->Capacity *= 2;
        PQ->Nodes = (PQNode*) realloc( PQ->Nodes, sizeof( PQNode ) * PQ->Capacity );
    }
    // ���� �迭�� ���� ���� NewNode ����
    PQ->Nodes[CurrentPosition] = NewNode;

    // reheap up�� ���� �� ���� �����ϱ�
    while ( CurrentPosition > 0 && PQ->Nodes[CurrentPosition].Priority < PQ->Nodes[ParentPosition].Priority ) {
        // �θ��� �켱������ �� ���� �� ����
        // ���� ���� �θ��带 ��ȯ�ϰ�, heap������ ����� �� ������ �ݺ�
        PQ_SwapNodes( PQ, CurrentPosition, ParentPosition );
        CurrentPosition = ParentPosition;
        ParentPosition  = PQ_GetParent( CurrentPosition );
    }
    PQ->UsedSize++;
}

/* �켱���� ť PQ�� Index1�� Index2 �ε����� ��� ��ȯ */
void PQ_SwapNodes( PriorityQueue* PQ, int Index1, int Index2 ) { 
    int CopySize = sizeof( PQNode );
    PQNode* Temp = (PQNode*)malloc(CopySize);
        
    memcpy( Temp, &PQ->Nodes[Index1], CopySize);
    memcpy( &PQ->Nodes[Index1] , &PQ->Nodes[Index2], CopySize);
    memcpy( &PQ->Nodes[Index2] , Temp, CopySize);

    free(Temp);
}

/*  �켱���� ť PQ���� �켱������ ���� ���� ��� ���� (0�� �ε��� ����)
    @param Root Dequeue�� ��Ʈ ��� ������ ���� */
void PQ_Dequeue( PriorityQueue* PQ, PQNode* Root ) {
    int ParentPosition = 0;
    int LeftPosition   = 0;    
    int RightPosition  = 0;    
    
    // 0��(root)���� ���� ���� ��带 �ٲٱ�
    memcpy(Root, &PQ->Nodes[0], sizeof(PQNode));
    memset(&PQ->Nodes[0], 0, sizeof(PQNode));
    PQ_SwapNodes( PQ, 0, --(PQ->UsedSize) );

    LeftPosition  = PQ_GetLeftChild( 0 );
    RightPosition = LeftPosition + 1;

    // reheap down�� ���� heap���� ����
    while ( 1 ) {
        // ���� ���� ��ü�ؾ� �� ����� �ε���
        int SelectedChild = 0;

        // �ڽ��� ���� ���
        if ( LeftPosition >= PQ->UsedSize )
            break;

        // ���� �ڽĸ� �ִ� ���
        if ( RightPosition >= PQ->UsedSize ) {
            SelectedChild = LeftPosition;
        }
        else {  // �ڽ��� ��� �ִ� ���
            // �켱������ �� ���� �ڽ��� ����
            if ( PQ->Nodes[LeftPosition].Priority > PQ->Nodes[RightPosition].Priority)
                SelectedChild = RightPosition;
            else
                SelectedChild = LeftPosition;                
        }

        // ��ü�ؾ� �� ������� Ȯ��
        if ( PQ->Nodes[SelectedChild].Priority < PQ->Nodes[ParentPosition].Priority) {
            PQ_SwapNodes(PQ, ParentPosition, SelectedChild);
            ParentPosition = SelectedChild;
        }
        // ��ü�ؾ��� ��尡 ���� ��� = �̹� heap������ �̷� ���
        else break;

        LeftPosition  = PQ_GetLeftChild(ParentPosition);
        RightPosition = LeftPosition + 1;
    }

    // ���� ���� ����ϴ� �뷮�� ��ü �뷮�� ���� �̸��̸� �뷮�� �ٿ��� ���� ����
    if ( PQ->UsedSize < ( PQ->Capacity / 2 ) ) {
        PQ->Capacity /= 2;
        PQ->Nodes =  (PQNode*) realloc( PQ->Nodes, sizeof( PQNode ) * PQ->Capacity );
    }
}
/* �θ��� �ε��� ��ȯ */
int PQ_GetParent( int Index ) {
    return (int) ((Index - 1) / 2);
}
/* ���� �ڽ��� �ε��� ��ȯ(������ �ڽ��� ���� �ڽ� �ε��� + 1) */
int PQ_GetLeftChild( int Index ) {
    return (2 * Index) + 1;
}
/* �켱���� ť�� ��������� 1, �ƴϸ� 0 ��ȯ*/
int PQ_IsEmpty( PriorityQueue* PQ ) {
    return ( PQ->UsedSize == 0 );
}