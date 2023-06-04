#include <bits/stdc++.h>
using namespace std;
const int INF = 0x7fffffff;

typedef struct {
    vector<int> tour;   // 방문한 정점의 순서
    int bound;          // 한정값
    int lastV;          // 마지막으로 방문한 정점
    int visit;          // 방문 정보를 비트마스킹으로 저장
} NODE;
// 한정값을 오름차순으로 정렬하기 위한 정렬 구조체
struct cmp {
    bool operator() (NODE& a, NODE& b) {
        return a.bound > b.bound;
    }
};

int n, bestValue;
vector<int> bestTour;
vector<vector<int>> edge;
priority_queue<NODE, vector<NODE>, cmp> pq;

// 분기 한정법을 이용하여 TSP 해결
void branch_bound();
// 주어진 상태에서의 경로의 길이를 계산
int get_length(NODE& cur);
// 방문한 정점 정보를 통해 정점끼리의 방문여부를 채워줌
void set_visit(int** visit, vector<int>& tour);
// 주어진 상태에서의 한정값을 계산
int get_bound(NODE& cur);

int main() {
	freopen("input.txt", "r", stdin);
    cin >> n;
    edge.resize(n);
    for (int i = 0; i < n; i++) {
        edge[i].resize(n);
        for (int j = 0; j < n; j++)
            cin >> edge[i][j];
    }
    
    printf("[ 분기 한정법을 이용한 TSP ]\n");
    clock_t start = clock();
    branch_bound();
    clock_t end = clock();
    printf("\n경로 : %d, 시간 : %.3lfs\n", bestValue, (double)(end - start)/CLOCKS_PER_SEC);
}

void branch_bound() {
    bestValue = INF;
    NODE initNode = {{0}, 0, 0, 1};
    initNode.bound = get_bound(initNode);
    pq.push(initNode);
    while (!pq.empty()) {
        NODE curNode = pq.top(); pq.pop();
        // 한정값이 현재 최적보다 크거나 같은 경우 -> 유망하지 않기 때문에 패스
        if (curNode.bound >= bestValue) continue;

        // 현재 모든 정점을 방문했고, 한정값이 최적보다 작을 때
        if (curNode.visit == (1 << n) - 1) {
            if (edge[curNode.lastV][0] == 0) continue;
            curNode.tour.push_back(0);

            // 최적 경로보다 적다면 갱신
            int curLength = get_length(curNode);
            if (bestValue > curLength) {
                bestValue = curLength;
                bestTour = curNode.tour;
            }
            continue;
        }

        for (int nxtV = 0; nxtV < n; nxtV++) {
            // 간선이 없거나 이미 방문한 정점은 패스
            if (edge[curNode.lastV][nxtV] == 0) continue;
            if ((curNode.visit >> nxtV) & 1) continue;

            NODE nxtNode;
            nxtNode.tour = vector<int>(curNode.tour);
            nxtNode.tour.push_back(nxtV);
            nxtNode.lastV = nxtV;
            nxtNode.visit = curNode.visit | (1 << nxtV);
            nxtNode.bound = get_bound(nxtNode);

            if (nxtNode.bound < bestValue)
                pq.push(nxtNode);
        }
    }

    // 최적 경로 출력
    for (auto it = bestTour.begin(); it != bestTour.end(); it++)
        cout << (char)((*it) + 'A') << ' ';
}

int get_length(NODE& cur) {
    int length = 0;
    for (auto it = cur.tour.begin() + 1; it != cur.tour.end(); it++)
        length += edge[*(it-1)][*it];
    return length;
}

void set_visit(int** visit, vector<int>& tour) {
    for (auto it = tour.begin() + 1; it != tour.end(); it++)
        visit[*(it-1)][*it] = visit[*it][*(it-1)] = true;
}

int get_bound(NODE& cur) {
    int result = 0;
    // 정점끼리의 방문여부를 저장하는 이차원 배열
    int** visit = (int**) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        visit[i] = (int*) malloc(sizeof(int) * n);
        memset(visit[i], 0, sizeof(int) * n);
    }
    set_visit(visit, cur.tour);

    for (int curV = 0; curV < n; curV++) {
        // 현재 정점(curV)로 들어오거나 나가는 간선의 수 확인
        int curVisitCount = 0;
        for (int nxtV = 0; nxtV < n; nxtV++)
            if (visit[curV][nxtV]) curVisitCount++, result += edge[curV][nxtV];

        // 2개 미만일 경우 2개가 되도록 계속 최솟값인 간선을 뽑음
        while (curVisitCount < 2) {
            int minV = -1;
            for (int nxtV = 0; nxtV < n; nxtV++) {
                if (edge[curV][nxtV] == 0) continue;
                if (visit[curV][nxtV]) continue;
                if (minV == -1 || edge[curV][minV] > edge[curV][nxtV])
                    minV = nxtV;
            }
            visit[curV][minV] = true;
            curVisitCount++, result += edge[curV][minV];
        }
    }
    for (int i = 0; i < n; i++) free(visit[i]);
    free(visit);
    return result / 2;
}