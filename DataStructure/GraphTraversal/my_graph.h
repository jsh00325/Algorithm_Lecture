#ifndef MY_GRAPH_H
#define MY_GRAPH_H

#include <stdio.h>
#include <stdlib.h>

enum Visit_Enum {NOT_VISITED, VISITED};
typedef int ElementType;

typedef struct tagVertex {
    ElementType data;
    int visited;
    int index;

    struct tagVertex* nxt_vertex;
    struct tagEdge* edge_list;
} Vertex;

typedef struct tagEdge {
    int weight;
    Vertex* from;
    Vertex* to;
    struct tagEdge* nxt_edge;
} Edge;

typedef struct tagGraph {
    Vertex* vertex_list;
    int vertex_cnt;
} Graph;

// 함수 선언
Graph* create_graph();
void destroy_graph(Graph* graph);
Vertex* create_vertex(ElementType val);
void destroy_vertex(Vertex* v);
Edge* create_edge(Vertex* from, Vertex* to, int w);
void destroy_edge(Edge* e);

void add_vertex(Graph* graph, Vertex* new_vertex);
void add_edge(Vertex* vertex, Edge* new_edge);
void print_graph(Graph* graph);

void set_not_visited(Graph* graph);

#endif