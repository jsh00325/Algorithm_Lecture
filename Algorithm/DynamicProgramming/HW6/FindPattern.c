#include <stdio.h>
#include <stdlib.h>

/** [n][n]ũ���� int�迭�� �����Ҵ�޾�, �� �ּҸ� ��ȯ
 *  @param n ��������ϴ� ���簢�� �迭�� �ʺ�
 *  @return [n][n]ũ���� �迭 �ּ� */
int** create_N_by_N_array(int n) {
    int** newArray = (int**) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        newArray[i] = (int*) malloc(sizeof(int) * n);
    return newArray;
}

/* �ּڰ��� ��ȯ */
int getMin(int a, int b) {
    return (a < b ? a : b);
}

/** �����Ҵ� ���� ������ �迭 free ��Ű��
 *  @param arr �Ҵ��� �����ϰ� ���� �迭 �ּ�
 *  @param n ������ �迭�� ũ�� */
void free_2D_array(int** arr, int n) {
    for (int i = 0; i < n; i++) free(arr[i]);
    free(arr);
}

/* ��������� ���� ������ ���� ���� ����ϴ� �Լ� */
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

/** dp ���̺��� ����Ž���ϸ鼭, ���� �� �ִ� �ִ� ũ���� üũ���� ã�� �Լ�
 *  @param arr ó�� �Է¹��� ��ü ����
 *  @param dp ä���� dp ���̺�
 *  @param n �迭�� �ʺ� */
void solve(int** arr, int*** dp, int n) {
    // ����Ž���ϸ鼭 �ִ� ����
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
    printf("�ִ� üũ������ �ʺ� : %d\n", mxVal);
    printf("���� : (%d, %d)���� (%d, %d)����\n\n", mxI - mxVal + 1, mxJ - mxVal + 1, mxI, mxJ);
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

    // DP ���̺� ä���
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