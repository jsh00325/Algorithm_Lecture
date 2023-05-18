#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef long long ll;

// 좌표 정보를 담을 구조체
typedef struct {
    ll x, y;
} Node;

// 최근접 점쌍의 정보를 담은 구조체
typedef struct {
    int p1Idx, p2Idx; // 최소 거리를 갖는 두점의 인덱스
    ll dist;    // 두 점사이의 거리의 제곱
} TwoPoint;

const ll INF = 9*1e18;
Node* point = NULL;

/** 정렬된 두 배열을 합치는 함수
 *  @param arr 병합할 배열
 *  @param temp 병합시 사용할 임시 저장 배열
 *  @param st~mid 병합할 처음 배열의 범위 
 *  @param mid~en 병합할 두번째 배열의 범위 
*   @param cmp 비교함수 */
void merge(int arr[], int temp[], int st, int mid, int en, int (*cmp)(int, int)) {
    int i = st, j = mid+1, k = st;
    while (i <= mid && j <= en)
        if (cmp(arr[i], arr[j]) <= 0) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= en) temp[k++] = arr[j++];
    for (int x = st; x <= en; x++) arr[x] = temp[x];
}
/** 병합 정렬을 하기 위한 재귀함수
 *  @param arr 정렬할 배열
 *  @param temp 병합시 사용할 임시 저장 배열
 *  @param st~en 정렬하고자 하는 arr의 범위 
*   @param cmp 비교함수 */
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
/* x좌표순으로 정렬하고 같다면 y좌표순으로 오름차순으로 정렬하도록 하는 비교함수 */
int cmpX(int a, int b) {
    if (point[a].x == point[b].x) return cmp(point[a].y, point[b].y);
    else return cmp(point[a].x, point[b].x);
}
/* y좌표순으로 정렬하고 같다면 x좌표순으로 오름차순으로 정렬하도록 하는 비교함수 */
int cmpY(int a, int b) {
    if (point[a].y == point[b].y) return cmp(point[a].x, point[b].x);
    else return cmp(point[a].y, point[b].y);
}

ll getMin(ll a, ll b) { return (a < b ? a : b); }

/* 두 점의 인덱스를 통해 두점사이의 거리의 제곱을 반환 */
ll getLength2(int aIdx, int bIdx) {
    return (point[aIdx].x - point[bIdx].x)*(point[aIdx].x - point[bIdx].x) 
                + (point[aIdx].y - point[bIdx].y)*(point[aIdx].y - point[bIdx].y);
}
/** 특정 범위에서의 점들 사이 거리를 브루트포스로 확인
 *  @param pIdx 정렬할 점들의 인덱스를 담은 배열
 *  @param st~en 정렬할 점들의 pIdx에서의 범위
 *  @return 최근접 점쌍의 정보를 담은 구조체 반환 */
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

/** 해당 점이 분할한 영역의 왼쪽에 존재하는지 확인하는 함수
 *  @param targetIdx 확인하고자 하는 점의 인덱스
 *  @param midIdx 영역을 가르는 기준이 되는 중앙점의 인덱스
 *  @return 해당 점이 왼쪽 영역이면 1, 아니면 0을 반환 */
int isLeftOfMidPoint(int targetIdx, int midIdx) {
    if (point[targetIdx].x < point[midIdx].x) return 1;
    if (point[midIdx].x < point[targetIdx].x) return 0;
    if (point[targetIdx].y < point[midIdx].y) return 1;
    else return 0;
}

/** 최근접 점의 쌍을 찾아 그 쌍을 반환하는 함수 - 분할정복 사용
 *  @param xSortIdx x좌표를 기준으로 정렬된 점들의 인덱스 배열
 *  @param ySortIdx y좌표를 기준으로 정렬된 점들의 인덱스 배열
 *  @param st~en 찾고자하는 점들의 xSortIdx에서의 범위
 *  @return 최근접 점쌍의 정보를 반환 */
TwoPoint findClosestPair(const int xSortIdx[], const int ySortIdx[], int st, int en) {
    if (en - st + 1 <= 3) return naiveLength(xSortIdx, st, en);

    int mid = (st + en) / 2;
    int midPointIdx = xSortIdx[mid];

    // 좌우 영역에 속하는 점을 나눠주는 과정 -> 나눈 배열에서도 y좌표를 기준으로 한 정렬상태 유지
    int* ySortLeft = (int*) malloc(sizeof(int) * (mid - st + 1));
    int* ySortRight = (int*) malloc(sizeof(int) * (en - mid));
    int leftIdx = 0, rightIdx = 0;
    for (int i = 0; i < (en - st + 1); i++)
        if (isLeftOfMidPoint(ySortIdx[i], midPointIdx))
            ySortLeft[leftIdx++] = ySortIdx[i];
        else ySortRight[rightIdx++] = ySortIdx[i];

    // 먼저 좌우 영역에서의 최소정보를 받아, 두 영역 중 가장 최소인 거리의 쌍을 저장
    TwoPoint leftRec = findClosestPair(xSortIdx, ySortLeft, st, mid);
    TwoPoint rightRec = findClosestPair(xSortIdx, ySortRight, mid + 1, en);
    TwoPoint Result = (leftRec.dist < rightRec.dist ? leftRec : rightRec);

    // 병합할 때 영역을 나눈 가운데 선을 기준으로 Result.dist만큼 떨어진 점들을 모으기
    //      -> y좌표를 기준으로 한 정렬 상태 유지됨.
    int* mergePointIdxYSort = (int*) malloc(sizeof(int) * (en - st + 1));
    int mergeCount = 0;
    for (int i = 0; i < (en - st + 1); i++)
        if ((point[ySortIdx[i]].x - point[midPointIdx].x) * (point[ySortIdx[i]].x - point[midPointIdx].x) < Result.dist)
            mergePointIdxYSort[mergeCount++] = ySortIdx[i];

    // 병합 영역안에 있는 점들사이의 거리를 확인하며 Result.dist보다 작은값이 있다면 갱신
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

/** 중복된 점이 있는지 찾는 함수
 *  @details 이미 x좌표를 기준으로 정렬된 함수를 탐색하므로 O(n)
 *  @param xSortIdx x좌표를 기준으로 정렬된 점들의 인덱스 배열
 *  @param len xSortIdx의 길이
 *  @return 중복이면 1, 중복이 없으면 0 반환 */
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
    
    // 점들을 각각 x좌표, y좌표를 기준으로 정렬하기 위해, 점의 인덱스를 저장하는 배열
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
    if (duplicationIdx) // 중복이 있다면 당연히 최근접 점의 거리는 0
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

    // 결과값을 확인하기 위해 점들의 정보를 파일출력
    fp = fopen("output.txt", "w");
    for (int i = 0; i < n; i++)
        fprintf(fp, "%lld\t%lld\t%d\n", point[i].x, point[i].y, (i == closestPair.p1Idx || i == closestPair.p2Idx));
    fclose(fp);

    free(point); free(xSortIdx); free(ySortIdx);
    return 0;
}