#include "Graph.h"
#include "MST.h"

/** MST�� �̷�� ������ ����ġ�� ���� ��ȯ�ϴ� �Լ�
 *  @details ������ �̷�� ����ġ�� ��� ���ϰ�, ����� �����̱� ������ 2�� ������.
 *  @param MST ���ϰ��� �ϴ� MST */
int get_MST_cost(Graph* MST) {
    int sum_of_weigh = 0;

    // ������ ������ ��ȸ
    Vertex* curVertex = MST->Vertices;
    while (curVertex != NULL) {
        // ���� ������ ����� ��� ���� ��ȸ
        Edge* curEdge = curVertex->AdjacencyList;
        while (curEdge != NULL) {
            // ���� ������ ����ġ ���ϱ�
            sum_of_weigh += curEdge->Weight;
            curEdge = curEdge->Next;
        }
        curVertex = curVertex->Next;
    }

    // MST�� ������ ����� �����̱� ������ �ߺ����� ���Ǳ� ������ 2�� ������.
    return sum_of_weigh / 2;
}

int main() {
    Graph* city = CreateGraph();
    Graph* MST = CreateGraph();

    // ���� ������ ����� city �׷����� ����
    Vertex* a = CreateVertex('a'); AddVertex(city, a);
    Vertex* b = CreateVertex('b'); AddVertex(city, b);
    Vertex* c = CreateVertex('c'); AddVertex(city, c);
    Vertex* d = CreateVertex('d'); AddVertex(city, d);
    Vertex* e = CreateVertex('e'); AddVertex(city, e);
    Vertex* f = CreateVertex('f'); AddVertex(city, f);
    Vertex* g = CreateVertex('g'); AddVertex(city, g);

    // ���� ������ �������� city �׷����� �߰�
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

    // ũ�罺Į �˰����� �̿��Ͽ� MST ���� & ��� ���
    Kruskal(city, MST);
    PrintGraph(MST);
    printf("���ø� �����ϴ� �ּ� ��� : %d\n", get_MST_cost(MST));
}