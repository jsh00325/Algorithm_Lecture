#ifndef MY_DEQUE_H
#define MY_DEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char ElementType;

typedef struct tagNode {
    ElementType Data;
    struct tagNode* PrevNode;
    struct tagNode* NextNode;
} Node;

typedef struct dq {
    int size;
    Node* front;
    Node* back;
} Deque;

/* 함수 정의 */
Deque* DQ_createDeque();
Node* DQ_make_node(ElementType data);
void DQ_push_front(Deque* dq, ElementType data);
void DQ_push_back(Deque* dq, ElementType data);
bool DQ_pop_front(Deque* dq);
bool DQ_pop_back(Deque* dq);

#endif