#include <stdio.h>
#include "my_graph.h"

int main() {
    Graph* graph = create_graph();

    Vertex* v1 = create_vertex(1);
    Vertex* v2 = create_vertex(2);
    Vertex* v3 = create_vertex(3);
    Vertex* v4 = create_vertex(4);

    add_edge(v1, create_edge(v1, v2, 4));
    add_edge(v1, create_edge(v1, v4, 2));
    add_edge(v2, create_edge(v2, v3, 1));
    add_edge(v2, create_edge(v2, v4, 5));
    add_edge(v3, create_edge(v3, v1, 7));
    
    add_vertex(graph, v1);
    add_vertex(graph, v2);
    add_vertex(graph, v3);
    add_vertex(graph, v4);

    print_graph(graph);
    return 0;
}