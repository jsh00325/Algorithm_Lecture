#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef long long ll;

// ��ǥ ������ ���� ����ü
typedef struct {
    ll x, y;
} Node;

// �ֱ��� ������ ������ ���� ����ü
typedef struct {
    int p1Idx, p2Idx; // �ּ� �Ÿ��� ���� ������ �ε���
    ll dist;    // �� �������� �Ÿ��� ����
} TwoPoint;

const ll INF = 9*1e18;
Node* point = NULL;

/** ���ĵ� �� �迭�� ��ġ�� �Լ�
 *  @param arr ������ �迭
 *  @param temp ���ս� ����� �ӽ� ���� �迭
 *  @param st~mid ������ ó�� �迭�� ���� 
 *  @param mid~en ������ �ι�° �迭�� ���� 
*   @param cmp ���Լ� */
void merge(int arr[], int temp[], int st, int mid, int en, int (*cmp)(int, int)) {
    int i = st, j = mid+1, k = st;
    while (i <= mid && j <= en)
        if (cmp(arr[i], arr[j]) <= 0) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= en) temp[k++] = arr[j++];
    for (int x = st; x <= en; x++) arr[x] = temp[x];
}
/** ���� ������ �ϱ� ���� ����Լ�
 *  @param arr ������ �迭
 *  @param temp ���ս� ����� �ӽ� ���� �迭
 *  @param st~en �����ϰ��� �ϴ� arr�� ���� 
*   @param cmp ���Լ� */
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
/* x��ǥ������ �����ϰ� ���ٸ� y��ǥ������ ������������ �����ϵ��� �ϴ� ���Լ� */
int cmpX(int a, int b) {
    if (point[a].x == point[b].x) return cmp(point[a].y, point[b].y);
    else return cmp(point[a].x, point[b].x);
}
/* y��ǥ������ �����ϰ� ���ٸ� x��ǥ������ ������������ �����ϵ��� �ϴ� ���Լ� */
int cmpY(int a, int b) {
    if (point[a].y == point[b].y) return cmp(point[a].x, point[b].x);
    else return cmp(point[a].y, point[b].y);
}

ll getMin(ll a, ll b) { return (a < b ? a : b); }

/* �� ���� �ε����� ���� ���������� �Ÿ��� ������ ��ȯ */
ll getLength2(int aIdx, int bIdx) {
    return (point[aIdx].x - point[bIdx].x)*(point[aIdx].x - point[bIdx].x) 
                + (point[aIdx].y - point[bIdx].y)*(point[aIdx].y - point[bIdx].y);
}
/** Ư�� ���������� ���� ���� �Ÿ��� ���Ʈ������ Ȯ��
 *  @param pIdx ������ ������ �ε����� ���� �迭
 *  @param st~en ������ ������ pIdx������ ����
 *  @return �ֱ��� ������ ������ ���� ����ü ��ȯ */
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

/** �ش� ���� ������ ������ ���ʿ� �����ϴ��� Ȯ���ϴ� �Լ�
 *  @param targetIdx Ȯ���ϰ��� �ϴ� ���� �ε���
 *  @param midIdx ������ ������ ������ �Ǵ� �߾����� �ε���
 *  @return �ش� ���� ���� �����̸� 1, �ƴϸ� 0�� ��ȯ */
int isLeftOfMidPoint(int targetIdx, int midIdx) {
    if (point[targetIdx].x < point[midIdx].x) return 1;
    if (point[midIdx].x < point[targetIdx].x) return 0;
    if (point[targetIdx].y < point[midIdx].y) return 1;
    else return 0;
}

/** �ֱ��� ���� ���� ã�� �� ���� ��ȯ�ϴ� �Լ� - �������� ���
 *  @param xSortIdx x��ǥ�� �������� ���ĵ� ������ �ε��� �迭
 *  @param ySortIdx y��ǥ�� �������� ���ĵ� ������ �ε��� �迭
 *  @param st~en ã�����ϴ� ������ xSortIdx������ ����
 *  @return �ֱ��� ������ ������ ��ȯ */
TwoPoint findClosestPair(const int xSortIdx[], const int ySortIdx[], int st, int en) {
    if (en - st + 1 <= 3) return naiveLength(xSortIdx, st, en);

    int mid = (st + en) / 2;
    int midPointIdx = xSortIdx[mid];

    // �¿� ������ ���ϴ� ���� �����ִ� ���� -> ���� �迭������ y��ǥ�� �������� �� ���Ļ��� ����
    int* ySortLeft = (int*) malloc(sizeof(int) * (mid - st + 1));
    int* ySortRight = (int*) malloc(sizeof(int) * (en - mid));
    int leftIdx = 0, rightIdx = 0;
    for (int i = 0; i < (en - st + 1); i++)
        if (isLeftOfMidPoint(ySortIdx[i], midPointIdx))
            ySortLeft[leftIdx++] = ySortIdx[i];
        else ySortRight[rightIdx++] = ySortIdx[i];

    // ���� �¿� ���������� �ּ������� �޾�, �� ���� �� ���� �ּ��� �Ÿ��� ���� ����
    TwoPoint leftRec = findClosestPair(xSortIdx, ySortLeft, st, mid);
    TwoPoint rightRec = findClosestPair(xSortIdx, ySortRight, mid + 1, en);
    TwoPoint Result = (leftRec.dist < rightRec.dist ? leftRec : rightRec);

    // ������ �� ������ ���� ��� ���� �������� Result.dist��ŭ ������ ������ ������
    //      -> y��ǥ�� �������� �� ���� ���� ������.
    int* mergePointIdxYSort = (int*) malloc(sizeof(int) * (en - st + 1));
    int mergeCount = 0;
    for (int i = 0; i < (en - st + 1); i++)
        if ((point[ySortIdx[i]].x - point[midPointIdx].x) * (point[ySortIdx[i]].x - point[midPointIdx].x) < Result.dist)
            mergePointIdxYSort[mergeCount++] = ySortIdx[i];

    // ���� �����ȿ� �ִ� ��������� �Ÿ��� Ȯ���ϸ� Result.dist���� �������� �ִٸ� ����
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

/** �ߺ��� ���� �ִ��� ã�� �Լ�
 *  @details �̹� x��ǥ�� �������� ���ĵ� �Լ��� Ž���ϹǷ� O(n)
 *  @param xSortIdx x��ǥ�� �������� ���ĵ� ������ �ε��� �迭
 *  @param len xSortIdx�� ����
 *  @return �ߺ��̸� 1, �ߺ��� ������ 0 ��ȯ */
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
    
    // ������ ���� x��ǥ, y��ǥ�� �������� �����ϱ� ����, ���� �ε����� �����ϴ� �迭
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
    if (duplicationIdx) // �ߺ��� �ִٸ� �翬�� �ֱ��� ���� �Ÿ��� 0
        (closestPair.p1Idx = xSortIdx[duplicationIdx-1]),
        (closestPair.p2Idx = xSortIdx[duplicationIdx]),
        (closestPair.dist = 0);
    else
        closestPair = findClosestPair(xSortIdx, ySortIdx, 0, n-1);
    clock_t end = clock();

    printf("\n[���� ����� �� ��]\n(%lld, %lld)  <->  (%lld, %lld)\n\n",
        point[closestPair.p1Idx].x, point[closestPair.p1Idx].y, 
        point[closestPair.p2Idx].x, point[closestPair.p2Idx].y);
    printf("[�Ÿ�]\n%.3lf\n\n", sqrt(closestPair.dist));
    printf("[���� �ð�]\n%.3lfs\n", (double)(end - start)/CLOCKS_PER_SEC);

    // ������� Ȯ���ϱ� ���� ������ ������ �������
    fp = fopen("output.txt", "w");
    for (int i = 0; i < n; i++)
        fprintf(fp, "%lld\t%lld\t%d\n", point[i].x, point[i].y, (i == closestPair.p1Idx || i == closestPair.p2Idx));
    fclose(fp);

    free(point); free(xSortIdx); free(ySortIdx);
    return 0;
}