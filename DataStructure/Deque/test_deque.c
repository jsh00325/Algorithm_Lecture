#include <stdio.h>
#include <string.h>
#include "my_deque.h"

Deque* deque = NULL;

void print_deque(Deque* dq) {
    printf("deque size: %d\n[ ", dq->size);
    Node* cur = dq->front;
    while (cur != NULL) {
        printf("%c ", cur->Data);
        cur = cur->NextNode;
    }
    printf("]\n");
}

int main() {
    deque = DQ_createDeque();

    char str[100];
    printf("팰린드롬을 검증할 문자열 : ");
    scanf("%s", str);

    // 현재 Deque에는 문자열을 순서대로 push
    for (int i = 0; i < strlen(str); i++)
        DQ_push_back(deque, str[i]);

    bool is_palindrome = true;
    // Deque에서 처음과 끝을 비교하는 연산을 계속하면서 확인
    while (deque->size >= 2) {
        if ((deque->front->Data) != (deque->back->Data)) {
            is_palindrome = false;
            break;
        }
        DQ_pop_front(deque);
        DQ_pop_back(deque);
    }
    
    if (is_palindrome) printf("\"%s\"는 팰린드롬 문자열입니다.\n", str);
    else printf("\"%s\"는 팰린드롬 문자열이 아닙니다.\n", str);
}