#ifndef MY_TOPOLOGICAL_SORT_H
#define MY_TOPOLOGICAL_SORT_H

#include "MyGraph.h"
#include "LinkedList.h"

void TopologicalSort(Graph* g, Node** list);
void TS_DFS(Vertex* v, Node** list);

#endif