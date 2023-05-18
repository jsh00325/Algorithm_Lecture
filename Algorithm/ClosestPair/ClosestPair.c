#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    int x, y;
} Node;

void merge(Node* arr, Node* temp, int st, int mid, int en, int (*cmp)(const Node*, const Node*)) {
    int i = st, j = mid+1, k = st;
    while (i <= mid && j <= en)
        if (cmp(&arr[i], &arr[j]) < 0) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= en) temp[k++] = arr[j++];
    for (int x = st; x <= en; x++) arr[x] = temp[x];
}
void mergeSort(Node* arr, Node* temp, int st, int en, int (*cmp)(const Node*, const Node*)) {
    if (st == en) return;
    int mid = (st + en) / 2;
    mergeSort(arr, temp, st, mid, cmp);
    mergeSort(arr, temp, mid+1, en, cmp);
    merge(arr, temp, st, mid, en, cmp);
}

int cmp(int a, int b) {
    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0;
}
int cmpX(const Node* a, const Node* b) {
    if (a->x == b->x) return cmp(a->y, b->y);
    else return cmp(a->x, b->x);
}
int cmpY(const Node* a, const Node* b) {
    if (a->y == b->y) return cmp(a->x, b->x);
    else return cmp(a->y, b->y);
}

int getMin(int a, int b) {
    return (a < b ? a : b);
}

int getLength2(const Node* a, const Node* b) {
    return (a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y);
}
int naiveLength(const Node p[], int st, int en) {
    int rslt = 0x7fffffff;
    for (int i = st; i < en; i++)
        for (int j = i + 1; j <= en; j++)
            rslt = getMin(rslt, getLength2(&p[i], &p[j]));
    return rslt;
}

int findClosestPairLength2(const Node xSort[], const Node ySort[], int st, int en) {
    if (en - st + 1 <= 3) return naiveLength(xSort, st, en);

    int mid = (st + en) / 2;
    Node midPoint = xSort[mid];

    Node* ySortLeft = (Node*) malloc(sizeof(Node) * (mid - st + 1));
    Node* ySortRight = (Node*) malloc(sizeof(Node) * (en - mid));
    int leftIdx = 0, rightIdx = 0;
    for (int i = 0; i < (en - st + 1); i++)
        if ((ySort[i].x < midPoint.x || (ySort[i].x == midPoint.x && ySort[i].y <= midPoint.y)) && leftIdx <= mid - st)
            ySortLeft[leftIdx++] = ySort[i];
        else ySortRight[rightIdx++] = ySort[i];

    
    int leftMinD = findClosestPairLength2(xSort, ySortLeft, st, mid);
    int rightMinD = findClosestPairLength2(xSort, ySortRight, mid + 1, en);
    int minD = getMin(leftMinD, rightMinD);

    Node* mergePointYSort = (Node*) malloc(sizeof(Node) * (en - st + 1));
    int mergeCount = 0;
    for (int i = 0; i < (en - st + 1); i++)
        if ((ySort[i].x - midPoint.x) * (ySort[i].x - midPoint.x) < minD)
            mergePointYSort[mergeCount++] = ySort[i];

        
    int mergeMinDist = 0x7fffffff;
    for (int i = 0; i < mergeCount; i++) {
        for (int j = i+1; j < mergeCount; j++) {
            if (mergePointYSort[j].y - mergePointYSort[i].y >= minD) break;
            mergeMinDist = getMin(mergeMinDist, getLength2(&mergePointYSort[i], &mergePointYSort[j]));
        }
    }
    free(ySortLeft); free(ySortRight); free(mergePointYSort);
    return getMin(minD, mergeMinDist);
}

int main() {
    FILE *fp = fopen("input.txt", "r");

    int n; fscanf(fp, "%d", &n);
    Node* point = (Node*) malloc(sizeof(Node)*n);
    for (int i = 0; i < n; i++)
        fscanf(fp, "%d %d", &point[i].x, &point[i].y);
    fclose(fp);
    
    Node* xSort = (Node*) malloc(sizeof(Node)*n);
    Node* ySort = (Node*) malloc(sizeof(Node)*n);
    for (int i = 0; i < n; i++)
        xSort[i] = ySort[i] = point[i];

    // point는 더이상 사용할 일이 없어서 mergeSort에서 임시공간으로 활용
    mergeSort(xSort, point, 0, n-1, cmpX);
    mergeSort(ySort, point, 0, n-1, cmpY);

    clock_t start = clock();
    printf("가장 가까운 점 사이의 거리 : %.3lf\n", sqrt(findClosestPairLength2(xSort, ySort, 0, n-1)));
    clock_t end = clock();
    printf("걸린 시간 : %.3lfs\n", (double)(end - start)/CLOCKS_PER_SEC);

    free(xSort); free(ySort); free(point);
}