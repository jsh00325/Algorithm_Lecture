#include "MySort.h"

void Swap(int* a, int* b) {
    int temp = *a;
    (*a) = (*b);
    (*b) = temp;
}

void InsertionSort(int arr[], int len) {
    for (int i = 1; i < len; i++) {
        int cur = arr[i];   // 삽입하고자 하는 배열의 값
        int j = i;          // arr[i]의 값이 삽입 되어야 하는 위치
        while (j > 0 && arr[j-1] > arr[i]) j--;
        memmove(&arr[j+1], &arr[j], sizeof(int)*(i-j));
        arr[j] = cur;
    }
}

void BubbleSort(int arr[], int len) {
    for (int j = len-1; j >= 1; j--)    // 각 단계별로 큰 값이 위치해야 할 index
        for (int i = 0; i < j; i++)     // 비교 연산의 시작 index
            if (arr[i] > arr[i+1]) Swap(&arr[i], &arr[i+1]);
}

void QuickSort(int arr[], int st, int en) {
    if (st >= en) return;
    int PivotIdx = _SetPivot(arr, st, en);
    QuickSort(arr, st, PivotIdx-1);
    QuickSort(arr, PivotIdx+1, en);
}
/** [st, en]범위에서 가장 앞의 값을 pivot으로 정하고
 *  pivot보다 작은 값은 왼쪽, 큰 값은 오른쪽으로 오도록 변경 */
int _SetPivot(int arr[], int st, int en) {
    int pivotValue = arr[st];
    int l = st + 1, r = en;
    while (l <= r) {
        while (pivotValue >= arr[l] && l < r) l++;
        while (pivotValue <= arr[r] && l <= r) r--;

        if (l < r) Swap(&arr[l], &arr[r]);
        else break;
    }
    Swap(&arr[st], &arr[r]);
    return r;
}