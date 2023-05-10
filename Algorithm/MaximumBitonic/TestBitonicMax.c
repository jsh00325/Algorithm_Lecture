#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** 이분탐색에서 해당 지점의 정보를 반환
 *  @param a 구하고자하는 바이토닉 수열
 *  @param len 수열의 길이
 *  @return [-1] 해당 지점의 수열이 증가수열일 때
 *          [0] 해당 지점이 극댓값일 때
 *          [1] 해당 지점의 수열이 감소수열일 때 */
int check(int a[], int len, int cur_idx) {
    if (cur_idx == 0) return -1;
    if (cur_idx == len-1) return 1;

    if (a[cur_idx - 1] < a[cur_idx] && a[cur_idx] < a[cur_idx + 1]) return -1;
    if (a[cur_idx - 1] > a[cur_idx] && a[cur_idx] > a[cur_idx + 1]) return 1;
    if (a[cur_idx - 1] < a[cur_idx] && a[cur_idx] > a[cur_idx + 1]) return 0;
}

/** 바이토닉 수열(증가하다가 감소하는 수열)에서 최댓값을 찾는 알고리즘
 *  @details 이분탐색을 이용하여 구하기 때문에 시간복잡도는 O(lgN)이다.
 *  @param a 구하고자하는 바이토닉 수열
 *  @param len 수열의 길이
 *  @return 수열에서의 최댓값*/
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
    /* 입력 파일의 형식
        t n                 <= 테스트케이스의 수, 수열의 길이
        a1 a2 ... an        
        a1 a2 ... an        <= 테스트 케이스 별 수열
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

        printf("[#%02d] 최댓값 : %d (%.3lfs)\n", tc, rslt, (double)(end - start) / CLOCKS_PER_SEC);

        free(arr);
    }
    fclose(fp);
    return 0;
}