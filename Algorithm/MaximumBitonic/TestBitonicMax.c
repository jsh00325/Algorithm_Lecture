#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** �̺�Ž������ �ش� ������ ������ ��ȯ
 *  @param a ���ϰ����ϴ� ������� ����
 *  @param len ������ ����
 *  @return [-1] �ش� ������ ������ ���������� ��
 *          [0] �ش� ������ �ش��� ��
 *          [1] �ش� ������ ������ ���Ҽ����� �� */
int check(int a[], int len, int cur_idx) {
    if (cur_idx == 0) return -1;
    if (cur_idx == len-1) return 1;

    if (a[cur_idx - 1] < a[cur_idx] && a[cur_idx] < a[cur_idx + 1]) return -1;
    if (a[cur_idx - 1] > a[cur_idx] && a[cur_idx] > a[cur_idx + 1]) return 1;
    if (a[cur_idx - 1] < a[cur_idx] && a[cur_idx] > a[cur_idx + 1]) return 0;
}

/** ������� ����(�����ϴٰ� �����ϴ� ����)���� �ִ��� ã�� �˰���
 *  @details �̺�Ž���� �̿��Ͽ� ���ϱ� ������ �ð����⵵�� O(lgN)�̴�.
 *  @param a ���ϰ����ϴ� ������� ����
 *  @param len ������ ����
 *  @return ���������� �ִ�*/
int GetMax(int a[], int len) {

    int left = 0, right = len - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        // printf("[%d, %d] - mid : %d\n", left, right, mid);
        int rslt = check(a, len, mid);

        if (rslt == 0)
            return a[mid];
        else if (rslt == -1)
            left = mid + 1;
        else 
            right = mid - 1;
    }
}

int main() {
    FILE *fp;
    /* �Է� ������ ����
        t n                 <= �׽�Ʈ���̽��� ��, ������ ����
        a1 a2 ... an        
        a1 a2 ... an        <= �׽�Ʈ ���̽� �� ����
            ...
        a1 a2 ... an
    */
    fp = fopen("input.txt", "r");

    int t, n;
    fscanf(fp, "%d %d", &t, &n);

    for (int tc = 1; tc <= t; tc++) {
        int* arr = (int*) malloc(sizeof(int)*n);
        for (int i = 0; i < n; i++) fscanf(fp, "%d", &arr[i]);

        
        clock_t start = clock();
        int rslt = GetMax(arr, n);
        clock_t end = clock();

        printf("[#%02d] �ִ� : %d (%.3lfs)\n", tc, rslt, (double)(end - start) / CLOCKS_PER_SEC);

        free(arr);
    }
    fclose(fp);
    return 0;
}