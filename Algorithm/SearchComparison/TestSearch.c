#include "MySearch.h"
#include "NumHash.h"
#include <time.h>

int* CopyArr(int a[], int l) {
    int* newArr = (int*) malloc(sizeof(int) * l);
    for (int i = 0; i < l; i++) newArr[i] = a[i];
    return newArr;
}
void LinearTime(int arr[], int len, int target) {
    printf("[ 선형 탐색 ]\n");
    printf("== [  전처리  ] %.3fs\n", 0);

    clock_t st = clock();
    LinearSearch(arr, len, target);
    clock_t en = clock();
    printf("== [ 탐색시간 ] %.3fs\n\n", (double)(en - st) / CLOCKS_PER_SEC);
    free(arr);
}
int static cmp(const void* x, const void* y) {
    int a = *(int*)x, b = *(int*)y;
    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0; 
}
void BinaryTime(int arr[], int len, int target) {
    printf("[ 이진 탐색 ]\n");

    clock_t st_pre = clock();
    qsort(arr, len, sizeof(int), cmp);
    clock_t en_pre = clock();
    printf("== [  전처리  ] %.3fs\n", (double)(en_pre - st_pre) / CLOCKS_PER_SEC);

    clock_t st_srch = clock();
    BinarySearch(arr, len, target);
    clock_t en_srch = clock();
    printf("== [ 탐색시간 ] %.3fs\n\n", (double)(en_srch - st_srch) / CLOCKS_PER_SEC);

    free(arr);
}
void HashTime(int arr[], int len, int target) {
    printf("[ 해시 탐색 ]\n");

    HashTable* HT = NH_CreateHashTable(1000);
    clock_t st_pre = clock();
    for (int i = 0; i < len; i++) NH_Set(&HT, arr[i]);
    clock_t en_pre = clock();
    printf("== [  전처리  ] %.3fs\n", (double)(en_pre - st_pre) / CLOCKS_PER_SEC);

    clock_t st_srch = clock();
    NH_Get(HT, target);
    clock_t en_srch = clock();
    printf("== [ 탐색시간 ] %.3fs\n\n", (double)(en_srch - st_srch) / CLOCKS_PER_SEC);
    free(arr);
}

int main() {
    FILE *fp;
    fp = fopen("input.txt", "r");

    int len, target;
    fscanf(fp, "%d %d", &len, &target);
    int* arr = (int*) malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++)
        fscanf(fp, "%d", &arr[i]);

    printf("데이터의 수 : %d개\n\n", len);
    LinearTime(CopyArr(arr, len), len, -1);
    BinaryTime(CopyArr(arr, len), len, -1);
    HashTime(CopyArr(arr, len), len, -1);
}