#include "MyDijkstra.h"

int* Dijkstra(Graph* g, Vertex* startVertex, Graph* dijk) {

    PriorityQueue* pq = PQ_Create(10);

    int* dist = (int*) malloc(sizeof(int) * g->vertex_cnt);
    Vertex** DijkVertexArr = (Vertex**) malloc(sizeof(Vertex*) * g->vertex_cnt);
    Vertex** OriginVertexArr = (Vertex**) malloc(sizeof(Vertex*) * g->vertex_cnt);
    Vertex** FromVertexArr = (Vertex**) malloc(sizeof(Vertex*) * g->vertex_cnt);
    
    Vertex* v = g->vertex_list;
    for (int i = 0; i < g->vertex_cnt; i++) {
        Vertex* new_dijk_vertex = create_vertex(v->data);
        add_vertex(dijk, new_dijk_vertex);
        dist[i] = 0x3f3f3f3f;
        DijkVertexArr[i] = new_dijk_vertex;
        OriginVertexArr[i] = v;
        FromVertexArr[i] = NULL;
        v = v->nxt_vertex;
    }

    dist[startVertex->index] = 0;
    PQNode start = {0, startVertex};
    PQ_Enqueue(pq, start);

    while (!PQ_IsEmpty(pq)) {
        PQNode cur; PQ_Dequeue(pq, &cur);

        int cur_dist = cur.Priority;
        Vertex* cur_vertex = cur.Data;

        if (dist[cur_vertex->index] < cur_dist) continue;

        Edge* e = cur_vertex->edge_list;
        while (e != NULL) {
            Vertex* nxt_vertex = e->to;
            if (dist[nxt_vertex->index] > cur_dist + e->weight) {
                dist[nxt_vertex->index] = cur_dist + e->weight;
                FromVertexArr[nxt_vertex->index] = cur_vertex;
                PQNode nxtPQ = {dist[nxt_vertex->index], nxt_vertex};
                PQ_Enqueue(pq, nxtPQ);
            }
            e = e->nxt_edge;
        }
    }

    for (int i = 0; i < dijk->vertex_cnt; i++) {
        if (FromVertexArr[i] == NULL) continue;

        int from_idx = FromVertexArr[i]->index;
        int cur_idx = i;

        add_edge(DijkVertexArr[from_idx], 
            create_edge(DijkVertexArr[from_idx], DijkVertexArr[cur_idx], dist[cur_idx]));
    }

    free(DijkVertexArr);
    free(OriginVertexArr);
    free(FromVertexArr);
    PQ_Destroy(pq);
    return dist;
}