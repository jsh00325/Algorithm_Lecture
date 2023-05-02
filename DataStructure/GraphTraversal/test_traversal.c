#include "my_graph.h"
#include "traversal.h"

void input_edge(Vertex* v[], int fr, int to, int w) {
    add_edge(v[fr-1], create_edge(v[fr-1], v[to-1], w));
}

int main() {
    Graph* graph = create_graph();

    Vertex* v[7];
    for (int i = 0; i < 7; i++) {
        v[i] = create_vertex(i+1);
        add_vertex(graph, v[i]);
    }
    
    input_edge(v, 1, 3, 1); input_edge(v, 1, 2, 1);
    input_edge(v, 2, 5, 1); input_edge(v, 2, 4, 1); 
    input_edge(v, 3, 6, 1); input_edge(v, 3, 4, 1); 
    input_edge(v, 4, 7, 1); input_edge(v, 4, 5, 1); 
    input_edge(v, 5, 7, 1);
    input_edge(v, 6, 7, 1);

    print_graph(graph);
    printf("DFS : ");
    dfs_graph(graph->vertex_list);
    set_not_visited(graph);
    printf("\nDFS2 : ");
    dfs_graph(graph->vertex_list);
    set_not_visited(graph);
    printf("\nBFS : ");
    bfs_graph(graph->vertex_list);
}