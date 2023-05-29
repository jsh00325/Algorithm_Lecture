#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tagNode{
    void* data;
    struct tagNode* next;
} Node;
typedef struct {
    Node* head;
    Node* tail;
} List;

List* create_list();
void destroy_list(List* list);
Node* create_node(void* data);
void append_node(List* list, Node* new_node);
void print_list(List* list, void (print_data)(void*));

#endif