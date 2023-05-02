#ifndef MY_CHAINING_H
#define MY_CHAINING_H

#include "RedBlackTree.h"

typedef char* KeyType;
typedef char* ValueType;

typedef RBTNode* Tree;
typedef struct tagHashTable {
    int tableSize;
    Tree* table;
} HashTable;

HashTable* CH_CreateHashTable(int TableSize);
void CH_DestroyHashTable(HashTable* HT);

RBTNode* CH_CreateRBTNode(KeyType Key, ValueType Value);
void CH_DestroyRBTNode(RBTNode* TheNode);

void CH_Set(HashTable* HT, KeyType Key, ValueType Value);
ValueType CH_Get(HashTable* HT, KeyType Key);
int CH_Hash(KeyType Key, int TableSize);

#endif