#ifndef NUM_HASH_H
#define NUM_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum ElementStatus { EMPTY = 0, OCCUPIED = 1 };

typedef struct tagNHNode {
    int key;
    enum ElementStatus status;
} NHNode;

typedef struct tagHashTable {
    int occupiedCount;
    int tableSize;
    NHNode* table;
} HashTable;

HashTable*  NH_CreateHashTable(int tableSize);
void        NH_DestroyHashTable(HashTable* HT);

void        NH_Set(HashTable** HT, int key);
bool        NH_Get(HashTable* HT, int key);
int         NH_Hash (int key, int tableSize);
int         NH_Hash2(int key, int tableSize);

void        NH_Rehash(HashTable** HT);

#endif