#include <stdio.h>
#include <stdlib.h>

/** [n][n]크기의 int배열을 동적할당받아, 그 주소를 반환
 *  @param n 만들고자하는 정사각형 배열의 너비
 *  @return [n][n]크기의 배열 주소 */
int** create_N_by_N_array(int n) {
    int** newArray = (int**) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        newArray[i] = (int*) malloc(sizeof(int) * n);
    return newArray;
}

/* 최솟값을 반환 */
int getMin(int a, int b) {
    return (a < b ? a : b);
}

/** 동적할당 받은 이차원 배열 free 시키기
 *  @param arr 할당을 해제하고 싶은 배열 주소
 *  @param n 이차원 배열의 크기 */
void free_2D_array(int** arr, int n) {
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
}

/* 결과적으로 얻은 범위를 보기 좋게 출력하는 함수 */
void print_maxRange(int** arr, int n, int stI, int stJ, int enI, int enJ) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", arr[i][j]);
        printf(" %s\t", (i == n/2 ? "=>" : ""));
        for (int j = 0; j < n; j++)
            printf("%c ", (stI < i && i <= enI && stJ < j && j <= enJ) ? (char)(arr[i][j] + '0') : '*');
        printf("\n");
    }
}

/** dp 테이블을 완전탐색하면서, 만들 수 있는 최대 크기의 체크패턴 찾는 함수
 *  @param arr 처음 입력받은 전체 상태
 *  @param dp 채워진 dp 테이블
 *  @param n 배열의 너비 */
void solve(int** arr, int*** dp, int n) {
    // 완전탐색하면서 최댓값 갱신
    int mxVal = 0, mxI = 0, mxJ = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int type = 0; type <= 1; type++) {
                if (mxVal < dp[type][i][j]) {
                    mxVal = dp[type][i][j];
                    mxI = i;
                    mxJ = j;
                }
            }
        }
    }
    printf("최대 체크무늬의 너비 : %d\n", mxVal);
    printf("범위 : (%d, %d)에서 (%d, %d)까지\n\n", mxI - mxVal + 1, mxJ - mxVal + 1, mxI, mxJ);
    print_maxRange(arr, n, mxI - mxVal, mxJ - mxVal, mxI, mxJ);
}

int main() {
    FILE *fp = fopen("input.txt", "r");

    int n;
    fscanf(fp, "%d", &n);

    int** arr = create_N_by_N_array(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(fp, "%d\n", &arr[i][j]);

    int*** dp = (int***) malloc(sizeof(int**) * 2);
    dp[0] = create_N_by_N_array(n);
    dp[1] = create_N_by_N_array(n);

    // base condition
    for (int type = 0; type <= 1; type++) {
        for(int i = 0; i < n; i++)
            dp[type][i][0] = (arr[i][0] == type);
        for (int j = 1; j < n; j++)
            dp[type][0][j] = (arr[0][j] == type);
    }

    // DP 테이블 채우기
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            for (int type = 0; type <= 1; type++) {
                if (arr[i][j] != type) dp[type][i][j] = 0;
                else {
                    int min_width = n+1;
                    min_width = getMin(min_width, dp[type][i-1][j-1]);
                    min_width = getMin(min_width, dp[!type][i][j-1]);
                    min_width = getMin(min_width, dp[!type][i-1][j]);
                    dp[type][i][j] = min_width + 1;
                }
            }
        }
    }

    solve(arr, dp, n);

    fclose(fp);
    free_2D_array(arr, n);
    free_2D_array(dp[0], n); free_2D_array(dp[1], n);
    free(dp);
}