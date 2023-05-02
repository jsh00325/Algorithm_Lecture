#include "MySort.h"

void Swap(int* a, int* b) {
    int temp = *a;
    (*a) = (*b);
    (*b) = temp;
}

void InsertionSort(int arr[], int len) {
    for (int i = 1; i < len; i++) {
        int cur = arr[i];   // �����ϰ��� �ϴ� �迭�� ��
        int j = i;          // arr[i]�� ���� ���� �Ǿ�� �ϴ� ��ġ
        while (j > 0 && arr[j-1] > arr[i]) j--;
        memmove(&arr[j+1], &arr[j], sizeof(int)*(i-j));
        arr[j] = cur;
    }
}

void BubbleSort(int arr[], int len) {
    for (int j = len-1; j >= 1; j--)    // �� �ܰ躰�� ū ���� ��ġ�ؾ� �� index
        for (int i = 0; i < j; i++)     // �� ������ ���� index
            if (arr[i] > arr[i+1]) Swap(&arr[i], &arr[i+1]);
}

void QuickSort(int arr[], int st, int en) {
    if (st >= en) return;
    int PivotIdx = _SetPivot(arr, st, en);
    QuickSort(arr, st, PivotIdx-1);
    QuickSort(arr, PivotIdx+1, en);
}
/** [st, en]�������� ���� ���� ���� pivot���� ���ϰ�
 *  pivot���� ���� ���� ����, ū ���� ���������� ������ ���� */
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