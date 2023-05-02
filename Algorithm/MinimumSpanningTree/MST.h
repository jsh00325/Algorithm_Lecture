#ifndef MST_H
#define MST_H

#include "Graph.h"
#include "PriorityQueue.h"
#include "DisjointSet.h"
#include <stdbool.h>

void Prim(Graph* G, Vertex* StartVertex, Graph* MST, int MaxWeight );
void Kruskal(Graph* G, Graph* MST );

#endif