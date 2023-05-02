#include "traversal.h"

void dfs_graph(Vertex* vertex) {
    printf("%d ", vertex->data);

    Edge* edge = vertex->edge_list;
    while (edge != NULL) {
        if (edge->to != NULL && edge->to->visited == NOT_VISITED) {
            edge->to->visited = VISITED;
            dfs_graph(edge->to);
        }
        edge = edge->nxt_edge;
    }
}
void dfs_graph2(Vertex* vertex) {
    if (vertex->visited == VISITED) return;
    vertex->visited = VISITED;
    printf("%d ", vertex->data);

    Edge* edge = vertex->edge_list;
    while (edge != NULL) {
        if (edge->to->visited == NOT_VISITED)
            dfs_graph(edge->to);
        edge = edge->nxt_edge;
    }
}
void bfs_graph(Vertex* vertex) {
    LinkedQueue* queue = NULL;
    LQ_CreateQueue(&queue);

    LQ_Enqueue(queue, LQ_CreateNode(vertex));
    vertex->visited = VISITED;

    while (!LQ_IsEmpty(queue)) {
        Vertex* cur = LQ_Dequeue(queue)->Data;
        printf("%d ", cur->data);

        Edge* edge = cur->edge_list;
        while (edge != NULL) {
            if (edge->to != NULL && edge->to->visited == NOT_VISITED) {
                edge->to->visited = VISITED;
                LQ_Enqueue(queue, LQ_CreateNode(edge->to));
            }
            edge = edge->nxt_edge;
        }
    }
    LQ_DestroyQueue(queue);
}