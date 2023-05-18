#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef long long ll;
typedef struct {
    ll x, y;
} Node;
typedef struct {
    int p1Idx, p2Idx;
    ll dist;
} TwoPoint;

const ll INF = 9*1e18;
Node* point = NULL;

void merge(int arr[], int temp[], int st, int mid, int en, int (*cmp)(int, int)) {
    int i = st, j = mid+1, k = st;
    while (i <= mid && j <= en)
        if (cmp(arr[i], arr[j]) <= 0) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= en) temp[k++] = arr[j++];
    for (int x = st; x <= en; x++) arr[x] = temp[x];
}
void mergeSort(int arr[], int temp[], int st, int en, int (*cmp)(int, int)) {
    if (st == en) return;
    int mid = (st + en) / 2;
    mergeSort(arr, temp, st, mid, cmp);
    mergeSort(arr, temp, mid+1, en, cmp);
    merge(arr, temp, st, mid, en, cmp);
}

int cmp(ll a, ll b) {
    if (a < b) return -1;
    else if (a > b) return 1;
    else return 0;
}
int cmpX(int a, int b) {
    if (point[a].x == point[b].x) return cmp(point[a].y, point[b].y);
    else return cmp(point[a].x, point[b].x);
}
int cmpY(int a, int b) {
    if (point[a].y == point[b].y) return cmp(point[a].x, point[b].x);
    else return cmp(point[a].y, point[b].y);
}

ll getMin(ll a, ll b) {
    return (a < b ? a : b);
}

ll getLength2(int aIdx, int bIdx) {
    return (point[aIdx].x - point[bIdx].x)*(point[aIdx].x - point[bIdx].x) 
                + (point[aIdx].y - point[bIdx].y)*(point[aIdx].y - point[bIdx].y);
}
TwoPoint naiveLength(const int pIdx[], int st, int en) {
    TwoPoint rslt = {-1, -1, INF};
    for (int i = st; i <= en; i++) {
        for (int j = i + 1; j <= en; j++) {
            ll curDist = getLength2(pIdx[i], pIdx[j]);
            if (rslt.dist > curDist) {
                rslt.p1Idx = pIdx[i];
                rslt.p2Idx = pIdx[j];
                rslt.dist = curDist;
            }
        }
    }
    return rslt;
}

int isLeftOfMidPoint(int targetIdx, int midIdx) {
    if (point[targetIdx].x < point[midIdx].x) return 1;
    if (point[midIdx].x < point[targetIdx].x) return 0;
    if (point[targetIdx].y <= point[midIdx].y) return 1;
    else return 0;
}

TwoPoint findClosestPair(const int xSortIdx[], const int ySortIdx[], int st, int en) {
    if (en - st + 1 <= 3) return naiveLength(xSortIdx, st, en);

    int mid = (st + en) / 2;
    int midPointIdx = xSortIdx[mid];

    int* ySortLeft = (int*) malloc(sizeof(int) * (mid - st + 1));
    int* ySortRight = (int*) malloc(sizeof(int) * (en - mid));
    int leftIdx = 0, rightIdx = 0;
    for (int i = 0; i < (en - st + 1); i++)
        if (isLeftOfMidPoint(ySortIdx[i], midPointIdx) && leftIdx <= mid - st)
            ySortLeft[leftIdx++] = ySortIdx[i];
        else ySortRight[rightIdx++] = ySortIdx[i];


    TwoPoint leftRec = findClosestPair(xSortIdx, ySortLeft, st, mid);
    TwoPoint rightRec = findClosestPair(xSortIdx, ySortRight, mid + 1, en);
    TwoPoint Result = (leftRec.dist < rightRec.dist ? leftRec : rightRec);

    int* mergePointIdxYSort = (int*) malloc(sizeof(int) * (en - st + 1));
    int mergeCount = 0;
    for (int i = 0; i < (en - st + 1); i++)
        if ((point[ySortIdx[i]].x - point[midPointIdx].x) * (point[ySortIdx[i]].x - point[midPointIdx].x) < Result.dist)
            mergePointIdxYSort[mergeCount++] = ySortIdx[i];

    for (int i = 0; i < mergeCount - 1; i++) {
        int fromIdx = mergePointIdxYSort[i];
        for (int j = i+1; j < mergeCount; j++) {
            int toIdx = mergePointIdxYSort[j];
            if (point[toIdx].y - point[fromIdx].y >= Result.dist) break;
            ll curDist = getLength2(fromIdx, toIdx);
            if (Result.dist > curDist) {
                Result.p1Idx = fromIdx;
                Result.p2Idx = toIdx;
                Result.dist = curDist;
            }
        }
    }
    free(ySortLeft); free(ySortRight); free(mergePointIdxYSort);
    return Result;
}

int checkDuplication(const int xSortIdx[], int len) {
    for (int i = 1; i < len; i++)
        if (point[xSortIdx[i-1]].x == point[xSortIdx[i]].x && point[xSortIdx[i-1]].y == point[xSortIdx[i]].y)
            return i;
    return 0;
}

int main() {
    FILE *fp = fopen("input.txt", "r");

    int n; fscanf(fp, "%d", &n);
    point = (Node*) malloc(sizeof(Node)*n);
    for (int i = 0; i < n; i++)
        fscanf(fp, "%lld %lld", &point[i].x, &point[i].y);
    fclose(fp);
    
    int* xSortIdx = (int*) malloc(sizeof(int)*n);
    int* ySortIdx = (int*) malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
        xSortIdx[i] = ySortIdx[i] = i;

    int* mergeTemp = (int*) malloc(sizeof(int) * n);
    mergeSort(xSortIdx, mergeTemp, 0, n-1, cmpX);
    mergeSort(ySortIdx, mergeTemp, 0, n-1, cmpY);
    free(mergeTemp);

    TwoPoint closestPair = {0,0,0};
    clock_t start = clock();

    int duplicationIdx = checkDuplication(xSortIdx, n);
    if (duplicationIdx)
        (closestPair.p1Idx = xSortIdx[duplicationIdx-1]),
        (closestPair.p2Idx = xSortIdx[duplicationIdx]),
        (closestPair.dist = 0);
    else
        closestPair = findClosestPair(xSortIdx, ySortIdx, 0, n-1);

    clock_t end = clock();

    printf("\n[가장 가까운 두 점]\n(%lld, %lld)  <->  (%lld, %lld)\n\n",
        point[closestPair.p1Idx].x, point[closestPair.p1Idx].y, 
        point[closestPair.p2Idx].x, point[closestPair.p2Idx].y);
    printf("[거리]\n%.3lf\n\n", sqrt(closestPair.dist));
    printf("[실행 시간]\n%.3lfs\n", (double)(end - start)/CLOCKS_PER_SEC);

    fp = fopen("output.txt", "w");
    for (int i = 0; i < n; i++)
        fprintf(fp, "%lld\t%lld\t%d\n", point[i].x, point[i].y, (i == closestPair.p1Idx || i == closestPair.p2Idx));
    fclose(fp);

    free(point); free(xSortIdx); free(ySortIdx);
    return 0;
}