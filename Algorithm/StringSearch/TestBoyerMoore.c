#include "BoyerMoore.h"

int main() {

    char text[200] = "";
    char pattern[200] = "";
    printf("���� : "); scanf("%s", text);
    printf("���� : "); scanf("%s", pattern);

    int search_result = BoyerMoore(text, strlen(text), pattern, strlen(pattern));
    
    if (search_result == -1) printf("\n[Ž�� ���] ������ ������ �������� ����!\n");
    else {
        printf("\n[Ž�� ���]\n%s\n", text);
        for (int i = 0; i < search_result; i++) printf(" ");
        for (int i = 0; i < strlen(pattern); i++) printf("^"); printf("\n");
        for (int i = 0; i < search_result; i++) printf(" "); printf("%s\n", pattern);
    }
    
    return 0;
}