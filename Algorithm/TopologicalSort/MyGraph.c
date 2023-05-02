#include "MyGraph.h"

/* 그래프 구조 생성 */
Graph* create_graph() {
    Graph* new_graph = (Graph*) malloc(sizeof(Graph));
    new_graph->vertex_cnt = 0;
    new_graph->vertex_list = NULL;
    return new_graph;
}
/* 그래프 구조 소멸 */
void destroy_graph(Graph* graph) {
    while (graph->vertex_list != NULL) {
        Vertex* temp = graph->vertex_list;
        graph->vertex_list = temp->nxt_vertex;
        destroy_vertex(temp);
    }
    free(graph);
}
/* 정점 구조 생성 */
Vertex* create_vertex(ElementType val) {
    Vertex* new_vertex = (Vertex*) malloc(sizeof(Vertex));
    new_vertex->data = val;
    new_vertex->visited = NOT_VISITED;
    new_vertex->index = -1;
    new_vertex->nxt_vertex = NULL;
    new_vertex->edge_list = NULL;
    return new_vertex;
}
/* 정점 구조 소멸 */
void destroy_vertex(Vertex* v) {
    while (v->edge_list != NULL) {
        Edge* temp = v->edge_list;
        v->edge_list = temp->nxt_edge;
        destroy_edge(temp);
    }
    free(v);
}
/* 간선 구조 생성 */
Edge* create_edge(Vertex* from, Vertex* to, int w) {
    Edge* new_edge = (Edge*) malloc(sizeof(Edge));
    new_edge->from = from;
    new_edge->to = to;
    new_edge->weight = w;
    new_edge->nxt_edge = NULL;
    return new_edge;
}
/* 간선 구조 소멸 */
void destroy_edge(Edge* e) {
    free(e);
}
/* graph에 new_vertex 삽입 */
void add_vertex(Graph* graph, Vertex* new_vertex) {
    if (graph->vertex_list == NULL) {
        graph->vertex_list = new_vertex;
    }
    else {
        Vertex* last_vertex = graph->vertex_list;
        while (last_vertex->nxt_vertex != NULL)
            last_vertex = last_vertex->nxt_vertex;
        last_vertex->nxt_vertex = new_vertex;
        new_vertex->index = (graph->vertex_cnt)++;
    }
}
/* vertex에 new_edge 삽입 */
void add_edge(Vertex* vertex, Edge* new_edge) {
    // 마지막에 삽입하지 않고 바로 헤드부분에 넣기
    new_edge->nxt_edge = vertex->edge_list;
    vertex->edge_list = new_edge;
}
/* 그래프를 출력 (인접리스트 형식 출력) */
void print_graph(Graph* graph) {
    Vertex* cur_vertex = graph->vertex_list;
    while (cur_vertex != NULL) {
        printf("from %d to ", cur_vertex->data);
        Edge* cur_edge = cur_vertex->edge_list;
        while (cur_edge != NULL) {
            printf("%d[%d] ", cur_edge->to->data, cur_edge->weight);
            cur_edge = cur_edge->nxt_edge;
        }
        printf("\n");
        cur_vertex = cur_vertex->nxt_vertex;
    }
    printf("\n");
}