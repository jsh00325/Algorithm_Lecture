#include "MySort.h"
#include <stdlib.h>
#include <time.h>

int* CopyArr(int a[], int l) {
    int* newArr = (int*) malloc(sizeof(int) * l);
    for (int i = 0; i < l; i++) newArr[i] = a[i];
    return newArr;
}
double Quick(int QuickArr[], int len) {
    clock_t startQuick = clock();
    QuickSort(QuickArr, 0, len-1);
    clock_t endQuick = clock();
    free(QuickArr);
    return (double)(endQuick - startQuick) / CLOCKS_PER_SEC;
}
double Insertion(int InsertionArr[], int len) {
    clock_t startInsertion = clock();
    InsertionSort(InsertionArr, len);
    clock_t endInsertion = clock();
    free(InsertionArr);
    return (double)(endInsertion - startInsertion) / CLOCKS_PER_SEC;
}
double Bubble(int BubbleArr[], int len) {
    clock_t startBubble = clock();
    InsertionSort(BubbleArr, len);
    clock_t endBubble = clock();
    free(BubbleArr);
    return (double)(endBubble - startBubble) / CLOCKS_PER_SEC;
}

char file_name[3][100] = {"input1.txt", "input2.txt", "input3.txt"};
char data_order[3][100] = {"무작위 순서의", "오름차순 정렬된", "내림차순 정렬된"};

int main() {
    for (int type = 0; type < 3; type++) {
        FILE *fp;
        fp = fopen(file_name[type], "r");

        int len;
        fscanf(fp, "%d", &len);
        int* arr = (int*) malloc(sizeof(int) * len);
        for (int i = 0; i < len; i++)
            fscanf(fp, "%d", &arr[i]);

        printf("\n- %s 데이터의 개수: %d개\n", data_order[type], len);
        printf("[  퀵 정렬] 소요 시간: %.3lfs\n", Quick(CopyArr(arr, len), len));
        printf("[삽입 정렬] 소요 시간: %.3lfs\n", Insertion(CopyArr(arr, len), len));
        printf("[버블 정렬] 소요 시간: %.3lfs\n", Bubble(CopyArr(arr, len), len));

        free(arr);
    }
}