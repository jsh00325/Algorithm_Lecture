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
    printf("�Ӹ������ ������ ���ڿ� : ");
    scanf("%s", str);

    // ���� Deque���� ���ڿ��� ������� push
    for (int i = 0; i < strlen(str); i++)
        DQ_push_back(deque, str[i]);

    bool is_palindrome = true;
    // Deque���� ó���� ���� ���ϴ� ������ ����ϸ鼭 Ȯ��
    while (deque->size >= 2) {
        if ((deque->front->Data) != (deque->back->Data)) {
            is_palindrome = false;
            break;
        }
        DQ_pop_front(deque);
        DQ_pop_back(deque);
    }
    
    if (is_palindrome) printf("\"%s\"�� �Ӹ���� ���ڿ��Դϴ�.\n", str);
    else printf("\"%s\"�� �Ӹ���� ���ڿ��� �ƴմϴ�.\n", str);
}