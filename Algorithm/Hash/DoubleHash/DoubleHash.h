#ifndef DOUBLE_HASH_H
#define DOUBLE_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* KeyType;
typedef char* ValueType;

enum ElementStatus { EMPTY = 0, OCCUPIED = 1 };

typedef struct tagDHNode {
    KeyType    key;
    ValueType  value;
    enum ElementStatus status;
} DHNode;

typedef struct tagHashTable {
    int occupiedCount;
    int tableSize;
    DHNode* table;
} HashTable;

HashTable*  DH_CreateHashTable(int tableSize);
void        DH_DestroyHashTable(HashTable* HT);
void        DH_ClearNode(DHNode* node);

void        DH_Set(HashTable** HT, KeyType key, ValueType value);
ValueType   DH_Get(HashTable* HT, KeyType key);
int         DH_Hash (KeyType key, int tableSize);
int         DH_Hash2(KeyType key, int tableSize);

void        DH_Rehash(HashTable** HT);

#endif