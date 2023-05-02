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

/*  ��� ���� */
Node* DLL_CreateNode(ElementType NewData) {
    Node* NewNode = (Node*)malloc(sizeof(Node));

    NewNode->Data = NewData;
    NewNode->PrevNode = NewNode->NextNode = NULL;

    return NewNode;
}

/*  ��� �Ҹ� */
void DLL_DestroyNode(Node* Node) {
    free(Node);
}

/* ��� ����(Current �տ�) */
void DLL_InsertFront(Node** Head, Node* Current, Node* NewNode) {
    // Current�� Head�̸� ���� �� NewNode�� ���ο� Head�� ��
    if (*Head == Current) *Head = NewNode;

    NewNode->NextNode = Current;
    NewNode->PrevNode = Current->PrevNode;

    if (Current->PrevNode != NULL)
        Current->PrevNode->NextNode = NewNode;
    Current->PrevNode = NewNode;
}

/*  ��� ���� */
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

/* ���Ḯ��Ʈ ��ü ��� */
void PrintDLL(Node* Head) {
    Node* CurNode = Head;
    while (CurNode != NULL) {
        printf("%c", CurNode->Data);
        CurNode = CurNode->NextNode;
    }
}

#endif