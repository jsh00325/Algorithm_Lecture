#include "SingleLinkedList.h"

List* create_list() {
    List* new_list = (List*) malloc(sizeof(List));
    new_list->head = NULL;
    new_list->tail = NULL;
    return new_list;
}
void destroy_list(List* list) {
    Node* cur = list->head;
    while (cur) {
        Node* temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(list);
}
Node* create_node(void* data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}
void append_node(List* list, Node* new_node) {
    if (list->head == NULL) list->head = new_node;
    else list->tail->next = new_node;
    list->tail = new_node;
}
void print_list(List* list, void (print_data)(void*)) {
    Node* cur_node = list->head;
    while (cur_node) {
        print_data(cur_node->data);
        cur_node = cur_node->next;
    }
}