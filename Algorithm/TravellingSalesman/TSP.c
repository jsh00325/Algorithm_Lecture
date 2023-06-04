#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int INF = 0x7fffffff;
int n;                  // 정점의 수
int** adjacency_edge;   // 인접 행렬 형태의 간선 정보

int* tour;
int* bestSolution;
int bestValue;
void backtracking();
/** 백트래킹을 이용하여 외판원순회 문제 해결
 *  @param cur 가장 마지막으로 방문한 정점의 번호
 *  @param dist 현재 경로의 길이
 *  @param tourCount 현재 방문한 정점의 수
 *  @param visit 비트마스킹을 이용하여 현재 방문한 정점들 표시
 *  @return 최단 경로의 길이 반환(최단 경로를 이루는 정점 순서는 모름) */
void backtrackingTSP(int cur, int dist, int tourCount, int visit);

int** dp;
void dynamicProgramming();
/** 동적계획법을 이용하여 외판원 순회 문제 해결
 *  @param cur 가장 마지막으로 방문한 정점의 번호
 *  @param visit 비트마스킹을 이용하여 현재 방문한 정점들 표시
 *  @return 마지막으로 cur번 정점을 방문했을 때의 최적 해 반환 */
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

    // 각 방법에서의 계산 결과와 시간 출력
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
    printf("[ 백트래킹을 이용한 TSP ]\n");
    clock_t start = clock();
    backtrackingTSP(0, 0, 1, 1);
    clock_t end = clock();
    for (int i = 0; i <= n; i++) printf("%c ", bestSolution[i] + 'A');
    printf("\n경로 : %d, 시간 : %.3lfs\n", bestValue, (double)(end - start)/CLOCKS_PER_SEC);
    free(tour); free(bestSolution);
}
void backtrackingTSP(int cur, int dist, int tourCount, int visit) {
    // 모든 정점을 방문했을 때
    if (visit == (1 << n) - 1) {
        // 마지막 정점에서 시작점(0번 정점)으로 가는 간선이 없는 경우
        if (adjacency_edge[cur][0] == 0) return;
        tour[n] = 0;
        dist += adjacency_edge[cur][0];

        // 현재 경로가 최적인 경우
        if (dist < bestValue) {
            bestValue = dist;
            for (int i = 0; i <= tourCount; i++)
                bestSolution[i] = tour[i];
        }
        return;
    }
    // 가지치기
    if (dist >= bestValue) return;

    for (int nxt = 0; nxt < n; nxt++) {
        // nxt번 정점으로 가는 간선이 없는 경우
        if (adjacency_edge[cur][nxt] == 0) continue;
        // nxt번이 이미 방문한 정점인 경우(비트마스킹)
        if ((visit >> nxt) & 1) continue;

        // tour에 현재 정점 넣고 backtracking
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

    printf("\n[ 동적 계획법을 적용한 TSP ]\n");
    clock_t start = clock();
    int result = dynamicProgrammingTSP(0, 1);
    clock_t end = clock();
    printf("경로 : %d, 시간 : %.3lfs\n", result, (double)(end - start)/CLOCKS_PER_SEC);
    for (int i = 0; i < n; i++) free(dp[i]);
    free(dp);
}
int get_min(int a, int b) { return a < b ? a : b; }
int dynamicProgrammingTSP(int cur, int visit) {
    if (visit == (1 << n) - 1) { // 모든 정점 방문 완료
        if (adjacency_edge[cur][0] == 0) return INF;    // 돌아가는 경로 없음
        else return adjacency_edge[cur][0];         // 돌아가는 경로의 길이 반환
    }
    
    // 이미 현재 값이 계산되어 있다면, 그 값을 바로 사용
    if (dp[cur][visit] != -1) return dp[cur][visit];

    dp[cur][visit] = INF;
    for (int nxt = 0; nxt < n; nxt++) {
        // 인접한 정점 찾아 계산
        if (adjacency_edge[cur][nxt] == 0) continue;
        if ((visit >> nxt) & 1) continue;
        
        // 인접한 정점에서의 계산값이 더 작다면 갱신
        dp[cur][visit] = get_min(dp[cur][visit],
            dynamicProgrammingTSP(nxt, visit | (1 << nxt)) + adjacency_edge[cur][nxt]);
    }
    return dp[cur][visit];
}