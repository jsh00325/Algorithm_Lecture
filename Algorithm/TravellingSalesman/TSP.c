#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int INF = 0x7fffffff;
int n;                  // ������ ��
int** adjacency_edge;   // ���� ��� ������ ���� ����

int* tour;
int* bestSolution;
int bestValue;
void backtracking();
/** ��Ʈ��ŷ�� �̿��Ͽ� ���ǿ���ȸ ���� �ذ�
 *  @param cur ���� ���������� �湮�� ������ ��ȣ
 *  @param dist ���� ����� ����
 *  @param tourCount ���� �湮�� ������ ��
 *  @param visit ��Ʈ����ŷ�� �̿��Ͽ� ���� �湮�� ������ ǥ��
 *  @return �ִ� ����� ���� ��ȯ(�ִ� ��θ� �̷�� ���� ������ ��) */
void backtrackingTSP(int cur, int dist, int tourCount, int visit);

int** dp;
void dynamicProgramming();
/** ������ȹ���� �̿��Ͽ� ���ǿ� ��ȸ ���� �ذ�
 *  @param cur ���� ���������� �湮�� ������ ��ȣ
 *  @param visit ��Ʈ����ŷ�� �̿��Ͽ� ���� �湮�� ������ ǥ��
 *  @return ���������� cur�� ������ �湮���� ���� ���� �� ��ȯ */
int dynamicProgrammingTSP(int cur, int visit);

int main() {
    FILE *fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &n);
    adjacency_edge = (int**) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        adjacency_edge[i] = (int*) malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
            fscanf(fp, "%d", &adjacency_edge[i][j]);
    }

    // �� ��������� ��� ����� �ð� ���
    // backtracking();
    dynamicProgramming();

    for (int i = 0; i < n; i++) free(adjacency_edge[i]);
    free(adjacency_edge);
}

void backtracking() {
    tour = (int*) malloc(sizeof(int) * (n+1));
    bestSolution = (int*) malloc(sizeof(int) * (n+1));
    bestValue = INF;
    tour[0] = 0;
    printf("[ ��Ʈ��ŷ�� �̿��� TSP ]\n");
    clock_t start = clock();
    backtrackingTSP(0, 0, 1, 1);
    clock_t end = clock();
    for (int i = 0; i <= n; i++) printf("%c ", bestSolution[i] + 'A');
    printf("\n��� : %d, �ð� : %.3lfs\n", bestValue, (double)(end - start)/CLOCKS_PER_SEC);
    free(tour); free(bestSolution);
}
void backtrackingTSP(int cur, int dist, int tourCount, int visit) {
    // ��� ������ �湮���� ��
    if (visit == (1 << n) - 1) {
        // ������ �������� ������(0�� ����)���� ���� ������ ���� ���
        if (adjacency_edge[cur][0] == 0) return;
        tour[n] = 0;
        dist += adjacency_edge[cur][0];

        // ���� ��ΰ� ������ ���
        if (dist < bestValue) {
            bestValue = dist;
            for (int i = 0; i <= tourCount; i++)
                bestSolution[i] = tour[i];
        }
        return;
    }
    // ����ġ��
    if (dist >= bestValue) return;

    for (int nxt = 0; nxt < n; nxt++) {
        // nxt�� �������� ���� ������ ���� ���
        if (adjacency_edge[cur][nxt] == 0) continue;
        // nxt���� �̹� �湮�� ������ ���(��Ʈ����ŷ)
        if ((visit >> nxt) & 1) continue;

        // tour�� ���� ���� �ְ� backtracking
        tour[tourCount] = nxt;
        backtrackingTSP(nxt, dist + adjacency_edge[cur][nxt], tourCount+1, visit | (1 << nxt));
    }
}


void dynamicProgramming() {
    dp = (int**) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        dp[i] = (int*) malloc(sizeof(int) * (1 << n));
        memset(dp[i], -1, sizeof(int) * (1 << n));
    }

    printf("\n[ ���� ��ȹ���� ������ TSP ]\n");
    clock_t start = clock();
    int result = dynamicProgrammingTSP(0, 1);
    clock_t end = clock();
    printf("��� : %d, �ð� : %.3lfs\n", result, (double)(end - start)/CLOCKS_PER_SEC);
    for (int i = 0; i < n; i++) free(dp[i]);
    free(dp);
}
int get_min(int a, int b) { return a < b ? a : b; }
int dynamicProgrammingTSP(int cur, int visit) {
    if (visit == (1 << n) - 1) { // ��� ���� �湮 �Ϸ�
        if (adjacency_edge[cur][0] == 0) return INF;    // ���ư��� ��� ����
        else return adjacency_edge[cur][0];         // ���ư��� ����� ���� ��ȯ
    }
    
    // �̹� ���� ���� ���Ǿ� �ִٸ�, �� ���� �ٷ� ���
    if (dp[cur][visit] != -1) return dp[cur][visit];

    dp[cur][visit] = INF;
    for (int nxt = 0; nxt < n; nxt++) {
        // ������ ���� ã�� ���
        if (adjacency_edge[cur][nxt] == 0) continue;
        if ((visit >> nxt) & 1) continue;
        
        // ������ ���������� ��갪�� �� �۴ٸ� ����
        dp[cur][visit] = get_min(dp[cur][visit],
            dynamicProgrammingTSP(nxt, visit | (1 << nxt)) + adjacency_edge[cur][nxt]);
    }
    return dp[cur][visit];
}