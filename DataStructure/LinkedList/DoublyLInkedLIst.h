#ifndef DOUBLY_LINKEDLIST_H
#define DOUBLY_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct tagNode {
    ElementType Data;
    struct tagNode* PrevNode;
    struct tagNode* NextNode;
} Node;

/*  노드 생성 */
Node* DLL_CreateNode(ElementType NewData) {
    Node* NewNode = (Node*)malloc(sizeof(Node));

    NewNode->Data = NewData;
    NewNode->PrevNode = NewNode->NextNode = NULL;

    return NewNode;
}

/*  노드 소멸 */
void DLL_DestroyNode(Node* Node) {
    free(Node);
}

/* 노드 삽입(Current 앞에) */
void DLL_InsertFront(Node** Head, Node* Current, Node* NewNode) {
    // Current가 Head이면 삽입 후 NewNode가 새로운 Head가 됨
    if (*Head == Current) *Head = NewNode;

    NewNode->NextNode = Current;
    NewNode->PrevNode = Current->PrevNode;

    if (Current->PrevNode != NULL)
        Current->PrevNode->NextNode = NewNode;
    Current->PrevNode = NewNode;
}

/*  노드 제거 */
void DLL_RemoveNode(Node** Head, Node* Remove) {
    if (*Head == Remove) {
        *Head = Remove->NextNode;
        if ((*Head) != NULL)
            (*Head)->PrevNode = NULL;
    }
    else {
        Node* Temp = Remove;
        if ( Remove->PrevNode != NULL )
            Remove->PrevNode->NextNode = Temp->NextNode;
        if ( Remove->NextNode != NULL )
            Remove->NextNode->PrevNode = Temp->PrevNode;
    }
    DLL_DestroyNode(Remove);
}

/* 연결리스트 전체 출력 */
void PrintDLL(Node* Head) {
    Node* CurNode = Head;
    while (CurNode != NULL) {
        printf("%c", CurNode->Data);
        CurNode = CurNode->NextNode;
    }
}

#endif