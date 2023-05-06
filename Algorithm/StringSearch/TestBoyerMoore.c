#include "BoyerMoore.h"

int main() {

    char text[200] = "";
    char pattern[200] = "";
    printf("본문 : "); scanf("%s", text);
    printf("패턴 : "); scanf("%s", pattern);

    int search_result = BoyerMoore(text, strlen(text), pattern, strlen(pattern));
    
    if (search_result == -1) printf("\n[탐색 결과] 본문에 패턴이 존재하지 않음!\n");
    else {
        printf("\n[탐색 결과]\n%s\n", text);
        for (int i = 0; i < search_result; i++) printf(" ");
        for (int i = 0; i < strlen(pattern); i++) printf("^"); printf("\n");
        for (int i = 0; i < search_result; i++) printf(" "); printf("%s\n", pattern);
    }
    
    return 0;
}