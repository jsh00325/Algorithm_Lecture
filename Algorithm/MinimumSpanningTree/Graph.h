#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

// 방문 여부를 체크하기 위한 열거형 변수
enum VisitMode { NotVisited, Visited };

typedef int ElementType;

typedef struct tagVertex {
    ElementType Data;
    int Visited;
    int Index;

    struct tagVertex* Next;
    struct tagEdge* AdjacencyList;
} Vertex;

typedef struct tagEdge {
    int Weight;
    struct tagEdge* Next;
    Vertex* From;
    Vertex* Target;
} Edge;

typedef struct tagGraph {
    Vertex* Vertices;
    int VertexCount;
} Graph;

Graph* CreateGraph();
void   DestroyGraph( Graph* G );

Vertex* CreateVertex( ElementType Data );
void    DestroyVertex( Vertex* V );

Edge*   CreateEdge( Vertex* From, Vertex* Target, int Weight );
void    DestroyEdge( Edge* E );

void   AddVertex( Graph* G, Vertex* V );
void   AddEdge( Vertex* V, Edge* E );
void   PrintGraph ( Graph* G );

#endif