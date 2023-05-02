#include "my_deque.h"

/* data를 데이터로 가지는 노드를 새로 동적할당 */
Node* DQ_make_node(ElementType data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->Data = data;
    new_node->PrevNode = NULL;
    new_node->NextNode = NULL;
    return new_node;
}
/* 새로운 Deque을 동적할당하고 그를 반환하는 함수 */
Deque* DQ_createDeque() {
    Deque* new_deque = (Deque*)malloc(sizeof(Deque));

    new_deque->size = 0;
    new_deque->front = NULL;
    new_deque->back = NULL;

    return new_deque;
}
/* Deque의 맨 앞에 data를 데이터로 갖는 노드 추가하는 함수 */
void DQ_push_front(Deque* dq, ElementType data) {
    Node* new_node = DQ_make_node(data);

    if (dq->size == 0)
        dq->back = new_node;
    else 
        dq->front->PrevNode = new_node;
    
    new_node->NextNode = dq->front;
    dq->front = new_node;
    (dq->size)++;
}
/* Deque의 맨 뒤에 data를 데이터로 갖는 노드 추가하는 함수 */
void DQ_push_back(Deque* dq, ElementType data) {
    Node* new_node = DQ_make_node(data);

    if (dq->size == 0)
        dq->front = new_node;
    else
        dq->back->NextNode = new_node;

    new_node->PrevNode = dq->back;
    dq->back = new_node;
    (dq->size)++;
}
/** Deque의 맨 앞에 있는 노드를 반환하는 함수
 * 노드를 pop할 수 있으면 pop하고 true를 반환하고, pop할 수 없으면 false를 반환 */
bool DQ_pop_front(Deque* dq) {
    if (dq->size == 0) return false;

    Node* temp = dq->front;

    if (dq->size == 1) 
        dq->back = NULL;
    else
        dq->front->NextNode->PrevNode = NULL;

    dq->front = dq->front->NextNode;
    free(temp);
    (dq->size)--;
    return true;
}
/** Deque의 맨 뒤에 있는 노드를 반환하는 함수
 * 노드를 pop할 수 있으면 pop하고 true를 반환하고, pop할 수 없으면 false를 반환 */
bool DQ_pop_back(Deque* dq) {
    if (dq->size == 0) return false;

    Node* temp = dq->back;

    if (dq->size == 1) 
        dq->front = NULL;
    else
        dq->back->PrevNode->NextNode = NULL;
    
    dq->back = dq->back->PrevNode;
    free(temp);
    (dq->size)--;
    return true;
}