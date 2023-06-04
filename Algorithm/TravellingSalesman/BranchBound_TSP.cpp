#include <bits/stdc++.h>
using namespace std;
const int INF = 0x7fffffff;

typedef struct {
    vector<int> tour;   // �湮�� ������ ����
    int bound;          // ������
    int lastV;          // ���������� �湮�� ����
    int visit;          // �湮 ������ ��Ʈ����ŷ���� ����
} NODE;
// �������� ������������ �����ϱ� ���� ���� ����ü
struct cmp {
    bool operator() (NODE& a, NODE& b) {
        return a.bound > b.bound;
    }
};

int n, bestValue;
vector<int> bestTour;
vector<vector<int>> edge;
priority_queue<NODE, vector<NODE>, cmp> pq;

// �б� �������� �̿��Ͽ� TSP �ذ�
void branch_bound();
// �־��� ���¿����� ����� ���̸� ���
int get_length(NODE& cur);
// �湮�� ���� ������ ���� ���������� �湮���θ� ä����
void set_visit(int** visit, vector<int>& tour);
// �־��� ���¿����� �������� ���
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
    
    printf("[ �б� �������� �̿��� TSP ]\n");
    clock_t start = clock();
    branch_bound();
    clock_t end = clock();
    printf("\n��� : %d, �ð� : %.3lfs\n", bestValue, (double)(end - start)/CLOCKS_PER_SEC);
}

void branch_bound() {
    bestValue = INF;
    NODE initNode = {{0}, 0, 0, 1};
    initNode.bound = get_bound(initNode);
    pq.push(initNode);
    while (!pq.empty()) {
        NODE curNode = pq.top(); pq.pop();
        // �������� ���� �������� ũ�ų� ���� ��� -> �������� �ʱ� ������ �н�
        if (curNode.bound >= bestValue) continue;

        // ���� ��� ������ �湮�߰�, �������� �������� ���� ��
        if (curNode.visit == (1 << n) - 1) {
            if (edge[curNode.lastV][0] == 0) continue;
            curNode.tour.push_back(0);

            // ���� ��κ��� ���ٸ� ����
            int curLength = get_length(curNode);
            if (bestValue > curLength) {
                bestValue = curLength;
                bestTour = curNode.tour;
            }
            continue;
        }

        for (int nxtV = 0; nxtV < n; nxtV++) {
            // ������ ���ų� �̹� �湮�� ������ �н�
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

    // ���� ��� ���
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
    // ���������� �湮���θ� �����ϴ� ������ �迭
    int** visit = (int**) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        visit[i] = (int*) malloc(sizeof(int) * n);
        memset(visit[i], 0, sizeof(int) * n);
    }
    set_visit(visit, cur.tour);

    for (int curV = 0; curV < n; curV++) {
        // ���� ����(curV)�� �����ų� ������ ������ �� Ȯ��
        int curVisitCount = 0;
        for (int nxtV = 0; nxtV < n; nxtV++)
            if (visit[curV][nxtV]) curVisitCount++, result += edge[curV][nxtV];

        // 2�� �̸��� ��� 2���� �ǵ��� ��� �ּڰ��� ������ ����
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