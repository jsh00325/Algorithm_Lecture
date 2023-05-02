#include "Graph.h"
#include "MST.h"

/** MST를 이루는 간선의 가중치의 합을 반환하는 함수
 *  @details 간선을 이루는 가중치를 모두 더하고, 양방향 간선이기 때문에 2로 나눠줌.
 *  @param MST 구하고자 하는 MST */
int get_MST_cost(Graph* MST) {
    int sum_of_weigh = 0;

    // 정점을 끝까지 순회
    Vertex* curVertex = MST->Vertices;
    while (curVertex != NULL) {
        // 현재 정점과 연결된 모든 간선 순회
        Edge* curEdge = curVertex->AdjacencyList;
        while (curEdge != NULL) {
            // 현재 간선의 가중치 합하기
            sum_of_weigh += curEdge->Weight;
            curEdge = curEdge->Next;
        }
        curVertex = curVertex->Next;
    }

    // MST의 간선은 양방향 간선이기 때문에 중복으로 계산되기 때문에 2로 나눠줌.
    return sum_of_weigh / 2;
}

int main() {
    Graph* city = CreateGraph();
    Graph* MST = CreateGraph();

    // 도시 정점을 만들고 city 그래프에 삽입
    Vertex* a = CreateVertex('a'); AddVertex(city, a);
    Vertex* b = CreateVertex('b'); AddVertex(city, b);
    Vertex* c = CreateVertex('c'); AddVertex(city, c);
    Vertex* d = CreateVertex('d'); AddVertex(city, d);
    Vertex* e = CreateVertex('e'); AddVertex(city, e);
    Vertex* f = CreateVertex('f'); AddVertex(city, f);
    Vertex* g = CreateVertex('g'); AddVertex(city, g);

    // 건축 가능한 간선들을 city 그래프에 추가
    AddEdge(a, CreateEdge(a, b, 4));
    AddEdge(a, CreateEdge(a, d, 3));
    AddEdge(a, CreateEdge(a, e, 15));

    AddEdge(b, CreateEdge(b, a, 4));
    AddEdge(b, CreateEdge(b, c, 12));
    AddEdge(b, CreateEdge(b, d, 2));
    AddEdge(b, CreateEdge(b, f, 5));

    AddEdge(c, CreateEdge(c, b, 12));
    AddEdge(c, CreateEdge(c, g, 8));

    AddEdge(d, CreateEdge(d, a, 3));
    AddEdge(d, CreateEdge(d, b, 2));
    AddEdge(d, CreateEdge(d, e, 7));
    AddEdge(d, CreateEdge(d, f, 6));

    AddEdge(e, CreateEdge(e, a, 15));
    AddEdge(e, CreateEdge(e, d, 7));
    AddEdge(e, CreateEdge(e, f, 13));

    AddEdge(f, CreateEdge(f, b, 5));
    AddEdge(f, CreateEdge(f, d, 6));
    AddEdge(f, CreateEdge(f, e, 13));
    AddEdge(f, CreateEdge(f, g, 1));

    AddEdge(g, CreateEdge(g, c, 8));
    AddEdge(g, CreateEdge(g, f, 1));

    // 크루스칼 알고리즘을 이용하여 MST 생성 & 결과 출력
    Kruskal(city, MST);
    PrintGraph(MST);
    printf("도시를 연결하는 최소 비용 : %d\n", get_MST_cost(MST));
}