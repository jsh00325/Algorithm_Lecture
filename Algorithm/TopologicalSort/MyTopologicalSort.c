#include "MyTopologicalSort.h"

void TopologicalSort(Graph* g, Node** list) {
    Vertex* v = g->vertex_list;
    while (v != NULL) {
        TS_DFS(v, list);
        v = v->nxt_vertex;
    }
}
void TS_DFS(Vertex* v, Node** list) {
    if (v->visited == VISTED) return;
    v->visited = VISTED;
    
    Edge* e = v->edge_list;
    while (e != NULL) {
        if (e->to->visited == NOT_VISITED)
            TS_DFS(e->to, list);
        e = e->nxt_edge;
    }
    SLL_InsertNewHead(list, SLL_CreateNode(v->data));
}