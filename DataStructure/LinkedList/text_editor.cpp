#include <stdio.h>
#include <string.h>
#include "DoublyLInkedLIst.h"
Node* list = DLL_CreateNode(0);
Node* cursor = list;

/* cursor �տ� ���ڸ� �߰��ϴ� �Լ� */
void insert(char c) {
    DLL_InsertFront(&list, cursor, DLL_CreateNode(c));
}
/* Ŀ���� �������� �� ĭ �ű�� �Լ� */
void cursor_left() {
    if (cursor->PrevNode == NULL) return;
    cursor = cursor->PrevNode;
}
/* Ŀ���� ���������� �� ĭ �ű�� �Լ� */
void cursor_right() {
    if (cursor->NextNode == NULL) return;
    cursor = cursor->NextNode;
}
/* cursor ���� ���ڸ� ����� �Լ� */
void erase() {
    if (cursor->PrevNode == NULL) return;
    DLL_RemoveNode(&list, cursor->PrevNode);
}

int main() {
    printf("��ɾ� �Է� : ");
    char command[200];
    scanf("%s", command);

    for (int i = 0; i < strlen(command); i++) {
        printf("%c  ->\t", command[i]);

        if (command[i] == '<') cursor_left();
        else if (command[i] == '>') cursor_right();
        else if (command[i] == '-') erase();
        else insert(command[i]);
        
        PrintDLL(list);
        printf("\n");
    }
    printf("���� ���ڿ� : \"");
    PrintDLL(list);
    printf("\"\n");
    return 0;
}