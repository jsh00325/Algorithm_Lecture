#include <stdio.h>
#include <string.h>
#include "DoublyLInkedLIst.h"
Node* list = DLL_CreateNode(0);
Node* cursor = list;

/* cursor 앞에 문자를 추가하는 함수 */
void insert(char c) {
    DLL_InsertFront(&list, cursor, DLL_CreateNode(c));
}
/* 커서를 왼쪽으로 한 칸 옮기는 함수 */
void cursor_left() {
    if (cursor->PrevNode == NULL) return;
    cursor = cursor->PrevNode;
}
/* 커서를 오른쪽으로 한 칸 옮기는 함수 */
void cursor_right() {
    if (cursor->NextNode == NULL) return;
    cursor = cursor->NextNode;
}
/* cursor 앞의 문자를 지우는 함수 */
void erase() {
    if (cursor->PrevNode == NULL) return;
    DLL_RemoveNode(&list, cursor->PrevNode);
}

int main() {
    printf("명령어 입력 : ");
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
    printf("최종 문자열 : \"");
    PrintDLL(list);
    printf("\"\n");
    return 0;
}